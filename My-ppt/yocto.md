# YOCTO
Yocto Project is an open-source framework (or build system) used for creating custom Linux distributions for embedded devices.

Feature	Description
Purpose	                To create a complete, minimal, and customizable Linux system for embedded boards (ARM, x86, etc.)
Developed by	        The Linux Foundation
Core Tool	            BitBake – a task scheduler and build engine
Main Metadata	        Recipes, Layers, and Configuration files
Output	                Bootable images, root filesystems, SDKs, and packages
Supported Hardware	    x86, ARM, PowerPC, RISC-V, and more


## kernal customisation
1. create a new layer 
<!-- bitbake-layers create-layer meta-my-kernel -->

2. Add it to your build:
<!-- bitbake-layers add-layer meta-my-kernel -->

3. Find the kernel recipe in your distro layer and create a .bbappend file(linux-intel_%.bbappend)

4. Customize kernel configuration
<!-- bitbake -c menuconfig virtual/kernel -->

5. Navigate menus and enable/disable features.

Save your .config

6. To preserve changes permanently:
<!-- bitbake -c savedefconfig virtual/kernel -->

This generates defconfig in your work directory. Copy it to your layer:

7. Update your .bbappend:

<!-- SRC_URI += "file://my-defconfig" -->


## Cross compilation using yocto

“Yocto provides its own cross-compiler through the SDK.
To cross_compile an application,

1. I first build an SDK for my target image using

<!-- bitbake core-image-minimal -c populate_sdk. -->

This generates an SDK installer inside tmp/deploy/sdk/.

2. I install the SDK on my host machine and then
source the environment script:
source environment-setup-<triple>
(for example environment-setup-aarch64-poky-linux).

This sets up all necessary cross-compile variables like
CC, CXX, LD, AR, sysroot paths, and pkg-config.

<!-- After sourcing, I simply build my application using the Yocto toolchain.
For C/C++ I use:
$CC myapp.c -o myapp. -->

3. If it's a CMake project, I use Yocto’s provided toolchain file:

cmake -DCMAKE_TOOLCHAIN_FILE=$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake ..

The output binary is built for the target architecture, and I deploy it to the board.

So in summary, Yocto cross-compilation means generating the SDK, sourcing the environment file, and then building applications using the Yocto-provided cross toolchain.”



## How to debug the fetch error in during yocto-build

short answer
<!--  -->
“Yocto fetch errors occur when BitBake cannot download sources from the given SRC_URI.
To debug, I first check the log.do_fetch file to see the exact failure reason.
Then I verify the URL manually using git or wget.
If it is a branch/tag mismatch, I correct the SRC_URI; if it’s a checksum mismatch, I update the SHA256.
For file:// URIs, I ensure the files exist in the recipe directory.
I also check proxy issues and use PREMIRRORS if the server is down.
After fixing, I run:
bitbake <recipe> -c cleanall && bitbake <recipe>
This usually resolves fetch errors.”
<!--  -->

<!-- Explanation -->

First Understand Why Fetch Errors Happen

Yocto fetches sources from:

1. Git repositories

2. HTTP/FTP servers

3. Local mirrors

4. Tarballs

A fetch error happens when Yocto cannot download or access these files due to:

Common reasons

1. Wrong SRC_URI

2. URL is down / server changed

3. Missing dependencies like git, wget

4. Branch or tag not found

5. Checksum mismatch (MD5/SHA256)

6. Local path incorrect for file:// sources


<!-- bitbake <recipe> -c fetch -v -->
This gives the exact reason.

Do
1. <!-- git ls-remote https://github.com/user/project.git -->

If it fails → URL is wrong or repo removed.

2. Yocto error example:

File checksum mismatch

bitbake <recipe> -c fetch -f
bitbake <recipe> -c do_unpack

Then update checksums:

devtool add <url>
devtool update-recipe <recipe>

or manually update:

SRC_URI[sha256] = "<new SHA>"


3. If using file:// sources

Make sure that files exist in:

<layer>/recipes-xxx/<recipe>/<file>

If not found → Yocto fetches fail.

4. Use PREMIRRORS & MIRRORS

If the upstream server is down:

PREMIRRORS_prepend = "git://.*/.* http://my-local-mirror/ \n"

## sample c program to compile and install in the target

SUMMARY = "Simple helloworld application"
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://helloworld.c"

S = "${WORKDIR}"

do_compile() {
         ${CC} helloworld.c -o helloworld
}

do_install() {
         install -d ${D}${bindir}
         install -m 0755 helloworld ${D}${bindir}
}
###################################################################