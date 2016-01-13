
Estimation=[]
j=0
long= length(voix)
for i=1:80:long
   j=j+1
   est=filter([0-LPC(j,2:end)],1,voix(((j*80)-79):(j*80),1));
   Estimation=[Estimation;est];

end




    
    
    
    