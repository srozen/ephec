void strtoupper(char * str);
void file_path_add_slash(char * filePath);
int file_exists(char * filepath); //fonction qui teste l'existence d'un fichier. Renvoie 1 si le fichier existe, 0 dans le cas contraire.
char * file_extension(char * filepath);
int file_extensions_supported(char extension[5]);
int file_is_extension_supported(char * filepath);
int file_create(char path[100]);
int file_delete(char path[100]);
int file_create_open_log(float meanPower);
