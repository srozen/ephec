#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <sndfile.h>
#include <fftw3.h>
#include <gtk/gtk.h>

#include "fft.h"
#include "gui.h"
#include "fichiers.h"
#include "globales.h"
#include "questions.h"
#include "traitement.h"
#include "parameters.h"
#include "main_functions.h"


int main(int argc,char * argv[]){
    benchmarkMode = 1;

    modeOpt = 0;
    iOpt = 0;
    oOpt = 0;
    lOpt = 0;
    powerOptBloc = 0;
    frequencyOptNfft = 0;
    frequencyOptFrequency = 0;
    frequencyOptTolerance = 0;


    if(argc > 1){
        if(!(paramsEntered = manage_arguments(argc,argv,0)))
            usage();
    }
    else{
        usage();
        guiMode = 0;
        verbose = 0;
    }

    if(guiMode)
        gui_init(argc,argv);

    if(!iOpt || !file_exists(fichier_entree)){
        system("clear");
        if(!choose_file_question())
           return 0;
        system("clear");
    }

    if(!oOpt || !file_exists(dossier_sortie)){
        system("clear");
        if(!choose_folder_question())
           return 0;
        system("clear");
    }
    else
        file_path_add_slash(dossier_sortie);


    if(!modeOpt)
        modeOpt = analyse_processing_mode_question();

    if( modeOpt == 'p')
       audioTrigger_mean_power(argc,argv);
    else if(modeOpt == 'f')
       audioTrigger_frequency(argc,argv);
    else
       return 0;

    return 1;
}
