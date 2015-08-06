#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	


	ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofBackground(0);

	width  = ofGetWidth ();
	height = ofGetHeight();

	blur.Setup(16);

	plane.Rect   ( ofRectangle(0, 0, width, height) );
	plane.Color  ( Change<ofColor>(ofColor(255, 0), ofColor(255, 0), 0.1) );

	wave.Color  ( Change<ofColor>(ofColor(255, 0), ofColor(255, 0), 0.1) );
	wave.Scale ().Resist(0.05);
	wave.Rotate().Resist(0.05);
	wave.Pos   ().Resist(0.05);
	wave.BasePos( Change<ofPoint>(ofPoint(0, height / 2, 0), ofPoint(0, height / 2, 0), 0) );

	wave.Setup(width, 300, OF_PRIMITIVE_LINE_STRIP);

	accel.Color  ( Change<ofColor>(ofColor(255), ofColor(255), 0.1) );

	accel.Scale ().Resist(0.05);
	accel.Rotate().Resist(0.05);

	accel.BasePos( Change<ofPoint>(
			ofPoint(width / 2, height / 2, 0)
		, ofPoint(width / 2, height / 2, 0)
		, 0
	) );
	
	accel.Setup(600, 300, OF_PRIMITIVE_LINE_STRIP);

	ofSoundStreamSetup(0, 1, SAMPLING_RATE, BUF_SIZE, 1);

	low .Setup<AttackDetection :: LOWPASS> (200 , 1, SAMPLING_RATE);
	high.Setup<AttackDetection :: HIGHPASS>(8000, 1, SAMPLING_RATE);

	lowthresh  = 0.1;
	highthresh = 0.8;

	low .Threshold(lowthresh);
	high.Threshold(highthresh);

	


}

//--------------------------------------------------------------
void ofApp::update(){

	plane.Update();
	wave .Update();
	accel.Update();

}

//--------------------------------------------------------------
void ofApp::draw(){

	blur.Begin();
		wave.Draw();
		accel.Draw();
	blur.End();
	blur.Draw(0, 0);
	
		plane.Draw();
	
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}

//--------------------------------------------------------------
void ofApp::audioIn(float *input, int buffersize, int n_channel){
	
	bool lowattack  = low.Process <AttackDetection :: AVERAGE> (input, buffersize);
	bool highattack = high.Process<AttackDetection :: MAXVALUE>(input, buffersize);

	plane.AudioIn(input, buffersize, lowattack, highattack);
	wave .AudioIn(input, buffersize, lowattack, highattack);
	accel.AudioIn(input, buffersize, lowattack, highattack);

}