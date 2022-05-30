import numpy as np
import sys
import numpy
from scipy.fft import dct, idct
import matplotlib.pyplot as plt
from numpy import r_
import rawpy
numpy.set_printoptions(threshold=sys.maxsize)

import imageio.v2 as imageio

quantatization_table = numpy.zeros([8,8])

with open('quantatization_table', 'r') as fd:
    values = fd.read()
    #values.replace("\n", "")
    
    
    values = values.split(' ')
    
    for i in range(8):
        for j in range(8):
            quantatization_table[i,j] = float(values[i*8+j])/2



def dct2(a):
    return dct( dct( a, axis=0, norm='ortho' ).astype(int), axis=1, norm='ortho' ).astype(int)

def idct2(a):
    return idct( idct( a, axis=0 , norm='ortho').astype(int), axis=1 , norm='ortho').astype(int)



im = imageio.imread("cameraman.tif").astype(int)

plt.figure()


plt.imshow(im,cmap='gray')
plt.show()



imsize = im.shape
y = np.zeros(imsize)

for i in r_[:imsize[0]:8]:
    for j in r_[:imsize[1]:8]:
        y[i:(i+8),j:(j+8)] = (dct2( im[i:(i+8),j:(j+8)] ))



#plt.imshow(y,cmap='gray')
#plt.show()



for i in range(imsize[0]):
    for j in range(imsize[1]):
        y[i,j] = int(y[i,j]/quantatization_table[i%8, j%8])
#print(y)

out = np.zeros(imsize)
for i in r_[:imsize[0]:8]:
    for j in r_[:imsize[1]:8]:
        out[i:(i+8),j:(j+8)] = (idct2( y[i:(i+8),j:(j+8)] ))

plt.imshow(out,cmap='gray')
plt.show()


#print(y[0][0])