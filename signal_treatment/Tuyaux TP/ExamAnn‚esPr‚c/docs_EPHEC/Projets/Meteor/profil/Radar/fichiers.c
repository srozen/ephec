#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#include "globales.h"

void strtoupper(char * str){
    unsigned short int i;

    for(i=0;str[i];i++)
       str[i] = toupper(str[i]);
}

void file_path_add_slash(char * filePath){
     if(filePath[strlen(filePath)-1] != '/'){
        int indicemax = strlen(filePath);
        filePath[indicemax+1] = filePath[indicemax];
        filePath[indicemax] = '/';
     }
}

int file_exists(char * filepath){
    FILE * fichier;

    if( (fichier = fopen(filepath,"r")) == NULL){
       if(verbose)
            printf("\n[%s] n existe pas...\n",filepath);
       return 0;
    }
    else{
       fclose(fichier);
       return 1;
    }
}

char * file_path(char * filePath){
    char * tmpFilepath;
    char * tokened = " ";
    char * result;

    tmpFilepath = (char *)malloc((strlen(filePath)+1)*sizeof(char));
    strcpy(tmpFilepath,filePath);

    result = strtok( tmpFilepath, "/" );

    while( result != NULL ){
       tokened = result;
       result = strtok( NULL, "/" );
    }

    return tokened;
}

char * file_extension(char * filepath){
    char * tmpFilepath;
    char * tokened = " ";
    char * result;

    tmpFilepath = (char *)malloc((strlen(filepath)+1)*sizeof(char));
    strcpy(tmpFilepath,filepath);

    result = strtok( tmpFilepath, "." );

    while( result != NULL ){
       tokened = result;
       result = strtok( NULL, "." );
    }

    filepath = tmpFilepath;

    return tokened;
}

int file_extensions_supported(char extension[5]){
    char extensionsSupported[21][5] = {"WAV","WAVE","AIFF","SGI","AIFF","AIFC","DEC","AU","SND","PAF","IFF","SVX","SF","VOC","W64","MAT4","MAT5","PVF","XI","HTK","CAF"};
    unsigned short int i;

    strtoupper(extension);

    for(i=0;i<21;i++){
        if(!strcmp(extension,extensionsSupported[i]))
            return 1;
    }

    return 0;
}

int file_is_extension_supported(char * filepath){
    char * extension = file_extension(filepath);

    if(!file_extensions_supported(extension)){
        printf("\n! Extension de fichier [%s] non supportee !\n",file_extension(extension));
        return 0;
     }

     return 1;
}

int file_create(char path[100]){
    char command[100];
    int file;

    if(!file_exists(path)){
        file = open(path,O_WRONLY,0777);
        if(file){
            close(file);
            return 1;
        }
        else
            return -2;
    }
    else{
        if(verbose)
            printf("\nThe file %s already exists\n",path);
        return -1;
    }
}

int file_delete(char path[100]){
    char command[100];
    strcpy(command,"rm -r ");

    if(!file_exists(path)){
        printf("\nAborting deletion, the file %s doesn't exist\n",path);
        return 0;
    }
    else{
        strcpy(command,path);
        system(command);

        if(file_exists(path)){
            printf("\nCould not delete the file %s, maybe you don't have the rights ?\n",path);
            return 0;
        }
        else{
            if(verbose)
                printf("\nFile %s deleted!\n",path);
            return 1;
        }
    }
}

int file_create_open_log(float meanPower){

       if(!lOpt || !file_exists(data_file)){
           strcpy(data_file,dossier_sortie);
           strcat(data_file,file_path(fichier_entree));
           strcat(data_file,".txt");
       }
       else{
           file_path_add_slash(data_file);
           strcat(data_file,file_path(fichier_entree));
           strcat(data_file,".txt");
       }

       if(verbose)
            printf("\nResults log: %s\n",data_file);

       if((logFileCreated = file_create(data_file))){
            logFile = fopen(data_file,"w+");
            if(logFile){
                fprintf(logFile,"Fichier %s:\nSamplerate: %d\nChannels : %d\nNumber of frames: %d\n\n[Analysis:]\n\n",fichier_entree,fd_in.samplerate,fd_in.channels,fd_in.frames);
                return logFileCreated = 1;
            }
            else
                return logFileCreated = 0;
       }
       else if(logFileCreated == -1)
            return logFileCreated = 1; //Le fichier de log existe deja, on s'en sert et on l ecrase
       else if(logFileCreated == -2)
            return logFileCreated = 0;
}
