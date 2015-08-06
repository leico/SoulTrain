#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	


	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);

	ofSoundStreamSetup(0, 1, SAMPLING_RATE, BUF_SIZE, 1);

	signalwave.setMode(OF_PRIMITIVE_LINE_STRIP);

	for(int i = 0 ; i < BUF_SIZE ; ++ i){
		vertices[i].x = i * (ofGetWidth() / BUF_SIZE);
		signalwave.addColor(ofColor(255));
	}

	low .Setup<AttackDetection :: LOWPASS> (200 , 1, SAMPLING_RATE);
	high.Setup<AttackDetection :: HIGHPASS>(8000, 1, SAMPLING_RATE);

	low .Threshold(0.1);
	high.Threshold(0.8);


}

//--------------------------------------------------------------
void ofApp::update(){

	signalwave.clearVertices();
	signalwave.addVertices(vertices, BUF_SIZE);

	o_low  = (o_low  - 8 < 0) ? 0 : o_low  - 8;
	o_high = (o_high - 8 < 0) ? 0 : o_high - 8;

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	signalwave.draw();

	ofPushStyle();

		if(o_low){
			ofSetColor(255, 0, 0, o_low);
			ofRect(0, 0, ofGetWidth(), ofGetHeight());
		}

		if(o_high){
			ofSetColor(0, 255, 0, o_high);
			ofRect(0, 0, ofGetWidth(), ofGetHeight());
		}

	ofPopStyle();

	
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

	int height   = ofGetHeight();
	int base     = height / 2;


	for(int i = 0 ; i < buffersize ; ++ i)
		vertices[i].y = base + input[i] * 100;


	
	o_low  = low.Process<AttackDetection :: AVERAGE>
				              (input, buffersize) ? 255 : o_low;

	o_high = high.Process<AttackDetection :: MAXVALUE>
		                   (input, buffersize) ? 255 : o_high;

}
