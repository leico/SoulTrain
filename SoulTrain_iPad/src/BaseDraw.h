//
//  BaseDraw.h
//  basic
//
//  Created by leico on 2015/07/29.
//
//

#ifndef __basic__BaseDraw__
#define __basic__BaseDraw__

#include "ofMain.h"
#include "Change.h"
#include "ofxOsc.h"

class BaseDraw{

	typedef unsigned char u_char;
	
	private:

		Change<ofPoint> base_pos;
		Change<ofPoint> base_rotate;
		Change<ofPoint> base_scale;

		Change<ofPoint> pos;
		Change<ofPoint> rotate;
		Change<ofPoint> scale;

		Change<ofColor> color;

		bool blur;

		std :: string address;

	public:
		/* ======================================= *
		 * Constructor/Destructor                  *
		 * ======================================= */
		        inline  BaseDraw();
		virtual inline ~BaseDraw();

		/* ======================================= *
		 * Get/Set OscAddress                      *
		 * ======================================= */
		inline const std :: string& OscAddress(void);
		inline const std :: string& OscAddress(const std :: string& address);

		/* ======================================= *
		 * Get/Set BasePos                         *
		 * ======================================= */
		inline Change<ofPoint>& BasePos(void);
		inline Change<ofPoint>& BasePos(const Change<ofPoint>& pos);
		inline Change<ofPoint>& BasePos(const ofPoint& target, const float resist);


		/* ======================================= *
		 * Get/Set BaseRotate                      *
		 * ======================================= */
		inline Change<ofPoint>& BaseRotate(void);
		inline Change<ofPoint>& BaseRotate(const Change<ofPoint>& rotate);
		inline Change<ofPoint>& BaseRotate(const ofPoint& target, const float resist);


		/* ======================================= *
		 * Get/Set BaseScale                       *
		 * ======================================= */
		inline Change<ofPoint>& BaseScale(void);
		inline Change<ofPoint>& BaseScale(const Change<ofPoint>& scale);
		inline Change<ofPoint>& BaseScale(const ofPoint& target, const float resist);

		/* ======================================= *
		 * Get/Set Pos                             *
		 * ======================================= */
		inline Change<ofPoint>& Pos(void);
		inline Change<ofPoint>& Pos(const Change<ofPoint>& pos);
	
			/* ======================================= *
			 * TargetPos                               *
			 * ======================================= */
			inline Change<ofPoint>& TargetPos(const ofPoint& target, const float resist);
	
			/* ======================================= *
			 * CurrentPos                              *
			 * ======================================= */
			inline Change<ofPoint>& CurrentPos(const ofPoint& current, const float resist);

		/* ======================================= *
		 * Get/Set Rotate                          *
		 * ======================================= */
		inline Change<ofPoint>& Rotate(void);
		inline Change<ofPoint>& Rotate(const Change<ofPoint>& rotate);

			/* ======================================= *
			 * TargetRotate                            *
			 * ======================================= */
			inline Change<ofPoint>& TargetRotate(const ofPoint& target, const float resist);
	
			/* ======================================= *
			 * CurrentRotate                           *
			 * ======================================= */
			inline Change<ofPoint>& CurrentRotate(const ofPoint& current, const float resist);

		/* ======================================= *
		 * Get/Set Scale                           *
		 * ======================================= */
		inline Change<ofPoint>& Scale(void);
		inline Change<ofPoint>& Scale(const Change<ofPoint>& scale);

			/* ======================================= *
			 * TargetScale                             *
			 * ======================================= */
			inline Change<ofPoint>& TargetScale(const ofPoint& target, const float resist);
	
			/* ======================================= *
			 * CurrentScale                            *
			 * ======================================= */
			inline Change<ofPoint>& CurrentScale(const ofPoint& current, const float resist);

		/* ======================================= *
		 * Get/Set Color                           *
		 * ======================================= */
		inline Change<ofColor>& Color(void);
		inline Change<ofColor>& Color(const Change<ofColor>& color);

			/* ======================================= *
			 * TargetColor                             *
			 * ======================================= */
			inline Change<ofColor>& TargetColor(const ofColor& target, const float resist);
	
			/* ======================================= *
			 * CurrentColor                            *
			 * ======================================= */
			inline Change<ofColor>& CurrentColor(const ofColor& current, const float resist);

		/* ======================================= *
		 * get/set Blurflag                        *
		 * ======================================= */
		inline bool Blur(void);
		inline bool Blur(const bool blur);

		/* ======================================= *
		 * Update                                  *
		 * ======================================= */
		inline void Update(void);

		/* ======================================= *
		 * OscMessage                              *
		 * ======================================= */
		virtual void Osc (const ofxOscMessage& m) = 0;


		/* ======================================= *
		 * Draw                                    *
		 * ======================================= */
		virtual void Draw() = 0;

		/* ======================================= *
		 * AudioIn                                 *
		 * ======================================= */
		virtual void AudioIn(
				const float *raw
			, int          size
			, bool         lowattack
			, bool         highattack
		) = 0;

	protected:
		/* ======================================= *
		 * Osc_BasePos                             *
		 * ======================================= */
		inline ofxOscMessage& Osc_BasePos(ofxOscMessage& m, float magnificate);
};

// ------------------------------------------------------------------

/* ======================================= *
 * Constructor/Destructor                  *
 * ======================================= */
BaseDraw :: BaseDraw(){
	{
		ofPoint zero(0, 0, 0);
		ofPoint one (1, 1, 1);

		base_pos   .Setup(zero, zero, 0);
		base_rotate.Setup(zero, zero, 0);
		base_scale .Setup(one, one, 0);

		pos    = base_pos;
		rotate = base_rotate;
		scale  = base_scale;
	}
	{
		ofColor zero(0, 0, 0, 0);

		color  .Setup(zero, zero, 0);
	}
}

BaseDraw :: ~BaseDraw(){
};

// ------------------------------------------------------------------

/* ======================================= *
 * Get/Set OscAddress                      *
 * ======================================= */
const std :: string& BaseDraw :: OscAddress(void){
	return address;
}

const std :: string& BaseDraw :: OscAddress(const std :: string& address){
	this -> address = address;
	return this -> address;
}


// ------------------------------------------------------------------


/* ======================================= *
 * Get/Set BasePos                         *
 * ======================================= */
Change<ofPoint>& BaseDraw :: BasePos(void){
	return base_pos; 
}

Change<ofPoint>& BaseDraw :: BasePos(const Change<ofPoint>& pos){
	base_pos = pos;
	return base_pos;
}

Change<ofPoint>& BaseDraw :: BasePos(const ofPoint& target, const float resist){
	return BasePos(
		Change<ofPoint>(base_pos.Current(), target, resist)
	);
}

// ------------------------------------------------------------------

/* ======================================= *
 * Get/Set BaseRotate                      *
 * ======================================= */
Change<ofPoint>& BaseDraw :: BaseRotate(void){
	return base_rotate; 
}

Change<ofPoint>& BaseDraw :: BaseRotate(const Change<ofPoint>& rotate){
	base_rotate = rotate;
	return base_rotate;
}

Change<ofPoint>& BaseDraw :: BaseRotate(const ofPoint& target, const float resist){
	return BaseRotate(
		Change<ofPoint>(base_rotate.Current(), target, resist)
	);
}

// ------------------------------------------------------------------

/* ======================================= *
 * Get/Set BaseScale                       *
 * ======================================= */
Change<ofPoint>& BaseDraw :: BaseScale(void){
	return base_scale; 
}

Change<ofPoint>& BaseDraw :: BaseScale(const Change<ofPoint>& scale){
	base_scale = scale;
	return base_scale;
}

Change<ofPoint>& BaseDraw :: BaseScale(const ofPoint& target, const float resist){
	return BaseScale(
		Change<ofPoint>(base_scale.Current(), target, resist)
	);
}

// ------------------------------------------------------------------


/* ======================================= *
 * Get/Set Pos                             *
 * ======================================= */
Change<ofPoint>& BaseDraw :: Pos(void){
	return pos; 
}

Change<ofPoint>& BaseDraw :: Pos(const Change<ofPoint>& pos){
	this -> pos = pos;
	return this -> pos;
}


/* ======================================= *
 * TargetPos                               *
 * ======================================= */
Change<ofPoint>& BaseDraw :: TargetPos(const ofPoint& target, const float resist){
	return Pos(
		Change<ofPoint>(Pos().Current(), target, resist)
	);
}

/* ======================================= *
 * CurrentPos                              *
 * ======================================= */
Change<ofPoint>& BaseDraw :: CurrentPos(const ofPoint& current, const float resist){
	return Pos(
		Change<ofPoint>(current, Pos().Target(), resist)
	);
}

// ------------------------------------------------------------------

/* ======================================= *
 * Get/Set Rotate                          *
 * ======================================= */
Change<ofPoint>& BaseDraw :: Rotate(void){
	return rotate; 
}

Change<ofPoint>& BaseDraw :: Rotate(const Change<ofPoint>& rotate){
	       this -> rotate = rotate;
	return this -> rotate;
}

/* ======================================= *
 * TargetRotate                            *
 * ======================================= */
Change<ofPoint>& BaseDraw :: TargetRotate(const ofPoint& target, const float resist){
	return Rotate( 
		Change<ofPoint>(Rotate().Current(), target, resist)
	);
}

/* ======================================= *
 * CurrentRotate                            *
 * ======================================= */
Change<ofPoint>& BaseDraw :: CurrentRotate(const ofPoint& current, const float resist){
	return Rotate(
		Change<ofPoint>(current, Rotate().Target(), resist)
	);
}

// ------------------------------------------------------------------

/* ======================================= *
 * Get/Set Scale                           *
 * ======================================= */
Change<ofPoint>& BaseDraw :: Scale(void){
	return scale;
}

Change<ofPoint>& BaseDraw :: Scale(const Change<ofPoint>& scale){
	this -> scale = scale;
	return this -> scale;
}

/* ======================================= *
 * TargetScale                             *
 * ======================================= */
Change<ofPoint>& BaseDraw :: TargetScale(const ofPoint& target, const float resist){
	return Scale(
		Change<ofPoint>(Scale().Current(), target, resist)
	);
}

/* ======================================= *
 * CurrentScale                            *
 * ======================================= */
Change<ofPoint>& BaseDraw :: CurrentScale(const ofPoint& current, const float resist){
	return Scale(
		Change<ofPoint>(current, Scale().Target(), resist)
	);
}

// ------------------------------------------------------------------


/* ======================================= *
 * Get/Set Color                           *
 * ======================================= */
Change<ofColor>& BaseDraw :: Color(void){
	return color; 
}

Change<ofColor>& BaseDraw :: Color(const Change<ofColor>& color){
	this -> color = color;
	return this -> color;
}

/* ======================================= *
 * TargetColor                             *
 * ======================================= */
Change<ofColor>& BaseDraw :: TargetColor(const ofColor& target, const float resist){
	return Color(
		Change<ofColor>(Color().Current(), target, resist)
	);
}

/* ======================================= *
 * CurrentColor                            *
 * ======================================= */
Change<ofColor>& BaseDraw :: CurrentColor(const ofColor& current, const float resist){
	return Color(
		Change<ofColor>(current, Color().Target(), resist)
	);
}

// ------------------------------------------------------------------

/* ======================================= *
 * get/set Blurflag                        *
 * ======================================= */
bool BaseDraw :: Blur(void){
	return blur;
}

bool BaseDraw :: Blur(const bool blur){
	this -> blur = blur;
	return this -> blur;
}

// ------------------------------------------------------------------
/* ======================================= *
 * Update                                  *
 * ======================================= */
void BaseDraw :: Update(void){
	base_pos   .Update();
	base_rotate.Update();
	base_scale .Update();

	pos    .Update();
	rotate .Update();
	scale  .Update();
	color  .Update();

}



// ------------------------------------------------------------------
/* ======================================= *
 * Osc_BasePos                             *
 * ======================================= */
ofxOscMessage& BaseDraw :: Osc_BasePos(ofxOscMessage& m, float magnificate){

	const string basepos = address + "Base/Pos/";

	const string address = m.getAddress();
	const float  value   = m.getArgAsFloat(0);

	if( address == basepos + "X/x"){
		BasePos(
				ofPoint(value * magnificate, BasePos().Target().y, BasePos().Target().z)
			, BasePos().Resist()
		);


		m.clear();
		return m;
	}

	if( address == basepos + "Y/x"){
		BasePos(
				ofPoint(BasePos().Target().x, value * magnificate, BasePos().Target().z)
			, BasePos().Resist()
		);

		m.clear();
		return m;
	}

	if( address == basepos + "Z/x"){
		BasePos(
				ofPoint(BasePos().Target().x, BasePos().Target().y, value * magnificate)
			, BasePos().Resist()
		);

		m.clear();
		return m;
	}

	return m;
}



#endif /* defined(__basic__BaseDraw__) */
