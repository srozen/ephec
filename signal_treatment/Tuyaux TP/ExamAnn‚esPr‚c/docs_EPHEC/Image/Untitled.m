clear all;
close all;
f = 440;
f2 = 500;
Fe = 22000; %fréquence d'échantillonage
Te=1/Fe; %période d'échantillonage
t = 0 :Te:4;%intervalle de 0 à 4s, avec une période d’échantillonnage de 1/Fe
A = 0.5; %amplitude
%1er signal
y = A*sin(2*pi*f*t); %y signal périodique
%2ème signal
y2 = A*sin(2*pi*f2*t);
x = (y+y2);

Fc = 500;
Wn1 = (Fc-1)/(Fe/2);
Wn2 = (Fc+1)/(Fe/2);
Wn = [Wn1 Wn2];
[b,a]=butter(1,Wn, 'stop') ;
filter(b,a,x);
sound(x,Fe); %son du signal
plot(t,x);
pause(5);
sound(ans,Fe); %son du signal atténué
plot(t,ans);
