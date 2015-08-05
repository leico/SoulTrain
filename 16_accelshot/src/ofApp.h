#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"

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

				double rad;

				static const int NUM_POS = 2000;

				ofImage image;

				ofFbo blur;

				ofPoint base;
				
				ofPoint   pos[NUM_POS];
				ofPoint *ppos[NUM_POS];

				ofMesh mesh;

				ofPoint force;

				int time;

};


