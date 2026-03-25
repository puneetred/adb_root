#!/bin/bash

if [ "$1" = "clean" ];then
    cd adbd_helper && ndk-build clean
    exit
fi

(cd adbd_helper && ndk-build)

# Default to arm64-v8a for now, can be expanded to support multiple zips or fat zips
ABI="arm64-v8a"
if [ ! -d "adbd_helper/libs/$ABI" ]; then
    ABI="x86_64"
fi

echo "Using ABI: $ABI"

cp README.md magisk_module/
cp adbd_helper/libs/$ABI/adbd magisk_module/system/apex/com.android.adbd/bin/adbd
cp adbd_helper/libs/$ABI/libadb_root_helper.so magisk_module/system/lib64/

(cd magisk_module && zip -r ../adb_root.zip -x "*.DS_Store" -- *)
