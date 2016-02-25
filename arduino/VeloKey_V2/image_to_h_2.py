import Image
from numpy import *
from pylab import *

fn = 'logo3.png'
im = Image.open(fn)
print im.size
rgb = array(im.getdata())[:,:3].reshape((im.size[1], im.size[0], 3))
print len(d)
print rgb.shape

## http://wo1fman.deviantart.com/art/Olympic-Pictogram-Cycling-167672083
hfn = 'logo.h'
f = open(hfn, 'w')
print >> f, 'uint8_t image[20480] = {'
print min(d)
for l in d:
    if l > 220:
        pass#l = 255
    print >> f, l, ','
print >> f, '};\n'

print 'wrote', hfn
im.show()
