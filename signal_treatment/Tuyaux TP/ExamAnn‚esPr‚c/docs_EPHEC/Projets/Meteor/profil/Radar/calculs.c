#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

char * timebToString(struct timeb timetime){
    char stringResult[100];

    if(timetime.millitm >= 100)
        sprintf(stringResult,"%d.%d secondes",timetime.time,timetime.millitm);
    else
        sprintf(stringResult,"%d.0%d secondes",timetime.time,timetime.millitm);


    return stringResult;
}

struct timeb sumtimeb(struct timeb time1,struct timeb time2){
    struct timeb result;
    unsigned short milliSum = (time2.millitm + time1.millitm);

    result.time = time2.time + time1.time;

    if(milliSum >= 1000){
        result.time = result.time + 1;
        result.millitm = (unsigned short)(milliSum - 1000);
    }
    else
        result.millitm = (unsigned short)milliSum;

    return result;
}

struct timeb difftimeb(struct timeb time1,struct timeb time2){
    struct timeb result;
    signed short milliDef = (signed short)(time2.millitm - time1.millitm);

    result.time = time2.time - time1.time;

    if( milliDef < 0 ){
        result.time = result.time - 1;
        result.millitm = (unsigned short)(1000 + milliDef);
    }
    else
        result.millitm = (unsigned short)milliDef;

    return result;
}

int two_power(int number){
    int power;

    for(power=1;(number>=power);power*=2);

    return power;
}

long compute_frame(long samplerate,unsigned short channels,double time){
    return lround((double)samplerate*time);
}
