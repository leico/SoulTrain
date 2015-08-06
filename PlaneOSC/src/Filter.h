
#ifndef basic_Filter_h
#define basic_Filter_h


#include "ofMain.h"
#include "ofxOsc.h"
#include "BiQuadFilter.h"

class Filter{

	private:
	float frequency;
	float q;
	float samplingrate;

	protected:
	BiQuadFilter filter;

	public:	
	/* ========================================= *
	 * Constructor/Destructor                    *
	 * ========================================= */
	         Filter(void){}
	virtual ~Filter(void){}

	/* ========================================= *
	 * Get/Set Frequency                         *
	 * ========================================= */
	float Frequency(void){ return frequency; }
	float Frequency(const float frequency){
		this -> frequency = frequency;
		return this -> frequency;
	}

	/* ========================================= *
	 * Get/Set Q                                 *
	 * ========================================= */
	float Q(void){ return q; }
	float Q(const float q){
		this -> q = q;
		return this -> q;
	}

	/* ========================================= *
	 * Get/Set SamplingRate                      *
	 * ========================================= */
	float SamplingRate(void){ return samplingrate; }
	float SamplingRate(const float samplingrate){
		this -> samplingrate = samplingrate;
		return this -> samplingrate;
	}

	/* ========================================= *
	 * AudioIn                                   *
	 * ========================================= */
	virtual void AudioIn(const float *input, const int size) = 0;

	/* ========================================= *
	 * Osc                                       *
	 * ========================================= */
	virtual void Osc(const ofxOscMessage &m) = 0;
};

#endif
