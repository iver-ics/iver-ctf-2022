bs = open('chall.bin','rb').read()
o = open('all.bin','wb')

for i in range(256):
    o.write(bytes([x^i for x in bs]))
