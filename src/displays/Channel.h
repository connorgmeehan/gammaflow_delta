#ifndef CHANNEL
#define CHANNEL

#include "ofMain.h"

class Channel {
public:
    virtual std::string getChannelName(){ return ofToString("general_channel"); }

    ofPoint translate = ofPoint(0, 0, 0);
    ofVec4f rotate = ofVec4f(0,0,0,0);
    bool useCam = true;
    bool isPrimary = true;

    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    
    virtual void recKeyDown(int key){};
    virtual void onSnare(float amp){};
    virtual void onKick(float amp){};
    virtual void onHat(float amp){};

    virtual ofPoint getTranslate(){ return translate; }
    virtual ofVec4f getRotate(){ return rotate; }
    virtual void setTranslate(ofPoint _p){ translate = _p; }
    virtual void setRotate(ofPoint _r){ rotate = _r; }

    virtual void setPrimary(bool _isPrimary){ isPrimary = _isPrimary; }

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
    

    //MODE FUNCTIONS AND VARIABLES
    int triggerInterval = 4;
    int triggerIndex = 0;
    int modeLength = 1;
    int modeIndex = 0;

    virtual void setModeLength(int _modeLength){ modeLength = _modeLength; }
    virtual int getModeLength(){ return modeLength; }
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


};

#endif