#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fftw3.h>

#include "calculs.h"
#include "globales.h"


void swap_double(double * a,double * b){
    double temp;

    temp = *b;
    *b = *a;
    *a = temp;
}

void reverse_vector(double * frequencies,double * coefficient,int length){
    unsigned i;

    for(i=0;i<floor((length)/2);i++){
        swap_double(&frequencies[i],&frequencies[length-1-i]);
        swap_double(&coefficient[i],&coefficient[length-1-i]);
    }
}

void sort_frequencies(double * frequencies,double * coefficient,unsigned length){
    unsigned i,j;

    for(i=0;i<(length-1);i++){
        for(j=1;j<(length);j++){
            if(frequencies[j]>frequencies[i]){
                swap_double(&frequencies[j],&frequencies[i]);
                swap_double(&coefficient[j],&coefficient[i]);
            }
        }
    }
}

int compute_fft(float * bloc_in,double * bloc_out,int nfft,long samplerate){
    int closestPower2 = two_power(nfft);  //on calcule la plus proche puissance de 2
    double bloc_in_f2d[closestPower2];
    int i;

    fftw_plan p;  //plan qui va contenir la FFT

    for(i=0;i<nfft;i++)
        bloc_in_f2d[i] = (double)bloc_in[i];  //on convertit les echantillons float en double
    for(;i<closestPower2;i++)
        bloc_in_f2d[i] = 0;   //on rempli de 0 le vecteur jusqu ' à la plus proche puissance de 2

    p = fftw_plan_r2r_1d(closestPower2,bloc_in_f2d,bloc_out,FFTW_R2HC,FFTW_FORWARD);  //on construit le plan de la FFT, "bloc_out" contiendra la FFT

    fftw_execute(p);  //on execute la FFT
    fftw_destroy_plan(p);  //on detruit le plan

    return 0;
}

int extract_fft(double * spectrum,int nfft,int fs,double * frequencies,double * coefficient,double precision){
    unsigned int i;
    int numberFrequencies = 0;
    double correction = (double)fs / (double)nfft;

    double mean = 0.0;
    int max = 0;

    for(i=0;i<nfft;i++){
        mean += fabs(spectrum[i]);
        if(fabs(spectrum[i]) > fabs(spectrum[max]))
            max = (double)i * correction;
    }

    mean /= (double)nfft;                           //on calcule la moyenne des coefficients de frequences

    for(i=0;i<2;i++)
        frequencies[i] = 0;

    for(i=0;i<(nfft/2);i++){
        if(spectrum[i] > (precision*mean)){
            frequencies[numberFrequencies] = (double)i * correction;
            coefficient[numberFrequencies] = spectrum[i];
            numberFrequencies++;
        }
    }

    sort_frequencies(frequencies,coefficient,numberFrequencies);
    frequencies[numberFrequencies] = -1;
    coefficient[numberFrequencies] = -1;
    printf("\nFrequence Max: %d Moyenne Frequences %f\n",(int)(max*correction),mean);
    return max;
}

void parse_fft(double * spectrum,int nfft,int fs,double triggerCoeff,int frame,float time){
   int i,m=0,entryLogFile=0;
   double absval;
   double frequency;
   double correction = (double)fs / (double)nfft;
   int lastrecorded = 0;
   float diffTimeRecorded;

    for (i = 0; i < (nfft-2); i++) {
        absval = fabs(spectrum[i]);
        frequency = m * correction;

        if((absval > triggerCoeff) && !entryLogFile && !(frequency > (fs/2))){
            entryLogFile = 1;
            if(verbose)
                fprintf(logFile,"\n\nBloc temps %f secondes:\n",time);
        }

        if(entryLogFile && (absval > triggerCoeff) && !(frequency > (fs/2))){
            if(verbose)
                fprintf(logFile,"%f Hz --> Power : %f\n", frequency, absval);

            if(((frequency >= (frequence-tolerance)) && ((frequency <= (frequence+tolerance)))) ){

                if(!lastrecorded){
                    diffTimeRecorded = time - lastEventDetected;

                    if(diffTimeRecorded > lengthRecord){
                        detectedEventsIndexes[detectedEvents] = lastrecorded = frame + i;

                        lastEventDetected = time;
                        fprintf(logFile,"\n--> Evenement enregistre (%.1fHz a %.4f) a %.4f secondes",frequency,absval,time);
                        fprintf(logFile,"\n--> Resultat : %s_%d.wav\n\n",fileName,detectedEvents);
                        detectedEvents++;
                    }
                }
            }
        }
        else if(verbose && (absval > triggerCoeff))
            printf("%f %f\n", frequency, absval);
        m++;
    }
}

void parse_frequencies(double * frequencies,double * coefficient,int nfft){
    unsigned int i;

    printf("\n Frequences:\n");

    for(i=0;frequencies[i] != -1;i++){
        printf("%dHz: %f ",(int)frequencies[i],coefficient[i]);
        if((i % 2) == 0)
            printf("\n");
    }
}
