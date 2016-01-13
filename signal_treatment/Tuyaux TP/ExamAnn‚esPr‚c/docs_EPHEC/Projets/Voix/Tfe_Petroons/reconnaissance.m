% RECONNAISSANCE
%--------------------------------------------------------------------------
% Demande � l'utilisateur d'enregistrer son signal pour l'action ainsi que
% l'objet concern�.
% Appelle ensuite la m�thode 'comparaison.m' afin de comparer ceux qui
% viennent d'�tre acquis avec ceux pr�sents dans le syst�me.


fprintf('===================================================================================== \n');
fprintf('===============================  RECONNAISSANCE  ==================================== \n');
fprintf('===================================================================================== \n\n');

fprintf('==================================  ACTION   ======================================== \n');
fprintf('Enregistrez le signal de l''ACTION avec le module "ACQUISITION_VOIX"\n');
fprintf('<ENTER> quand op�ration finie...\n');
input('');
fprintf('Calculez ses coeff LPC avec le module "TRAITEMENT_LPC" \n');
fprintf('<ENTER> quand op�ration finie...\n');
input('');

% Les coeff LPC du signal acquis sont plac�s dans la variable 'LPC_action'
% qui sera utilis�e par la m�thode 'comparaison.m'.
LPC_action = LPC0;

fprintf('==================================  OBJET   ======================================== \n');
fprintf('Enregistrez le signal de l''OBJETavec le module "ACQUISITION_VOIX"\n');
fprintf('<ENTER> quand op�ration finie...\n');
input('');
fprintf('Calculez ses coeff LPC avec le module "TRAITEMENT_LPC" \n');
fprintf('<ENTER> quand op�ration finie...\n');
input('');

% Les coeff LPC du signal acquis sont plac�s dans la variable 'LPC_objet'
% qui sera utilis�e par la m�thode 'comparaison.m'
LPC_objet = LPC0;

run('.\comparaison.m')

% Affichage du r�sultat une fois que la comparaison a �t� effectu�e.
fprintf('================================  RESULTAT   ====================================== \n');
fprintf('La commande demand�e est : %s - ',nom_action(1,:));
fprintf('%s\n',nom_objet(1,:));

clear LPC_action;
clear LPC_objet;
