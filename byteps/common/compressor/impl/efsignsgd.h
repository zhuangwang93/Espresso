// Copyright 2019 Amazon Inc. or its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// =============================================================================

#ifndef BYTEPS_COMPRESSOR_IMPL_EFSIGNSGD_H
#define BYTEPS_COMPRESSOR_IMPL_EFSIGNSGD_H

#include "../compressor.h"

namespace byteps {
namespace common {
namespace compressor {

/*!
 * \brief SignSGD Compressor
 *
 * paper: Error Feedback Fixes SignSGD and other Gradient Compression Schemes
 * 
 * \note 0 represents positive and 1 represents negative.
 */
class EFSignSGDCompressor : public Compressor {
 public:
  EFSignSGDCompressor(size_t size, DataType dtype, size_t numel, bool use_scale = false)
      : Compressor(size, dtype), _numel(numel), _use_scale(use_scale) {}
  virtual ~EFSignSGDCompressor() = default;

  /*!
   * \brief Compress function
   *
   * compress and pack into byte array.
   * each bit represents a sign.
   *
   * \param grad gradient tensor
   * \param compressed compressed tensor
   */
  tensor_t Compress(tensor_t grad) override;

  /*!
   * \brief Decompress function
   *
   * unpack from byte array to FP tensor
   *
   * \param compressed compressed tensor
   * \param decompressed decompressed tensor
   */
  tensor_t Decompress(tensor_t compressed) override;

  /*!
   * \brief help function for error feedback `UpdateError`
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

  template <typename scalar_t, typename index_t>
  tensor_t DecompressImpl(scalar_t* dst, const index_t* src,
                          size_t compressed_size);

  template <typename index_t, typename scalar_t>
  tensor_t IntraDecompressImpl(scalar_t* dst, index_t* src,
                          size_t compressed_size, size_t num);

  template <typename scalar_t, typename index_t>
  void FastUpdateErrorImpl(scalar_t* error, scalar_t* corrected,
                           const index_t* compressed, size_t compressed_size);

 private:
  size_t _numel;
  bool _use_scale;
};
}  // namespace compressor
}  // namespace common
}  // namespace byteps

#endif  // BYTEPS_COMPRESSOR_IMPL_EFSIGNSGD_H
