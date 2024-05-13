# libFluxion

libFluxion is a C++ implementation of the Fluxion.

libFluxion is written in C++ 11.

Documentation is available in the "doc" folder and an example application is available in a format of C++ console 
application under "src/main.cpp" file.

This library (as for all Fluxion libraries) is released under GNU GPL v3 license. [Click here](./LICENSE) to see the
license.

libFluxxion should supports these systems:
 - Windows 7 (SP1) and newer,
 - macOS 10.9 and newer,
 - Debian 9 or newer,
 - Ubuntu 14.04 or newer,
 - Fedora 28 or newer,
 - CentOS 7 or newer (we recommend using Rocky Linux),
 - Rocky Linux 9 or newer,
 - openSUSE Leap 15.2 or newer,
 - Alpine 3.12 or newer,
 - Void Linux (musl libc) 1.1.26 or newer,
 - Arch Linux,
 - Gentoo,
 - openSUSE Tumbleweed,
 - FreeBSD 10.3 or newer,
 - NetBSD 8.9 or newer,
 - OpenBSD 6.9 or newer,
 - DragonFlyBSD 5.13.1 or newer,
 - iOS 5.0 or newer,
 - Android 14 API 14 or newer.

## Build

Requires CMake 3.29 or higher.

1. Get the source code of libFluxion by either [downloading as ZIP](https://github.com/Haltroy/libFluxion/archive/refs/heads/main.zip) or cloning this repository (either via GitHub Desktop or commands like `git clone https://haltroy/libFluxion.git`).
2. In the root folder of libFluxion source code, create a folder named "build".
3. Open up a terminal on the build folder or open up a terminal and navigate to the build folder with commands like "cd".
4. Run `cmake ..`. You can add additional configurations in the arguments.
5. Build the applicaton:
    - To build the library, use `make Fluxion`.
    - To build the sample application, use `make FluxionExample`. This will also build the library itself.
6. (Optional) Install Fluxion with `sudo make install`. This will install the libFLuxion, the headers and the documentations.
7. (Optional) Run the executable "FluxionExample", which is a console application.

## Operating System administrators and/or maintainers

You are free to distribute the libFluxion in your system as long as it follows the license (which is GNU GPL v3). We recommend not including the example app and just building Fluxion (with `make Fluxion`) instead. This library is made to include as small requirements as much as possible and no other than the C++ 11 standard libraries are used.