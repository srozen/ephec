#! /usr/bin/env python
# *-* coding: cp850 *-* 
## imporation librairies
import PIL
import Image
import numpy
import ImageOps
import os

## efface l'écran
os.system("cls")



def OuvrirImg(chemin) :
	Img = Image.open(str(chemin))
	Img1 = ImageOps.grayscale(Img)
	largeur, hauteur = Img1.size
	Imdata = Img1.getdata()
	tab = numpy.array(Imdata)
	matrix = numpy.reshape(tab, (largeur, hauteur))
	return matrix

def ReconstruireImg(donnees, chemin) :
	copie = Image.new("L", (donnees.shape[1], donnees.shape[0]))
	copie.putdata(list(donnees.flat))
	copie.save(fp=str(chemin))

a = OuvrirImg("c:/test/test.bmp")
print "\n a :\n"
print a
print "\n"

ReconstruireImg(a, "C:/test/test_copie.bmp")