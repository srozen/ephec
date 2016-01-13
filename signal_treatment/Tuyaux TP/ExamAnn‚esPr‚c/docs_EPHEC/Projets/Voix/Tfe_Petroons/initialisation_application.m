% INIT_APPLICATION
%--------------------------------------------------------------------------
%Lance tous les modules et fonctions n�cessaires au pr�alable pour le bon
%fonctionnement de l'application.


% Lance simulink, qui est n�cessaire pour l'acquisition du son et du
% traitement LPC.
run simulink

% Lance les deux modules d'acquisition et de traitement LPC du signal.
uiopen('traitement_LPC.mdl',1)
uiopen('acquisition_voix.mdl',1)

% Initialise toute la partie "synth�se vocale" en appelant les fonctions de
% cr�tion des deux librairies n�cessaires au fonctionnement de la synth�se
% vocale.
run('.\synthese_vocale\creation_librairie_diphones.m')
run('.\synthese_vocale\creation_librairie_phrases.m')
