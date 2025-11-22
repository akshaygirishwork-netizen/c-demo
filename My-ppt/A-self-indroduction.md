
# SELF INTRODUCTION

Hi, I’m Akshay Girish, from Calicut, Kerala.
I completed my B.Tech in Electrical and Electronics Engineering from NSS College of Engineering, Palakkad.

I have also completed Advanced Embedded Systems Training from Vector India, Bangalore, 
where I strengthened my skills in Embedded C/C++, Linux internals, debugging, and system-level programming.

I have worked as an Embedded Linux Engineer at Openmynz Softlab Private Limited,
where I focused on Yocto-based Linux development, BSP customization, and C/C++ programming.




## PROJECT 1 (custom Yocto-based Linux distributions for Intel x86 embedded platforms.)

I developed and maintained custom Yocto-based Linux distributions for Intel x86 embedded platforms.
My work involved customizing Yocto layers and recipes to include board-specific features, drivers, and applications.
I used CMake-based build systems and Bash scripting to automate builds, manage dependencies, and the image generation process.

## PROJECT 2  (Created and encrypt disk partitions and store key in tpm)

In the project, I worked on customizing a Yocto-based Linux installation script to support automatic partition creation and disk encryption using TPM and cryptsetup.

The base script was provided as part of the Yocto build, but I modified it to:

Dynamically create multiple partitions during installation (like boot rootfs1, rootfs2, logs, and storage).

<!-- Integrate cryptsetup to encrypt each partition using the LUKS1 format with AES-256 encryption. -->

Generate a random encryption key (KEK) during runtime.

seal the key securely inside the TPM (using tpm2-tools), and then use that key to encrypt the partitions.

Finally, the temporary key is deleted from RAM, ensuring that only the TPM holds the sealed key.

This approach ensures that all the data on the device remains encrypted and secure, and the decryption key is hardware-protected — it can only be unsealed by the same TPM chip during boot.

I also tested the installation flow end-to-end to verify that the encrypted partitions could be mounted automatically during boot using the TPM-stored key.”


## PROJECT 3 (Developed a light weight docker container to run a c++ application)

Built and deployed Docker container integrating C++ applications for efficient software update processing and version tracking.


## PROJECT 4  (gRPC server daemon in C++ using Protocol Buffers)

“In this project, I developed a gRPC server daemon in C++ using Protocol Buffers (Protobuf) for managing system configurations on an embedded Linux platform.

The server exposes several gRPC APIs that allow client applications to set or update configuration values, query current system status, and receive real-time data streams.

It runs as a background systemd service, handling multiple client requests efficiently and providing instant responses with the latest configuration data.

Using gRPC made the communication between different modules fast, reliable, and structured, while Protobuf ensured compact and efficient data serialization.


## PROJECT 5 (Developed and customized BSP)

I worked on developing and optimizing Board Support Packages (BSPs) for an x86-based embedded Linux platform.
My work included configuring and integrating the Linux kernel, customizing the bootloader (GRUB), and modifying systemd startup 
scripts to ensure that all hardware components and services were properly initialized during system boot.
