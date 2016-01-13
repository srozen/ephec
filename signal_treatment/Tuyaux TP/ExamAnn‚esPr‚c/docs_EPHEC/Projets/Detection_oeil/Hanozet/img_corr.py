import Image, ImageOps, ImageChops, numpy, os
from VideoCapture import Device

os.system("cls")

cam = Device(devnum=0)

#################  image 1  #################

cam.saveSnapshot("./AAA1.jpg")

im1 = Image.open("./AAA1.jpg")
im1 = ImageOps.grayscale(im1)
L, H = im1.size
data1 = list(im1.getdata())
mat1 = numpy.reshape(data1, (L, H))

print mat1

for i in range(im1.size[0]):
	for j in range(im1.size[1]):
		if mat1[i][j] > 50:
			mat1[i][j] = 255
			##copie[i][h]=max([mat[i-1][j-1],mat[i][j-1],mat[i+1][j-1],mat[i-1][j],mat[i][j],mat[i+1][j],mat[i-1][j+1],mat[i][j+1],mat[i+1][j+1]])
		else:
			mat1[i][j] = 0
			##copie[i][h]=max([mat[i-1][j-1],mat[i][j-1],mat[i+1][j-1],mat[i-1][j],mat[i][j],mat[i+1][j],mat[i-1][j+1],mat[i][j+1],mat[i+1][j+1]])

print mat1

Copie1=Image.new("L",(L,H))
Copie1.putdata(list(mat1.flat))
Copie1.save("./seuil1.jpg")

#################  image 2  #################

cam.saveSnapshot("./AAA2.jpg")

im2 = Image.open("./AAA2.jpg")
im2 = ImageOps.grayscale(im2)
L, H = im2.size
data2 = list(im2.getdata())
mat2 = numpy.reshape(data2, (L, H))

print mat2

for i in range(im2.size[0]):
	for j in range(im2.size[1]):
		if mat2[i][j] > 30:
			mat2[i][j] = 255
			##copie[i][h]=max([mat[i-1][j-1],mat[i][j-1],mat[i+1][j-1],mat[i-1][j],mat[i][j],mat[i+1][j],mat[i-1][j+1],mat[i][j+1],mat[i+1][j+1]])
		else:
			mat2[i][j] = 0
			##copie[i][h]=max([mat[i-1][j-1],mat[i][j-1],mat[i+1][j-1],mat[i-1][j],mat[i][j],mat[i+1][j],mat[i-1][j+1],mat[i][j+1],mat[i+1][j+1]])

print mat2

Copie2=Image.new("L",(L,H))
Copie2.putdata(list(mat2.flat))
Copie2.save("./seuil2.jpg")


#################  soustraction  #################

im3 = ImageChops.subtract_modulo(Copie1, Copie2)
L,H = im3.size
data3 = list(im3.getdata())
mat3 = numpy.reshape(data3, (L,H))

print mat3

copie3 = Image.new("L", (L,H))
copie3.putdata(list(mat3.flat))
copie3.save("./sub.jpg")
