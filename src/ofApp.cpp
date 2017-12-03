#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofLog(OF_LOG_NOTICE) << "ofApp::setup() - @"<< ofGetElapsedTimef() << "s";
	//SETUP ENVIRONMENT
	ofSetVerticalSync(false);
	ofSetFrameRate(60);
	//SETUP AUDIO ANALYSER
	aa.setup(5);
	//SETUP DISPLAY MANAGER
	dm.setup();
	//SETUP CONTROL PANEL
	cp.setup(&aa, &dm);
}

//--------------------------------------------------------------
void ofApp::updateControl(ofEventArgs & args){
	//UPDATE AUDIO ANALYSER
	aa.update();
	cp.update();
}

void ofApp::drawControl(ofEventArgs & args){
	ofClear(0);
	cp.draw();
}

// THIS RUNS AFTER updateControl
void ofApp::update(){
	//UPDATE CONTROL PANEL SO IT CAN MAKE CHANGES TO THE DISPLAY MANAGER
	dm.update();
}

//--------------------------------------------------------------
void ofApp::draw(){	
	ofClear(0);
	dm.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	cp.onKeyPress(key);
	dm.recKeyDown(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
