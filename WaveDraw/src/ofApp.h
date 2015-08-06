

#ifndef __basic_OF_APP_H__
#define __basic_OF_APP_H__

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"

#include "BaseDraw.h"
#include "Change.h"
#include "PlaneDraw.h"
#include "WaveDraw.h"
#include "BlurDraw.h"
#include "AttackDetection.h"


/* 波形クラス化、音によるフェードつける。 */

class ofApp : public ofxiOSApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);

				void audioIn(float *input, int buffersize, int n_channel);

				BlurDraw blur;
				
				PlaneDraw plane;
				WaveDraw  wave;

				static const int BUF_SIZE      = 512;
				static const int SAMPLING_RATE = 44100;

				int width;
				int height;

				float lowthresh;
				float highthresh;

				AttackDetection low;
				AttackDetection high;

};
#endif

