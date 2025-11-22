
# BSP

A BSP (Board Support Package) is a collection of software and configuration files that make the Linux operating system run on a specific hardware platform — 
in my case, an x86-based board.

“In my project, I worked on a Yocto-based x86 BSP, which included components like the GRUB bootloader, kernel configuration, and root filesystem customization.
The BSP helped the Linux system boot and run properly on the x86 hardware by providing all the required drivers and initialization scripts.
Basically, it acted as a bridge between the x86 hardware and the Linux OS.”


My main tasks involved customizing the Yocto BSP layer — adding and modifying recipes for the bootloader (GRUB), Linux kernel, and root filesystem.

I configured the kernel features and drivers required for our x86 board, like storage, Ethernet, and USB support, and ensured they were included during image builds.

I also worked with BitBake recipes and local.conf / bblayers.conf files to integrate BSP changes into the Yocto build system.

After building the image, I tested it on the x86 hardware to verify that the system booted correctly, all devices were detected, and the init scripts and services started as expected.

In short, my role was to ensure the Yocto build generated a complete and stable Linux image tailored to our x86 hardware.


# Key-points

Used Yocto meta-layers (like meta-intel) as base BSP.

Customized kernel config, bootloader parameters, and systemd startup scripts.

Debugged boot issues and driver dependencies during BSP bring-up.

Ensured smooth integration of root filesystem and hardware drivers.


# Bootup sequence in linux

## About BIOS-Based Booting


On a BIOS-based system running the Oracle Linux release, the boot process is as follows:

1. The system's BIOS performs a power-on self-test (POST), and then detects and initializes any peripheral devices and the hard disk.

2. The BIOS reads the Master Boot Record (MBR) into memory from the boot device. The MBR stores information about the organization of partitions on that device, the partition table, and the boot signature which is used for error detection. The MBR also includes the pointer to the boot loader program (GRUB 2), usually on a dedicated /boot partition on the same disk device.

3. The boot loader loads the vmlinuz kernel image file and the initramfs image file into memory. The kernel then extracts the contents of initramfs into a temporary, memory-based file system (tmpfs).

4. The kernel loads the driver modules from the initramfs file system that are needed to access the root file system.

5. The kernel searches for the init process within initramfs and starts the defined process with a process ID of 1 (PID 1). On Oracle Linux, the default init process is configured as systemd.

systemd runs any other processes defined for it.





