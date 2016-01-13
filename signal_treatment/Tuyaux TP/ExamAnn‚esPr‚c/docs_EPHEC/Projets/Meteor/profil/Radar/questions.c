#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "globales.h"
#include "fichiers.h"

int analyse_processing_mode_question(){
    if(guiMode){
        gui_yes_no_dialog("Quelle analyse/traitement voulez-vous effectuer ?","Sur la puissance moyenne","Sur la frequence");

        if(yesNoAnswer == 1)
            return 'p';
        else if(yesNoAnswer == 2)
            return 'f';
        else
            return 0;
    }
    else{
        char buf[100];
        char rep;

        do{
            printf("\nQuelle analyse/traitement voulez-vous effectuer ?\nSur la puissance moyenne(1)\nSur la frequence(2)\nReponse:");

            fgets(buf,sizeof(buf),stdin);
            sscanf(buf,"%c",&rep);
            fflush(stdin);

            if(rep == '1')
                return 'p';
            else if(rep == '2')
                return 'f';
            else
                printf("\nOption %c invalide\n",rep);

        }while(rep != '1' || rep != '2');
    }
}

int choose_file_question(){
     char buf[100];

     do{
        if(guiMode)
              gui_file_chooser("/home","Choisissez le fichier a analyser/traiter",GTK_FILE_CHOOSER_ACTION_OPEN);
        else{
            printf("\nEntrez le chemin du fichier .wav a analyser/traiter (sans espace(s),ni caracteres speciaux) : ");
            fgets(buf,sizeof(buf),stdin);
            sscanf(buf,"%s",fichier_entree);
            fflush(stdin);
        }

     }while(!file_exists(fichier_entree) || !file_is_extension_supported(fichier_entree));

     return 1;
}

int choose_folder_question(){
     char buf[100];

     do{
        if(guiMode){
            gui_file_chooser("/home","Choisissez le dossier de sortie",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
            file_path_add_slash(dossier_sortie);
        }
        else{
            printf("\nEntrez le chemin du dossier de sortie : ");
            fgets(buf,sizeof(buf),stdin);
            sscanf(buf,"%s",dossier_sortie);
            fflush(stdin);
            file_path_add_slash(dossier_sortie);
        }

     }while(!file_exists(dossier_sortie));

     return 1;
}

void reading_questions(char * wavefile,float *debut,float *duree){
    char buf[100];
    char rep = 'o';

    if(verbose){
        printf("Fichier a ouvrir : %s\n",wavefile);
        printf("\nExtension du fichier: %s\n\n",file_extension(wavefile));
    }

    if(rep == 'o' || rep == 'O'){
        printf("Lire le fichier a partir de ou (en secondes)? : ");
        fgets(buf,sizeof(buf),stdin);
        sscanf(buf,"%f",debut);
        fflush(stdin);

        printf("Duree a afficher (en secondes)? (0 - jusqu a la fin): ");
        fgets(buf,sizeof(buf),stdin);
        sscanf(buf,"%f",duree);
        fflush(stdin);
    }
}

int automagic_question(){
    char buf[100];
    char rep;

    if(guiMode){
        gui_yes_no_dialog("Voulez-vous modifier les parametres du traitement/analyse?","Non","Oui");
        if(yesNoAnswer == 2)
            automagic = 0;
        else
            automagic = 1;

        if(automagic)
            precision = BLOC;
    }
    else{
        printf("\nVoulez-vous changer les parametres du traitement/analyse?\n(Parametres par defaut et analyse directe)\n\nParametres par defaut:\nAnalyse complete du fichier\n-Precision de reconnaissance des signaux: %d\n-Seuils de declenchement du trigger: Max: %.1f , Min: %.1f\n\nOui(o) | Non(n): ",BLOC,pseuil_max,pseuil_min);
        fgets(buf,sizeof(buf),stdin);
        sscanf(buf,"%c",&rep);
        fflush(stdin);

        if(rep == 'N' || rep == 'n'){
            precision = BLOC;
            yesNoAnswer = 1;

            automagic = 1;
            return 1;
        }
        else{
            yesNoAnswer = 2;
            automagic = 0;
            return 0;
        }
    }

    return 1;
}

void bloc_question(){
   char buf[100];

   if(!powerOptBloc || powerOptBloc > 250 || powerOptBloc < 10){
       do{
         printf("Precision de la reconnaissance du signal (Default %d. Entre 10 et 250): ",BLOC);
         fgets(buf,sizeof(buf),stdin);
         sscanf(buf,"%hu",&precision);
         fflush(stdin);

         if(precision < 10)
              printf("\n  Erreur, la precision est trop faible, pour de meilleurs resultats choisir une precision superieure a 5 et inferieure a 250 !\n");
         else if(precision > 250)
              printf("\n  Erreur, la precision est trop grande, pour de meilleurs resultats choisir une precision superieure a 5 et inferieure a 250 !\n");
       }while(precision > 250 || precision <10);
   }
   else{
       precision = (unsigned short)powerOptBloc;
       printf("\nPrecision : %d\n",precision);
   }
}

int mean_power_threshold_questions(double pmoyenne){
    char buf[100];

    do{
          printf("\nPrecision pour le seuil minimal ? (Defaut : %f. Entre 0 et 100) : ",pseuil_min);
          fgets(buf,sizeof(buf),stdin);
          sscanf(buf,"%e",&pseuil_min);
          fflush(stdin);

    }while( (pseuil_min < 0) || (pseuil_min > 100 ) );

    do{
          printf("\nPrecision pour le seuil maximal ? (Defaut : %f. Entre 0 et 100) : ",pseuil_max);
          fgets(buf,sizeof(buf),stdin);
          sscanf(buf,"%e",&pseuil_max);
          fflush(stdin);

    }while( (pseuil_max < 0) || (pseuil_max > 100 ) );

    return 1;
}

int frequency_threshold_questions(int fs){
    char buf[100];


    if(1){
        system("clear");
        if(frequencyOptFrequency > fs/2 || frequencyOptFrequency <= 1){
            do{
              printf("\nQuelle frequence voulez-vous detecter ? (Max %.2fHz): ",(float)(fs/2));
              fgets(buf,sizeof(buf),stdin);
              sscanf(buf,"%e",&frequence);
              fflush(stdin);

            }while( frequence > fs/2 );
        }
        else{
            frequence = (float)frequencyOptFrequency;
            printf("\nFrequence a detecter : %.1f\n",frequence);
        }

        if(frequencyOptTolerance > frequence/2 || frequencyOptTolerance <= 1){
            do{
              printf("\nAvec quelle tolerance ? (Max %.2fHz): ",(float)(frequence/2.0));
              fgets(buf,sizeof(buf),stdin);
              sscanf(buf,"%e",&tolerance);
              fflush(stdin);
            }while( tolerance > frequence/2 );
        }
        else{
            tolerance = (float)frequencyOptTolerance;
            printf("\nTolerance : %.1f\n",tolerance);
        }

        if(!frequencyOptNfft)
            Nfft = 1024;
        else if(frequencyOptNfft > MAXFFT || frequencyOptNfft < MINFFT){
            do{
              printf("\nQuelle Nfft ? (Min %d , Max %d): ",MINFFT,MAXFFT);
              fgets(buf,sizeof(buf),stdin);
              sscanf(buf,"%d",&Nfft);
              fflush(stdin);
            }while( Nfft > MAXFFT || Nfft < MINFFT);
        }
        else{
            Nfft = (int)frequencyOptNfft;
            printf("\nNfft: %d\n",Nfft);
        }
    }
    else
        exit(1);

    return 1;
}
