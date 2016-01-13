#include <sndfile.h>

int audio_write(char filepath[100],long frameStart,long nbFrames);  //fonction qui permet d'écrire le résultat dans un fichier wave de sortie. Renvoie le nombre de frames (echantillon * nombre de canaux) écrites.
void audio_processor_meanPower(float *p_moyenne_des_bloc,int taillebloc,int nbblocs,float pmoyenne,long frames,long start,long end);
void audio_processor_frequency(long startframe,long frames,unsigned short precision,float *wavedata,int taillebloc,int nbblocs);
float read_sndfile(long startframe,long frames,float *wavedata,float *p_moyenne_des_bloc,int taillebloc,int nbblocs);
void open_sndfile(char filePath[100],double beginning,double duration,long *startframe,long *frames); //fonction qui ouvre le fichier wave (file), affiche les echantillons dans les intervalles specifiée en secondes (debut et duree). Renvoie la puissance moyenne des echantillons, puissance calculée en faisant la somme des niveaux de tous les échantillons portés au carré, divisée par le nombre d'échantillons.
