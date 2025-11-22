# For more detail on how the handle is chosen please refer below link.
					# https://1atxmd.atlassian.net/wiki/spaces/KAT/pages/8989278274/Generate+and+secure+KEK+LLD#1.5.-Persisting-the-sealed-KEK-in-TPM-under-a-specified-Handle.

					TPM_HANDLE=$(diskEncryptionTPMHandle)

					# Set DA lockout parameters to avoid TPM DA lockout during reboot.
					# For more details on TPM DA lockout mode please refer below link.
					# https://1atxmd.atlassian.net/wiki/spaces/KAT/pages/9166913804/Updates+for+TPM+DA+Lockout+Mode
					tpm2_dictionarylockout --setup-parameters --lockout-recovery-time=0 --recovery-time=0 --max-tries=32

					# Retrieve and save a TPM-sealed key to /tmp/kek.key.
					tpm2_unseal -Q --object-context=$TPM_HANDLE > /tmp/kek.key

					# Decrypt rootfs1
					cryptsetup luksOpen $rootfs1_fs $LUKS_ROOTFS1_NAME --key-file=/tmp/kek.key

					# Decrypt rootfs2
					cryptsetup luksOpen $rootfs2_fs $LUKS_ROOTFS2_NAME --key-file=/tmp/kek.key

					# Decrypt mfg
					cryptsetup luksOpen $mfg_fs $LUKS_MFG_NAME --key-file=/tmp/kek.key

					# Decrypt log
					cryptsetup luksOpen $log_fs $LUKS_LOG_NAME --key-file=/tmp/kek.key

					# Decrypt storage
					cryptsetup luksOpen $storoage_fs $LUKS_STORAGE_NAME --key-file=/tmp/kek.key
					rm -rf /tmp/k1.mc 
