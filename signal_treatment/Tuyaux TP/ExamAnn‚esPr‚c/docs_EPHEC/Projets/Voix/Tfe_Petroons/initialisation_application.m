% INIT_APPLICATION
%--------------------------------------------------------------------------
%Lance tous les modules et fonctions nécessaires au préalable pour le bon
%fonctionnement de l'application.


% Lance simulink, qui est nécessaire pour l'acquisition du son et du
% traitement LPC.
run simulink

% Lance les deux modules d'acquisition et de traitement LPC du signal.
uiopen('traitement_LPC.mdl',1)
uiopen('acquisition_voix.mdl',1)

% Initialise toute la partie "synthèse vocale" en appelant les fonctions de
% crétion des deux librairies nécessaires au fonctionnement de la synthèse
% vocale.
run('.\synthese_vocale\creation_librairie_diphones.m')
run('.\synthese_vocale\creation_librairie_phrases.m')
