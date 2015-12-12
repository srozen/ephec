# CODE DECODER

## Ouvrir l'image du qrcode dans une matrice
qrcode = imread('qrcode.jpg')

## Créer un vecteur de resize pour notre qrcode
vector = [21 21]

## Resize la capture selon le vecteur
qr = imresize(qrcode, vector)

## Mise à niveau des blancs et noirs
*Fonction MatLab qui prend une image en niveau de gris et applique un niveau de treshold pour retourner une image
 en noir et blanc, la matrice retournée est une matrice LOGIQUE*

qr = im2bw(qr, 0.5)


## Visualiser
imshow(img);



C = corner(I);
imshow(I);
hold on
plot(C(:,1), C(:,2), 'r*');
