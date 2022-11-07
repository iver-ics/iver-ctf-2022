# stackframe_massacre

## Description

The objective is to cause a buffer overflow to overwrite the stack, causing arbritrary code execution.

## Writeup

`gets` is deprecated today. Compiling the program gives a bunch of warnings, as `gets` doesn't do any buffer size checks. This means we can cause a buffer overflow by giving the program more than 128 bytes (its size according to src/stackframe_massacre.c).

Let's inspect the binary with `$ checksec ./program`:

```
[*] '/home/chris/iver_ctf_wip/challs/stackframe_massacre/program'
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x400000)
    RWX:      Has RWX segments
```

`NX: NX disabled` means that the stack is executable. This means that we can put actual CPU instructions in the `stuff` buffer, and the CPU wouldn't consider it a bad idea to execute it. But we have to fool the CPU to actually execute it.

`stuff` is located in the stack with a size of 128 bytes. I think the return value of `gets` comes afterwards (8 bytes 64 bit signed integer), but I'm honestly not sure. Doesn't really matter much anyways. But what is important is what comes after that, which is the return pointer, which is what address the CPU should return to once it's done running `exploit_me()`. This address is called `saved rip` in GDB for 64 bit architectures.

We can run our own code if we overwrite the return pointer to somewhere in our code, preferably the beginning of it. Luckily, the program tells us where our code is.

So write your payload as `<some code extracting flag.txt>` + `<padding until 128 + 8 bytes are filled>` + `<pointer to stuff>`.

The payload has to be smaller than 136 bytes though, but it's enough for us to put an `execve("/bin/sh")`. From there, you can run `cat flag.txt`.

See [test/solve.py](test/solve.py)
