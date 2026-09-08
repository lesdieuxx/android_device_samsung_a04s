/*
 * Copyright 2021, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <aidl/android/hardware/security/keymint/BnRemotelyProvisionedComponent.h>

namespace skeymint {
using namespace ::aidl::android::hardware::security::keymint;

using ::ndk::ScopedAStatus;
using std::vector;

class SRemotelyProvisionedComponent : public BnRemotelyProvisionedComponent {
  public:
    explicit SRemotelyProvisionedComponent();
    virtual ~SRemotelyProvisionedComponent() = default;

    ScopedAStatus getHardwareInfo(RpcHardwareInfo* info) override;

    ScopedAStatus generateEcdsaP256KeyPair(bool testMode, MacedPublicKey* macedPublicKey,
                                           vector<uint8_t>* privateKeyHandle) override;

    ScopedAStatus generateCertificateRequest(bool testMode,
                                             const vector<MacedPublicKey>& keysToSign,
                                             const vector<uint8_t>& endpointEncCertChain,
                                             const vector<uint8_t>& challenge,
                                             DeviceInfo* deviceInfo, ProtectedData* protectedData,
                                             vector<uint8_t>* keysToSignMac) override;
};
}  // namespace skeymint
