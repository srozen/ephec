#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "globales.h"

void usage(){
    printf("Usage: ./audioTrigger -m [Processing mode] -i [input file] -o [output directory] -g [GUI|CLI mode] <OPTIONS>\n\n");
}

void help(){
    printf("\nUsage: ./audioTrigger -m [Processing mode] -i [input file] -o [output directory] -g [GUI|CLI mode] <OPTIONS>\n");

    printf("\nArguments :\n");
    printf("\nAucun de ces arguments n est obligatoire. Ces arguments definissent des parametres importants du programme. Ils peuvent etre entres dans n importe quel ordre en minuscules ou en majuscules.\n");
    printf("\n    -help ou -HELP: affiche ce message\n");
    printf("\n    -m (ou -M): Suivi de 'p' ou 'f'.Definit le mode de traitement et d analyse.\n         Deux modes sont disponibles:\n         'p' ou 'P' definit le mode de traitement et d analyse sur la puissance moyenne\n         'f' ou 'F' definit le mode d' analyse et de traitement sur la frequence. Ex: -m P\n");
    printf("\n    -i (ou -I): Suivi du chemin relatif ou absolu d un fichier. Definit le chemin du fichier a traiter/analyser, il doit etre accessible en lecture a l utilisateur courant. Si on ne specifie rien il sera demande par apres. Ex: -i /home/root/test.wav\n");
    printf("\n    -o (ou -O): Suivi du chemin relatif ou absolu d un dossier. Definit le chemin du dossier de destination dans lequel seront enregistrés tous les resultats. Ce dossier doit etre accessible en lecture/ecriture pour l utilisateur courant. Si on ne specifie rien il sera demande par apres. Ex: /home/root/results\n");
    printf("\n    -g (ou -G): Suivi de 'g' ou 'c'.Definit le type d interface desiree. Le mode CLI est active par defaut si il n est pas specifie\n        Deux interfaces sont disponibles:\n         'c' ou 'C' definit le mode CLI\n         'g' ou 'G' definit le mode par interface graphique. Ex: -g G\n");
    printf("\n    -l (ou -L): Suivi du chemin relatif ou absolu d un dossier. Definit le chemin du dossier dans lequel sera ecrit le fichier log. Ce dossier doit exister. Si il n est pas specifie, ou que le chemin n est pas valide, par defaut il sera cree dans le dossier de destination avec le nom du fichier d entree suivi de l extension .txt. Ex: -l /home/results/\n\n");
    printf("\n    -v (ou -V): Suivi de 'v' ou 'n'.Definit le mode verbeux ou non-verbeux. Ce mode permet d'afficher a l ecran, sur la console, des informations sur le traitement en cours, a des fins de diagnostique.\n        'v' ou 'V' definit le mode verbeux\n        'n' ou 'N' definit le mode non-verbeux\n\n");

    printf("\nOptions :\n");
    printf("\n Aucun de ces options n est obligatoire. Ces options definissent les parametres des traitements. Ils doivent obligatoirement etre en majuscule\n");

    printf("\n    -B: Suivi d un nombre entier. Il est utilise pour definir la taille des blocs du traitement et de l analyse. Cette valeur divisera la frequence d echantillonage. Elle doit etre comprise entre 100 et 250. Si la valeur fournie est invalide, ou aucune valeur n est fournie, la valeur de 100 sera prise par defaut. Ex: -B 100\n");
    printf("\n    -F: Suivi d un nombre entier. Definit la frequence a detecter. Il faut entrer une valeur comprise entre 1 et la moitie de la frequence d echantillonage du fichier. Si la valeur fournie est invalide, ou aucune valeur n est fournie, elle sera redemandee lors de l etape du traitement.Ex: -F 440\n");
    printf("\n    -T: Suivi d un nombre entier. Definit la marge de tolerance pour la detection de la frequence. Ainsi le programme pourra detecter des frequences superieures ou inferieures (de ce nombre) a la frequence a detecter. Cette valeur ne pourra etre superieure a la moitie de la valeur de la frequence a detecter. Si la valeur fournie est invalide, ou aucune valeur n est fournie, elle sera redemandee lors de l etape du traitement. Ex: -T 50\n");
    printf("\n    -N: Suivi d un nombre entier. Definit le parametre de NFFT du calcul de la FFT.Cette valeur devrait etre une puissance de 2 superieure a 256. Si la valeur fournie est invalide, ou aucune valeur n est fournie la valeur de 512 sera prise par defaut. Ex: -N 512\n");
}

int manage_arguments(int argc,char *argv[],int verbose){
    int numParams = 0;

    char inputFile[100];
    char outputDirectory[100];
    char logfile[100];

    int index;
    int i;

    guiMode = 0;
    verbose = 0;

    while((i = getopt(argc, argv, "-h:-H:-m:-M:-i:-I:-o:-O:-g:-G:-l:-L:-f:-F:-n:-N:-t:-T:-b:-B:-v:-V")) > 0){
        switch(i){
            case 'H':
            case 'h':if(!strcmp(optarg,"elp") || !strcmp(optarg,"ELP")){
                        help();
                        exit(0);
                     }
                     break;
            case 'M':
            case 'm':if(!strcmp(optarg,"f") || !strcmp(optarg,"F"))
                        modeOpt = 'f';
                     if(!strcmp(optarg,"p") || !strcmp(optarg,"P"))
                        modeOpt = 'p';
                     break;
            case 'b':
            case 'B':if(modeOpt == 'p')
                        powerOptBloc = atoi(optarg);
                     break;
            case 'N':
            case 'n':if(modeOpt == 'f')
                        frequencyOptNfft = atoi(optarg);
                     break;
            case 'F':
            case 'f':if(modeOpt == 'f')
                        frequencyOptFrequency = atoi(optarg);
                     break;
            case 't':
            case 'T':if(modeOpt == 'f')
                        frequencyOptTolerance = atoi(optarg);
                     break;
            case 'G':
            case 'g':if(strcmp(optarg,"") || strcmp(optarg," ")){
                         if(!strcmp(optarg,"g") || !strcmp(optarg,"G"))
                            guiMode = 1;
                     }
                     break;
            case 'I':
            case 'i':if(strcmp(optarg,"") || strcmp(optarg," ")){
                        iOpt = 1;
                        strcpy(fichier_entree,optarg);
                     }
                     break;
            case 'O':
            case 'o':if(strcmp(optarg,"") || strcmp(optarg," ")){
                        oOpt = 1;
                        strcpy(dossier_sortie,optarg);
                     }
                     break;
            case 'L':
            case 'l':if(strcmp(optarg,"") || strcmp(optarg," ")){
                        lOpt = 1;
                        strcpy(data_file,optarg);
                     }
                     break;
            case 'V':
            case 'v':if(!strcmp(optarg,"1"))
                        verbose = 1;
                     else
                        verbose = 0;
                    break;
            default:printf("\nArguments \'%c\' non valide\n",i);
                    break;
        }
    }

    if(optind == argc)
        usage();

    if(!guiMode){
        if(verbose)
            printf("Pas de mode specifie, par defaut, mode CLI\n");
    }
    else{
        if(verbose){
            if(guiMode)
                printf("Mode GUI\n");
            else
                printf("Mode CLI\n");
        }
        numParams++;
    }
    if(!modeOpt)
        printf("Pas de mode specifie, vous devrez le choisir\n");
    else{
        if(modeOpt == 'p'){
            if(verbose){
                printf("Mode Puissance Moyen\n");
                if(powerOptBloc)
                    printf("  Precision : %d\n",powerOptBloc);
            }
        }
        else{
            if(verbose){
                printf("Mode Frequence\n");
                if(frequencyOptNfft)
                    printf("  Nfft : %d\n",frequencyOptNfft);
                if(frequencyOptFrequency)
                    printf("  Frequence : %d\n",frequencyOptFrequency);
                if(frequencyOptTolerance)
                    printf("  Tolerance : %d\n",frequencyOptTolerance);
            }
        }
        numParams++;
    }

    if(!iOpt)
        printf("Pas de fichier d entree specifie, vous devrez le choisir\n");
    else{
        if(verbose)
            printf("Fichier d entree : %s\n",fichier_entree);
        numParams++;
    }
    if(!oOpt)
        printf("Pas de dossier de destination vous devrez le choisir\n");
    else{
        if(verbose)
            printf("Dossier de destination : %s\n",dossier_sortie);
        numParams++;
    }
    if(!lOpt)
        printf("Pas de fichier log specifie, par defaut dans le dossier de destination\n");
    else{
        if(verbose)
            printf("Fichier log : %s\n",data_file);
        numParams++;
    }

    for(index = optind; index < argc; index++)
        printf ("Argument non-valide \'%s\' ignore \n",argv[index]);

    return numParams;
}
