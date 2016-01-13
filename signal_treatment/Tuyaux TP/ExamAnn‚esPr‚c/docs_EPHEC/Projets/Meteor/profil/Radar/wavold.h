
/* Ces fonctions sont développées dans le fichier wavold.c
 * Ces fonction ont été developpées pour afficher le contenu d'un fichier wave en utilisant sa structure au format canonique, décrite ci-au-dessus. Elles ne sont plus utilisée dans ce programme à cause d'un nombre trop élevés d'irregularités (formats non canoniques) dans la structure des fichiers wave.
 *


int lecture_format(FILE * fileread,FormatChunk * format); //fonction qui lit le Format Chunk d'un fichier wave, voir description au-dessus
void affichage_format(FormatChunk * format); //fonction qui affiche le Format Chunk
int lecture_datachunk(FILE * fileread,DataChunk * data,int size); //fonction qui lit le Data Chunk, décrite au-dessus
void affichage_datachunk(DataChunk * data); //fonction qui affiche le Data Chunk
int lecture_wave_struct(char * wavefilepath); //fonction qui lit les échantillons du fichier wave, à utiliser qu'après avoir lu le Format Chunk et le Data Chunk

 */
