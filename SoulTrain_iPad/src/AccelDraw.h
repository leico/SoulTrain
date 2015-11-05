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
	std :: vector<ofPoint>      vertices;
	std :: vector<ofFloatColor> colors;

	ofPoint center;

	struct param{
		bool kick;
		bool hat;
		float amp;
	} rotateparam, scaleparam;


	float amplitude;

	public:

	/* ========================================== *
	 * Constructor/Destructor                     *
	 * ========================================== */
	 AccelDraw() : BaseDraw("/Accel/") {};
	~AccelDraw(){};

	/* ========================================== *
	 * Clear                                      *
	 * ========================================== */
	void Clear(void){
		accellog.clear();
		vertices.clear();
	}

	/* ========================================== *
	 * Get/Set Size                               *
	 * ========================================== */
	int Size(void){ return vertices.size(); }
	int Size(const int size){
		vertices.resize(size);
		colors  .resize(size);
		return vertices.size();
	}

	/* ========================================== *
	 * Get/Set Amplitude                          *
	 * ========================================== */
	float Amplitude(void){ return amplitude; }
	float Amplitude(const float amplitude){
		this -> amplitude = amplitude;
		return this -> amplitude;
	}

	/* ========================================== *
	 * Get/Set Mode                               *
	 * ========================================== */
	ofPrimitiveMode Mode(void){ return accellog.getMode(); }
	ofPrimitiveMode Mode(ofPrimitiveMode mode){
		accellog.setMode(mode);
		return accellog.getMode();
	}

	/* ========================================== *
	 * Setup                                      *
	 * ========================================== */
	void Setup(const int size, const float amplitude, ofPrimitiveMode mode){

		Size     (size);
		Amplitude(amplitude);
		Mode     (mode);

		ofxAccelerometer.setup();

		for(int i = 0 ; i < vertices.size() ; ++ i)
			colors[i] = ofColor(255);
	}

	/* ========================================== *
	 * Update                                     *
	 * ========================================== */
	void Update(void){
		BaseDraw :: Update();

		for(int i = 0 ; i < Size() - 1 ; ++ i){
			vertices[i] = vertices[i + 1];
			colors  [i] = colors  [i + 1];
		}
		vertices[Size() - 1] = (center - ofxAccelerometer.getForce()) * Amplitude();
		colors  [Size() - 1] = Color().Current();

		accellog.clearVertices();
		accellog.addVertices(vertices);

		accellog.clearColors();
		accellog.addColors(colors);
	}

	/* ========================================== *
	 * Osc                                        *
	 * ========================================== */
	void Osc(const ofxOscMessage& m){

    ofxOscMessage osc = m;

		const string address = m.getAddress();
		const float  value   = m.getArgAsFloat(0);

		const string accel = "/Accel/";


		const string rotate = accel + "Rotate/";
		const string scale  = accel + "Scale/";

    if( Osc_Rotate(osc, 10).getNumArgs() == 0) return;

		if( address == rotate + "Kick/x"){
			rotateparam.kick = value == 1;
			return;
		}
		if( address == rotate + "Hat/x"){
			rotateparam.hat = value == 1;
			return;
		}
		if( address == rotate + "Swing/x"){
			rotateparam.amp = value * 10;
			return;
		}

    if( Osc_Scale(osc, 1).getNumArgs() == 0) return;


		if( address == scale + "Kick/x"){
			scaleparam.kick = value == 1;
			return;
		}
		if( address == scale + "Hat/x"){
			scaleparam.hat = value == 1;
			return;
		}
		if( address == scale + "Swing/x"){
			scaleparam.amp = value;
			return;
		}



		if( address == accel + "Amplitude/x"){
			Amplitude(value * 100);
			return;
		}

		if( address == accel + "Resist/x"){
			BasePos   ().Resist( value );
			BaseRotate().Resist( value );
			BaseRotate().Resist( value );

			Pos   ().Resist( value );
			Rotate().Resist( value );
			Rotate().Resist( value );

			Color().Resist ( value );
		}



		const string  color  = accel + "Color/";
		const ofColor target = Color().Target();
		const float   resist = Color().Resist();

		if( address == color + "R/x"){
			TargetColor( ofColor(value * 255, target.g, target.b, target.a), resist);
			return;
		}
		if( address == color + "G/x"){
			TargetColor( ofColor(target.r, value * 255, target.b, target.a), resist);
			return;
		}
		if( address == color + "B/x"){
			TargetColor( ofColor(target.r, target.g, value * 255, target.a), resist);
			return;
		}
		if( address == color + "A/x"){
			TargetColor( ofColor(target.r, target.g, target.b, value * 255), resist);
			return;
		}


		if( address == accel + "Set/x")
			center = ofxAccelerometer.getForce();

	
	}

	/* ========================================== *
	 * Draw                                       *
	 * ========================================== */
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

				accellog.draw();

		ofPopMatrix();
		ofPopStyle ();

	}

	/* ========================================== *
	 * AudioIn                                    *
	 * ========================================== */
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
