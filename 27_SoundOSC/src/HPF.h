//
//  HPF.h
//  basic
//
//  Created by leico on 2015/07/31.
//
//

#ifndef basic_HPF_h
#define basic_HPF_h

#include "ofMain.h"
#include "Filter.h"

class HPF : public Filter{
	
	private:
	vector<float> data;
	float attack_threshold;

	public:
	 HPF(void){};
	~HPF(void){};

	/* =========================================== *
	 * Get/Set AttackThreshold                     *
	 * =========================================== */
	float AttackThreshold(void){ return attack_threshold; }
	float AttackThreshold(const float threshold){
		attack_threshold = threshold;
		return attack_threshold;
	}

	/* =========================================== *
	 * Setup                                       *
	 * =========================================== */
	void Setup(float attack_threshold){
		filter.HighPass(Frequency(), Q(), SamplingRate());
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
			if( abs(data[i]) > attack_threshold)
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

		if(m.getAddress() == "/HPF/Frequency/x"){
			Frequency( m.getArgAsFloat(0) * 100 );
			Setup(AttackThreshold());
			ofLogVerbose() << Frequency();
			return;
		}

		if(m.getAddress() == "/HPF/Q/x"){
			Q( m.getArgAsFloat(0) );
			Setup(AttackThreshold());
			ofLogVerbose() << Q();
			return;
		}

		if(m.getAddress() == "/HPF/Threshold/x"){
			AttackThreshold( m.getArgAsFloat(0) );

			ofLogVerbose() << AttackThreshold();
			return;
		}
	}


};

#endif
