#ifndef TEXT_FLOAT
#define TEXT_FLOAT

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class TextFloat : public Channel {
private:
    ofTrueTypeFont fontA, fontB;
    vector<ofPoint> fontAPos, fontBPos;
    std::string testString = "crackedit";
public:
    std::string getChannelName(){ return "text_float"; };

    void setup(){
        fontA.load("fonts/OpenSans-ExtraBold.ttf",40, true, true, true);
        fontB.load("fonts/OpenSans-ExtraBold.ttf",72, true, true, true);
        fontAPos.resize(10);
        fontBPos.resize(10);
    }
    void update(){
        if(snareAmp > 0.5){
            for(vector<ofPoint>::size_type i = 0; i < fontAPos.size(); i++){
                fontAPos[i] = ofPoint( ofRandom(-ofGetWidth()/2, ofGetWidth()/2), ofRandom(-ofGetHeight()/2,ofGetHeight()/2) );
                fontBPos[i] = ofPoint( ofRandom(-ofGetWidth()/2, ofGetWidth()/2), ofRandom(-ofGetHeight()/2,ofGetHeight()/2) );
            }
        }
    }
    void draw(){
        ofSetColor(255);
        ofFill();
        for(vector<ofVec3f>::size_type i = 0; i < snareAmp*10; i++){
            fontA.drawStringAsShapes(testString, fontAPos[i].x, fontAPos[i].y);
            fontB.drawStringAsShapes(testString, fontBPos[i].x, fontBPos[i].y);
        }   
    }
};

#endif