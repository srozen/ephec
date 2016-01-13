from VideoCapture import Device
import PIL, Image, ImageOps, numpy

##################
## de 	finition de fonction
##################
def enregistre(self, fich) :
    try :
        self.save(fich)
        print "Limage a ete enregristree (" + fich + ")"
    except :
        print "Le dossier est protege en ecriture"

## fin def fonction

cam = Device(devnum=0)
cam.displayCapturePinProperties()

i = 1

rep = "./images/"
nom = "image"
trav = "gris"
ext = ".jpg"

while i <= 1:
	chemin = rep + nom + str(i) + ext
	cam.saveSnapshot(chemin)
	print "Limage a ete enregristree (" + chemin +  + ")"
	if i%2 == 100:
		img = Image.open(chemin).convert('RGB')
		img = ImageOps.grayscale(img)
		enregistre(img, rep + trav + str(i) + ext)
	i += 1
	
