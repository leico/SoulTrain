#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	

	ofBackground(0);
	ofEnableDepthTest();
	cam.setDistance(100);

	w = 100;
	h = 100;

	for(int i = 0 ; i < w ; ++ i)
		for(int j = 0 ; j < h ; ++ j)
			mesh.addColor( ofFloatColor(0.5, 0.8, 1.0) );
}

//--------------------------------------------------------------
void ofApp::update(){

	mesh.clearVertices();

	for(int i = 0 ; i < w ; ++ i){
		for(int j = 0 ; j < h ; ++ j){
			float x = sin( i * 0.1   + ofGetElapsedTimef() ) * 10.0;
			float y = sin( j * 0.15  + ofGetElapsedTimef() ) * 10.0;
            float z = x + y;
			mesh.addVertex( ofVec3f(i - w/2, j - h/2, z) );
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetHexColor(0xffffff);
	cam.begin();

		glPointSize(2.0);
		glEnable(GL_POINTS);
		
		mesh.drawVertices();

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

