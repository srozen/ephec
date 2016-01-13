#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <sndfile.h>
#include <fftw3.h>
#include <gtk/gtk.h>

#include "fft.h"
#include "calculs.h"
#include "fichiers.h"
#include "globales.h"
#include "questions.h"
#include "traitement.h"
#include "parameters.h"

int audioTrigger_mean_power(){
   float * wavedata;
   int blocSize;     //définition de la taille d'un bloc de n échantillons, n calculé par la formule à droite du signe "="
   long nbblocs;     //définition du nombre de blocs en fonction du nombre d'échantillons et de la taille d'un bloc
   double meanPower;
   float * meanBlocsPower;  //[nbblocs]

   float beginning=0.0;  //variable utilisée pour définir l'échantillon de début à analyser
   float duration=0.0;  //pour définir la durée totale de l'analyse

   long startframe;
   long frames;

   pseuil_min = 4.0;
   pseuil_max = 1.0;

   system("clear");

   automagic_question();
   if(yesNoAnswer == 2){
      bloc_question();
   }

   system("clear");

   open_sndfile(fichier_entree,beginning,duration,&startframe,&frames);

   blocSize = lround( ((fd_in.samplerate)*(fd_in.channels))/(precision) ); //définition de la taille d'un bloc de n échantillons, n calculé par la formule à droite du signe "="
   nbblocs =(long)(lround((frames*fd_in.channels)/blocSize));//définition du nombre de blocs en fonction du nombre d'échantillons et de la taille d'un bloc
   meanBlocsPower = (float *)malloc(nbblocs * sizeof(float));
   wavedata = (float *)malloc(blocSize*sizeof(float));

   strcpy(fileName,file_path(fichier_entree));

   if((meanPower = read_sndfile(startframe,frames,wavedata,meanBlocsPower,blocSize,nbblocs)) != (double)(-1.0)){
       file_create_open_log(meanPower);

       if(!automagic && mean_power_threshold_questions(meanPower) == 0){
          if(verbose)
            printf("\nValeurs par defaut :\n Seuil min: %10f\n Seuil max: %10f\n\n",pseuil_min,pseuil_max);
       }

       audio_processor_meanPower(meanBlocsPower,blocSize,nbblocs,meanPower,frames,startframe,(startframe+frames));

       if(benchmarkMode){
            char loadingTime[100],
                 processingTime[100],
                 totalTime[100];

            strcpy(loadingTime,timebToString(difftimeb(timeFileStartedLoading,timeFileStoppedLoading)));
            strcpy(processingTime,timebToString(difftimeb(timeFileStartedProcessing,timeFileStoppedProcessing)));
            strcpy(totalTime,timebToString(sumtimeb(difftimeb(timeFileStartedLoading,timeFileStoppedLoading),difftimeb(timeFileStartedProcessing,timeFileStoppedProcessing))));

            if(logFileCreated)
                fprintf(logFile,"\n\nTemps pour charger le fichier : %s\nTemps pour traiter le fichier : %s\nTemps total: %s\n",loadingTime,processingTime,totalTime);

            printf("\n\nTemps pour charger le fichier : %s\nTemps pour traiter le fichier : %s\nTemps total: %s\n",loadingTime,processingTime,totalTime);
       }

       if(logFileCreated)
            fclose(logFile);
   }

   return EXIT_SUCCESS;
}

int audioTrigger_frequency(){
   float * wavedata;
   int blocSize;     //définition de la taille d'un bloc de n échantillons, n calculé par la formule à droite du signe "="
   long nbblocs;     //définition du nombre de blocs en fonction du nombre d'échantillons et de la taille d'un bloc
   double meanPower;
   float beginning=0.0;  //variable utilisée pour définir l'échantillon de début à analyser
   float duration=0.0;  //pour définir la durée totale de l'analyse
   unsigned nfft = BLOC;
   long startframe;
   long frames;

   pseuil_min = 4.0;
   pseuil_max = 1.0;

   open_sndfile(fichier_entree,beginning,duration,&startframe,&frames);
   frequency_threshold_questions(fd_in.samplerate);
   system("clear");

   strcpy(fileName,file_path(fichier_entree));

//   blocSize = lround( ((fd_in.samplerate)*(fd_in.channels))/(nfft) ); //définition de la taille d'un bloc de n échantillons, n calculé par la formule à droite du signe "="
   blocSize = 1024;
   nbblocs =(long)(lround((frames*fd_in.channels)/blocSize));//définition du nombre de blocs en fonction du nombre d'échantillons et de la taille d'un bloc
   wavedata = (float *)malloc(blocSize*sizeof(float));

   file_create_open_log(meanPower);
   audio_processor_frequency(startframe,frames,nfft,wavedata,blocSize,nbblocs);

   if(logFileCreated)
        fclose(logFile);

   return EXIT_SUCCESS;
}
