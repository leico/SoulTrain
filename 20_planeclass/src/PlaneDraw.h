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

class PlaneDraw{

	private:
		bool draw;

		ofRectangle rect;
		ofColor     clr;

	public:
		 PlaneDraw(void) : rect(0, 0, 0, 0), clr(0) {};
		~PlaneDraw(void){};

		void Setup(const ofRectangle &rect, const ofColor &color){
			this -> rect = rect;
			this -> clr  = color;
		}

		bool isDraw(void){ return draw; }
		bool isDraw(bool draw){ return this -> draw = draw; }

		const ofColor& Color(void){ return clr; }
		const ofColor& Color(const ofColor& color){
			clr = color;
			return clr;
		}

		void Draw(void){
			if(draw){
				ofPushStyle();
					ofSetColor(clr);
					ofRect(rect);
				ofPopStyle();
				draw = false;
			}
		}
};

#endif /* defined(__basic__PlaneDraw__) */
