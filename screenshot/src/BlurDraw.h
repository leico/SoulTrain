//
//  Draw.h
//  basic
//
//  Created by leico on 2015/07/27.
//
//

#ifndef __basic__Draw__
#define __basic__Draw__

#include "ofMain.h"

class BlurDraw{


	public:
	ofFbo _front;
	ofFbo _back;
	int   _opacity;

	
	public:

	         BlurDraw(void);
	         BlurDraw(int width, int height, int opacity = 255);
	virtual ~BlurDraw();

	void setup(int width, int height, int opacity);

	int Opacity(void);
	int Opacity(int opacity);

	void begin(void);
	void end  (void);

	void draw(int x, int y);

	ofFbo& getFbo(void);
};



#endif /* defined(__basic__Draw__) */
