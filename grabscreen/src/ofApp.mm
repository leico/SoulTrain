#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	blur.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void ofApp::update(){


	rad += 0.01;
	pos.x = ofGetWidth()  / 2 + 100 * sin(rad * 5);
	pos.y = ofGetHeight() / 2 + 100 * cos(rad * 6);

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255, 255, 255, 128);
	blur.draw(0, 0);
		
	ofSetColor(255,255,255,255);
	ofCircle(pos, 30);


	blur.grabScreen(0, 0, ofGetWidth(), ofGetHeight());


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

