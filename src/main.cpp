#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.width = 1024;
	settings.height = 768;
	settings.setPosition(ofVec2f(700,0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.width = 1024;
	settings.height = 768;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = false;
	// uncomment next line to share main's OpenGL resources with gui
	//settings.shareContextWith = mainWindow;	
	shared_ptr<ofAppBaseWindow> viewWindow = ofCreateWindow(settings);
	viewWindow->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);
	ofAddListener(viewWindow->events().update,mainApp.get(),&ofApp::updateView);
	ofAddListener(viewWindow->events().draw,mainApp.get(),&ofApp::drawView);
	

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
