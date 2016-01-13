% ESTIMATION_SIGNAL_ACQUIS
%--------------------------------------------------------------------------

% Permet d'estimer le signal acquis grâces aux coefficients LPC obtenus.


estimation=[];
j=0;

taille_fen = 160;
longueur_signal = length(voix);

for i=1:taille_fen:longueur_signal
   j=j+1;
   
   est=filter([0-LPC0(j,2:end)],1,voix(((j*160)-159):(j*160),1));
   estimation=[estimation;est];

end

% Permet d'afficher le signal par la méthode de Burg afin d'y visualiser
% les différents formants.
% On y met comme paramêtre l'estimation du signal ainsi que l'ordre du
% modèle utilisé.
pburg(estimation,12);




    
    
    
    