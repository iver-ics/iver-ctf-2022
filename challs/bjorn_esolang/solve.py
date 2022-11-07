
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
