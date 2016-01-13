
#include "globales.h"  //fichiers qui contient les variables globales et les constantes

/* Liste des fonctions utilisées dans le projet */
int file_exists(char * filepath); //fonction qui teste l'existence d'un fichier. Renvoie 1 si le fichier existe, 0 dans le cas contraire.
void questions_lecture(char * wavefile,float *debut,float *duree);  //fonction qui permet de specifier la duree d'affichage des echantillons du fichier wave, duree en secondes aux formats double
void question_bloc(unsigned short *precision); //procédure qui détermine la taille du bloc. Prend un entier entre 10 et 250 en paramètre
void question_ecriture(); //fonction qui demande à l'utilisateur si il veut écrire le résultat dans un fichier externe.
int questions_seuils(double pmoyenne,double *seuil_min,double *seuil_max);

void traitement(float *echantillons,double *p_moyenne_des_bloc,int taillebloc,int nbblocs,double pmoyenne,long frames,long samplerate,long start,long end);//float p_moyenne_des_bloc[nbblocs]
int ecrire_wave(char filepath[100],int nbframes);  //fonction qui permet d'écrire le résultat dans un fichier wave de sortie. Renvoie le nombre de frames (echantillon * nombre de canaux) écrites.
float open_sndfile(char * file,double debut,double duree,unsigned short precision); //fonction qui ouvre le fichier wave (file), affiche les echantillons dans les intervalles specifiée en secondes (debut et duree). Renvoie la puissance moyenne des echantillons, puissance calculée en faisant la somme des niveaux de tous les échantillons portés au carré, divisée par le nombre d'échantillons.
float readsndfile(SNDFILE * audiofile,SF_INFO fd_in,long startframe,long frames,unsigned short precision);
int compute_fft(float * bloc_in,double * bloc_out,int nfft,long samplerate);
void parse_fft(double * bloc_out,int nfft,int fs);

#include "fichiers.c"  //fichiers qui contient les fonctions pour le traitement des fichiers de manière générale
#include "questions.c" //contient les fonctions pour demander des paramètres à l'utilisateur
#include "fft.c"  //de calcul de la fft avec fftw
#include "traitement.c"//fonctions de traitement du fichier audio


/*
 * Strcuture d'un fichier wave canonique, voire http://crteknologies.free.fr/programmation/ressources/wav.html

typedef struct {
  char           chunkRIFF[4];  //contient 'RIFF'
  long           fileLength;
  char           chunkFormat[4];  //contient 'WAVE'

  char           chunkID[4];  //contient 'fmt ' - nb: espace après fmt
  long           chunkSize;

  short          wFormatTag;
  unsigned short wChannels;
  unsigned long  dwSamplesPerSec;
  unsigned long  dwAvgBytesPerSec;
  unsigned short wBlockAlign;
  unsigned short wBitsPerSample;
} FormatChunk;

typedef struct {
  char           chunkID[4];  //contient 'data'
  long           chunkSize;
} DataChunk;


/* Ces fonctions sont développées dans le fichier wavold.c
 * Ces fonction ont été developpées pour afficher le contenu d'un fichier wave en utilisant sa structure au format canonique, décrite ci-au-dessus. Elles ne sont plus utilisée dans ce programme à cause d'un nombre trop élevés d'irregularités (formats non canoniques) dans la structure des fichiers wave.
 *


int lecture_format(FILE * fileread,FormatChunk * format); //fonction qui lit le Format Chunk d'un fichier wave, voir description au-dessus
void affichage_format(FormatChunk * format); //fonction qui affiche le Format Chunk
int lecture_datachunk(FILE * fileread,DataChunk * data,int size); //fonction qui lit le Data Chunk, décrite au-dessus
void affichage_datachunk(DataChunk * data); //fonction qui affiche le Data Chunk
int lecture_wave_struct(char * wavefilepath); //fonction qui lit les échantillons du fichier wave, à utiliser qu'après avoir lu le Format Chunk et le Data Chunk

 */
