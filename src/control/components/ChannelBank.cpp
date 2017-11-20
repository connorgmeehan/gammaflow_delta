#ifndef CHANNEL_BANK
#define CHANNEL_BANK

#include "ofMain.h"
#include "control/ControlComponent.h"
#include "engine/DisplayManager.h"

#include "control/Dragable.cpp"
class ChannelBank : public ControlComponent {
public:
    DisplayManager* dm;
    vector<std::string> channelList;
    int elHeight = 20;
    int hoverIndex = -1;
    void setup(DisplayManager* _dm){
        dm = _dm;
        channelList.resize(dm->getChannelBankSize());
        for(vector<std::string>::size_type i = 0; i < channelList.size(); i++){
            channelList[i] = dm->getChannelName(i);
        }
    }

    void update(){
        //FIGURE OUT HOW TO DO EFFICIENT MOUSE LOGIC
        calculateMouseLogic(ofGetMouseX()-getX(), ofGetMouseY()-getY());
    }

    void draw(){
        ofNoFill();
        ofSetColor(200);
        ofSetLineWidth(1);
        for(vector<std::string>::size_type i = 0; i < channelList.size(); i++){
            if(hoverIndex == i){
                ofSetColor(255);
            } else {
                ofSetColor(200);
            }
            ofDrawRectangle(getX(), getY() + (i* elHeight), getWidth(), elHeight);
            ofDrawBitmapString(channelList[i], getX()+3, getY() + (i* elHeight) + elHeight*0.7);
        }
    }

    void calculateMouseLogic(int mx, int my){
        if(mx > 0 && mx < getWidth() && my > 0 && my < getHeight()){
            hoverIndex = my / elHeight;

            if(mouseClick){

                if(hoverIndex < channelList.size()){
                    dragable.setup(DRAG_CHANNEL_INDEX, channelList[hoverIndex], hoverIndex);
                }

            }
        }
    }
};

#endif