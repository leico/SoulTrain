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

		ofPoint base;
		float   amplitude;

		float sum;

	public:
	 	 WaveDraw(){};
		~WaveDraw(){};

		void Clear(void){
			signalwave.clear();
			vertices  .clear();
		}

		int Size(void)    { return vertices.size(); }
		int Size(const int size){
			vertices.resize(size);
			return vertices.size();
		}

		ofPoint& Base(void){ return base; }
		ofPoint& Base(const ofPoint& base){
			this -> base = base;
			return this -> base;
		}

		float Amplitude(void){ return amplitude; }
		float Amplitude(const float amplitude){
			this -> amplitude = amplitude;
			return this -> amplitude;
		}

		ofPrimitiveMode Mode(void){ return signalwave.getMode(); }
		ofPrimitiveMode Mode(ofPrimitiveMode mode){
			signalwave.setMode(mode);
			return signalwave.getMode();
		}

		
		

		void Setup(const int size, const ofPoint& base, const float amplitude, ofPrimitiveMode mode){
			
			Size     (size);
			Base     (base);
			Amplitude(amplitude);
			Mode     (mode);

			for(int i = 0 ; i < vertices.size() ; ++ i){
				vertices[i].x = i;
				signalwave.addColor(ofColor(255));
			}
		}




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


		void Osc(const ofxOscMessage& m){}

		void Draw(void){

			ofPushStyle ();
			ofPushMatrix();

				ofTranslate( base);
					
				ofTranslate(    Pos().Current() );
				ofRotateX  ( Rotate().Current().x );
				ofRotateY  ( Rotate().Current().y );
				ofRotateZ  ( Rotate().Current().z );
				ofScale(
						Scale().Current().x
					, Scale().Current().y
					, Scale().Current().z
				);

				ofSetColor( Color().Current() );
				signalwave.draw();

			ofPopMatrix();
			ofPopStyle ();
		}


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
