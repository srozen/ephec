function [I_val, freq] = valeur_formant (F,I,P)
%Cette fonction sert a récuperer les picks des formants

 x=1;
 I_ind = zeros(length(I),1);
 
 for y=1 : length(I)
  while((F(x)~=I(y))&(I(y)~=0))
   x=x+1;
  end 
  I_ind(y)=x;
 end 
 
 f_max=zeros(length(I),1);
 
 for x=1 : length(I)
  f_max(x)=P(I_ind(x));   
 end    

 freq1=zeros(length(I),1);
 for x=1 : length(I)
  freq1(x)=F(I_ind(x))*4000;   
 end    
 freq=freq1;
 I_val=f_max;