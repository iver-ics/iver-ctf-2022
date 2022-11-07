# stackframe_massacre_2

## Description

The objective is to cause a buffer overflow to overwrite the stack, causing arbritrary code execution.

What differentiates this challenge to the first is that this time you can't just drop into a shell and read `flag.txt`. The flag is now only accessible in the flag variable.

## Writeup

Same as last challenge, but this time we have to put some very specific machine code to print out our flag.

The `flag` variable is located in the stack, exactly 176 bytes after `stuff`, and it's 1024 bytes long. The actual flag string is probably much smaller though.

So instead of just dropping into a shell, we will have to create some shellcode that prints out the `flag` buffer.

The assembly code below does exactly that:
```asm
; set syscall to write
mov rax,1

; set file descriptor to stdout
mov rdi,1

; set how much to write
mov rdx,1024

; set what to write
mov rdx,<address>
```

We've got to put the address of the `flag` variable in the code as well. As mentioned above, it's 176 bytes away from `stuff`, so it can be computed quite easily.

What could also work is to actually just dump the whole stack to stdout, and then pipe it to `strings`. I would go about it to just like write from address `&flag - 1024`, and size `1024 * 4` or something like that.

Once you've gotten the `flag` buffer to stdout, then it's just a matter of parsing the nul terminated string.

See [test/solve.py](test/solve.py)

