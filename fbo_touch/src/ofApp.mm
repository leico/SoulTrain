#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	

	receiver.setup(8000);

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofBackground(0);
  ofEnableAlphaBlending();
	ofEnableDepthTest();

	for(int i = 0 ; i < w ; ++ i){
		for(int j = 0 ; j < h ; ++ j){
			verts  [j * w + i].set(i - w / 2, j - h / 2, 0 );
			vertclr[j * w + i].set(0.5, 0.8, 1.0, 1.0);
		}
	}

	vbo.setVertexData(verts, num, GL_DYNAMIC_DRAW);
	vbo.setColorData (vertclr, num, GL_DYNAMIC_DRAW);

	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
}

//--------------------------------------------------------------
void ofApp::update(){

	while( receiver.hasWaitingMessages() ){

		ofxOscMessage m;
		receiver.getNextMessage(&m);

		if(m.getAddress() == "/Cam/x/x"){
			tilt = 360 * m.getArgAsFloat(0);
			continue;
		}
		if(m.getAddress() == "/Cam/y/x"){
			roll = 360 * m.getArgAsFloat(0);
			continue;
		}
		if(m.getAddress() == "/Cam/z/x"){
			pan = 360 * m.getArgAsFloat(0);
			continue;
		}
		if(m.getAddress() == "/Cam/Zoom/x"){
			scale = m.getArgAsFloat(0) * 100;
		}
	}


	for(int i = 0 ; i < w ; ++ i){
		for(int j = 0 ; j < h ; ++ j){
			float x = sin( i * 0.1   + ofGetElapsedTimef() ) * 10.0;
			float y = sin( j * 0.15  + ofGetElapsedTimef() ) * 10.0;
      float z = x + y;
			verts[ j * w + i] = ofVec3f(i - w / 2, j - h / 2, z);
		}
	}

	vbo.updateVertexData(verts, num);
}

//--------------------------------------------------------------
int y = 0;
void ofApp::draw(){

	y ++;
    

	fbo.begin();
        ofClear(0, 0, 0, 0.5);
        ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            ofRotateX(tilt);
            ofRotateY(roll);
            ofRotateZ(pan);
            ofScale(scale, scale, scale);
	
            vbo.draw(GL_LINES, 0, num);

            ofSetColor(255);
    
        ofPopMatrix();
	fbo.end();

	ofSetColor(255, 255, 255);

	fbo.draw(0, 0);


	string info  = "Vertex num = " + ofToString(w * h, 0) + "\n";
	       info += "FPS = " + ofToString( ofGetFrameRate(), 2);
	ofDrawBitmapString(info, 30, 30);
	
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

