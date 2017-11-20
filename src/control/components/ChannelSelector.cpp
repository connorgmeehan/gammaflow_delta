#ifndef CHANNEL_SELECTOR
#define CHANNEL_SELECTOR

#include "globals.h"

#include "ofMain.h"
#include "control/ControlComponent.h"
#include "control/Dragable.cpp"
#include "engine/DisplayManager.h"

#include "ofxDatGui.h"

struct ChannelOption{
    string name;
    int channelId;
};

class ChannelSelector : public ControlComponent{
public:

    DisplayManager* dm;
    bool isPrimary;
    vector<ChannelOption> channelSelection;

    int toolbarSize = 10;
    int elementWidth;  
    int keyOffset = -1;
    int toolBarWidth = -1;

    char primaryKeys[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    char secondaryKeys[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')'};

    int hoverIndex = -1;
    int activeChannel = -1;
    int behaviourMode = 0; // 0 = NONE, 1 = SHUFFLE, 2 = CYCLE
    int triggerMode = 0; // 0 = KICK, 1 = SNARE, 2 = HIHAT
    int numberOfBeatsToWait = 4;
    int numberOfBeatsCounter = 0;

    //GUI ELEMENTS
    ofxDatGuiDropdown* behaviourDropdown;
    ofxDatGuiDropdown* triggerDropdown;

    vector<string> behaviourOptions = {"NONE", "SHUFFLE", "CYCLE"};
    vector<string> triggerOptions = {"KICK", "SNARE", "HAT"};

    ofxDatGuiSlider* numberOfBeatsSlider;
    ofParameter<int> numberOfBeatsParam;


    void setup(DisplayManager* _dm, bool _isPrimary){
        dm = _dm;
        toolBarWidth = getWidth()-200;
        elementWidth = toolBarWidth/toolbarSize;
        isPrimary = _isPrimary;
        if(isPrimary){
            keyOffset = 49;
        } else {
            keyOffset = 81;
        }

        behaviourDropdown = new ofxDatGuiDropdown("change by:", behaviourOptions);
        behaviourDropdown->setWidth(200,0.2);
        behaviourDropdown->setPosition(getX() + getWidth()-200, getY()-20);
        behaviourDropdown->onDropdownEvent(this, &ChannelSelector::onBehaviourChange);

        triggerDropdown = new ofxDatGuiDropdown("on:", triggerOptions);
        triggerDropdown->setWidth(200,0.2);
        triggerDropdown->setPosition(getX() + getWidth()-200, getY()+10);
        triggerDropdown->onDropdownEvent(this, &ChannelSelector::onTriggerChange);

        numberOfBeatsSlider = new ofxDatGuiSlider(numberOfBeatsParam.set("every number of beats:", 4, 1, 16));
        numberOfBeatsSlider->setWidth(200,0.2);
        numberOfBeatsSlider->setPosition(getX() + getWidth()-200, getY()+40);
        numberOfBeatsSlider->onSliderEvent(this, &ChannelSelector::onNumberOfBeatsChange);


    }

    void update(){
        calculateMouseLogic(ofGetMouseX()-getX(), ofGetMouseY()-getY());

        if(behaviourMode != 0){
            if(isBeats[triggerMode] == true){
                beatTriggered(behaviourMode);
            }
        }

        triggerDropdown->update();
        behaviourDropdown->update();
        numberOfBeatsSlider->update();
    } 

    void draw(){
        ofFill();
        for(int i = 0; i < toolbarSize; i++){
            int baseColor = 100;
            if(i < channelSelection.size()){
                baseColor += 50;
            }
            if(i == hoverIndex){
                baseColor += 50;
            }
            ofSetColor(baseColor);

            ofDrawRectangle(getX() + i*elementWidth, getY(), elementWidth-1, getHeight());

            if(i == activeChannel){
                ofSetColor(255,0,0);
                ofDrawRectangle(getX() + i*elementWidth +1, getY()+1, elementWidth-2, getHeight()-1);

            }

            if(i < channelSelection.size()){
                ofSetColor(255);
                if(isPrimary){
                    ofDrawBitmapString(primaryKeys[i], getX() + i*elementWidth, getY()+12);
                } else {
                    ofDrawBitmapString(secondaryKeys[i], getX() + i*elementWidth, getY()+12);
                }
                ofDrawBitmapString(channelSelection[i].name, getX() + i*elementWidth, getY()+24);
            }
        }
        numberOfBeatsSlider->draw();
        triggerDropdown->draw();
        behaviourDropdown->draw();
    }

    void calculateMouseLogic(int mx, int my){
        if(mx > 0 && mx < toolBarWidth && my > 0 && my < getHeight()){
            hoverIndex = mx / elementWidth;
            if(mouseClick){
                if(hoverIndex < channelSelection.size()){
                    dragable.setup(DRAG_CHANNEL_INDEX, channelSelection[hoverIndex].name, channelSelection[hoverIndex].channelId);
                    channelSelection.erase(channelSelection.begin() + hoverIndex);
                }
            }
            if(dragable.getDragType() == DRAG_CHANNEL_INDEX && mouseUnclick){
                addChannel(hoverIndex);
            }

        } else {
            hoverIndex = -1;
        }
    }
    void addChannel(int desiredIndex){
        if(desiredIndex > channelSelection.size()){
            channelSelection.push_back(ChannelOption{dragable.getName(), dragable.getValue()});
        } else {
            channelSelection.insert(channelSelection.begin() + desiredIndex, ChannelOption{dragable.getName(), dragable.getValue()} );
        }
    }

    void onKeyPress(int key){
        for(vector<ChannelOption>::size_type i = 0; i < channelSelection.size(); i++){
            if(isPrimary){
                if(key == primaryKeys[i]){
                    dm->setActivePrimary(channelSelection[i].channelId);
                }
            } else {
                if(key == secondaryKeys[i]){
                    dm->setActiveSecondary(channelSelection[i].channelId);
                }
            }
        }
    }

    void onBehaviourChange(ofxDatGuiDropdownEvent e){
        behaviourMode = e.child;
    }

    void onTriggerChange(ofxDatGuiDropdownEvent e){
        triggerMode = e.child;
    }

    void onNumberOfBeatsChange(ofxDatGuiSliderEvent e){
        numberOfBeatsToWait = e.value;
    }

    void beatTriggered(int _behaviourMode){
        numberOfBeatsCounter++;
        if(numberOfBeatsCounter >= numberOfBeatsToWait){
            numberOfBeatsCounter = 0;
            if(_behaviourMode == 1){
                activeChannel = ofRandom(channelSelection.size()-1);
            } else {
                if(channelSelection.size() != 0){
                    activeChannel = (activeChannel+1)%channelSelection.size();
                }
            }
            if(isPrimary){
                dm->setActivePrimary(channelSelection[activeChannel].channelId);
            }else{
                dm->setActiveSecondary(channelSelection[activeChannel].channelId);
            }
        }
    }
};

#endif