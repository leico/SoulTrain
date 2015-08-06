//
//  AccelDraw.h
//  basic
//
//  Created by leico on 2015/07/31.
//
//

#ifndef basic_AccelDraw_h
#define basic_AccelDraw_h

class AccelDraw : public BaseDraw{

	private:
	ofMesh accellog;
	std :: vector<ofPoint> vertices;

	float amplitude;

	public:

	 AccelDraw(){};
	~AccelDraw(){};

	void Clear(void){
		accellog.clear();
		vertices.clear();
	}

	int Size(void){ return vertices.size(); }
	int Size(const int size){
		vertices.resize(size);
		return vertices.size();
	}

	float Amplitude(void){ return amplitude; }
	float Amplitude(const float amplitude){
		this -> amplitude = amplitude;
		return this -> amplitude;
	}

	ofPrimitiveMode Mode(void){ return accellog.getMode(); }
	ofPrimitiveMode Mode(ofPrimitiveMode mode){
		accellog.setMode(mode);
		return accellog.getMode();
	}

	void Setup(const int size, const float amplitude, ofPrimitiveMode mode){

		Size     (size);
		Amplitude(amplitude);
		Mode     (mode);

		ofxAccelerometer.setup();

		for(int i = 0 ; i < vertices.size() ; ++ i)
			accellog.addColor(ofColor(255));
	}

	void Update(void){
		BaseDraw :: Update();

		for(int i = 0 ; i < Size() - 1 ; ++ i){
			vertices[i] = vertices[i + 1];
		}
		vertices[Size() - 1] = ofxAccelerometer.getForce() * Amplitude();

		accellog.clearVertices();
		accellog.addVertices(vertices);
	}


	void Osc(const ofxOscMessage& m){}


	void Draw(void){
		
		ofPushStyle();
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
				accellog.draw();

		ofPopMatrix();
		ofPopStyle ();

	}

	void AudioIn(
			const float* raw
		, int          size
		, bool         lowattack
		, bool         highattack
	){
		
		if(lowattack)
			Rotate().Target(
				ofPoint(
					  ofRandom(-180, 180)
					, ofRandom(-180, 180)
					, ofRandom(-180, 180)
				)
			);

		if(highattack)
			Scale().Target(
				ofPoint(
					  ofRandom(-3, 3)
					, ofRandom(-3, 3)
					, ofRandom(-3, 3)
				)
			);

	}
	



};


#endif
