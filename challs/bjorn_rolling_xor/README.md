# Rolling Xor

This challenge was a compiled binary containing a program that was taking input and xor-ing it with some pre-generated random data and comparing it to some other data to see if it was correct.

If you send in the correct flag it should return "Success".

Efter the competition I was informed that the program always returned FAIL, even with the correct flag. This ended up being a bug where the XOR:ing ended up resulting in a negative value because the rolling variable was not marked as unsigned.

The challenge was still possible to solve using reverse engineering using Ghidra or similar tool and extracting the ransoms and the results.

Below is a python program that solved the rolling xor and output:ing the flag.


```
randoms = b'\xe3\x98\x67\x3c\xc4\x5e\xc4\x88\x62\x4d\x4d\x1f\xae\xf1\xea\x86\x72\x04\x21\x8c\x19\x00\x75\x5a\x1f\x30\x30\x39\xf8\xa6\x69\x84\x43\x9a\x01\x48\xeb'
results = b'\x90\x78\x70\x23\x8c\xab\x14\xfe\xf5\xd6\xfa\x97\x40\xee\x68\x87\x9e\xff\x81\x6c\x2a\x5d\x49\x60\x17\x4e\x10\x4e\xe9\x22\x2a\xcd\xe6\x15\x7a\x57\xc1'

x = 0
for i in range(37):
    x = x^randoms[i]
    s = x^results[i]
    print(chr(s), end='')
    x = x^s
```

I've adjusted the program in the GIT-repo so that it works as intented