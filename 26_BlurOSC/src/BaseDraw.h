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

	public:
		/* ======================================= *
		 * Constructor/Destructor                  *
		 * ======================================= */
		 BaseDraw(){
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

		virtual ~BaseDraw(){};

		/* ======================================= *
		 * Get/Set BasePos                         *
		 * ======================================= */
		Change<ofPoint>& BasePos(void){ return base_pos; }
		Change<ofPoint>& BasePos(const Change<ofPoint>& pos){
			base_pos = pos;
			return base_pos;
		}
		Change<ofPoint>& BasePos(const ofPoint& target, const float resist){
			return BasePos( Change<ofPoint>(base_pos.Current(), target, resist) );
		}
		/* ======================================= *
		 * Get/Set BaseRotate                      *
		 * ======================================= */
		Change<ofPoint>& BaseRotate(void){ return base_rotate; }
		Change<ofPoint>& BaseRotate(const Change<ofPoint>& rotate){
			base_rotate = rotate;
			return base_rotate;
		}
		Change<ofPoint>& BaseRotate(const ofPoint& target, const float resist){
			return BaseRotate( Change<ofPoint>(base_rotate.Current(), target, resist) );
		}

		/* ======================================= *
		 * Get/Set BaseScale                       *
		 * ======================================= */
		Change<ofPoint>& BaseScale(void){ return base_scale; }
		Change<ofPoint>& BaseScale(const Change<ofPoint>& scale){
			base_scale = scale;
			return base_scale;
		}
		Change<ofPoint>& BaseScale(const ofPoint& target, const float resist){
			return BaseScale( Change<ofPoint>(base_scale.Current(), target, resist) );
		}

		/* ======================================= *
		 * Get/Set Pos                             *
		 * ======================================= */
		Change<ofPoint>& Pos(void){ return pos; }
		Change<ofPoint>& Pos(const Change<ofPoint>& pos){
			this -> pos = pos;
			return this -> pos;
		}

		/* ======================================= *
		 * TargetPos                               *
		 * ======================================= */
		Change<ofPoint>& TargetPos(const ofPoint& target, const float resist){
			return Pos( Change<ofPoint>(Pos().Current(), target, resist) );
		}

		/* ======================================= *
		 * CurrentPos                              *
		 * ======================================= */
		Change<ofPoint>& CurrentPos(const ofPoint& current, const float resist){
			return Pos( Change<ofPoint>(current, Pos().Target(), resist) );
		}

		/* ======================================= *
		 * Get/Set Rotate                          *
		 * ======================================= */
		Change<ofPoint>& Rotate(void){ return rotate; }
		Change<ofPoint>& Rotate(const Change<ofPoint>& rotate){
			this -> rotate = rotate;
			return this -> rotate;
		}

		/* ======================================= *
		 * TargetRotate                            *
		 * ======================================= */
		Change<ofPoint>& TargetRotate(const ofPoint& target, const float resist){
			return Rotate( Change<ofPoint>(Rotate().Current(), target, resist) );
		}

		/* ======================================= *
		 * CurrentRotate                            *
		 * ======================================= */
		Change<ofPoint>& CurrentRotate(const ofPoint& current, const float resist){
			return Rotate( Change<ofPoint>(current, Rotate().Target(), resist) );
		}

		/* ======================================= *
		 * Get/Set Scale                           *
		 * ======================================= */
		Change<ofPoint>& Scale(void){ return scale; }
		Change<ofPoint>& Scale(const Change<ofPoint>& scale){
			this -> scale = scale;
			return this -> scale;
		}

		/* ======================================= *
		 * TargetScale                             *
		 * ======================================= */
		Change<ofPoint>& TargetScale(const ofPoint& target, const float resist){
			return Scale( Change<ofPoint>(Scale().Current(), target, resist) );
		}

		/* ======================================= *
		 * CurrentScale                            *
		 * ======================================= */
		Change<ofPoint>& CurrentScale(const ofPoint& current, const float resist){
			return Scale( Change<ofPoint>(current, Scale().Target(), resist) );
		}

		/* ======================================= *
		 * Get/Set Color                           *
		 * ======================================= */
		Change<ofColor>& Color(void){ return color; }
		Change<ofColor>& Color(const Change<ofColor>& color){
			this -> color = color;
			return this -> color;
		}

		/* ======================================= *
		 * TargetColor                             *
		 * ======================================= */
		Change<ofColor>& TargetColor(const ofColor& target, const float resist){
			return Color( Change<ofColor>(Color().Current(), target, resist) );
		}

		/* ======================================= *
		 * CurrentColor                            *
		 * ======================================= */
		Change<ofColor>& CurrentColor(const ofColor& current, const float resist){
			return Color( Change<ofColor>(current, Color().Target(), resist) );
		}

		/* ======================================= *
		 * Update                                  *
		 * ======================================= */
		void Update(void){
			pos    .Update();
			rotate .Update();
			scale  .Update();
			color  .Update();

		}

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
};

#endif /* defined(__basic__BaseDraw__) */
