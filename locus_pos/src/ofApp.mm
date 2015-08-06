#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	touched = false;

	ofSetColor(255,255,255);

	ofEnableAlphaBlending();

	fbo.allocate(ofGetWidth(), ofGetHeight(), true);

	ofBackground(0);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	fbo.begin();

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);

	ofSetColor(0, 0, 0, 128);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	ofSetColor(255, 255, 255);
	if(touched){
		ofLine(posX,    0,         posX, ofGetHeight());
		ofLine(0   , posY, ofGetWidth(),          posY);
	}
    glDisable(GL_BLEND);
	fbo.end();

	fbo.draw(0, 0);
	
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

