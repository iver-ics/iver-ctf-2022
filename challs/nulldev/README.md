# nulldev

## Description

The objective is to cause a buffer overflow to overwrite a file descriptor to point to stdout (or stdin also works) instead of `/dev/null`.

## Writeup

See `test/solve.py`

The char array (C string) variable `message` is 255 bytes long, and is exploitable by the user input, because `scanf` doesn't do any boundary (size) checks. Variables appearing after `message` in memory is `flag_fd` and `void_of_nothingness_fd` in that order.

What we have to do is overflow `message` and overwrite `void_of_nothingness_fd` to be a 32 bit (4 byte) signed integer with the value one (stdout) or zero (stdin, yes, you can actually write to stdin and it will be routed to stdout).

But because `flag_fd` is between `message` and `void_of_nothingness_fd`, we have to keep `flag_fd` intact. Since it's the second file opened by the program, we can assume its value is 4 (stdin is first, then stdout, stderr, void_of_nothingness_fd, and lastly flag_fd. Index starts at zero).

The compiler does some simple optimizations where it puts variables aligned in memory, and therefore adds some padding to the `message` variable; 5 bytes in this case. This can be assumed for most C programs, but can also be seen if you debug the program, or compile it yourself with debugging symbols.

If you have `gdb` installed, then you can run `make gdb` to see all memory addresses of above mentioned variables, and their distances in bytes.

So to actually solve this, we have to provide the programs' stdin with just any random text to fill out `message`, 5 bytes padding, a 32 bit (4 byte) signed integer with the value 4 to keep `flag_fd` intact, and then overwrite `void_of_nothingness` to our desired value (32 bit signed integer with the value zero (0, stdin) or one (1, stdout)), and then finally terminate our input with a single UNIX newline ASCII character (single byte "\n" or 0x0a).

Note that scanf will also add an extra NUL character (i.e. one zeroed byte) after your input, which could overwrite other parts of the program. Luckily, I haven't had issues with this, and can be avoided as you only have to overwrite the first byte of `void_of_nothingness`, and let `scanf` overwrite the second byte to zero. The program is compiled for little-endian byte ordering, which helps us when trying to avoid overwriting other variables.

Also, `scanf("%s")` doesn't like whitespaces, so yeah, avoid those.

So stdin should be something like this:
```bash
echo -n 'some_random_string'
echo -n 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
# We've now filled message, first 18 bytes, then remaining 237 bytes
echo -n 'PPPPP' # 5 byte padding
echo -ne '\04\0\0\0' # little-endian byte ordered signed 32 bit integer with the value 4, overwriting flag_fd which already has the value 4
echo -ne '\01' # little-endian byte ordered signed 32 bit integer with the value 1, overwriting void_of_nothingness_fd which initially had the value 3
echo '' # Just a newline to tell scanf we're done
```
See [test/solve.sh](test/solve.sh)

