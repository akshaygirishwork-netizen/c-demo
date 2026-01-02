U-Boot Verified Boot — Complete Explanation (Simplified)
⭐ What is Verified Boot?

Verified Boot ensures that every piece of software executed from power-on onward is authentic, unchanged, and approved for the device.

It protects against:

Malicious firmware

Corrupted updates

Untrusted operating systems

The system will boot only if signatures match.

🔑 Key Concepts
1. Signing

You generate a private key (.key) and public key (.crt).

Private key → used to sign images (kernel, DTB, initramfs, etc.)

Public key → stored in U-Boot for verification.

Why?

Because the public key alone cannot be used to forge images.
So U-Boot safely holds it in ROM or as part of the device tree.

🔍 How Signing + Verification Works
Signing side (offline)

Developer builds images (kernel, dtb).

Developer signs image → produces signature.

Signed image (FIT image) is deployed.

Verification side (U-Boot)

U-Boot loads FIT image.

U-Boot uses built-in public key.

If signature matches → boot continues.

If signature mismatch → boot stops.

This ensures:
✔ Image is unchanged
✔ Image was released by authorized signer
✔ No attacker can insert new firmware

🔗 Chaining Keys (Secure Update Support)

This is powerful.

You can create a hierarchy of trust:

Stage 1: ROM Bootloader

Holds master public key in read-only storage

Verifies U-Boot SPL / 1st stage

Stage 2: U-Boot

Contains secondary public key

Verifies kernel FIT image

Stage 3: Kernel

Uses dm-verity or other methods to verify root filesystem

Why use multiple keys?

If one key leaks, you don’t lose entire chain.

You can rotate only secondary keys for updates.

📦 FIT Image (Flattened Image Tree)

U-Boot prefers FIT because:

It stores multiple images (kernel, dtb, ramdisk)

It stores hash + signature inside a device-tree-like structure

Supports multiple keys + multiple signatures

Works perfectly with Verified Boot

A signed FIT looks like this:

/ {
  images {
     kernel { data, hash, signature }
     fdt    { data, hash, signature }
     ramdisk{ data, hash, signature }
  }
  configurations {
     default = "conf-1";
  }
}

🔑 Where Does U-Boot Store Public Keys?

U-Boot stores public keys in its Device Tree (CONFIG_OF_CONTROL).

Example:

/signature-keys {
   key1 {
      algo = "rsa2048";
      key-name-hint = "dev-key";
      rsa,r-squared = ...;
      rsa,n0-inv = ...;
      rsa,modulus = ...;
   }
}


This key is used at boot time to verify FIT image signatures.

🧠 Why Verified Boot Matters

Prevents unauthorized firmware.

Ensures software integrity during OTA updates.

Meets security certification requirements (Android Verified Boot, Secure Boot).

Prevents persistent malware at bootloader level.

👍 Summary in Simple Points
Concept	Meaning
Verified Boot	Boot only trusted + signed images
Private Key	Used by developer to sign images
Public Key	Burned into U-Boot; verifies signatures
FIT Image	Container holding kernel/DTB with signatures
Chaining Keys	Multi-stage verification from ROM → U-Boot → Kernel
Security	Stops unauthorized firmware updates