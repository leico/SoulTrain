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
		Change<ofPoint> pos;
		Change<ofPoint> rotate;
		Change<ofPoint> scale;
		Change<ofColor> color;
		Change<u_char>  opacity;

	public:
		/* ======================================= *
		 * Constructor/Destructor                  *
		 * ======================================= */
		 BaseDraw(){
			 {
				 ofPoint zero(0, 0, 0);
				 ofPoint one (1, 1, 1);

				 pos  .Setup(zero, zero, 0);
				 rotate.Setup(zero, zero, 0);
				 scale .Setup(one, one, 0);
			 }
			 {
			 	ofColor zero(0, 0, 0, 0);

				color  .Setup(zero, zero, 0);
				opacity.Setup(255, 255, 0);
			 }
		 }

		virtual ~BaseDraw(){};

		/* ======================================= *
		 * Get/Set Pos                             *
		 * ======================================= */
		Change<ofPoint>& Pos(void){ return pos; }
		Change<ofPoint>& Pos(const ofPoint& current, const ofPoint& target, const float resist){
			this -> pos.Setup(current, target, resist);
			return this -> pos;
		}

		/* ======================================= *
		 * Get/Set Rotate                          *
		 * ======================================= */
		Change<ofPoint>& Rotate(void){ return rotate; }
		Change<ofPoint>& Rotate(const ofPoint& current, const ofPoint& target, const float resist){
			this -> rotate.Setup(current, target, resist);
			return this -> rotate;
		}

		/* ======================================= *
		 * Get/Set Scale                           *
		 * ======================================= */
		Change<ofPoint>& Scale(void){ return scale; }
		Change<ofPoint>& Scale(const ofPoint& current, const ofPoint& target, const float resist){
			this -> scale.Setup(current, target, resist);
			return this -> scale;
		}

		/* ======================================= *
		 * Get/Set Color                           *
		 * ======================================= */
		Change<ofColor>& Color(void){ return color; }
		Change<ofColor>& Color(const ofColor& current,  const ofColor& target, const float resist){
			this -> color.Setup(current, target, resist);
			return this -> color;
		}

		/* ======================================= *
		 * Get/Set Opacity                         *
		 * ======================================= */
		Change<unsigned char>& Opacity(void){ return opacity; }
		Change<unsigned char>& Opacity(const u_char current, const u_char target, const float resist){
			this -> opacity.Setup(current, target, resist);

			color.Current(
				ofColor(
						color  .Current().r
					, color  .Current().g
					, color  .Current().b
					, opacity.Current()
				)
			);
			
			color.Target(
				ofColor(
						color  .Target().r
					, color  .Target().g
					, color  .Target().b
					, opacity.Target()
				)
			);
			return this -> opacity;
		}


		/* ======================================= *
		 * Get/Set Opacity                         *
		 * ======================================= */
		void Update(void){
			pos    .Update();
			rotate .Update();
			scale  .Update();
			opacity.Update();
			color  .Update();

			color.Current(
				ofColor(
					  color.Current().r
					, color.Current().g
					, color.Current().b
					, opacity.Current()
				)
			);
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
