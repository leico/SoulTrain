//
//  WaveDraw.h
//  basic
//
//  Created by leico on 2015/07/29.
//
//

#ifndef basic_WaveDraw_h
#define basic_WaveDraw_h

#include "ofMain.h"
#include "ofxOsc.h"
#include "Change.h"
#include "BaseDraw.h"


class WaveDraw : public BaseDraw{

  private:
    ofMesh   signalwave;
    std :: vector<ofPoint> vertices;
    std :: vector<ofFloatColor> colors;

    float   amplitude;

    struct param{
      bool kick;
      bool hat;
      float amp;
    } posparam, rotateparam, scaleparam;

    float sum;

  public:
    /* =========================================== *
     * Constructor/Destructor                      *
     * =========================================== */
    WaveDraw () : BaseDraw("/Wave/") {};
    ~WaveDraw(){};

    /* =========================================== *
     * Clear                                       *
     * =========================================== */
    void Clear(void){
      signalwave.clear();
      vertices  .clear();
    }

    /* =========================================== *
     * Get/Set Size                                *
     * =========================================== */
    int Size(void){ return vertices.size(); }
    int Size(const int size){
      vertices.resize(size);
      colors  .resize(size);
      return vertices.size();
    }

    /* =========================================== *
     * Get/Set Wave Amplitude                      *
     * =========================================== */
    float Amplitude(void){ return amplitude; }
    float Amplitude(const float amplitude){
      this -> amplitude = amplitude;
      return this -> amplitude;
    }

    /* =========================================== *
     * Get/Set DrawMode                            *
     * =========================================== */
    ofPrimitiveMode Mode(void){ return signalwave.getMode(); }
    ofPrimitiveMode Mode(ofPrimitiveMode mode){
      signalwave.setMode(mode);
      return signalwave.getMode();
    }


    /* =========================================== *
     * Setup                                       *
     * =========================================== */
    void Setup(const int size, const float amplitude, ofPrimitiveMode mode){

      Size     (size);
      Amplitude(amplitude);
      Mode     (mode);

      for(int i = 0 ; i < vertices.size() ; ++ i){
        vertices[i].x = i;
        colors  [i]   = ofColor(255);
      }
    }


    /* =========================================== *
     * Update                                      *
     * =========================================== */
    void Update(void){
      BaseDraw :: Update();

      for(int i = 0 ; i < Size() - 1 ; i += 2){
        vertices[i    ].y = vertices[i + 2    ].y;
        vertices[i + 1].y = vertices[i + 2 + 1].y;

        colors[i    ] = colors[i + 2    ];
        colors[i + 1] = colors[i + 2 + 1];
      }

      float tmp = sum / Size() * Amplitude();
      vertices[Size() - 2].y =  tmp;
      vertices[Size() - 1].y = -tmp;

      signalwave.clearVertices();
      signalwave.addVertices(vertices);

      colors[Size() - 2] = colors[Size() - 1] = Color().Current();

      signalwave.clearColors();
      signalwave.addColors(colors);

    }

    /* =========================================== *
     * Get OscMessage                              *
     * =========================================== */
    void Osc(const ofxOscMessage& m){

      ofxOscMessage osc = m;


      const string wave = "/Wave/";

      const string address = m.getAddress();
      const float  value   = m.getArgAsFloat(0);



      if( Osc_BasePos   (osc, 100).getNumArgs() == 0) return;
      if( Osc_BaseRotate(osc,  10).getNumArgs() == 0) return;
      if( Osc_BaseScale (osc,   1).getNumArgs() == 0) return;

      if( Osc_Pos   (osc, 100).getNumArgs() == 0) return;
      if( Osc_Rotate(osc,  10).getNumArgs() == 0) return;
      if( Osc_Scale (osc,   1).getNumArgs() == 0) return;

      if( Osc_Color(osc).getNumArgs() == 0) return;

      {

        const string pos    = wave + "Pos/";
        const string rotate = wave + "Rotate/";
        const string scale  = wave + "Scale/";


        if( address == pos + "Kick/x"){
          posparam.kick = value == 1;
          return;
        }
        if( address == pos + "Hat/x"){
          posparam.hat = value == 1;
          return;
        }
        if( address == pos + "Swing/x"){
          posparam.amp = value * 100;
          return;
        }

        if( address == rotate + "Kick/x"){
          rotateparam.kick = value == 1;
          return;
        }
        if( address == rotate + "Hat/x"){
          rotateparam.hat = value == 1;
          return;
        }
        if( address == rotate + "Swing/x"){
          rotateparam.amp = value * 10;
          return;
        }

        if( address == scale + "Kick/x"){
          scaleparam.kick = value == 1;
          return;
        }
        if( address == scale + "Hat/x"){
          scaleparam.hat = value == 1;
          return;
        }
        if( address == scale + "Swing/x"){
          scaleparam.amp = value;
          return;
        }
      }

      if( address == wave + "Amplitude/x"){
        Amplitude(value * 100);
        return;
      }

      if( address == wave + "Resist/x"){
        BasePos   ().Resist( value );
        BaseRotate().Resist( value );
        BaseRotate().Resist( value );

        Pos   ().Resist( value );
        Rotate().Resist( value );
        Rotate().Resist( value );

        Color().Resist ( value );
      }


    }


    /* =========================================== *
     * Draw                                        *
     * =========================================== */
    void Draw(void){

      ofPushStyle ();
      ofPushMatrix();

      ofPoint pos    = BasePos()   .Current() + Pos()   .Current();
      ofPoint rotate = BaseRotate().Current() + Rotate().Current();
      ofPoint scale  = BaseScale() .Current() * Scale() .Current();

      ofTranslate( pos );
      ofRotateX  ( rotate.x );
      ofRotateY  ( rotate.y );
      ofRotateZ  ( rotate.z );
      ofScale    (scale.x, scale.y, scale.z);

      signalwave.draw();

      ofPopMatrix();
      ofPopStyle ();
    }

    /* =========================================== *
     * AudioIn                                     *
     * =========================================== */
    void AudioIn(
        const float *raw
        , int          size
        , bool         lowattack
        , bool         highattack
        ){

      sum = 0;
      for(int i = 0 ; i < size ; ++ i)
        sum += abs(raw[i]);


      if(lowattack && posparam.kick)
        TargetPos(
            ofPoint(
              ofRandom(-posparam.amp, posparam.amp)
              , ofRandom(-posparam.amp, posparam.amp)
              , ofRandom(-posparam.amp, posparam.amp)
              )
            , Pos().Resist() 
            );

      if(lowattack && rotateparam.kick)
        TargetRotate(
            ofPoint(
              ofRandom(-rotateparam.amp, rotateparam.amp)
              , ofRandom(-rotateparam.amp, rotateparam.amp)
              , ofRandom(-rotateparam.amp, rotateparam.amp)
              )
            , Rotate().Resist() 
            );

      if(lowattack && scaleparam.kick)
        TargetScale(
            ofPoint(
              ofRandom(-scaleparam.amp, scaleparam.amp)
              , ofRandom(-scaleparam.amp, scaleparam.amp)
              , ofRandom(-scaleparam.amp, scaleparam.amp)
              )
            , Scale().Resist() 
            );


      if(highattack && posparam.hat)
        TargetPos(
            ofPoint(
              ofRandom(-posparam.amp, posparam.amp)
              , ofRandom(-posparam.amp, posparam.amp)
              , ofRandom(-posparam.amp, posparam.amp)
              )
            , Pos().Resist() 
            );

      if(highattack && rotateparam.hat)
        TargetRotate(
            ofPoint(
              ofRandom(-rotateparam.amp, rotateparam.amp)
              , ofRandom(-rotateparam.amp, rotateparam.amp)
              , ofRandom(-rotateparam.amp, rotateparam.amp)
              )
            , Rotate().Resist() 
            );

      if(highattack && scaleparam.hat)
        TargetScale(
            ofPoint(
              ofRandom(-scaleparam.amp, scaleparam.amp)
              , ofRandom(-scaleparam.amp, scaleparam.amp)
              , ofRandom(-scaleparam.amp, scaleparam.amp)
              )
            , Scale().Resist() 
            );


    }
};

#endif
