% DISTANCE_DTW
%--------------------------------------------------------------------------
% Fonction dans laquelle on rentre en argument les deux matrices de coeff
% LPC dont on doit calculer la distance.


function distance = distance_dtw(lpc1,lpc2) 

n = size(lpc1,1); 
m = size(lpc2,1); 
 
d = zeros(n,m); 
 
for i = 1:n 
    
    for j = 1:m 
        
        d(i,j) = sum((lpc1(i,:)-lpc2(j,:)).^2); 
    
    end 
end 
 
D =  ones(n,m) * realmax; 
D(1,1) = d(1,1); 
 
 
for i = 2:n 
    for j = 1:m 
        D1 = D(i-1,j); 
 
        if j>1 
            D2 = D(i-1,j-1);
            
        else 
            D2 = realmax; 
        end 

        if j>2 
            D3 = D(i-1,j-2); 
            
        else 
            D3 = realmax; 
        end 

        D(i,j) = d(i,j) + min([D1,D2,D3]); 
    end 
end 
 
distance = D(n,m);