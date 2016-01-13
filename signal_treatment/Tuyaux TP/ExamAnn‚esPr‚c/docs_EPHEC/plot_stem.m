clear all;
close all;
t=0:0.2:4;
size(t)
y=sin(t);
subplot(4,1,1);plot(t,y)
t=0:0.5:4;
y=sin(t);
subplot(4,1,2);plot(t,y)
t=0:0.2:4;
y=sin(t);
subplot(4,1,3);stem(t,y)
t=0:0.5:4;
y=sin(t);
subplot(4,1,4);stem(t,y)