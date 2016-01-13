% APPRENTISSAGE_SYSTEME
%--------------------------------------------------------------------------
% Permet de faire apprendre le systeme par l'utilisateur en le guidant
% étape par étape.
% Sert à créer la librairie de mots qui devront être reconnus
% par la méthode reconnaissance.m"


% Listes des actions et leur référence (une référence par nom)
% !!!! Il doit y'avor le même nombre d'espaces/lettres pour chaque mot !!!!
action_nom =[
            ' allumer'; 
            'éteindre'; 
            '  ouvrir'; 
            '  fermer';
    ];

action_ref = [
            'action_01';
            'action_02';
            'action_03';
            'action_04';       
];

% Listes des objets
objet_nom =[
            '  lampe'; 
            '  radio'; 
            '  porte'; 
            'fenêtre';
    ];

objet_ref = [
            'objet_01';
            'objet_02';
            'objet_03';
            'objet_04';       
];


% Boucles servant à aider l'utilisateur à entrainer le systême avec des
% instructions et étapes à suivre.
fprintf('===================================================================================== \n');
fprintf('=========================  ENREGISTREMENT DES ACTIONS  ============================== \n');
fprintf('===================================================================================== \n\n');

for i=1:size(action_nom,1)
    
    if i==1
        
        fprintf('=======================  PREMIERE ACTION : %s   =========================== \n',action_nom(i,:));
    end
    if i>=2
        fprintf('======================  ACTION SUIVANTE : %s   ============================ \n',action_nom(i,:));
    end   
    
    % Messages avec explication de la procédure à suivre avec les modules
    % sur SIMULINK
    fprintf('Enregistrez le signal avec le module "ACQUISITION_VOIX" du mot "%s" : \n',action_nom(i,:));
    fprintf('<ENTER> quand opération finie...\n');
    input('');
    fprintf('Calculez ses coeff LPC avec le module "TRAITEMENT_LPC" \n');
    fprintf('<ENTER> quand opération finie...\n');
    input('');
    
    % Sauvegarde la matrice dans un .dat
    a = action_ref(i,:);
    b = '.dat';
    ab = strcat(a,b); 
    % commande sous la forme : wk1write('<nom_matrice>.dat',<nom_matrice>);
    wk1write(ab,LPC0); 
    
    fprintf('Enregistrement...\n\n');
    
end

fprintf('===================================================================================== \n');
fprintf('==========================  ENREGISTREMENT DES OBJETS  ============================== \n');
fprintf('=====================================================================================  \n\n');

for i=1:size(objet_nom,1)
    
    if i==1
        
        fprintf('=======================  PREMIERE ACTION : %s   =========================== \n',objet_nom(i,:));
    end
    if i>=2
        fprintf('======================  ACTION SUIVANTE : %s   ============================ \n',objet_nom(i,:));
    end   
    
    % Messages avec explication de la procédure à suivre avec les modules
    % sur SIMULINK
    fprintf('Enregistrez le signal avec le module "ACQUISITION_VOIX" du mot "%s" : \n',objet_nom(i,:));
    fprintf('<ENTER> quand opération finie...\n');
    input('');
    fprintf('Calculez ses coeff LPC avec le module "TRAITEMENT_LPC" \n');
    fprintf('<ENTER> quand opération finie...\n');
    input('');
    
    % Sauvegarde la matrice dans un .dat
    a = objet_ref(i,:);
    b = '.dat';
    ab = strcat(a,b); 
    % commande sous la forme : wk1write('<nom_matrice>.dat',<nom_matrice>);
    wk1write(ab,LPC0); 
    
    fprintf('Enregistrement...\n\n');
    
end

% Sauvegarde mes listes de mots dans la librairie contenant le vocabulaire
% pour la reconnaissance vocale
save librairie_vocabulaire_recovoc.mat action_nom action_ref objet_nom objet_ref;



