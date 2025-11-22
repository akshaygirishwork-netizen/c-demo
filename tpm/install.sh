# encrypting the disk.
# This KEY is stored in the RAM memory for very short period of time.
# This Key will be deleted once KEYS are stored onto TPM.
tmpdir=mktemp -d /tmp/kek-tpm2.XXXXXX
PRI_KEY_CONTEXT_BLOB="$tmpdir/pri_key_context_blob"

# For more detail on how the handle is chosen please refer below link.
# https://1atxmd.atlassian.net/wiki/spaces/KAT/pages/8989278274/Generate+and+secure+KEK+LLD#1.5.-Persisting-the-sealed-KEK-in-TPM-under-a-specified-Handle.
TPM_HANDLE=$(diskEncryptionTPMHandle)

create_Key_encryption_key_and_persist_at_tpm()
{
	# Clears lockout, endorsement and owner hierarchy authorization values and other TPM data.
	echo "TPM2 owner hierarchy clear"
	tpm2_clear
	[ $? != 0 ] && echo "Unable to clear tpm, Exit installation" && exit_func 2

	echo "Creating a primary key"
	# create primary key context in quite mode under owner hirarcy.
	tpm2_createprimary -Q --hierarchy=o --key-context=$PRI_KEY_CONTEXT_BLOB
	[ $? != 0 ] && echo "Unable to create the primary key, Exit installtion" && exit_func 2

	# Generate 128bit random AES KEK used for encrypting the DEK.
	tpm2_getrandom -o /tmp/kek.key 32
	[ $? != 0 ] && echo "Unable to generate kek, exit installtion" && exit_func 2

	cat /tmp/kek.key | \
	tpm2_create --hash-algorithm=sha256 --public=seal.pub --private=seal.priv \
		--sealing-input=- --parent-context=$PRI_KEY_CONTEXT_BLOB
	[ $? != 0 ] && echo "Unable to create encrypted key, exit installtion" && exit_func 2

	tpm2_load -Q --parent-context=$PRI_KEY_CONTEXT_BLOB --public=seal.pub --private=seal.priv --name=seal.name --key-context=seal.ctx
	[ $? != 0 ] && echo "Unable to load key" && exit_func 2

	# Make the key persistent in the TPM.
	tpm2_evictcontrol -Q --hierarchy=o --object-context=seal.ctx $TPM_HANDLE
	[ $? != 0 ] && echo "Unable to evict tpm keys" && exit_func 2
	echo "successfully persisted the key ..."
}

# Function to encrypt disk partitions.
encrypt_disk_partition()
{
	partition_name=$1
	luks_dev_name=$2
	key_file=$3

	echo "encrypting $1"
	cryptsetup luksFormat --type luks1 --cipher aes-xts-plain64 --key-size 256 --hash sha256 --use-random --batch-mode $partition_name --key-file=$key_file
	cryptsetup luksOpen $partition_name $luks_dev_name --key-file=$key_file
	mkfs.ext4 /dev/mapper/"${luks_dev_name}"
}

while true; do

	# This api is explained in Key generation and secure LLD
	create_Key_encryption_key_and_persist_at_tpm

	# Encrypting rootfs1
	encrypt_disk_partition $rootfs1 $rootfs1_luksname "/tmp/kek.key"

	# Encrypting rootfs2
	encrypt_disk_partition $rootfs2 $rootfs2_luksname "/tmp/kek.key"

	# Encrypting mfg
	encrypt_disk_partition $mfg_fs $mfgfs_luksname "/tmp/kek.key"

	# Encrypting log
	encrypt_disk_partition $log_fs $logfs_luksname "/tmp/kek.key"

	# Encrypting storage
	encrypt_disk_partition $storage_fs $storagefs_luksname "/tmp/kek.key"

	# Removing the Random Key generated
	rm -rf /tmp/kek.key

	mkdir /src_root
	mkdir /tgt_root1
	mkdir /tgt_root2
	mount -o rw,loop,noatime,nodiratime /run/media/$1/$2 /src_root

	echo "Copying rootfs files..."

	# Mount the root partition.
	mount /dev/mapper/"${rootfs1_luksname}" /tgt_root1
	mount /dev/mapper/"${rootfs2_luksname}" /tgt_root2
	cp -a /src_root/* /tgt_root1
	sync
	cp -a /src_root/* /tgt_root2
	sync
	break
done

