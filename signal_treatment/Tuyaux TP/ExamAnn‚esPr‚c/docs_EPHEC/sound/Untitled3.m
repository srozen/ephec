clear all;clc;

N = 2;
Fc=1000;

[s,Fs,nbits] = wavread('tarzan.wav');
duree = length(s)/Fs;

f=0:1/duree:Fs/2;

subplot(2,1,1);
y=fftshift(fft(s));
u=y(Fs*(duree/2):Fs*duree);
plot(f,abs(u));

Wn = Fc/(Fs/2);

[b,a] = butter(N,Wn,'low');
sf = filter(b,a,s);

y=fftshift(fft(sf));

v=y(Fs*(duree/2):Fs*duree);
subplot(2,1,2);
plot(f,abs(v));