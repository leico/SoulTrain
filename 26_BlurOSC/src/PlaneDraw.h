//
//  PlaneDraw.h
//  basic
//
//  Created by leico on 2015/07/29.
//
//

#ifndef __basic__PlaneDraw__
#define __basic__PlaneDraw__

#include "ofMain.h"
#include "BaseDraw.h"

class PlaneDraw : public BaseDraw{

	private:
		ofRectangle rect;

	public:
		/* ============================================ *
		 * Constructor/Destructor                       *
		 * ============================================ */
		 PlaneDraw(void) : rect(0, 0, 0, 0){};
		~PlaneDraw(void){};

		/* ============================================ *
		 * Get/Set Rect                                 *
		 * ============================================ */
		ofRectangle& Rect(void){ return rect; }
		ofRectangle& Rect(const ofRectangle& rect){
			this -> rect = rect;
			return this -> rect;
		}

		/* ============================================ *
		 * Get OscMessage                               *
		 * ============================================ */
		void Osc(const ofxOscMessage& m){}

		/* ============================================ *
		 * Draw                                         *
		 * ============================================ */
		void Draw(void){

			ofPushStyle();
			ofPushMatrix();
	
				ofSetColor( Color().Current() );
				ofRect(rect);
	
				ofTranslate(    Pos().Current() );
				ofRotateX  ( Rotate().Current().x );
				ofRotateY  ( Rotate().Current().y );
				ofRotateZ  ( Rotate().Current().z );
				ofScale(
						Scale().Current().x
					, Scale().Current().y
					, Scale().Current().z
				);
	
			ofPopMatrix();
			ofPopStyle();
		}

		/* ============================================ *
		 * AudioIn                                      *
		 * ============================================ */
		void AudioIn(
				const float *raw
			, int          size
			, bool         lowattack
			, bool         highattack
		){
			ofColor current = Color().Current();
			CurrentColor( 
					ofColor(
							current.r
						, current.g
						, current.b
						, lowattack ? 255 : current.a
					)
				, Color().Resist() 
			);
		}

};

#endif /* defined(__basic__PlaneDraw__) */
