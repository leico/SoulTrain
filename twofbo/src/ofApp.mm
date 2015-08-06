#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	buffer = (GLubyte *)malloc(ofGetWidth() * ofGetHeight() * 4);

	image.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
	fbo  .allocate(ofGetWidth(), ofGetHeight(), GL_ALPHA);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

}

//--------------------------------------------------------------
void ofApp::update(){


	rad += 0.01;
	pos.x = ofGetWidth()  / 2 + 100 * sin(rad * 5);
	pos.y = ofGetHeight() / 2 + 100 * cos(rad * 6);


}

//--------------------------------------------------------------
void ofApp::draw(){

	fbo.begin();
	ofSetColor(255, 255, 255, 200);
	image.draw(0, 0);

	ofSetColor(255,255,255,200);
	ofCircle(pos, 30);
	glReadPixels(0, 0, ofGetWidth(), ofGetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	image.setFromPixels(buffer, ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	fbo.end();

	fbo.draw(0, 0);

	

}

//--------------------------------------------------------------
void ofApp::exit(){

	free(buffer);

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

