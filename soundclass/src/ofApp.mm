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

	ofSetLogLevel(OF_LOG_VERBOSE);

}

//--------------------------------------------------------------
void ofApp::update(){

	signalwave.clearVertices();
	lowwave   .clearVertices();
	highwave  .clearVertices();
	signalwave.addVertices(vertices, BUF_SIZE);
	lowwave   .addVertices(low,      BUF_SIZE);
	highwave  .addVertices(high,     BUF_SIZE);

	o_low  = (o_low  - 32 < 0) ? 0 : o_low  - 32;
	o_high = (o_high - 32 < 0) ? 0 : o_high - 32;

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	signalwave.draw();
	lowwave.draw();
	highwave.draw();

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
	int lowbase  = base + height / 4;
	int highbase = base - height / 4;

	float lowsum  = 0;
	float highsum = 0;

	for(int i = 0 ; i < buffersize ; ++ i){
		vertices[i].y = input[i];
		low     [i].y = lowpass .Process(input[i]);
		high    [i].y = highpass.Process(input[i]);

		lowsum  += abs(low [i].y);
		highsum += abs(high[i].y);
	}

	ofLogVerbose() << "L_sum : " << lowsum ;
	ofLogVerbose() << "H_sum : " << highsum;
	
	o_low  = ( (lowsum  / buffersize) > 0.05) ? 255 : o_low;
	o_high = ( (highsum / buffersize) > 0.05) ? 255 : o_high;
		

}
