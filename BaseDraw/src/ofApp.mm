#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	


	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(true);
	ofBackground(0);

	width  = ofGetWidth ();
	height = ofGetHeight();


	vertices = new ofPoint[width];


	blur.Setup(16);

	plane.Setup(
		ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), 
		ofColor(255)
	);

	ofSoundStreamSetup(0, 1, SAMPLING_RATE, BUF_SIZE, 1);

	signalwave.setMode(OF_PRIMITIVE_LINE_STRIP);

	for(int i = 0 ; i < width + 1 ; ++ i){
		vertices[i].x = i;
		signalwave.addColor(ofColor(255));
	}

	low .Setup<AttackDetection :: LOWPASS> (200 , 1, SAMPLING_RATE);
	high.Setup<AttackDetection :: HIGHPASS>(8000, 1, SAMPLING_RATE);

	lowthresh  = 0.1;
	highthresh = 0.8;

	low .Threshold(lowthresh);
	high.Threshold(highthresh);

	


}

//--------------------------------------------------------------
void ofApp::update(){

	signalwave.clearVertices();
	signalwave.addVertices(vertices, width);

	o_low  = (o_low  - 8 < 0) ? 0 : o_low  - 8;
	o_high = (o_high - 8 < 0) ? 0 : o_high - 8;

}

//--------------------------------------------------------------
void ofApp::draw(){

	blur.Begin();
		plane.Draw();
	blur.End();
	blur.Draw(0, 0);
	
	signalwave.draw();
/*
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
*/

	
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


	float sum = 0;
	for(int i = 0 ; i < buffersize ; ++ i)
		sum +=  abs(input[i]);
	
	for(int i = 0 ; i < width - 1 ; i += 2){
		vertices[i]    .y = vertices[i + 2]    .y;
		vertices[i + 1].y = vertices[i + 2 + 1].y;
	}
	float tmp =  sum / buffersize * 300;
	ofLogVerbose() << tmp;
	vertices[width - 2].y = base + tmp;
	vertices[width - 1].y = base - tmp;

	plane.isDraw( low.Process<AttackDetection :: AVERAGE> (input, buffersize));
	o_high = high.Process<AttackDetection :: MAXVALUE>(input, buffersize) ? 255 : o_high;

}
