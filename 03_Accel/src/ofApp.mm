#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofxAccelerometer.setup();

	ofBackground(0);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();

	ofPoint force = ofxAccelerometer.getForce();
	ofPoint pos( 1000 * force.x, 1000 * force.y, 1000 * force.z);

	ofLine(-10000,      0,      0, 10000,     0,     0);
	ofLine(     0, -10000,      0,     0, 10000,     0);
	ofLine(     0,      0, -10000,     0,     0, 10000);

	ofLine( -100,     0, pos.z,   100,    0, pos.z);
	ofLine(pos.x,  -100,     0, pos.x,  100,     0);
	ofLine(    0, pos.y,  -100,     0, pos.y,  100);    

	cam.end();
	
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

