#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

#include "globals.h"

int screenWidth = 1024;
int screenHeight = 768;

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.width = screenWidth;
	settings.height = screenHeight;
	settings.setPosition(ofVec2f(700,0));
	settings.resizable = false;
	settings.setGLVersion(3,2);
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.width = screenWidth;
	settings.height = screenHeight;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = true;
	// uncomment next line to share main's OpenGL resources with gui
	settings.shareContextWith = mainWindow;	
	settings.setGLVersion(3,2);
	shared_ptr<ofAppBaseWindow> viewWindow = ofCreateWindow(settings);
	viewWindow->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);
	ofAddListener(viewWindow->events().update,mainApp.get(),&ofApp::updateView,OF_EVENT_ORDER_AFTER_APP);
	ofAddListener(viewWindow->events().draw,mainApp.get(),&ofApp::drawView,OF_EVENT_ORDER_AFTER_APP);
	

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
