//
//  LPF.h
//  basic
//
//  Created by leico on 2015/07/31.
//
//

#ifndef basic_LPF_h
#define basic_LPF_h

#include "ofMain.h"
#include "Filter.h"

class LPF : public Filter{

	private:
	vector<float> data;
	float attack_threshold;

	public:	
	 LPF(void){}
	~LPF(void){}

	/* =========================================== *
	 * Get/Set AttackThreshold                     *
	 * =========================================== */
	float AttackThreshold(void){return attack_threshold; }
	float AttackThreshold(const float threshold){
		attack_threshold = threshold;
		return attack_threshold;
	}

	/* =========================================== *
	 * Setup                                       *
	 * =========================================== */
	void Setup(float attack_threshold){
		filter.LowPass(Frequency(), Q(), SamplingRate());
		this -> attack_threshold = attack_threshold;
		return;
	}

	/* =========================================== *
	 * Get Data                                    *
	 * =========================================== */
	const vector<float>& Data(void){
		return data;
	}

	/* =========================================== *
	 * isAttack_Average                            *
	 * =========================================== */
	bool isAttack_Average(void){

		float sum = 0;
		for(int i = 0 ; i < data.size() ; ++ i)
			sum += abs( data[i] );
		
		return (sum / data.size()) > attack_threshold;
	}

	/* =========================================== *
	 * isAttack_Peak                               *
	 * =========================================== */
	bool isAttack_Peak(void){
		for(int i = 0 ; i < data.size() ; ++ i)
			if( abs(data[i]) > attack_threshold )
					return true;

		return false;
	}

	/* =========================================== *
	 * AudioIn                                     *
	 * =========================================== */
	void AudioIn(const float *input, const int buffersize){
		data.resize(buffersize);
		
		for(int i = 0 ; i < data.size() ; ++ i)
			data[i] = filter.Process(input[i]);
	}

	/* =========================================== *
	 * Osc                                         *
	 * =========================================== */
	void Osc(const ofxOscMessage &m){

		

		if(m.getAddress() == "/LPF/Frequency/x"){
			Frequency( m.getArgAsFloat(0) * 100 );
			Setup(AttackThreshold());
			return;
		}

		if(m.getAddress() == "/LPF/Q/x"){
			Q( m.getArgAsFloat(0) );
			Setup(AttackThreshold());
			return;
		}

		if(m.getAddress() == "/LPF/Threshold/x"){
			AttackThreshold( m.getArgAsFloat(0) );
			return;
		}
	}

	
};

#endif
