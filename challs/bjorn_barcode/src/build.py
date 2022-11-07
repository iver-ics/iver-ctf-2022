
import code128
from PIL import Image, ImageOps

flag = open('flag.txt').readline()
print("Flag: " + flag)
code128.image(flag).save("flag.png")
im = Image.open('flag.png')
im_invert = ImageOps.invert(im)
im_invert.save('chall.png')

im2 = Image.open('chall.png')
im_invert2 = ImageOps.invert(im2)
im_invert2.save('solved.png')

