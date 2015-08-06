#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	touched = false;

	ofSetColor(255,255,255);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	if(touched){
		ofLine(posX,    0,         posX, ofGetHeight());
		ofLine(0   , posY, ofGetWidth(),          posY);
	}
	
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){

	touched = true;

	posX = touch.x;
	posY = touch.y;

}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){

	posX = touch.x;
	posY = touch.y;

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

	
	touched = false;

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

