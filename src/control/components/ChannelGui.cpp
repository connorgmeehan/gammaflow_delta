#ifndef CHANNEL_GUI
#define CHANNEL_GUI

#include "ofMain.h"
#include "control/ControlComponent.h"
#include "engine/DisplayManager.h"
#include "ofxDatGui.h"

class ChannelGui : public ControlComponent{
public:
    DisplayManager* dm;
    int primaryIndex = -1;
    int secondaryIndex = -1;
    bool displayPrimary = true;
    void setup(DisplayManager* _dm){
        dm = _dm;
    }   
    void update(){

        calculateMouseLogic(ofGetMouseX()-getX(), ofGetMouseY()-getY());

        if(displayPrimary){
            if(primaryIndex != -1){
                if(dm->hasGui(primaryIndex)){
                    dm->getChannelGui(primaryIndex)->update();
                }
            }
        } else {
            if(secondaryIndex != -1){
                if(dm->hasGui(secondaryIndex)){
                    dm->getChannelGui(secondaryIndex)->update();
                }
            }
        }
    } 
    void draw(){
        if(displayPrimary){
            if(primaryIndex != -1){
                if(dm->hasGui(primaryIndex)){
                    dm->getChannelGui(primaryIndex)->draw();
                }
            }
        } else {
            if(secondaryIndex != -1){
                if(dm->hasGui(secondaryIndex)){
                    dm->getChannelGui(secondaryIndex)->draw();
                }
            }
        }
    }

    void setChannelGui(int _channelIndex, bool _isPrimary){
        ofLog(OF_LOG_NOTICE) << "ChannelGui::setChannelGui(_channelIndex = " << _channelIndex << ", _isPrimary = " << _isPrimary << ");";
        if(_isPrimary){
            primaryIndex = _channelIndex;
        } else {
            secondaryIndex = _channelIndex;
        }
        ofLog(OF_LOG_NOTICE) << "       ChannelGui::setChannelGui(); DONE!";
    }

    void calculateMouseLogic(int mx, int my){
        if(mx > 0 && mx < getWidth() && my > -getTopGap() && my < 0){
            if(mouseClick){
                displayPrimary = !displayPrimary;
                if(displayPrimary){
                    setName(ofToString("Channel Gui: Primary"));
                } else {
                    setName(ofToString("Channel Gui: Secondary"));
                }
            }
        }
    }
};

#endif