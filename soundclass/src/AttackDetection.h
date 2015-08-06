//
//  AttackDetection.h
//  basic
//
//  Created by leico on 2015/07/28.
//
//

#ifndef __basic__AttackDetection__
#define __basic__AttackDetection__

#include "ofMain.h"
#include "BiQuadFilter.h"

class AttackDetection : protected BiQuadFilter{

	private:

	float threshold;

	public:
	enum FilterType{
		LOWPASS,
		HIGHPASS
	};

	enum ProcessType{
		AVERAGE,
		MAXVALUE
	};

	inline          AttackDetection(void);
	inline virtual ~AttackDetection(void);

	template<FilterType>
	void Setup(float freq, float q, float samplingrate);

	inline float Threshold(void);
	inline float Threshold(float threshold);

	template<ProcessType>
	bool Process(float *samples, int buffersize);

};


/* ============================================ *
 * Constructor/Destructor                       *
 * ============================================ */
AttackDetection ::  AttackDetection(void){}
AttackDetection :: ~AttackDetection(void){}

/* ============================================ *
 * Get/Set Threshold                            *
 * ============================================ */
float AttackDetection :: Threshold(void)           { return threshold; }
float AttackDetection :: Threshold(float threshold){
	this -> threshold = threshold;
	return this -> threshold; 
}


#endif /* defined(__basic__AttackDetection__) */
