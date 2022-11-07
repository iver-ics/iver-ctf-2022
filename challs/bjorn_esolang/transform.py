
from sys import stdin


def TrivialBrainfuckSubstitution(b,r,a,i,n,f,u,c,k):
    for x in b:
        if x == '>':
            print(r, end='')
        if x == '<':
            print(a, end='')
        if x == '+':
            print(i, end='')
        if x == '-':
            print(n, end='')
        if x == '.':
            print(f, end='')
        if x == ',':
            print(u, end='')
        if x == '[':
            print(c, end='')
        if x == ']':
            print(k, end='')

        print(' ', end='')

# bf = open('flag.bf', 'r').read()
bf = stdin.read()
TrivialBrainfuckSubstitution(bf, "iver", "Iver", "IVER", "IVer", "IVEr", "iVEr", "ivER", "IveR")
