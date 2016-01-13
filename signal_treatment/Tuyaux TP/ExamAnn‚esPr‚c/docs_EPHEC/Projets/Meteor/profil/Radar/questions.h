
int analyse_processing_mode_question();
int choose_file_question();
int choose_folder_question();
void reading_questions(char * wavefile,float *debut,float *duree);  //fonction qui permet de specifier la duree d'affichage des echantillons du fichier wave, duree en secondes aux formats double
int automagic_question();
void bloc_question(); //procédure qui détermine la taille du bloc. Prend un entier entre 10 et 250 en paramètre
int mean_power_threshold_questions(double pmoyenne);
int frequency_threshold_questions(int fs);
