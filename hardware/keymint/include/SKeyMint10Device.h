/*
 * Copyright 2020, The Android Open Source Project
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

#include <aidl/android/hardware/security/keymint/BnKeyMintDevice.h>

namespace skeymint {
using namespace ::aidl::android::hardware::security::keymint;

using ::aidl::android::hardware::security::secureclock::TimeStampToken;
using ::ndk::ScopedAStatus;
using std::array;
using std::optional;
using std::vector;

class SKeyMint10Device : public BnKeyMintDevice {
  public:
    explicit SKeyMint10Device(SecurityLevel securityLevel);
    virtual ~SKeyMint10Device();

    ScopedAStatus getHardwareInfo(KeyMintHardwareInfo* info) override;

    ScopedAStatus addRngEntropy(const vector<uint8_t>& data) override;

    ScopedAStatus generateKey(const vector<KeyParameter>& keyParams,
                              const optional<AttestationKey>& attestationKey,
                              KeyCreationResult* creationResult) override;

    ScopedAStatus importKey(const vector<KeyParameter>& keyParams, KeyFormat keyFormat,
                            const vector<uint8_t>& keyData,
                            const optional<AttestationKey>& attestationKey,
                            KeyCreationResult* creationResult) override;

    ScopedAStatus importWrappedKey(const vector<uint8_t>& wrappedKeyData,
                                   const vector<uint8_t>& wrappingKeyBlob,
                                   const vector<uint8_t>& maskingKey,
                                   const vector<KeyParameter>& unwrappingParams,
                                   int64_t passwordSid, int64_t biometricSid,
                                   KeyCreationResult* creationResult) override;

    ScopedAStatus upgradeKey(const vector<uint8_t>& keyBlobToUpgrade,
                             const vector<KeyParameter>& upgradeParams,
                             vector<uint8_t>* keyBlob) override;

    ScopedAStatus deleteKey(const vector<uint8_t>& keyBlob) override;
    ScopedAStatus deleteAllKeys() override;
    ScopedAStatus destroyAttestationIds() override;

    ScopedAStatus begin(KeyPurpose purpose, const vector<uint8_t>& keyBlob,
                        const vector<KeyParameter>& params,
                        const optional<HardwareAuthToken>& authToken, BeginResult* result) override;

    ScopedAStatus deviceLocked(bool passwordOnly,
                               const optional<TimeStampToken>& timestampToken) override;
    ScopedAStatus earlyBootEnded() override;

    ScopedAStatus convertStorageKeyToEphemeral(const vector<uint8_t>& storageKeyBlob,
                                               vector<uint8_t>* ephemeralKeyBlob) override;

    ScopedAStatus getKeyCharacteristics(const vector<uint8_t>& keyBlob,
                                        const vector<uint8_t>& appId,
                                        const vector<uint8_t>& appData,
                                        vector<KeyCharacteristics>* keyCharacteristics) override;

    void initialize();

  protected:
    SecurityLevel securityLevel_;
};
}  // namespace skeymint
