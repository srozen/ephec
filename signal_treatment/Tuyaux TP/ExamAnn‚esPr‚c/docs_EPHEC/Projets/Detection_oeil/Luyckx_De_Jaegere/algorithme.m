close all;
clear all;
clc;

%variables modifiable
%Seuil à adapter en fonction de l'image : mode automatique 	(cfr ligne 39)
% Sv=10;
% Sh=50;

%Variable pour la détection de bord (seuils)
tresh=[1/8 1/6];

%Variable pour le lissage
conva=[1/3 1/3 1/3];

%Variables images
image_analyser = 'C:\Documents and Settings\tib\Mes documents\projet tds\00000129.JPG';
image_template_droit='C:\Documents and Settings\tib\Mes documents\projet tds\templated2.jpg';
image_template_gauche='C:\Documents and Settings\tib\Mes documents\projet tds\templateg2.jpg';

%variables FIN

%Lecture de l'image et transformation de celle-ci en noir et blanc
a= imread(image_analyser);
b= rgb2gray(a);

%detection des bords
c=EDGE (b,'canny',tresh);

%Addition des points et lissage
ver= sum(c,1);
verl=conv(ver,conva);
verli=conv(verl,conva);

hor= sum(c,2);
horl=conv(hor,conva);
horli=conv(horl,conva);

%Seuillage automatique 
Sv=(3/5)*(max (verli));
Sh=(3/5)*(max (horli));

%Affichage de l'image originale en noir et blanc + image de la détection des
%contours + graphique 
subplot(4,1,1);imshow(b);
title 'Original';
subplot(4,1,2);imshow(c);
title 'détection de contour';
subplot(4,1,3);plot(verl);
title 'Somme verticale des points lissés';
subplot(4,1,4);;plot(horl);
title 'Somme horizontale des points lissés';

%figure, imshow(c);


%Découpage des petites images en vue de la corrélation
yv=find(verli>Sv);
yvm=round(min(yv));
yvM=round(max(yv));


yh=find(horli>Sh);
yhm=min(yh);
yhM=max(yh);

yvd=yvM-yvm;
yhd=yhM-yhm;

yvd1=yvd/2;
yvm1=round(yvm+yvd1);

vectcropa= [yvm  yhm  yvd1 yhd];
vectcropb= [yvm1  yhm  yvd1 yhd];

cibleg=imcrop(b,vectcropa);
cibled=imcrop(b,vectcropb);

%//////traitment de l'oeil gauche\\\\\\\\

% lecture de l'image template gauche
im1=imread(image_template_gauche);



% lecture de l'image cible
im2=cibleg;


% conversion de l'image
image1=double(im1)/255;
image2=double(im2)/255;

%vérification que les images soient bien en niveaux de gris 
if size(image1,3)==3
    image1=rgb2gray(image1);
end
if size(image2,3)==3
    image2=rgb2gray(image2);
end

% vérification que le template soit plus petit que l'image de base 

if size(image1)>size(image2)
    Target=image1;
    Template=image2;
else
    Target=image2;
    Template=image1;
end

% Détection de la taille des images 
[r1,c1]=size(Target);
[r2,c2]=size(Template);

% moyenne du template
image22=Template-mean(mean(Template));

%corrélation des images 
M=[];
for i=1:(r1-r2+1)
    for j=1:(c1-c2+1)
        Nim=Target(i:i+r2-1,j:j+c2-1);
        Nim=Nim-mean(mean(Nim));  
        corr=sum(sum(Nim.*image22));
        M(i,j)=corr/sqrt(sum(sum(Nim.^2)));
    end 
end

% Traçage des lignes blanches sur la petite image

[r,c]=max(M);
[r3,c3]=max(max(M));

id=round(c(c3));
jd=round(c3);
resultd=Target;


resultd(id:id+r2-1,jd)=255;

resultd(id:id+r2-1,jd+c2-1)=255;

resultd(id,jd:jd+c2-1)=255;

resultd(id+r2-1,jd:jd+c2-1)=255;


%Affichage de l'image template, de la petite image sans ligne blanche et de
%l'image avec ligne blanche
figure,
subplot(1,2,1),imshow(im1);title('Template');
subplot(1,2,2),imshow(im2);title('Target');
%figure,imshow(resultd);title('Matching Result');


%//////traitment de l'oeil droit\\\\\\\\

% lecture de l'image template droite
im1=imread(image_template_droit);



%lecture de l'image cible
im2=cibled;


% conversion de l'image
image1=double(im1)/255;
image2=double(im2)/255;

%vérification que les images sont bien en niveaux de gris 
if size(image1,3)==3
    image1=rgb2gray(image1);
end
if size(image2,3)==3
    image2=rgb2gray(image2);
end

% vérification que le template soit plus petit que l'image de base 

if size(image1)>size(image2)
    Target=image1;
    Template=image2;
else
    Target=image2;
    Template=image1;
end


% Détection de la taille des images 
[r1,c1]=size(Target);
[r2,c2]=size(Template);

% moyenne du template
image22=Template-mean(mean(Template));

%corrélation des images 
M=[];
for i=1:(r1-r2+1)
    for j=1:(c1-c2+1)
        Nim=Target(i:i+r2-1,j:j+c2-1);
        Nim=Nim-mean(mean(Nim));  
        corr=sum(sum(Nim.*image22));
        M(i,j)=corr/sqrt(sum(sum(Nim.^2)));
    end 
end

% Traçage des lignes blanches sur la  petite image

[r,c]=max(M);
[r3,c3]=max(max(M));

ig=round(c(c3));
jg=round(c3);
resultg=Target;
resultg(ig:ig+r2-1,jg)=255;

resultg(ig:ig+r2-1,jg+c2-1)=255;

resultg(ig,jg:jg+c2-1)=255;

resultg(ig+r2-1,jg:jg+c2-1)=255;



%Affichage de l'image template , de la petite image sans ligne blanche et de
%l'image avec ligne blanche

figure,
subplot(1,2,1),imshow(im1);title('Template');
subplot(1,2,2),imshow(im2);title('Target');
%figure,imshow(resultg);title('Matching Result ');

% Traçage des lignes blanches sur l'image de base
ig=ig+yhm;
jg=jg+yvm1;

id=id+yhm;
jd=jd+yvm;

b(ig:ig+r2-1,jg)=255;

b(ig:ig+r2-1,jg+c2-1)=255;

b(ig,jg:jg+c2-1)=255;

b(ig+r2-1,jg:jg+c2-1)=255;

b(id:id+r2-1,jd)=255;

b(id:id+r2-1,jd+c2-1)=255;

b(id,jd:jd+c2-1)=255;

b(id+r2-1,jd:jd+c2-1)=255;

%affichage de l'image de base avec lignes blanches
figure, imshow(b);