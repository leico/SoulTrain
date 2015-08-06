#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	

	ofBackground(0);

	ofxAccelerometer.setup();

	location = new ofxiOSCoreLocation();
	location -> startLocation();

	sender.setup("192.168.10.255", 8000);
	second = ofGetSeconds();
}

//--------------------------------------------------------------
void ofApp::update(){

	lat = location -> getLatitude ();
	lng = location -> getLongitude();
	
	force = ofxAccelerometer.getForce();

	int now = ofGetSeconds();
	if(second != now){
		ofxOscMessage location;
		location.setAddress("/location");
		location.addFloatArg( lat );
		location.addFloatArg( lng );

		ofxOscMessage accel;
		accel.setAddress("/accel");
		accel.addFloatArg(force.x);
		accel.addFloatArg(force.y);
		accel.addFloatArg(force.z);

		sender.sendMessage(location);
		sender.sendMessage(accel);

		second = now;
	}
	

}

//--------------------------------------------------------------
void ofApp::draw(){

	stringstream ss;
	ss        << fixed   << setprecision(13) <<
	"LAT   :" << lat     << "\n" <<
	"LNG   :" << lng     << "\n" <<
	"ForceX:" << force.x << "\n" << 
	"ForceY:" << force.y << "\n" <<
	"ForceZ:" << force.z << "\n";

	ofLogVerbose() << lat << "|" << lng;

	ofDrawBitmapString(ss.str(), 10, 10);
	
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

