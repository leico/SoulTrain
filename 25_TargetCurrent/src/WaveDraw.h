//
//  WaveDraw.h
//  basic
//
//  Created by leico on 2015/07/29.
//
//

#ifndef basic_WaveDraw_h
#define basic_WaveDraw_h

#include "ofMain.h"
#include "ofxOsc.h"
#include "Change.h"
#include "BaseDraw.h"


class WaveDraw : public BaseDraw{

	private:
		ofMesh   signalwave;
		std :: vector<ofPoint> vertices;

		float   amplitude;

		float sum;

	public:
		/* =========================================== *
		 * Constructor/Destructor                      *
		 * =========================================== */
	 	 WaveDraw(){};
		~WaveDraw(){};

		/* =========================================== *
		 * Clear                                       *
		 * =========================================== */
		void Clear(void){
			signalwave.clear();
			vertices  .clear();
		}

		/* =========================================== *
		 * Get/Set Size                                *
		 * =========================================== */
		int Size(void){ return vertices.size(); }
		int Size(const int size){
			vertices.resize(size);
			return vertices.size();
		}

		/* =========================================== *
		 * Get/Set Wave Amplitude                      *
		 * =========================================== */
		float Amplitude(void){ return amplitude; }
		float Amplitude(const float amplitude){
			this -> amplitude = amplitude;
			return this -> amplitude;
		}

		/* =========================================== *
		 * Get/Set DrawMode                            *
		 * =========================================== */
		ofPrimitiveMode Mode(void){ return signalwave.getMode(); }
		ofPrimitiveMode Mode(ofPrimitiveMode mode){
			signalwave.setMode(mode);
			return signalwave.getMode();
		}

		
		/* =========================================== *
		 * Setup                                       *
		 * =========================================== */
		void Setup(const int size, const float amplitude, ofPrimitiveMode mode){

			Size     (size);
			Amplitude(amplitude);
			Mode     (mode);

			for(int i = 0 ; i < vertices.size() ; ++ i){
				vertices[i].x = i;
				signalwave.addColor(ofColor(255));
			}
		}


		/* =========================================== *
		 * Update                                      *
		 * =========================================== */
		void Update(void){
			BaseDraw :: Update();

			for(int i = 0 ; i < Size() - 1 ; i += 2){
				vertices[i    ].y = vertices[i + 2    ].y;
				vertices[i + 1].y = vertices[i + 2 + 1].y;
			}
			
			float tmp = sum / Size() * Amplitude();
			vertices[Size() - 2].y =  tmp;
			vertices[Size() - 1].y = -tmp;

			signalwave.clearVertices();
			signalwave.addVertices(vertices);
			
		}

		/* =========================================== *
		 * Get OscMessage                              *
		 * =========================================== */
		void Osc(const ofxOscMessage& m){}


		/* =========================================== *
		 * Draw                                        *
		 * =========================================== */
		void Draw(void){

			ofPushStyle ();
			ofPushMatrix();

				ofPoint pos    = BasePos()   .Current() + Pos()   .Current();
				ofPoint rotate = BaseRotate().Current() + Rotate().Current();
				ofPoint scale  = BaseScale() .Current() * Scale() .Current();

				ofTranslate( pos );
				ofRotateX  ( rotate.x );
				ofRotateY  ( rotate.y );
				ofRotateZ  ( rotate.z );
				ofScale    (scale.x, scale.y, scale.z);

				ofSetColor( Color().Current() );
				signalwave.draw();

			ofPopMatrix();
			ofPopStyle ();
		}

		/* =========================================== *
		 * AudioIn                                     *
		 * =========================================== */
		void AudioIn(
				const float *raw
			, int          size
			, bool         lowattack
			, bool         highattack
		){

			sum = 0;
			for(int i = 0 ; i < size ; ++ i)
				sum += abs(raw[i]);

			if(lowattack)
				Rotate().Current(
					ofPoint(
						  ofRandom(-10, 10)
						, ofRandom(-10, 10)
						, ofRandom(-10, 10)
					)
				);

			if(highattack)
				Pos().Current(
					ofPoint(
							ofRandom(-300, 300)
						, ofRandom(-300, 300)
						, ofRandom(-300, 300)
					)
				);
		}
};

#endif
