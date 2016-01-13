#include <time.h>
#include <sys/timeb.h>
#include <sndfile.h>

#define BUF 5
#define BLOC 100
#define MAXFFT 4096
#define MINFFT 256

#define ON 1
#define OFF 0

unsigned short  modeOpt,
                iOpt,
                oOpt,
                lOpt;

int        powerOptBloc,
           frequencyOptNfft,
           frequencyOptFrequency,
           frequencyOptTolerance;

char fichier_entree[100],
     dossier_sortie[100],
     data_file[100];

char fileName[100];

SNDFILE * audiofile;
SF_INFO fd_in;
SF_INFO fd_out;
FILE * logFile;

struct timeb timeFileStartedLoading,
             timeFileStoppedLoading,
             timeFileStartedProcessing,
             timeFileStoppedProcessing;

int automagic,  //variable qui définit le mode d'analyse et de traitement. 0 = manuel, 1 = automatique.
    benchmarkMode,
    guiMode,
    logFileCreated,
    yesNoAnswer,
    verbose,
    paramsEntered;

float  pseuil_min,
       pseuil_max;

unsigned short precision;

float frequence,
      tolerance;

int Nfft,
    detectedEvents;
int * detectedEventsIndexes;
float lengthRecord;
float lastEventDetected;
