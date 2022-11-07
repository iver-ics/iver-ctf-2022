#!/bin/bash
set -eufo pipefail

FILENAME="${1:-"${FILENAME:-usb-backup.img}"}"
SIZE_MB="${2:-"${SIZE_MB:-32}"}"

DUMMY_FILES_PATH="${DUMMY_FILES_PATH:-./dummy-files}"
FLAG_FILE_PATH="${FLAG_FILE_PATH:-flag.png}"

PARTITION="${PARTITION:-yes}"
LABEL="${LABEL:-SPOOKTOBER}"

flag_basename="$( basename "$FLAG_FILE_PATH" )"
size=$(( 1024 * 1024 * "$SIZE_MB" ))

SUDO=

# Add sbin paths so that sfdisk etc can be found without root
PATH="$PATH:/sbin:/usr/sbin:/usr/local/sbin"

if [ "$( id -u )" != "0" ]; then
	SUDO=sudo
fi

if [ -f "$FILENAME" ]; then
    echo "Truncating to size $SIZE_MB MB ($size B) and zeroing out $FILENAME"
    truncate --size="$size" "$FILENAME"
    sync
    dd if=/dev/zero of="$FILENAME" iflag=fullblock bs=1M count="$SIZE_MB" status=none
else
    echo "Allocating $FILENAME of size $SIZE_MB MB ($size B)"
    fallocate -l "$size" "$FILENAME"
fi
sync

if [ "x$PARTITION" == "xyes" ]; then
	echo "Partitioning disk to MBR (DOS) with single 'W95 FAT32' type partition"
	cat <<EOF | sfdisk "$FILENAME" >/dev/null
label: dos
unit: sectors

type=0b
EOF
fi

echo "Mounting disk as loop device"
loop_dev="$( $SUDO losetup -P --direct-io=on -v --find --show "$FILENAME")"
trap "$SUDO losetup -d ""$loop_dev" EXIT

echo "Loop device mounted as: $loop_dev"

fs_partition="$loop_dev"
if [ "x$PARTITION" == "xyes" ]; then
	fs_partition="$( lsblk -o path "$loop_dev" | tail -n 1 )"
fi

echo "File system partition is at $fs_partition"

echo "Formatting $fs_partition as FAT32"
$SUDO mkfs.vfat -n "$LABEL" "$fs_partition" >/dev/null

temp_mountpoint="$(mktemp -d)"
trap "rmdir -- ""$temp_mountpoint""; $SUDO losetup -d ""$loop_dev" EXIT

uid=$(id -u)
gid=$(id -g)

echo "Mounting to $temp_mountpoint"
$SUDO mount -t vfat -o "uid=$uid,gid=$gid" "$fs_partition" "$temp_mountpoint"
trap "$SUDO umount ""$temp_mountpoint""; rmdir -- ""$temp_mountpoint""; $SUDO losetup -d ""$loop_dev" EXIT

echo "Copying dummy-files to root of disk"
cp -v --no-preserve=all -r "${DUMMY_FILES_PATH}/." "${temp_mountpoint}/"
sync -f "${temp_mountpoint}"

echo "Copying flag to root of disk"
cp -v --no-preserve=all "${FLAG_FILE_PATH}" "${temp_mountpoint}/"
sync -f "${temp_mountpoint}"

echo "Removing flag from root of disk"
rm -vf "${temp_mountpoint}/${flag_basename}"
sync -f "${temp_mountpoint}"

#read -p "Press [Enter] to finish. This is a time for you to inspect that everything has been done correctly, or add additional files"

echo "Unmounting, removing temp dir, and removing loop device"
$SUDO umount -v "$temp_mountpoint"
rmdir -v -- "$temp_mountpoint"
$SUDO losetup -vd "$loop_dev"

trap '' EXIT

echo "Done!"
exit
