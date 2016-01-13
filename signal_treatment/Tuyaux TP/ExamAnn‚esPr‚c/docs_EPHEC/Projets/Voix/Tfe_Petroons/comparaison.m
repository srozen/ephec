% COMPARAISON
%--------------------------------------------------------------------------
% Effectue la comparaison entre les matrices de coeff LPC �talons et la
% matrice du son � reconnaitre afin de d�terminer laquelle est la plus
% proche.
% Un seuil est pr�sent pour �viter une r�ponse non correcte.


% Charge la librairie de tout le vocabulaire appris par le syst�me.
load librairie_vocabulaire_recovoc.mat

% Charge les matrices de coefficients LPC des diff�rentes actions.
action_01 = wk1read('action_01.dat');
action_02 = wk1read('action_02.dat');
action_03 = wk1read('action_03.dat');
action_04 = wk1read('action_04.dat');

% Charge les matrices de coefficients LPC des diff�rentes actions.
objet_01 = wk1read('objet_01.dat');
objet_02 = wk1read('objet_02.dat');
objet_03 = wk1read('objet_03.dat');
objet_04 = wk1read('objet_04.dat');


% Prend la matrice de l'action et de l'objet � reconnaitre .
action_a_reconnaitre = LPC_action;
objet_a_reconnaitre = LPC_objet;

% Appelle la fonction 'dist_dtw' qui va donc calculer la distance DTW entre
% chacune des matrices �talons et l'action ou l'objet � reconnaitre.
%
%Les distances sont ensuite toutes plac�es dans la matrice
%'distance_action' et 'distance_objet'.
distance_action = [
    distance_dtw(action_a_reconnaitre,action_01); 
    distance_dtw(action_a_reconnaitre,action_02); 
    distance_dtw(action_a_reconnaitre,action_03);
    distance_dtw(action_a_reconnaitre,action_04)
    ];

distance_objet = [
    distance_dtw(objet_a_reconnaitre,objet_01); 
    distance_dtw(objet_a_reconnaitre,objet_02); 
    distance_dtw(objet_a_reconnaitre,objet_03);
    distance_dtw(objet_a_reconnaitre,objet_04)
    ];

% Va prendre la plus petite valeur contenue dans la matrice
% 'distance_action' et'distance_objet' ainsi que leur indice.
[dist_action , indice_action] = min(distance_action);
[dist_objet , indice_objet] = min(distance_objet);

% Prend comme nom, le nom de r�f�r�nce correspondant � l'indice.
if dist_action <= 60 
    nom_action = action_nom(indice_action,:);
else 
    nom_action = '???';
end
if dist_objet <= 60 
    nom_objet = objet_nom(indice_objet,:);
else
    nom_objet = '???';
end    


% V�rifie que la distance est plus petite qu'un seuil limite d�termin� et
% on renvoit une 'r�ponse' de type positive (1).
%
% Si on d�passe ce seuil, on consid�re la distance trop elev�e que pour �tre
% pertinente. Dans ce cas, on renvoit une 'r�ponse' de type n�gative (0)
if (dist_action <= 60 && dist_objet <= 60 )
    reponse = 1; % r�ponse positive    
else
    reponse = 0; % r�ponse n�gative
end

% On appelle 'lire_phrase' qui prendra la valeur de 'reponse' pour choisir
% quel type de phrase synth�tiser.
run('.\synthese_vocale\lire_phrase.m')