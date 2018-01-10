#ifndef CHANNEL
#define CHANNEL

#include "ofMain.h"
#include "ofxDatGui.h"

class Channel {
public:
    virtual std::string getChannelName(){ return ofToString("general_channel"); }

    bool useCam = true;
    bool hasBeenSetup = false;

    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    
    virtual bool getHasBeenSetup(){ return hasBeenSetup; }
    virtual bool setHasBeenSetup(bool _input){ hasBeenSetup = _input; }
    /* BEAT DETECTION FUNCTIONS */
    #pragma region BEAT_INTERACTIVITY_FUNCTIONS
    virtual void onSnare(float amp = -1){};
    virtual void onKick(float amp = -1){};
    virtual void onHat(float amp = -1){};
    #pragma endregion

    /* POSITIONING FUNCTIONS AND VARIABLES */
    #pragma region POSITIONING_FUNCTIONS AND VARIABLES
    ofPoint translate = ofPoint(0, 0, 0);
    ofVec4f rotate = ofVec4f(0,0,0,0);

    virtual ofPoint getTranslate(){ return translate; }
    virtual ofVec4f getRotate(){ return rotate; }
    virtual void setTranslate(ofPoint _p){ translate = _p; }
    virtual void setRotate(ofPoint _r){ rotate = _r; }
    #pragma endregion

    #pragma region CAMERA_USE_FUNCTIONS
    virtual void gfUseCam(){ 
        if(!useCam){
            translate.x -= ofGetWidth()/2; 
            translate.y -= ofGetHeight()/2; 
        }
        useCam = true; 
    }
    virtual void gfNoUseCam(){
        if(useCam){
            translate.x += ofGetWidth()/2; 
            translate.y += ofGetHeight()/2; 
        }
        useCam = false; 
    }
    virtual bool gfGetUseCam(){ return useCam; }
    #pragma endregion
    

    //MODE FUNCTIONS AND VARIABLES
    #pragma region MODE
    bool isModeSetup = false;
    ofParameter<int> triggerInterval = 4;
    int triggerIndex = 0;
    int modeLength = 1;
    ofParameter<int> modeIndex;

    virtual void setupModes(int _modeLength){
        ofLog(OF_LOG_NOTICE) << "Channel::setupModes(_modeLength " << _modeLength << ");";
        if(!isModeSetup){
            ofLog(OF_LOG_NOTICE) << "Setting up modes with a mode length of " << _modeLength << " on " << getChannelName();
            isModeSetup = true;
            if(!isGuiSetup){
                setupChannelGui();
            }
            modeLength = _modeLength;
            modeIndex.set("mode: ", 0, 0, modeLength-1);
            triggerInterval.set("trigger interval: ", 2, 1, 16);
            getChannelGui()->addHeader("MODE CONTROLS");
            getChannelGui()->addSlider(modeIndex);
            getChannelGui()->addSlider(triggerInterval);
            getChannelGui()->setPosition(250, 536);
            getChannelGui()->onSliderEvent(this, &Channel::onModeChangeEvent);
            getChannelGui()->addFooter();
        }
    }

    virtual void onModeChangeEvent(ofxDatGuiSliderEvent e){
        if(e.target->getLabel() == "mode: "){
            modeIndex = e.value;
        } else if(e.target->getLabel() == "trigger interval: "){
            triggerInterval = e.value;
        }
        onSliderEvent(e);
    }
    virtual void onSliderEvent(ofxDatGuiSliderEvent e){
        //overload this for in app functionality;
    }

    virtual void setModeLength(int _modeLength){
        modeLength = _modeLength;
        if(modeIndex > modeLength){
            modeIndex = modeLength;
        }
    }
    virtual int getModeLength(){ return modeLength; }
    virtual void setMode(int _mode){ modeIndex = _mode;}
    virtual int getMode(){ return modeIndex; }

    virtual void cycleMode(){
        if(modeLength != 1){
            triggerIndex++;
            if(triggerIndex >= triggerInterval){
                triggerIndex = 0;
                modeIndex = (modeIndex + 1) % modeLength;
                onModeChange(modeIndex);
            }
            modeIndex = (modeIndex + 1) % modeLength;
        }
    }

    virtual void shuffleMode(){
        if(modeLength!= 1){
            triggerIndex++;
            if(triggerIndex >= triggerInterval){
                triggerIndex = 0;
                modeIndex = ofRandom(modeLength);
                onModeChange(modeIndex);
            } 
        }
    }

    virtual void setTriggerInterval(int _triggerInterval){ triggerInterval = _triggerInterval; }
    virtual int getTriggerInterval(){ return triggerInterval; }
    virtual void onModeChange(int _mode){};
    #pragma endregion

    /* INPUT FUNCTIONS AND VARIABLES */
    virtual void recKeyDown(int key){};
    ofxDatGui* channelGui;
    bool isGuiSetup = false;
    virtual ofxDatGui* getChannelGui(){ return channelGui; }
    virtual void setupChannelGui(){ 
        if(!isGuiSetup){
            isGuiSetup = true;
            channelGui = new ofxDatGui(250, 536);
            if(isModeSetup){
                channelGui->setPosition(250,536);
            }
            channelGui->addHeader(ofToString(getChannelName()), false);
            channelGui->setWidth(512, 0.2); 
            channelGui->setAutoDraw(false,0);
        }
    }
    virtual bool hasGui(){ return isGuiSetup; }


};

#endif