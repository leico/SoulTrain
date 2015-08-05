//
//  Draw.cpp
//  basic
//
//  Created by leico on 2015/07/27.
//
//

#include "BlurDraw.h"

BlurDraw :: BlurDraw(void){
}

BlurDraw :: ~BlurDraw(void){}

BlurDraw :: BlurDraw(int width, int height, int opacity) :
_opacity(opacity)
{
	_front.allocate(width, height, GL_RGBA);
	_back = _front;
}

void BlurDraw :: setup(int width, int height, int opacity){
    _front.allocate(width, height);
    _back    = _front;
    _opacity = opacity;
	return;
}

int BlurDraw :: Opacity(void){
	return _opacity;
}

int BlurDraw :: Opacity(int opacity){
	_opacity = opacity;
	return Opacity();
}

void BlurDraw :: begin(void){
	_front.begin();

	ofSetColor(_opacity, _opacity);
	_back.draw(0, 0);
	return;
}

void BlurDraw :: end(void){
	_front.end();
	_back = _front;
	return;
}

void BlurDraw :: draw(int x, int y){
	_front.draw(x, y);
}

