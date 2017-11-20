#ifndef INTERFACE_CIRCLE
#define INTERFACE_CIRCLE

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class InterfaceCircle : public Channel {
private:
    int numWide = 32;
    int numHigh = 32;
    int numberOfCirclePlanes = 1;
    int circleRadius;
    int circleDistance;
    float scale = 10.0f;

    vector<float> volHistory;

    float theta = 0.0f;
    float phi = 0.0f;
public:
    virtual std::string getChannelName(){ return ofToString("interface_cirlces"); }

    void setup(){
        volHistory.resize(numWide/2);
    }
    void update(){
        theta += 0.002f;
        phi += 0.002f;
        volHistory.insert(volHistory.begin(), volume);
        volHistory.pop_back();
    }
    void draw(){
        draw(numberOfCirclePlanes);
        /*ofSetColor(255);
        ofNoFill();
        ofSetLineWidth(1);
        for(int i = 0; i < numberOfCirclePlanes; i++){
            circleRadius = sin(i+theta)*fftBin[i*10];
            for(int x = 0; x < numWide; x++){
                for(int y = 0; y < numHigh; y++){
                    ofDrawCircle(x*circleRadius, y*circleRadius, circleRadius);
                }
            }
        }*/
    }

    void draw(int numberToDraw){
        ofSetColor(255);
        ofNoFill();
        ofSetLineWidth(1);
        if(numberToDraw > 0){
            draw(numberToDraw-1);
        }
        ofPushMatrix();
        ofRotate(
            ofSignedNoise(numberToDraw, phi)*50, 
            ofSignedNoise(numberToDraw, theta+50)*10, 
            ofSignedNoise(numberToDraw, phi+100)*10, 
            90
        );
        ofTranslate(
            0,0, ofSignedNoise(numberToDraw, theta+2)*10
        );
            circleRadius = sin(numberToDraw+theta)*fftBin[numberToDraw*10]*scale;
            circleDistance = 30+((circleDistance + fftBin[numberToDraw*10]*20) / 2);
            for(int x = -numWide/2; x < numWide/2; x++){
                for(int y = -numHigh/2; y < numHigh/2; y++){
                    ofSetLineWidth(volHistory[abs(x+y)]*5);
                    ofDrawCircle(x*circleDistance, y*circleDistance, volHistory[abs(x+y)]*20, 35 + circleRadius);
                }
            }
        ofPopMatrix();
    }
};

#endif