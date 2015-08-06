#include "ofMain.h"
#include "ofApp.h"

int main(){
	ofAppiOSWindow *window = new ofAppiOSWindow();

	//window -> enableRendererES2 ();
	window -> enableDepthBuffer ();
	window -> enableAntiAliasing(4);
	
	if( window -> isRetinaSupportedOnDevice() )
		window -> enableRetina();

	ofSetupOpenGL(window, 1024, 768, OF_FULLSCREEN);



	ofRunApp(new ofApp);
}
