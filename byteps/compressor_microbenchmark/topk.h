#ifndef BYTEPS_COMPRESSOR_IMPL_TOPK_H
#define BYTEPS_COMPRESSOR_IMPL_TOPK_H

#include <queue>
#include "compressor.h"

namespace byteps {
namespace common {
namespace compressor {

/*!
 * \brief TopK Compressor
 *
 * paper: Sparsified SGD with Memory
 * https://arxiv.org/pdf/1809.07599.pdf
 *
 * sending the most significant entries of the stochastic gradient
 *
 */
class TopkCompressor : public Compressor {
 public:
  TopkCompressor(size_t size, DataType dtype, size_t numel, float compress_ratio)
      : Compressor(size, dtype, "TopK"), _numel(numel), _compress_ratio(compress_ratio) {};
  virtual ~TopkCompressor() = default;

  /*!
   * \brief Compress function
   *
   * select topk entries and corresponding indices
   *
   * \note compare with absolute values
   *
   * \param grad gradient tensor
   * \param compressed compressed tensor
   */
  tensor_t Compress(tensor_t grad) override;

  /*!
   * \brief Decompress function
   *
   * fill a zero tensor with topk entries and corresponding indices
   *
   * \param compressed compressed tensor
   * \param decompressed decompressed tensor
   */
  tensor_t Decompress(tensor_t compressed) override;

  /*!
   * \brief faster version of `UpdateError`
   *
   * 1. e <- p (e is the error and p is the corrected gradient)
   * 2. zero-fill e with selected k indices
   *
   * \param corrected gradient corrected with error
   * \param error error
   * \param compressed compressed gradient
   */
  void FastUpdateError(tensor_t error, tensor_t corrected,
                       tensor_t compressed) override;

 private:
  template <typename index_t, typename scalar_t>
  tensor_t CompressImpl(index_t* dst, const scalar_t* src, size_t len);

  template <typename index_t, typename scalar_t>
  tensor_t DecompressImpl(scalar_t* dst, const index_t* src,
                          size_t compressed_size);

  template <typename index_t, typename scalar_t>
  void FastUpdateErrorImpl(scalar_t* error, scalar_t* corrected,
                           const index_t* compressed, size_t compressed_size);

 private:
  size_t _numel;
  float _compress_ratio;
};
}  // namespace compressor
}  // namespace common
}  // namespace byteps

#endif  // BYTEPS_COMPRESSOR_IMPL_TOPK_H