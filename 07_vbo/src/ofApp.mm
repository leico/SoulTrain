#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	

	receiver.setup(8000);

	ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);


	ofBackground(0);
    ofEnableAlphaBlending();
	ofEnableDepthTest();

	cam.setPosition(0, 0, -300);
	cam.lookAt( ofVec3f(0, 0, 0) );
	cam.setFov( 45 );

	for(int i = 0 ; i < w ; ++ i){
		for(int j = 0 ; j < h ; ++ j){
			verts  [j * w + i].set(i - w / 2, j - h / 2, 0 );
			vertclr[j * w + i].set(0.5, 0.8, 1.0, 1.0);
		}
	}

	vbo.setVertexData(verts, num, GL_DYNAMIC_DRAW);
	vbo.setColorData (vertclr, num, GL_DYNAMIC_DRAW);
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
			cam.setPosition(0, 0, -300 + (-0.5 + m.getArgAsFloat(0)) * 600);
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
void ofApp::draw(){
    

	ofSetHexColor(0xffffff);
	cam.begin();
		ofPushMatrix();
			ofRotateX(tilt);
			ofRotateY(roll);
			ofRotateZ(pan);

			glPointSize(2.0);
			vbo.draw(GL_LINES, 0, num);
		
		ofPopMatrix();

	cam.end();

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

