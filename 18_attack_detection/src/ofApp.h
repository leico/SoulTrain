#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#include "BiQuadFilter.h"

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

				static const int BUF_SIZE      = 512;
				static const int SAMPLING_RATE = 44100;

				float buffer[BUF_SIZE];

				ofMesh signalwave;
				ofMesh lowwave;
				ofMesh highwave;

				ofPoint vertices[BUF_SIZE];
				ofPoint low [BUF_SIZE];
				ofPoint high[BUF_SIZE];

				BiQuadFilter lowpass;
				BiQuadFilter highpass;

				unsigned char o_low;
				unsigned char o_high;

};


