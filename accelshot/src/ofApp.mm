#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	ofxAccelerometer.setup();

	blur.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	base.set(0);

	for(int i = 0 ; i < NUM_POS ; ++ i){
		pos [i].set(0.0f);
		ppos[i] = &pos[i];
	}

	mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
	for(int i = 0 ; i < NUM_POS ; ++ i)
		mesh.addColor(ofColor(255));

	rad = 0.0;

	time = ofGetSeconds();
}

//--------------------------------------------------------------
void ofApp::update(){

	rad += 0.5;

	force = ofxAccelerometer.getForce();

	mesh.clearVertices();

	ofPoint tmp = pos[0];
	for(int i = 0 ; i < NUM_POS - 1 ; ++ i)
		pos[i] = pos[i + 1];
	pos[NUM_POS - 1] = (base - ofxAccelerometer.getForce()) * 400;

	mesh.addVertices(pos, NUM_POS);

}

//--------------------------------------------------------------

/* ================================================= *
 *	 アンチエイリアス入れるとios版は全般的にバグる。 *
 * ================================================= */


void ofApp::draw(){

	blur.begin();
		ofPushMatrix();

			ofSetColor(0, 16);
			ofRect(0, 0, ofGetWidth(), ofGetHeight());

			ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
			ofRotateY(rad);

			ofSetColor(255);
			mesh.draw();

			ofSetColor(255, 0, 0);
			ofEllipse(pos[NUM_POS - 1], 10, 10);

		ofPopMatrix();

	blur.end();

	blur.draw(0, 0);

	string info  = "X = " + ofToString(force.x) + "\n";
	       info += "Y = " + ofToString(force.y) + "\n";
				 info += "Z = " + ofToString(force.z) + "\n";
				 
	ofDrawBitmapString(info, 30, 30);

	int now = ofGetSeconds();

	if(time != ofGetSeconds()){
		string filename  =  ofToString(ofGetHours(),    2, '0');
			     filename +=  ofToString(ofGetMinutes(),  2, '0');
					 filename +=  ofToString(ofGetSeconds(),  2, '0');
										 
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage(ofxiOSGetDocumentsDirectory() + filename + ".png");
		time = now;
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

	base = ofxAccelerometer.getForce();
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

