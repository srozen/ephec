
Estimrec=[]
j=0
tempo= length(rec)
for i=1:80:tempo
   j=j+1
   est=filter([0-RLPC(j,2:end)],1,rec(((j*80)-79):(j*80),1));
   Estimrec=[Estimrec;est];

end




    
    
    
    