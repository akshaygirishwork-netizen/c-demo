# Secure Boot — Simple Interview Explanation

Secure Boot ensures that a device boots only firmware and software that is cryptographically trusted.
It prevents attackers from running modified bootloaders, kernels, or OS images.

⭐ 1. What Secure Boot Tries to Solve

Prevent unauthorized code from running at boot.

Stop boot-time malware, backdoors, or rootkits.

Make sure only software signed by the device vendor can boot.

⭐ 2. High-Level Flow (Generic Secure Boot)

Think of it as a chain of trust:

ROM Code  →  Bootloader (Stage 1)  →  U-Boot (Stage 2)  →  Kernel  →  RootFS


At each stage:

Current stage verifies the next stage using a digital signature.

If signature is valid → boot continues.

If signature fails → boot stops.

⭐ 3. Components Used in Secure Boot
A. Cryptographic Keys

Private key → Used to sign images.

Public key → Stored inside device hardware (immutable memory).

B. Immutable Storage

eFuses

One-Time Programmable (OTP) memory

Mask ROM (burned during chip manufacturing)

This prevents attackers from replacing the public key.

⭐ 4. Secure Boot in U-Boot (Verified Boot)

U-Boot supports verified boot (vboot) using RSA/ECDSA signatures and FIT images.

Steps:

Create a FIT image (.itb) containing kernel, DTB, ramdisk.

Sign the FIT image using private key on build system.

Embed the public key into U-Boot binary (or OTP).

U-Boot at runtime:

extracts signature

verifies it using embedded public key

boots only if valid

⭐ 5. Key Concepts Interviewers Expect
✔ Chain of Trust

Each stage verifies the next → protects entire boot flow.

✔ Root of Trust

The first code that is trusted without verification (usually ROM).

✔ Anti-rollback (optional)

Prevents booting older, vulnerable firmware.

✔ Key Revocation (optional)

Ability to invalidate compromised keys.

⭐ 6. Typical Secure Boot Boot Flow (U-Boot)
1. ROM Code:
   - Loads SPL
   - Verifies SPL signature using key in eFuse

2. SPL:
   - Verifies full U-Boot

3. U-Boot:
   - Verifies FIT image (kernel + dtb + initrd)

4. Kernel:
   - Verifies modules (optional)

⭐ 7. Advantages

Prevents unauthorized firmware.

Protects device integrity.

Essential for automotive, IoT, gateways, payment terminals, medical devices.

⭐ 8. What Interviewers Will Ask
Q1: What is chain of trust?

A sequence where each stage verifies the next image before execution.

Q2: Where do you store public keys?

Immutable memory → eFuse/OTP/ROM or embedded in U-Boot build.

Q3: What happens if signature verification fails?

Boot stops OR falls back to recovery.

Q4: Difference between secure boot and verified boot?

Secure Boot → Ensures authenticity of bootloader.

Verified Boot → Continues verification up to kernel, rootfs.