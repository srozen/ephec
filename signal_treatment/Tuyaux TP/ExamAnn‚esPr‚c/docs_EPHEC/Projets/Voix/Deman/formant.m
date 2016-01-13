function [P, F, I] = formant(y,choix)
order = 18;
P = pburg(y,order,[]);
P = 10*log10(P); 
F = 0:1/128:1; 

[Pm,I] = pickmax(P,choix);
I = I/128;