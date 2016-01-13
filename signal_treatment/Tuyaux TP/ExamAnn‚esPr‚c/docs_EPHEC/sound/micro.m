%sans triggers, juste faire l'acquisition du micro 

%1 micro

clear all;
%attention, v�rifier au pr�alable que le micro est bien activ� dans
%>d�marrer>panneau de configuration>audio
close all;
FsM=8000;
duree=2;
aiM=analoginput('winsound');
addchannel(aiM,1);                          %channel 1 entr�e mono de la carte son
set(aiM,'SampleRate',FsM)
set(aiM,'SamplesPerTrigger',duree*FsM)           %2 sec puisque 22050 echantillons avec Fech=11025
start(aiM)
waittilstop(aiM,2)                          %attend 2 sec pour finir enreg micro
dataM=getdata(aiM);
delete(aiM)
clear aiM


%2 affichage
%t=2s =FsM �ch  -->  
t=1/FsM:1/FsM:duree;
subplot (3,1,1), plot(t,dataM);
title('data');
%pour affichage du spectre
%attention, le micro fournit une composante continue importante
%on l'enl�vera en enlevant la la composante z�ro du spectre ou en enlevant la valeur moyenne au signal

u=-FsM/2+1/duree:1/duree:FsM/2;
xfft=fftshift(abs(fft(dataM)));
subplot (3,1,2),  plot(u,xfft);
title('spectre de f=-Fs/2 Hz � f= Fs/2') 
%attention, si le micro fournit une composante continue importante
%on l'enl�vera en enlevant la composante z�ro du spectre ou en enlevant la %valeur moyenne au signal
u=1/duree:1/duree:FsM/2;
%xfft1=xfft(1/duree:1/duree:FsM/2);%on divise le nombre de points par deux puis on transpose
%attention ceci donne des r�sultats erron�s car les indices ne sont pas entiers
xfft1=xfft(length(xfft)/2+1:length(xfft),:)';%on a un nbre entier d'indices 
subplot (3,1,3),  plot(u,xfft1);
title('spectre de f= 0 Hz � f= Fs/2') 
