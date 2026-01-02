# Linux boot sequence

The Linux boot process starts with BIOS/UEFI running a POST (Power-On Self-Test) and finding the bootloader (like GRUB) in the MBR or EFI partition. The bootloader loads the Linux kernel into memory, which then initializes hardware, mounts the root filesystem, and starts the init system (typically systemd). The init system brings the system to a usable state by starting essential services and presenting a login prompt or desktop environment. 

##  BIOS/UEFI Initialization:
When you power on the computer, the firmware (BIOS or UEFI) starts.
It performs a Power-On Self-Test (POST) to check hardware.
UEFI is newer, uses GPT, and supports features like Secure Boot, while BIOS uses MBR.

## Bootloader Loading (GRUB):

BIOS/UEFI finds the bootloader, usually GRUB 2, from the Master Boot Record (MBR) or EFI partition.
GRUB presents a menu to select an OS or kernel, then loads the kernel into RAM.

## Kernel Initialization:

The kernel takes control, decompresses itself, and initializes essential hardware and loads drivers.
It sets up memory management and starts the init process (PID 1).

## Initramfs & Root Filesystem:

The kernel uses an initial RAM filesystem (initramfs) to find and mount the actual root filesystem (e.g., /).

## System Initialization (systemd):

The init system (commonly systemd) begins, becoming the parent of all other processes.
It reads configuration files (like default.target) to start services (networking, logging, etc.) in parallel.

## User Space & Login:

systemd brings the system to the final "target" (e.g., multi-user.target for CLI or graphical.target for GUI).
A login prompt appears, allowing users to log in and start applications