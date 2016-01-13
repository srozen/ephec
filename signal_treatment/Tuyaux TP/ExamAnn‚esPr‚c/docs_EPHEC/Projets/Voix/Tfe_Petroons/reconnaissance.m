% RECONNAISSANCE
%--------------------------------------------------------------------------
% Demande à l'utilisateur d'enregistrer son signal pour l'action ainsi que
% l'objet concerné.
% Appelle ensuite la méthode 'comparaison.m' afin de comparer ceux qui
% viennent d'être acquis avec ceux présents dans le systême.


fprintf('===================================================================================== \n');
fprintf('===============================  RECONNAISSANCE  ==================================== \n');
fprintf('===================================================================================== \n\n');

fprintf('==================================  ACTION   ======================================== \n');
fprintf('Enregistrez le signal de l''ACTION avec le module "ACQUISITION_VOIX"\n');
fprintf('<ENTER> quand opération finie...\n');
input('');
fprintf('Calculez ses coeff LPC avec le module "TRAITEMENT_LPC" \n');
fprintf('<ENTER> quand opération finie...\n');
input('');

% Les coeff LPC du signal acquis sont placés dans la variable 'LPC_action'
% qui sera utilisée par la méthode 'comparaison.m'.
LPC_action = LPC0;

fprintf('==================================  OBJET   ======================================== \n');
fprintf('Enregistrez le signal de l''OBJETavec le module "ACQUISITION_VOIX"\n');
fprintf('<ENTER> quand opération finie...\n');
input('');
fprintf('Calculez ses coeff LPC avec le module "TRAITEMENT_LPC" \n');
fprintf('<ENTER> quand opération finie...\n');
input('');

% Les coeff LPC du signal acquis sont placés dans la variable 'LPC_objet'
% qui sera utilisée par la méthode 'comparaison.m'
LPC_objet = LPC0;

run('.\comparaison.m')

% Affichage du résultat une fois que la comparaison a été effectuée.
fprintf('================================  RESULTAT   ====================================== \n');
fprintf('La commande demandée est : %s - ',nom_action(1,:));
fprintf('%s\n',nom_objet(1,:));

clear LPC_action;
clear LPC_objet;
