#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0, 0, 0);

	ofSetFrameRate(60);

	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){

	for(int i = bnum - 1 ; i >= 0 ; -- i){
		pos[i] = pos[i - 1];
	}

	rad += 0.01;
	pos[0].x = ofGetWidth()  / 2 + 100 * sin(rad * 5);
	pos[0].y = ofGetHeight() / 2 + 100 * cos(rad * 6);

}

//--------------------------------------------------------------
void ofApp::draw(){


	for(int i = 0 ; i < bnum ; ++ i){
		ofSetColor(255, 255, 255, 255 * (1.0 - (1.0 * i / bnum)));
		ofCircle(pos[i], 30);
	}

	
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

