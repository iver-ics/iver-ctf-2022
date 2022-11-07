# shred

## Description

A somewhat simple challenge if you know what to look for. It's a simple FAT32 filesystem where a file has been deleted - the `flag.png` file. Most file systems doesn't zero-out a deleted files' content, but rather just regards its (previously) allocated disk-blocks as "free space", and removes its inode entry.

The flag is in a png file so that to prevent `strings out/usb-backup.img | grep -Eo 'flag{[^}]+}'`

There's some dummy files (see `src/dummy-files`) just to add some noise to the disk. This could potentially be misleading to a contestant.

### Build instructions

Simply run make to build everything with Docker. Requires `zip` for final archiving of the resulting binary image.

```
$ make
```

If you want to build without Docker, install dependencies (as shown in the Dockerfiles) and `make -f Makefile-local`.

There's some kind of bug to be aware of: losetup doesn't seem to work properly in Docker. Partitions aren't properly mapped. /dev/loopXpY doesn't exist. Building without partition table works in Docker, as /dev/loopX exists.

## Writeup

There's multiple methods to solve this. Just Google "recover deleted file" and you'll get multiple search results of different softwares to help you with this. Some might also call this "data carving".

### `testdisk`

TestDisk source can be found [here](https://github.com/cgsecurity/testdisk).

```bash
$ sudo apt install testdisk
...
$ testdisk out/usb-backup.img
```

Navigate through the TUI to recover deleted files.

### `foremost`

Foremost source can be found [here](https://github.com/korczis/foremost).

```
$ foremost -v -i out/usb-backup.img
Foremost version 1.5.7 by Jesse Kornblum, Kris Kendall, and Nick Mikus
Audit File

Foremost started at Thu Oct 13 23:43:19 2022
Invocation: /usr/bin/foremost -v -i out/usb-backup.img
Output directory: /home/chris/iver_ctf_wip/challs/shred/output
Configuration file: /etc/foremost.conf
Processing: out/usb-backup.img
|------------------------------------------------------------------
File: out/usb-backup.img
Start: Thu Oct 13 23:43:19 2022
Length: 32 MB (33554432 bytes)

Num      Name (bs=512)         Size      File Offset     Comment

0:      00003344.jpg           5 MB         1712128
1:      00014384.png           8 KB         7364608       (1537 x 81)
2:      00000168.pdf           1 MB           86016
*|
Finish: Thu Oct 13 23:43:20 2022

3 FILES EXTRACTED

jpg:= 1
png:= 1
pdf:= 1
------------------------------------------------------------------

Foremost finished at Thu Oct 13 23:43:20 2022

$ md5sum output/png/00014384.png build/flag.png
43c4f828ac30b60e56ec064588b289ae  output/png/00014384.png
43c4f828ac30b60e56ec064588b289ae  build/flag.png
```

### Recuva (Windows)

Found [here](https://www.ccleaner.com/recuva) (freeware).

## Epilogue

So how does one prevent your (deleted) secrets to be leaked? Here's some ideas to consider:

- Disk encryption
- File/folder encryption
- `shred -u flag.png`
- TRIM/Discard maybe?? i.e. `fstrim -v /mnt/usb-drive`
- `zerofree -v out/usb-backup.img` (for ext2, ext3 or ext4 file systems)
- [partclone](https://partclone.org/) when cloning filesystems only copies used disk-blocks.

The only viable and secure enough solution (IMO) is encrypting your data, and sometimes also shredding. TRIM/Discard is sometimes [not recommended with at-rest encryption](https://en.wikipedia.org/wiki/Trim_\(computing\)#Disadvantages).

