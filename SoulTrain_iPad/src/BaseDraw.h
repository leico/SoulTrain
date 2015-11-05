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

		Change<ofPoint> _base_pos;
		Change<ofPoint> _base_rotate;
		Change<ofPoint> _base_scale;

		Change<ofPoint> _pos;
		Change<ofPoint> _rotate;
		Change<ofPoint> _scale;

		Change<ofColor> _color;

		bool _blur;

		std :: string _address;

	public:
		/* ======================================= *
		 * Constructor/Destructor                  *
		 * ======================================= */
		        inline  BaseDraw();
            inline  BaseDraw(const std :: string& address);
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

    // ------------------------------------------------------------------------
		/* ======================================= *
		 * Osc_BasePos                             *
		 * ======================================= */
		inline ofxOscMessage& Osc_BasePos   (ofxOscMessage& m, float magnificate);

		/* ======================================= *
		 * Osc_BaseRotate                          *
		 * ======================================= */
    inline ofxOscMessage& Osc_BaseRotate(ofxOscMessage& m, float magnificate);

		/* ======================================= *
		 * Osc_BaseScale                           *
		 * ======================================= */
    inline ofxOscMessage& Osc_BaseScale (ofxOscMessage& m, float magnificate);

    // ------------------------------------------------------------------------
		/* ======================================= *
		 * Osc_Pos                                 *
		 * ======================================= */
    inline ofxOscMessage& Osc_Pos(ofxOscMessage& m, float magnificate);

		/* ======================================= *
		 * Osc_Rotate                              *
		 * ======================================= */
    inline ofxOscMessage& Osc_Rotate(ofxOscMessage& m, float magnificate);

    
};

// ------------------------------------------------------------------

/* ======================================= *
 * Constructor/Destructor                  *
 * ======================================= */
BaseDraw :: BaseDraw(){
	{
		ofPoint zero(0, 0, 0);
		ofPoint one (1, 1, 1);

		_base_pos   .Setup(zero, zero, 0);
		_base_rotate.Setup(zero, zero, 0);
		_base_scale .Setup(one, one, 0);

		_pos    = _base_pos;
		_rotate = _base_rotate;
		_scale  = _base_scale;
	}
	{
		ofColor zero(0, 0, 0, 0);

		_color  .Setup(zero, zero, 0);
	}
}


BaseDraw :: BaseDraw(const std :: string& address) : 
_address(address)
{
	{
		ofPoint zero(0, 0, 0);
		ofPoint one (1, 1, 1);

		_base_pos   .Setup(zero, zero, 0);
		_base_rotate.Setup(zero, zero, 0);
		_base_scale .Setup(one, one, 0);

		_pos    = _base_pos;
		_rotate = _base_rotate;
		_scale  = _base_scale;
	}
	{
		ofColor zero(0, 0, 0, 0);

		_color  .Setup(zero, zero, 0);
	}

}

BaseDraw :: ~BaseDraw(){
};

// ------------------------------------------------------------------

/* ======================================= *
 * Get/Set OscAddress                      *
 * ======================================= */
const std :: string& BaseDraw :: OscAddress(void){
	return _address;
}

const std :: string& BaseDraw :: OscAddress(const std :: string& address){
	       _address = address;
	return _address;
}


// ------------------------------------------------------------------


/* ======================================= *
 * Get/Set BasePos                         *
 * ======================================= */
Change<ofPoint>& BaseDraw :: BasePos(void){
	return _base_pos; 
}

Change<ofPoint>& BaseDraw :: BasePos(const Change<ofPoint>& basepos){
	       _base_pos = basepos;
	return _base_pos;
}

Change<ofPoint>& BaseDraw :: BasePos(const ofPoint& target, const float resist){
	return BasePos(
		Change<ofPoint>(_base_pos.Current(), target, resist)
	);
}

// ------------------------------------------------------------------

/* ======================================= *
 * Get/Set BaseRotate                      *
 * ======================================= */
Change<ofPoint>& BaseDraw :: BaseRotate(void){
	return _base_rotate; 
}

Change<ofPoint>& BaseDraw :: BaseRotate(const Change<ofPoint>& baserotate){
	       _base_rotate = baserotate;
	return _base_rotate;
}

Change<ofPoint>& BaseDraw :: BaseRotate(const ofPoint& target, const float resist){
	return BaseRotate(
		Change<ofPoint>(_base_rotate.Current(), target, resist)
	);
}

// ------------------------------------------------------------------

/* ======================================= *
 * Get/Set BaseScale                       *
 * ======================================= */
Change<ofPoint>& BaseDraw :: BaseScale(void){
	return _base_scale; 
}

Change<ofPoint>& BaseDraw :: BaseScale(const Change<ofPoint>& basescale){
	       _base_scale = basescale;
	return _base_scale;
}

Change<ofPoint>& BaseDraw :: BaseScale(const ofPoint& target, const float resist){
	return BaseScale(
		Change<ofPoint>(_base_scale.Current(), target, resist)
	);
}

// ------------------------------------------------------------------


/* ======================================= *
 * Get/Set Pos                             *
 * ======================================= */
Change<ofPoint>& BaseDraw :: Pos(void){
	return _pos; 
}

Change<ofPoint>& BaseDraw :: Pos(const Change<ofPoint>& pos){
	       _pos = pos;
	return _pos;
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
	return _rotate; 
}

Change<ofPoint>& BaseDraw :: Rotate(const Change<ofPoint>& rotate){
	       _rotate = rotate;
	return _rotate;
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
	return _scale;
}

Change<ofPoint>& BaseDraw :: Scale(const Change<ofPoint>& scale){
	       _scale = scale;
	return _scale;
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
	return _color; 
}

Change<ofColor>& BaseDraw :: Color(const Change<ofColor>& color){
	       _color = color;
	return _color;
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
	return _blur;
}

bool BaseDraw :: Blur(const bool blur){
	       _blur = blur;
	return _blur;
}

// ------------------------------------------------------------------
/* ======================================= *
 * Update                                  *
 * ======================================= */
void BaseDraw :: Update(void){
	_base_pos   .Update();
	_base_rotate.Update();
	_base_scale .Update();

	_pos    .Update();
	_rotate .Update();
	_scale  .Update();
	_color  .Update();

}



// ------------------------------------------------------------------
/* ======================================= *
 * Osc_BasePos                             *
 * ======================================= */
ofxOscMessage& BaseDraw :: Osc_BasePos(ofxOscMessage& m, float magnificate){

	const string basepos = _address + "Base/Pos/";

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

/* ======================================= *
 * Osc_BaseRotate                          *
 * ======================================= */
ofxOscMessage& BaseDraw :: Osc_BaseRotate(ofxOscMessage& m, float magnificate){

  const string baserotate = _address + "Base/Rotate/";
  
  const string address = m.getAddress();
  const float  value   = m.getArgAsFloat(0);

  if( address == baserotate + "X/x"){
    BaseRotate(
        ofPoint(value * magnificate, BaseRotate().Target().y, BaseRotate().Target().z)
      , BaseRotate().Resist()
    );

    m.clear();
    return m;
  }

  if( address == baserotate + "Y/x"){
    BaseRotate(
        ofPoint(BaseRotate().Target().x, value * magnificate, BaseRotate().Target().z)
      , BaseRotate().Resist()
    );

    m.clear();
    return m;
  }

  if( address == baserotate + "Z/x"){
    BaseRotate( 
        ofPoint(BaseRotate().Target().x, BaseRotate().Target().y, value * magnificate)
      , BaseRotate().Resist() 
    );

    m.clear();
    return m;
  }

  return m;
}

/* ======================================= *
 * Osc_BaseScale                           *
 * ======================================= */
ofxOscMessage& BaseDraw :: Osc_BaseScale(ofxOscMessage& m, float magnificate){

  const string basescale = _address + "Base/Scale/";

  const string address = m.getAddress();
  const float  value   = m.getArgAsFloat(0);

  if( address == basescale + "X/x"){
    BaseScale( 
        ofPoint(value * magnificate, BaseScale().Target().y, BaseScale().Target().z)
      , BaseScale().Resist()
    );

    m.clear();
    return m;
  }

  if( address == basescale + "Y/x"){
    BaseScale( 
        ofPoint(BaseScale().Target().x, value * magnificate, BaseScale().Target().z)
      , BaseScale().Resist()
    );

    m.clear();
    return m;
  }

  if( address == basescale + "Z/x"){
    BaseScale( 
        ofPoint(BaseScale().Target().x, BaseScale().Target().y, value * magnificate)
      , BaseScale().Resist()
    );

    m.clear();
    return m;
  }

  return m;
}


// ------------------------------------------------------------------
/* ======================================= *
 * Osc_Pos                                 *
 * ======================================= */
ofxOscMessage& BaseDraw :: Osc_Pos(ofxOscMessage& m, float magnificate){

  const string pos = _address + "Pos/";

  const string address = m.getAddress();
  const float  value   = m.getArgAsFloat(0);

  if( address == pos + "X/x"){
    TargetPos( 
        ofPoint(value * magnificate, Pos().Target().y, Pos().Target().z)
      , Pos().Resist()
    );

    m.clear();
    return m;
  }
  if( address == pos + "Y/x"){
    TargetPos( 
        ofPoint(Pos().Target().x, value * magnificate, Pos().Target().z)
      , Pos().Resist()
    );

    m.clear();
    return m;
  }
  if( address == pos + "Z/x"){
    TargetPos( 
        ofPoint(Pos().Target().x, Pos().Target().y, value * magnificate)
      , Pos().Resist()
    );

    m.clear();
    return m;
  }

  return m;
}

/* ======================================= *
 * Osc_Rotate                              *
 * ======================================= */
ofxOscMessage& BaseDraw :: Osc_Rotate(ofxOscMessage& m, float magnificate){

  const string rotate = _address + "Rotate/";

  const string address = m.getAddress();
  const float  value   = m.getArgAsFloat(0);


  if( address == rotate + "X/x"){
    TargetRotate( 
        ofPoint(value * magnificate, Rotate().Target().y, Rotate().Target().z)
      , Rotate().Resist()
    );

    m.clear();
    return m;
  }
  if( address == rotate + "Y/x"){
    TargetRotate( 
        ofPoint(Rotate().Target().x, value * magnificate, Rotate().Target().z)
      , Rotate().Resist()
    );

    m.clear();
    return m;
  }
  if( address == rotate + "Z/x"){
    TargetRotate( 
        ofPoint(Rotate().Target().x, Rotate().Target().y, value * magnificate)
      , Rotate().Resist()
    );

    m.clear();
    return m;
  }

  return m;
}

#endif /* defined(__basic__BaseDraw__) */
