#! /usr/bin/env python
# *-* coding: cp850 *-* 

import PIL
import Image
import numpy
import ImageOps
import os

## efface l'écran
os.system("cls")



img = Image.open("test.bmp")

img = ImageOps.grayscale(img)

imgdata = img.getdata()

larg, haut = img.size
print "\nLargeur : " + str(larg) + "\tHauteur : " + str(haut) + "\n"
print list(imgdata)
print "\n"

tab = numpy.array(imgdata)
print tab
print "\n"

print numpy.shape(tab)
print "\n"

matrix = numpy.reshape(tab, (larg, haut))
print matrix
print "\n"