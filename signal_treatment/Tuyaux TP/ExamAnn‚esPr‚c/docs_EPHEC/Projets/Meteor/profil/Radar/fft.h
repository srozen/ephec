#include "globales.h"

void swap_double(double * a,double * b);
void reverse_vector(double * frequencies,double * coefficient,int length);
void sort_frequencies(double * frequencies,double * coefficient,unsigned length);
int compute_fft(float * bloc_in,double * bloc_out,int nfft,long samplerate);
void parse_fft(double * spectrum,int nfft,int fs,double triggerCoeff,int frame,float time);
int extract_fft(double * spectrum,int nfft,int fs,double * frequencies,double * coefficient,double precision);
void parse_frequencies(double * frequencies,double * coefficient,int nfft);
