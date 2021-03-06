

#ifndef __basic_OF_APP_H__
#define __basic_OF_APP_H__

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"

#include "Change.h"
#include "BaseDraw.h"
#include "PlaneDraw.h"
#include "WaveDraw.h"
#include "AccelDraw.h"

#include "BlurDraw.h"
#include "LPF.h"
#include "HPF.h"

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

				ofxOscReceiver receiver;

				BlurDraw blur;
				
				PlaneDraw plane;
				WaveDraw  wave;
				AccelDraw accel;

				LPF lpf;
				HPF hpf;

				static const int BUF_SIZE      = 512;
				static const int SAMPLING_RATE = 44100;

				int width;
				int height;

};
#endif

