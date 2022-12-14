// Copyright 2019 Bytedance Inc. or its affiliates. All Rights Reserved.
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

#ifndef BYTEPS_CORE_LOOPS_H
#define BYTEPS_CORE_LOOPS_H

namespace byteps {
namespace common {

void CoordinateNoneLoop();

void CoordinateReduceLoop();
void CoordinateIntraReduceLoop();
void CoordinateIntraGatherLoop();
void CoordinateIntraBroadcastLoop();
void CoordinateIntraReducescatterLoop();
void CoordinateIntraAllgatherLoop();
void CoordinateIntraAlltoallLoop();

void CoordinateBroadcastLoop();

void CoordinatePushLoop();

void PcieReduceLoop();

void RootNcclLoop();

void NonRootNcclLoop();

void SyncNcclLoop();

void CopyDevice2HostLoop();
void CompressCopyDevice2HostLoop();

void CompressLoop();

void PushLoop();

void PullLoop();

void DecompressLoop();

void RootCopyHost2DeviceLoop();

void NonRootCopyListenLoop();

void NonRootCopyHost2DeviceLoop();

}  // namespace common
}  // namespace byteps

#endif  // BYTEPS_CORE_LOOPS_H
