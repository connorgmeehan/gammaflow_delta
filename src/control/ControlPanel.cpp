#include "control/ControlPanel.h"

Dragable dragable;

bool mouseClick = false;
bool mouseUnclick = false;

void ControlPanel::setup(AudioAnalyser* _aa, DisplayManager* _dm){
	ofLog(OF_LOG_NOTICE) << "ofApp.ControlPanel::setup() - @"<< ofGetElapsedTimef() << "s";
    
    aa = _aa;
    dm = _dm;

    fftDisplay.pre_setup( ofToString("FFT Display: "), 250, 250, 512, 256);
    fftDisplay.setup(aa);

    channelBank.pre_setup( ofToString("Channel Bank"), 10,250,230,400);
    channelBank.setup(dm);

    channelGui.pre_setup( ofToString("Channel Gui"), 250, 516, 512, 256);
    channelGui.setup(dm);

    primarySelector.pre_setup( ofToString("Primary Channels"), 10, 50, 1000, 90);
    primarySelector.setup(dm, &channelGui, true);

    secondarySelector.pre_setup( ofToString("Secondary Channels (hold shift)"), 10, 150, 1000, 90);
    secondarySelector.setup(dm, &channelGui, false);

    controlComponents.push_back(&channelBank);
    controlComponents.push_back(&fftDisplay);
    controlComponents.push_back(&secondarySelector);
    controlComponents.push_back(&primarySelector);
    controlComponents.push_back(&channelGui);
}

void ControlPanel::update(){
    if(!mouseDownLastFrame && ofGetMousePressed()){
        mouseClick = true;
        mouseUnclick = false;
    } else if(mouseDownLastFrame && !ofGetMousePressed()){
        mouseClick = false;
        mouseUnclick = true;
    } else {
        mouseUnclick = mouseClick = false;
    }
    mouseDownLastFrame = ofGetMousePressed();

    for(vector<ControlComponent>::size_type i = 0; i < controlComponents.size(); i++){
        controlComponents[i]->update();
    }
    if(mouseUnclick){
        dragable.reset();
    }
}

void ControlPanel::draw(){
    for(vector<ControlComponent>::size_type i = 0; i < controlComponents.size(); i++){
        controlComponents[i]->pre_draw();
        controlComponents[i]->draw();
    }

    drawDragable();
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()) + ofToString("fps"), 1000, 12);
    
}

void ControlPanel::drawDragable(){
    if(dragable.getDragType() != DRAG_EMPTY){
        if(dragable.getDragType() == DRAG_BEAT_ZONE_INDEX){
            ofSetColor(255);
            ofNoFill();
            ofSetLineWidth(2);
            ofDrawCircle(ofGetMouseX(), ofGetMouseY(),4);
        } else {
            //DEFAULT DRAW
            ofSetColor(255);
            ofFill();
            ofSetLineWidth(1);
            ofDrawRectangle(ofGetMouseX() - dragable.name.length()*4, ofGetMouseY()-12, dragable.name.length()*8, 30);
            ofSetColor(0);
            ofDrawBitmapString(dragable.getName(), ofGetMouseX() - dragable.getName().length()*4, ofGetMouseY());
            ofDrawBitmapString(dragable.getValue(), ofGetMouseX() - ofToString(dragable.getValue()).length()*4, ofGetMouseY()+12);
            
        }
    }
}

void ControlPanel::onKeyPress(int key){
    ofLog(OF_LOG_NOTICE) << key;
    for(vector<ControlComponent>::size_type i = 0; i < controlComponents.size(); i++){
        controlComponents[i]->onKeyPress(key);
    }
}
