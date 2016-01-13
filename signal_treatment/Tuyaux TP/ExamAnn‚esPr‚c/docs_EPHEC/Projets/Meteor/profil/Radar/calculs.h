#include <sys/timeb.h>

char * timebToString(struct timeb timetime);
struct timeb sumtimeb(struct timeb time1,struct timeb time2);
struct timeb difftimeb(struct timeb time1,struct timeb time2);
int two_power(int number);
long compute_frame(long samplerate,unsigned short channels,double time);
