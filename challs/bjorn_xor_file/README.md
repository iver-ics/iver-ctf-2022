# Bloody XOR

This challange consists of a file with lots of random bytes and a flag hidden in there somewhere.

The name of the challenge hints that this has something to do with XOR. Without any other hints it should be guessable that the file is just XOR:ed by one value.

How can we know if we are correct? Well, we know that the flag has some known bytes. In this case "spooky{".

Here is a small python program that just opens the file and for every value of a single byte

```
bs = open('chall.bin','rb').read()
o = open('all.bin','wb')

for i in range(256):
    o.write(bytes([x^i for x in bs]))
```

This will create a file called ``all.bin`` where all the different xor:ed versions. You can then just do a ``strings`` on the file and grep out the flag

```
strings all.bin  | grep spoo
```
