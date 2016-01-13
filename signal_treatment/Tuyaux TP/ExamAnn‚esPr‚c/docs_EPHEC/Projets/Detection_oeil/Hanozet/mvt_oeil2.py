#! /usr/bin/env python
# *-* coding: cp850 *-* 

import PIL, Image, ImageOps, numpy, os
from VideoCapture import Device

os.system("cls")

############################################
def OuvrirImg(chemin) :
	Img = Image.open(str(chemin))
	##Img1 = ImageOps.grayscale(Img)
	largeur, hauteur = Img.size
	Imdata = Img.getdata()
	tab = numpy.array(Imdata)
	matrix = numpy.reshape(tab, (largeur, hauteur))
	return matrix
	
def ReconstruireImg(donnees, chemin) :
	copie = Image.new("L", (donnees.shape[1], donnees.shape[0]))
	copie.putdata(list(donnees.flat))
	copie.save(fp=str(chemin))
############################################

cam = Device(devnum=0)

cam.saveSnapshot("c:/test/AAA.jpg")

photo1 = OuvrirImg("c:/test/AAA.jpg")
##ReconstruireImg(photo1, "c:/test/AAA-1.jpg")




"""
a = cam.getImage()
imdata = a.getdata()
tab = numpy.array(imdata)
L, H = a.size
img = numpy.reshape(tab, (L, H))
print tab
cam.saveSnapshot("c:/test/AAA.jpg")
ReconstruireImg(img, "c:/test/AAA-1.jpg")
"""

##a = OuvrirImg("c:/test/AAA.jpg")

##ReconstruireImg(a, "c:/test/AAA-1.jpg")

