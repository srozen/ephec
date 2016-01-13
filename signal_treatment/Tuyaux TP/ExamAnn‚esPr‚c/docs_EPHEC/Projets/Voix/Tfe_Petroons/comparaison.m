% COMPARAISON
%--------------------------------------------------------------------------
% Effectue la comparaison entre les matrices de coeff LPC étalons et la
% matrice du son à reconnaitre afin de déterminer laquelle est la plus
% proche.
% Un seuil est présent pour éviter une réponse non correcte.


% Charge la librairie de tout le vocabulaire appris par le systême.
load librairie_vocabulaire_recovoc.mat

% Charge les matrices de coefficients LPC des différentes actions.
action_01 = wk1read('action_01.dat');
action_02 = wk1read('action_02.dat');
action_03 = wk1read('action_03.dat');
action_04 = wk1read('action_04.dat');

% Charge les matrices de coefficients LPC des différentes actions.
objet_01 = wk1read('objet_01.dat');
objet_02 = wk1read('objet_02.dat');
objet_03 = wk1read('objet_03.dat');
objet_04 = wk1read('objet_04.dat');


% Prend la matrice de l'action et de l'objet à reconnaitre .
action_a_reconnaitre = LPC_action;
objet_a_reconnaitre = LPC_objet;

% Appelle la fonction 'dist_dtw' qui va donc calculer la distance DTW entre
% chacune des matrices étalons et l'action ou l'objet à reconnaitre.
%
%Les distances sont ensuite toutes placées dans la matrice
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

% Prend comme nom, le nom de référénce correspondant à l'indice.
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


% Vérifie que la distance est plus petite qu'un seuil limite déterminé et
% on renvoit une 'réponse' de type positive (1).
%
% Si on dépasse ce seuil, on considère la distance trop elevée que pour être
% pertinente. Dans ce cas, on renvoit une 'réponse' de type négative (0)
if (dist_action <= 60 && dist_objet <= 60 )
    reponse = 1; % réponse positive    
else
    reponse = 0; % réponse négative
end

% On appelle 'lire_phrase' qui prendra la valeur de 'reponse' pour choisir
% quel type de phrase synthétiser.
run('.\synthese_vocale\lire_phrase.m')