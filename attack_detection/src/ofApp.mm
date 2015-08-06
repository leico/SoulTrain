#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	


	ofBackground(0);

	ofSoundStreamSetup(0, 1, SAMPLING_RATE, BUF_SIZE, 1);

	signalwave.setMode(OF_PRIMITIVE_LINE_STRIP);
	lowwave   .setMode(OF_PRIMITIVE_LINE_STRIP);
	highwave  .setMode(OF_PRIMITIVE_LINE_STRIP);

	{
		int width = ofGetWidth();
		for(int i = 0 ; i < BUF_SIZE ; ++ i){
			signalwave.addColor(ofColor(255));
			low[i].x = high[i].x = vertices[i].x = i * width / BUF_SIZE;
		}
	}

	lowpass  .LowPass ( 200, 1.0, SAMPLING_RATE);
	highpass .HighPass(5000, 1.0, SAMPLING_RATE);

}

//--------------------------------------------------------------
void ofApp::update(){

	signalwave.clearVertices();
	lowwave   .clearVertices();
	highwave  .clearVertices();
	signalwave.addVertices(vertices, BUF_SIZE);
	lowwave   .addVertices(low,      BUF_SIZE);
	highwave  .addVertices(high,     BUF_SIZE);

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	signalwave.draw();
	lowwave.draw();
	highwave.draw();
	
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
	int lowbase  = base + height / 4;
	int highbase = base - height / 4;

	for(int i = 0 ; i < buffersize ; ++ i){
		vertices[i].y = base     + input[i] * 300;
		low     [i].y = lowbase  + lowpass .Process(input[i]) * 500;
		high    [i].y = highbase + highpass.Process(input[i]) * 500;
	}

}
