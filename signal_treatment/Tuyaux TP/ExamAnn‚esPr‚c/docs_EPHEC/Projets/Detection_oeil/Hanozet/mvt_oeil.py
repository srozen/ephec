#! /usr/bin/env python
# *-* coding: cp850 *-* 

import PIL, Image, ImageOps, numpy, os
from VideoCapture import Device
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

cam = Device(devnum=0)

cam.saveSnapshot("c:/test/AAA.jpg")


a = OuvrirImg("c:/test/AAA.jpg")

ReconstruireImg(a, "c:/test/AAA-1.jpg")

