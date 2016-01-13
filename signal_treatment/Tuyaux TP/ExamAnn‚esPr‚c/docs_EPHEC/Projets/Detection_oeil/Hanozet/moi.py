#! /usr/bin/env python
# *-* coding: cp850 *-* 

import PIL, Image, ImageOps, numpy, os
from VideoCapture import Device

os.system("cls")

def Bord(data):
    data=numpy.array(data)
    x=data.shape[1]+2
    y=data.shape[0]+2
    new=[x*[0]]*y  #création du tableau
    new=numpy.array(new)
    
    h=1
    for i in range(1,y-1):
        for j in range(1,x-1):
            new[i][j]=data[i-1][j-1] #remplissage du tableau
            
    return new

def Dilatation(img):
    
    Dilate=[0]*(img.shape[1]-2)*(img.shape[0]-2)
    h=0
    for i in range(1,img.shape[0]-1):
        for j in range(1,img.shape[1]-1):
           Dilate[h]=max([img[i-1][j-1],img[i][j-1],img[i+1][j-1],img[i-1][j],img[i][j],img[i+1][j],img[i-1][j+1],img[i][j+1],img[i+1][j+1]]) 
		   #Mise de la valeur max du voisinage 3x3 au point(x,y)
           h+=1
    
    Dilate=numpy.array(Dilate)
    Dilate=numpy.reshape(Dilate,(img.shape[0]-2,img.shape[1]-2))
    RebuildImg(Dilate,"c:/test/dilate.bmp")
	
def OuvrirImg(path):
		Img=Image.open(str(path))
		Img1=ImageOps.grayscale(Img)
		largeur,hauteur=Img1.size
		imdata=Img1.getdata()
		tab=numpy.array(imdata)
		matrix=numpy.reshape(tab,(hauteur,largeur))
		return matrix

def RebuildImg(data,path): #data de limage a reconstruire, plus chemin de sortie.
	Copie=Image.new("L",(data.shape[1],data.shape[0]))
	Copie.putdata(list(data.flat))
	Copie.save(fp=str(path))
#################################

cam = Device(devnum=0)
cam.saveSnapshot("c:/test/AAA.bmp")

a = OuvrirImg("c:/test/AAA.bmp")
b = Bord(a)
c = Dilatation(b)
	