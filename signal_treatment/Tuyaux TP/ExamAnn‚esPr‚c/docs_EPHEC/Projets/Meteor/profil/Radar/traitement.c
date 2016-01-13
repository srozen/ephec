#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <sndfile.h>
#include <gtk/gtk.h>

#include "fft.h"
#include "calculs.h"
#include "globales.h"
#include "fichiers.h"
#include "questions.h"

int audio_write(char filepath[100],long frameStart,long nbFrames){
    SNDFILE * audioOut;
    float * waveout;  //variable utilisée pour écrire le(s) fichiers wav résultants
    int nbframes_ecrites;
    int readFrames;

    char chemin[100];
    char action[100] = "rm -r ";

    fd_out.frames = nbFrames;

    strcpy(chemin,dossier_sortie);
    strcat(chemin,filepath);

    if(file_exists(chemin)){
        strcat(action,chemin);
        system(action);
        if(verbose)
            printf("\nLe fichier %s existe deja et va etre ecrase\n",chemin);
    }
    else{
        if(verbose)
            printf("\nLe fichier %s va etre cree\n",chemin);
    }

    if(!file_exists(fichier_entree)){
        if(verbose)
            printf("\nLe fichier %s a ete supprime ou deplace!\n",fichier_entree);
        exit(1);
    }

    if( (audiofile = sf_open(fichier_entree,SFM_READ,&fd_in)) != NULL){
        waveout = (float *)malloc(nbFrames*(fd_in.channels)*sizeof(float));

        if(sf_seek(audiofile,frameStart,SEEK_SET) != frameStart){  //on ne positionne pas lorsque le premier frame est 0 sinon on a une erreur de positionnement
            printf("\nErreur de positionnement dans le fichier %s!",fichier_entree);
            return -1;
        }

        if((readFrames = sf_readf_float(audiofile, waveout, nbFrames)) != nbFrames){ //(readFrames = sf_readf_float(audiofile, waveout, nbFrames)) != nbFrames)
            printf("\nErreur de lecture : nombre de frames lues(%d) differente du nombre attendu (%d)\n\n",readFrames,nbFrames);
            return -1;
        }

        sf_close(audiofile);
    }

    if( (audioOut = sf_open(chemin,SFM_WRITE,&fd_out)) != NULL){
        if((nbframes_ecrites = sf_writef_float(audioOut,waveout,nbFrames)) != nbFrames)
           printf("\nAttention, le nombre de frames ecrites (%d) est different du nombre de frames attendues (%d)",nbframes_ecrites,nbFrames);

        sf_write_sync(&fd_out);
        sf_close(audioOut);
        free(waveout);
    }
    else{
       printf("\nErreur, ne peut ouvrir le fichier %s avec sf_open",chemin);
       return -1;
    }

    return nbframes_ecrites;
}

void audio_processor_meanPower(float *p_moyenne_des_bloc,int taillebloc,int nbblocs,float pmoyenne,long frames,long start,long end){
    long i;
    long beginSample,endSample;

    float deltaBlocTrigger;
    float deltaBlocReleaseTrigger;
    float triggeringLevel;

    int startrecord=0;

    long triggeringBloc=0;
    long releasingBloc = 0;

    int nbOutputFiles = 0;
    char outputFileName[50];

    long nbSamples;

    detectedEvents = 0;

    printf("\nTraitement du fichier...\n");
    if(benchmarkMode)
            ftime(&timeFileStartedProcessing);

    for(i=1 ; i<nbblocs ; i++){
        //debut de l'enregistrement

        if(!p_moyenne_des_bloc[i-1])
            p_moyenne_des_bloc[i-1] = 0.000001;
        deltaBlocTrigger = ((p_moyenne_des_bloc[i]-pmoyenne)/p_moyenne_des_bloc[i-1]); //
        if( !startrecord && (( (i*taillebloc) + taillebloc)>= start) && (((i*taillebloc) - taillebloc) <= end) && ( deltaBlocTrigger >= (pseuil_max)) ){//p_moyenne_des_bloc[i-1]*pseuil_max
            triggeringLevel = p_moyenne_des_bloc[i];
            startrecord = 1;

            if((triggeringBloc = (i-BUF)) < 0 ) triggeringBloc = 0;

            beginSample = ((triggeringBloc)*taillebloc);

            if(verbose)
                printf("\nDebut record a %f secondes: delta [%f] a depasse seuil max %f\n",((float)((start+(i*taillebloc))/(float)(fd_in.samplerate*fd_out.channels))),deltaBlocTrigger,pseuil_max);
            if(logFileCreated)
                fprintf(logFile,"\nEvenement %d detecte a %f secondes: delta [%f] a depasse seuil max %f\n",nbOutputFiles,((float)((start+(i*taillebloc))/(float)(fd_in.samplerate*fd_out.channels))),deltaBlocTrigger,pseuil_max);
        }
        i++;

        //fin de l'enregistrement
        if(!p_moyenne_des_bloc[i])
            p_moyenne_des_bloc[i] = 0.000001;
        deltaBlocReleaseTrigger = ((p_moyenne_des_bloc[i]-triggeringLevel)/p_moyenne_des_bloc[i]);//((p_moyenne_des_bloc[i]-p_moyenne_des_bloc[i-1])/p_moyenne_des_bloc[i]);
        if((startrecord) && (deltaBlocReleaseTrigger < 0) && (fabs(deltaBlocReleaseTrigger) >= (pseuil_min)) ){//p_moyenne_des_bloc[i-1]*pseuil_min
            releasingBloc = (i+BUF);

            endSample = ((releasingBloc)*taillebloc);
            nbSamples = endSample-beginSample;

            if(verbose)
                printf("\nFin record a %f secondes: delta [%f] a depasse seuil min %f\n",((float)((start+(i*taillebloc))/(float)(fd_in.samplerate*fd_out.channels))),deltaBlocReleaseTrigger,pseuil_min);

            sprintf(outputFileName,"%s_%d.wav",fileName,detectedEvents);
            detectedEvents++;

            if(logFileCreated){
                fprintf(logFile,"Fin evenement %d a %f secondes: delta [%f] a depasse seuil min %f\n",nbOutputFiles,((float)((start+(i*taillebloc))/(float)(fd_in.samplerate*fd_out.channels))),deltaBlocReleaseTrigger,pseuil_min);
                fprintf(logFile,"Resultat: %s",outputFileName);
            }

            if((audio_write(outputFileName,beginSample,nbSamples) != -1)){
                if(verbose)
                    printf("\nEcriture fichier %s reussie !\n",outputFileName);
            }

            nbOutputFiles++;

            startrecord = 0;

            i = releasingBloc; //on repositionne le compteur à la fin de l'enregistrement précedent
        }
    }
    printf("\nFin du traitement. Nombre d evenements detectes : %d\n",detectedEvents);

    if(benchmarkMode)
            ftime(&timeFileStoppedProcessing);

    printf("\nTraitement termine! Appuyez sur [Return] pour continuer !\n");
    getchar();
}

void audio_processor_frequency(long startframe,long frames,unsigned short precision,float *wavedata,int taillebloc,int nbblocs){
   float samplepower;

   int numReadFrames = lround(taillebloc/fd_in.channels);
   long readFrames;
   long lastReadFrame = 0;
   float time = 0.0;

   float bloc[taillebloc];  //tableau des blocs
   double bloc_out[two_power(taillebloc)];
   detectedEventsIndexes = (int *)malloc(nbblocs * sizeof(int));

   long int i,
            j=0,
            k=0,
            l=0,
            m=0;

   int frame;

   detectedEvents = 0;
   lastEventDetected = 0.0;
   lengthRecord = 1.5;

   if(benchmarkMode)
      ftime(&timeFileStartedLoading);

   if(!(readFrames = sf_readf_float(audiofile, wavedata,numReadFrames ) == numReadFrames)){
      printf("\nErreur de lecture : nombre de frames lues (%10d) differente du nombre attendu (%10d)\n\n",readFrames,numReadFrames);
      return -1;
   }

   printf("\nAnalyse en cours...\n");

   lastReadFrame = readFrames;

   for(i=0;i<(nbblocs*taillebloc);i++){

      samplepower = wavedata[m]*wavedata[m];

      if(l < (nbblocs*taillebloc)){

        if( j < taillebloc ){
          bloc[j] = wavedata[m];
          j++;
        }
        else if( k < nbblocs ){
          frame = (int)k*(int)taillebloc;
          time = ((float)frame/(float)(fd_in.samplerate*fd_out.channels));

          if(!(k%800)){
              system("clear");
              printf("\nAnalyse en cours %.2f\%\n",(((float)lastReadFrame / (float)fd_in.frames)*10000.0));
          }

          compute_fft(bloc,bloc_out,taillebloc,fd_in.samplerate);

          if(verbose){
            printf("\nFFT EFFECTUEE POUR %d ECHANTILLONS\n",two_power(taillebloc));
            printf("Bloc %d au temps %f secondes",k,((float)((k*taillebloc))/(float)(fd_in.samplerate*fd_out.channels)));
          }

          parse_fft(bloc_out,two_power(taillebloc),fd_in.samplerate,11.5,frame,time);

          j=1;
          k++;

          if((fd_in.frames - lastReadFrame) < numReadFrames)
            numReadFrames = fd_in.frames % numReadFrames;

          if(!(readFrames = sf_readf_float(audiofile, wavedata,numReadFrames) == numReadFrames)){
            printf("\nErreur de lecture : nombre de frames lues (%10d) differente du nombre attendu (%10d)\n\n",readFrames,numReadFrames);
            return -1;
          }

          lastReadFrame += readFrames;
          m=0;
        }
        l++;
      }
      m++;
   }

   if(benchmarkMode)
      ftime(&timeFileStoppedLoading);

   if(benchmarkMode)
      ftime(&timeFileStartedProcessing);

   system("clear");
   printf("\nAnalyse terminee\n");
   printf("\nTraitement en cours...\n");

   if(logFileCreated)
      fclose(logFile);

   sf_close(audiofile);

   char outputFileName[100];

   if(verbose){
       printf("\nNombre evenements detectes dans la bande de frequences (%.1f - %.1f)Hz: %d , premier evenement : %d , deuxieme evenement : %d\n",frequence-(float)tolerance,frequence+(float)tolerance,detectedEvents,*(detectedEventsIndexes),*(detectedEventsIndexes+1));
       getchar();
   }
   else
       printf("\nNombre evenements detectes dans la bande de frequences (%.1f - %.1f)Hz: %d\n",frequence-(float)tolerance,frequence+(float)tolerance,detectedEvents);

   for(i=0;i<detectedEvents;i++){
        sprintf(outputFileName,"%s_%d.wav",fileName,i);

        if((audio_write(outputFileName,*(detectedEventsIndexes+i)-(lround(lengthRecord*(fd_in.samplerate/fd_in.channels)))/2,(lround((lengthRecord*1.5)*(fd_in.samplerate/fd_in.channels)))) != -1)){
            if(verbose)
                printf("\nEcriture fichier %s\n",outputFileName);
        }
   }

   if(benchmarkMode)
        ftime(&timeFileStoppedProcessing);

   printf("\nTraitement termine! Appuyez sur [Return] pour continuer !\n");
   getchar();

   exit(0);
}

float read_sndfile(long startframe,long frames,float *wavedata,float *p_moyenne_des_bloc,int taillebloc,int nbblocs){
   float samplepower;
   float pmoyenne=0.0;
   int numReadFrames = lround(taillebloc/fd_in.channels);
   long readFrames;
   long lastReadFrame = 0;

   float bloc[taillebloc];  //tableau des blocs
   double pmoyenne_du_bloc = 0.0;

   long int i,j=0,k=0,l=0,m=0;

   printf("\nChargement du fichier...\n");

   if(benchmarkMode)
      ftime(&timeFileStartedLoading);

   if(!(readFrames = sf_readf_float(audiofile, wavedata,numReadFrames ) == numReadFrames)){
      printf("\nErreur de lecture : nombre de frames lues (%10d) differente du nombre attendu (%10d)\n\n",readFrames,numReadFrames);
      return -1;
   }

   lastReadFrame = readFrames;

   for(i=0;i<(nbblocs*taillebloc);i++){

      samplepower = wavedata[m]*wavedata[m];

      if(l < (nbblocs*taillebloc)){

        if( j < taillebloc ){
          bloc[j] = wavedata[m];
          pmoyenne_du_bloc += samplepower;
          j++;
        }
        else if( k < nbblocs ){
          pmoyenne_du_bloc /= j;
          p_moyenne_des_bloc[k] = pmoyenne_du_bloc;
          pmoyenne_du_bloc = samplepower;

          if(!(k%1200)){
              system("clear");
              printf("\nChargement du fichier %.2f\%\n",(((double)lastReadFrame / (double)fd_in.frames)*10000.0));
          }

          j=1;
          k++;

          if((fd_in.frames - lastReadFrame) < numReadFrames)
            numReadFrames = fd_in.frames % numReadFrames;

          if(!(readFrames = sf_readf_float(audiofile, wavedata,numReadFrames) == numReadFrames)){
            printf("\nErreur de lecture : nombre de frames lues (%10d) differente du nombre attendu (%10d)\n\n",readFrames,numReadFrames);
            return -1;
          }

          lastReadFrame += readFrames;
          m=0;

        }
        l++;
      }
      m++;
      pmoyenne += samplepower;
   }
   system("clear");
   sf_close(audiofile);
   printf("\nChargement du fichier termine!\n");

   if(benchmarkMode)
        ftime(&timeFileStoppedLoading);

   pmoyenne /= (float)(fd_in.frames*fd_in.channels);

   if(verbose)
        printf("\nPuissance moyenne du signal = %f\n",pmoyenne);

   return pmoyenne;
}

void open_sndfile(char filePath[100],double beginning,double duration,long *startframe,long *frames){
    *startframe=0;

    if( (audiofile = sf_open(filePath,SFM_READ,&fd_in)) != NULL){
       if(verbose)
            printf("Fichier audio %s correctement ouvert !\nNombre de frames dans le fichier : %d\n",filePath,fd_in.frames);

       fd_out = fd_in;

       if(beginning == 0.0){
           *startframe = 0;
           if(duration ==0.0)
              *frames = fd_in.frames;
           else
              *frames = lround(duration*(fd_in.samplerate));
       }
       else{
           *startframe = lround(beginning*(fd_in.samplerate));
           if(duration ==0.0)
              *frames = fd_in.frames-(*startframe);
           else
              *frames = lround(duration*(fd_in.samplerate));
       }
    }
}
