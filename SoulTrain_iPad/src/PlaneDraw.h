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

		bool kick;
		bool hat;

		ofColor kick_color;
		ofColor hat_color;

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
		void Osc(const ofxOscMessage& m){

			const string K = "/Plane/Kick/";
			const string H = "/Plane/Hat/";

			if(m.getAddress() == K + "Button/x"){
				kick = (m.getArgAsFloat(0) == true);
				return;
			}

			if(m.getAddress() == K + "R/x"){
				kick_color.r = m.getArgAsFloat(0) * 255;
				return;
			}

			if(m.getAddress() == K + "G/x"){
				kick_color.g = m.getArgAsFloat(0) * 255;
				return;
			}

			if(m.getAddress() == K + "B/x"){
				kick_color.b = m.getArgAsFloat(0) * 255;
				return;
			}




			if(m.getAddress() == H + "Button/x"){
				hat = (m.getArgAsFloat(0) == true);
				return;
			}

			if(m.getAddress() == H + "R/x"){
				hat_color.r = m.getArgAsFloat(0) * 255;
				return;
			}

			if(m.getAddress() == H + "G/x"){
				hat_color.g = m.getArgAsFloat(0) * 255;
				return;
			}

			if(m.getAddress() == H + "B/x"){
				hat_color.b = m.getArgAsFloat(0) * 255;
				return;
			}




			if(m.getAddress() == "/Plane/Resist/x"){
				Color().Resist(m.getArgAsFloat(0));
				return;
			}

		}

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

			if(kick && lowattack){
				current   += kick_color;
				current.a  = 255;
			}

			if(hat && highattack){
				current   += hat_color;
				current.a  = 255;
			}

			Color().Current( current );
		}

};

#endif /* defined(__basic__PlaneDraw__) */
