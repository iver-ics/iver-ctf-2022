# Brains

This challenge is a trivial Brain-fuck substitution language with the operators replaced by different casings of the work "Iver"


To solve the challange you can write a script like the one below to replace the "iver"s with Brain-fuck operators.
```
from sys import stdin


def TrivialBrainfuckSubstitution(b,r,a,i,n,f,u,c,k):
    b = b \
        .replace(r, '>') \
        .replace(a, '<') \
        .replace(i, '+') \
        .replace(n, '-') \
        .replace(f, '.') \
        .replace(u, ',') \
        .replace(c, '[') \
        .replace(k, ']') \
        .replace(' ', '')
    print(b)
    

# bf = open('flag.bf', 'r').read()
bf = stdin.read()
TrivialBrainfuckSubstitution(bf, "iver", "Iver", "IVER", "IVer", "IVEr", "iVEr", "ivER", "IveR")

```

...and then use any brain-fuck implementation.

Like this one: https://www.tutorialspoint.com/execute_brainfk_online.php


## Creation
----------
The program to create the program for the flag was done using this site: https://copy.sh/brainfuck/text.html
