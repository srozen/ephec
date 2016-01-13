function [Y, I] = pickmax(y,choix)
% pick the first 5 picks
Y = zeros(choix,1);
I = zeros(choix,1);
% get the difference
xd = diff(y);
% pick the index where the difference goes from + to -
% this is the local maxima
index = 1;
pos = 0;
for i=1:length(xd)
 if xd(i)>0
  pos = 1;
 else
  if pos==1
   pos = 0;
   Y(index) = xd(i);
   I(index) = i-1;
   index = index + 1;
   if index>choix
    return
   end
  end
 end
end