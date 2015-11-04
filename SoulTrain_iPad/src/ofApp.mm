#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	


  ofSetLogLevel(OF_LOG_VERBOSE);
  ofEnableAlphaBlending();
  ofSetVerticalSync(true);
  ofBackground(0);

  receiver.setup(9000);

  width  = ofGetWidth ();
  height = ofGetHeight();

  blur.Setup(16);

  plane.Rect   ( ofRectangle(0, 0, width, height) );
  plane.Color  ( Change<ofColor>(ofColor(0, 0), ofColor(0, 0), 0.1) );

  wave.Color  ( Change<ofColor>(ofColor(255, 0), ofColor(255, 0), 0.1) );
  wave.Scale ().Resist(0.05);
  wave.Rotate().Resist(0.05);
  wave.Pos   ().Resist(0.05);
  wave.BasePos   ( ofPoint(0, height / 2, 0), 0.1);
  wave.BaseRotate( ofPoint(0,          0, 0), 0.1);
  wave.BaseScale ( ofPoint(1,          1, 1), 0.1);
  wave.OscAddress("/Wave/");

  wave.Setup(width, 300, OF_PRIMITIVE_LINE_STRIP);

  accel.Color  ( Change<ofColor>(ofColor(255), ofColor(255), 0.1) );

  accel.Scale ().Resist(0.05);
  accel.Rotate().Resist(0.05);

  accel.BasePos( Change<ofPoint>(
        ofPoint(width / 2, height / 2, 0)
        , ofPoint(width / 2, height / 2, 0)
        , 0
        ) );

  accel.Setup(600, 300, OF_PRIMITIVE_LINE_STRIP);

  ofSoundStreamSetup(0, 1, SAMPLING_RATE, BUF_SIZE, 1);

  lpf.Frequency(200);
  lpf.Q(1);
  lpf.SamplingRate(SAMPLING_RATE);
  lpf.Setup(0.1);

  hpf.Frequency(8000);
  hpf.Q(1);
  hpf.SamplingRate(SAMPLING_RATE);
  hpf.Setup(0.8);

}

//--------------------------------------------------------------
void ofApp::update(){

  while(receiver.hasWaitingMessages()){
    ofxOscMessage m;
    receiver.getNextMessage(&m);

    lpf .Osc(m);
    hpf .Osc(m);
    blur.Osc(m);
    plane.Osc(m);
    wave.Osc(m);
    accel.Osc(m);
  }

  plane.Update();
  wave .Update();
  accel.Update();

}

//--------------------------------------------------------------
void ofApp::draw(){

  blur.Begin();
  wave.Draw();
  accel.Draw();
  blur.End();
  blur.Draw(0, 0);

  plane.Draw();

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

  lpf.AudioIn(input, buffersize);
  hpf.AudioIn(input, buffersize);

  bool kick  = lpf.isAttack_Average();
  bool hihat = hpf.isAttack_Peak();

  plane.AudioIn(input, buffersize, kick, hihat);
  wave .AudioIn(input, buffersize, kick, hihat);
  accel.AudioIn(input, buffersize, kick, hihat);

}
