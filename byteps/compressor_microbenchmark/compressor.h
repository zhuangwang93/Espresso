#ifndef BYTEPS_COMPRESSOR_COMPRESSOR_H
#define BYTEPS_COMPRESSOR_COMPRESSOR_H

#include <iostream>
#include <string>
#include <memory>
#include "common.h"

namespace byteps {
namespace common {
namespace compressor {
/*!
 * \brief Compressor interface
 * Compressor defines two universal API - Compress & Decompress
 *
 * \par
 * The caller do not need to allocate additional memory to store compressed data
 * because there is an internal buffer to store the compressed data and the
 * pointer will be returned to the caller. Then the caller can send the returned
 * compressed data as normal.
 *
 * \par
 * There are two optional features of the compressor - error-feedback &
 * momentum. These two features can be added to any common compressors like 1bit
 * and topk. To be generic, these two features are also compressors, exposing
 * the same API as Compressor. More details can be found in their own files.
 *
 * \par
 * To add a new compressor, developers need to inherit this class in 'impl'
 * directory. If a new optional feature like error-feedback is needed,
 * developers need to use decorator pattern and add new files in the current
 * directory. The existing implementation can be used as a reference.
 *
 *
 * \sa ErrorFeedback, Momentum
 */
class Compressor {
 public:
 // TODO: the size is the size of bytes. if dtype is float16 or float32, 
 // it may lead to overflow
  Compressor(size_t size, DataType dtype, std::string name)
      : _size(size), _dtype(dtype), _buf(new byte_t[size]),  _convert_buf(new byte_t[size]), _compressor_name(name){
        if (std::getenv("OMP_NUM_THREADS")) {
          _num_threads = atoi(std::getenv("OMP_NUM_THREADS"));
        }
      };
  virtual ~Compressor() = default;

  /*!
   * \brief Compress function
   *
   * \note Except for error-feedback and momentum, the underlying data of input
   * should never be changed. this is because input is still used in error
   * feedback if enabled.
   *
   * \note Compressed data should be stored in the buffer of the compressor. So
   * it is not an inplace operation.
   *
   * \param grad gradient tensor, passed by value.
   * \return compressed tensor. it is the buffer of the compressor,
   * which contains the compressed data. the returned size is the size of
   * compressed data.
   */
  virtual tensor_t Compress(tensor_t grad) = 0;

  /*!
   * \brief Decompress function
   *
   * \note For servers, decompression is not an inplace operation. The
   * decompressed results locates in the buffer of the compressor. For workers,
   * it is an inplace operation.
   *
   * \param compressed compressed tensor.
   * \return decompressed tensor. For servers, it is the buffer of the
   * compressor, which contains the decompressed data. For workers, its pointer
   * is the same as the input's, while the size is decompressed size, which is
   * also the original size.
   */
  virtual tensor_t Decompress(tensor_t compressed) = 0;

  /*!
   * \brief faster version of `UpdateError` via operation fusion
   *
   * \par
   * This is a helper function implemented by each compressor. If defined,
   * `ErrorFeedback` will use this function instead of defualt `UpdateError`
   * function implemented in error_feedback.cc. If undefined, default
   * `UpdateError` will be used.
   *
   * \par
   * Typically `UpdateError` needs to decompress and do a substraction. But for
   * most compressors, the step of decompression can be avoided. For example,
   * for topk compressor, `UpdateError` can be simplied in this way:
   * 1. e <- p (e is the error and p is the corrected gradient)
   * 2. zero-fill e with selected k indices
   *
   * Actually it is a fusion of original decompression and substraction. It is
   * optional to override.
   *
   * \param corrected gradient corrected with error
   * \param error error
   * \param compressed compressed gradient
   */
  virtual void FastUpdateError(tensor_t error, tensor_t corrected,
                               tensor_t compressed) {
    std::cout << "FastUpdateError is not implemented\n";
  };

  std::string GetCompressorName() {
    return _compressor_name;
  }
  std::unique_ptr<byte_t[]> _convert_buf;

 protected:
  /*! \brief original size */
  size_t _size;
  size_t _num_threads = 1;
  DataType _dtype;
  /*! \brief buffer to store compressed grad */
  std::unique_ptr<byte_t[]> _buf;
  std::string _compressor_name = std::string("compressor");
};

}  // namespace compressor
}  // namespace common
}  // namespace byteps

#endif  // BYTEPS_COMPRESSOR_COMPRESSOR_H