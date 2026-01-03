#!/bin/bash

pushd ..
Vendor/Binaries/Premake/macOS/premake5 xcode4 --file=Build.lua
popd
