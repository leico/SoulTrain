#include "AttackDetection.h"

/* ============================================ *
 * <FilterType>Setup                            *
 * ============================================ */
template<AttackDetection :: FilterType>
void AttackDetection :: Setup(float freq, float q, float samplingrate){
	AllPass(freq, q, samplingrate);
	threshold = 0;
}


/* ============================================ *
 * <LOWPASS>Setup                               *
 * ============================================ */
template<> 
void AttackDetection :: Setup<AttackDetection :: LOWPASS>
(float freq, float q, float samplingrate){
	LowPass(freq, q, samplingrate);
	threshold = 0;
}

/* ============================================ *
 * <HIGHPASS>Setup                              *
 * ============================================ */
template<> 
void AttackDetection :: Setup<AttackDetection :: HIGHPASS>
(float freq, float q, float samplingrate){
	HighPass(freq, q, samplingrate);
	threshold = 0;
}


/* ============================================ *
 * <ProcessType>Process                         *
 * ============================================ */
template<AttackDetection :: ProcessType>
bool AttackDetection :: Process(float *samples, int buffersize){
	return false;
}

/* ============================================ *
 * <AVERAGE>Process                             *
 * ============================================ */
template<>
bool AttackDetection :: Process<AttackDetection :: AVERAGE>
(float *samples, int buffersize){

	float sum = 0;

	for(int i = 0 ; i < buffersize ; ++ i)
		sum += abs( BiQuadFilter :: Process(samples[i]) );

	return ( (sum / buffersize) > (this -> threshold) );
}

/* ============================================ *
 * <MAXVALUE>Process                            *
 * ============================================ */
template<>
bool AttackDetection :: Process<AttackDetection :: MAXVALUE>
(float *samples, int buffersize){

	for(int i = 0 ; i < buffersize ; ++ i)
		if(samples[i] > threshold) return true;
	
	return false;
}
