# Taida

## Linux Build

### Ubuntu

sudo apt install -y \
build-essential \
libx11-dev \
libxrandr-dev \
libxinerama-dev \
libxcursor-dev \
libxi-dev \
libgl-dev \
libasound2-dev \
libflac-dev \
libogg-dev \
libvorbis-dev \
libopus-dev


## Windows Build

Needs vcpkg to compile libsndfile

```
git clone https://github.com/microsoft/vcpkg
```
```
.\vcpkg\bootstrap-vcpkg.bat
```
```
.\vcpkg\vcpkg install libogg:x64-windows-static libvorbis:x64-windows-static libflac:x64-windows-static opus:x64-windows-static libogg:x86-windows-static libvorbis:x86-windows-static libflac:x86-windows-static opus:x86-windows-static
```

Then and add this parameter to cmake command line:

-DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake

You also need to set VCPKG_TARGET_TRIPLET because you use static libraries:

-DVCPKG_TARGET_TRIPLET=x64-windows-static

> Note: Use must use the same CRT library for external libraries and the libsndfile library itself. For *-static triplets Vcpkg uses static CRT.
