//
//  BlurDraw.h
//  basic
//
//  Created by leico on 2015/07/29.
//
//

#ifndef __basic__BlurDraw__
#define __basic__BlurDraw__

#include "ofMain.h"

class BlurDraw{

	private:
		ofFbo blur;

		unsigned char opacity;

	public:

		/* =================================================== *
		 * Constructor/Destructror                             *
		 * =================================================== */
		 BlurDraw(){};
		~BlurDraw(){};

		/* =================================================== *
		 * Setup(opacity)                                      *
		 * =================================================== */
		void Setup(unsigned char opacity){
			blur.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
			this -> opacity = opacity;
		};

		/* =================================================== *
		 * Set/Get Opacity(opacity)                            *
		 * =================================================== */
		unsigned char Opacity(unsigned char opacity){return this -> opacity = opacity; }
		unsigned char Opacity(void)                 {return this -> opacity;           }

		/* =================================================== *
		 * Begin()                                             *
		 * =================================================== */
		void Begin(void){
			blur.begin();
				ofPushStyle();
					ofSetColor(0, opacity);
					ofRect(0, 0, blur.getWidth(), blur.getHeight());
				ofPopStyle();
		};

		/* =================================================== *
		 * End()                                               *
		 * =================================================== */
		void End(void){
			blur.end();
		};

		/* =================================================== *
		 * Osc(oscemessage)                                    *
		 * =================================================== */
		void Osc(ofxOscMessage& m){
			if(m.getAddress() == "/Blur/Opacity/x") opacity = m.getArgAsFloat(0) * 255;
		}

		/* =================================================== *
		 * Draw()                                              *
		 * =================================================== */
		void Draw(int x, int y)              { blur.draw(x, y); }
		void Draw(int x, int y, int w, int h){ blur.draw(x, y, w, h); };

};

#endif /* defined(__basic__BlurDraw__) */
