#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#


from extract_utils.fixups_blob import (
    blob_fixup,
    blob_fixups_user_type,
)
from extract_utils.fixups_lib import (
    lib_fixup_vendorcompat,
    lib_fixups_user_type,
    libs_proto_3_9_1,
)
from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)

namespace_imports = [
    'device/samsung/a04s',
    'hardware/samsung',
    'hardware/samsung_slsi-linaro/exynos',
    'hardware/samsung_slsi-linaro/graphics',
]

def lib_fixup_vendor_suffix(lib: str, partition: str, *args, **kwargs):
    return f'{lib}_{partition}' if partition == 'vendor' else None

lib_fixups: lib_fixups_user_type = {
    libs_proto_3_9_1: lib_fixup_vendorcompat,
    (
        'libuuid',
    ) : lib_fixup_vendor_suffix
} # fmt: skip

blob_fixups: blob_fixups_user_type = {
    (
        'vendor/lib64/libexynoscamera3.so',
    ) : blob_fixup()
        .add_needed('libui_shim.so'),

    (
        'vendor/lib64/libskeymint10device.so',
        'vendor/lib64/libskeymint_cli.so',
    ) : blob_fixup()
        .add_needed('libshim_crypto.so'),
    (
        'vendor/lib64/vendor.samsung.hardware.keymint-V1-ndk.so'
    ) : blob_fixup()
        .add_needed('android.hardware.security.rkp-V1-ndk.so'),

    (
        'vendor/lib/libsensorlistener.so',
        'vendor/lib64/libsensorlistener.so',
    ) : blob_fixup()
        .add_needed('libshim_sensorndkbridge.so'),
}  # fmt: skip

module = ExtractUtilsModule(
    'a04s',
    'samsung',
    namespace_imports=namespace_imports,
    blob_fixups=blob_fixups,
    lib_fixups=lib_fixups,
)

if __name__ == '__main__':
    utils = ExtractUtils.device(module)
    utils.run()
