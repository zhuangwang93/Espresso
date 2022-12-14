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

#ifndef BYTEPS_COMPRESSOR_COMMON_H
#define BYTEPS_COMPRESSOR_COMMON_H

#include <iostream>
#include <unordered_map>

namespace byteps {
namespace common {
namespace compressor {

typedef uint32_t size_t;
typedef char byte_t;

enum DataType {
  BYTEPS_FLOAT32 = 0,
  BYTEPS_FLOAT64 = 1,
  BYTEPS_FLOAT16 = 2,
  BYTEPS_UINT8 = 3,
  BYTEPS_INT32 = 4,
  BYTEPS_INT8 = 5,
  BYTEPS_INT64 = 6,
  // below are not in mshadow, should avoid using these
  // BYTEPS_UINT16 = 7,
  // BYTEPS_INT16 = 8,
  // BYTEPS_BOOL = 9,
  // BYTEPS_BYTE = 10,
};

/*!
 * \brief Tensor type
 */
typedef struct BPSTensor {
  byte_t* data;
  size_t size;
  int num; /* TODO: number of items */
  int dtype;

  BPSTensor() : data(nullptr), size(0), num(0), dtype(0) {}
  BPSTensor(void* data, size_t size = 0, size_t num = 0, int dtype = 0)
      : data(reinterpret_cast<byte_t*>(data)), size(size), num(num), dtype(dtype) {}
} tensor_t;

using kwargs_t = std::unordered_map<std::string, std::string>;

#define COMPRESS_IMPL_SWITCH(dtype, func, dst, src, size)                     \
  switch (dtype) {                                                            \
    case BYTEPS_FLOAT32:                                                      \
      return func(reinterpret_cast<uint32_t*>(dst),                           \
                  reinterpret_cast<const float*>(src), size / sizeof(float)); \
    case BYTEPS_FLOAT64:                                                      \
      return func(reinterpret_cast<uint64_t*>(dst),                           \
                  reinterpret_cast<const double*>(src),                       \
                  size / sizeof(double));                                     \
    default:                                                                  \
      std::cout << "Unsupported data type:" << dtype;                      \
  }


#define DECOMPRESS_IMPL_SWITCH(dtype, func, dst, src, compressed_size)      \
  switch (dtype) {                                                          \
    case BYTEPS_FLOAT32:                                                    \
      return func(reinterpret_cast<float*>(dst),                            \
                  reinterpret_cast<const uint32_t*>(src), compressed_size); \
    case BYTEPS_FLOAT64:                                                    \
      return func(reinterpret_cast<double*>(dst),                           \
                  reinterpret_cast<const uint64_t*>(src), compressed_size); \
    default:                                                                \
      std::cout << "Unsupported data type:" << dtype;                    \
  }


#define FAST_UPDATE_ERROR_IMPL_SWITCH(dtype, func, dst, src1, src2,          \
                                      compressed_size)                       \
  switch (dtype) {                                                           \
    case BYTEPS_FLOAT32:                                                     \
      return func(reinterpret_cast<float*>(dst),                             \
                  reinterpret_cast<float*>(src1),                            \
                  reinterpret_cast<const uint32_t*>(src2), compressed_size); \
    case BYTEPS_FLOAT64:                                                     \
      return func(reinterpret_cast<double*>(dst),                            \
                  reinterpret_cast<double*>(src1),                           \
                  reinterpret_cast<const uint64_t*>(src2), compressed_size); \
    default:                                                                 \
      std::cout << "Unsupported data type:" << dtype;                     \
  }



}  // namespace compressor
}  // namespace common
}  // namespace byteps

#endif  // BYTEPS_COMPRESSOR_COMMON_H