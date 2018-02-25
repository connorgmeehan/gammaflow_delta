#ifndef DATA_FLOOD
#define DATA_FLOOD

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class PointCloud : public Channel {
    string getChannelName(){ return ofToString("point_cloud"); }

    int pointNumber = 800;
    float pointSpeedMultiplier = 0.12; // 1 = instant
    
    vector<ofVec3f> points;
    vector<ofVec3f> pointsTarget;

    int modeCounter = 0;
    int modeChangeThreshold = 4;
    int mode = 0;
    int modeLength = 2;

    int snareCounter = 0;

    bool doLinks = false;
    int numberOfLinks = 2 ;
    int numberOfLinksMultiplier = pointNumber/numberOfLinks;

    int fftBinIndex = 0;

    void setup(){
        gfUseCam();
        setCurrentModeLength(3);
        points.resize(pointNumber);
        pointsTarget.resize(pointNumber);
        for(int i = 0; i < pointNumber; i++){
            pointsTarget[i] = ofVec3f(
                ofSignedNoise(1,(float) (i)/100 )*100,
                ofSignedNoise(2,(float) (i)/100 )*100,
                ofSignedNoise(3,(float) (i)/100 )*100
            );
            points[i] = ofVec3f(0,0,0);
        }
    }

    void update(){
        fftBinIndex++;
        for(int i = 0; i < pointNumber; i++){
            points[i] -= (points[i] - pointsTarget[i])*pointSpeedMultiplier;
            
        }
    }

    void draw(){
        for(int i = 0; i < pointNumber; i++){
            ofDrawCircle(points[i]*(0.8+fftBin[(fftBinIndex+i)%fftBin.size()]),1);
            if(doLinks){
                ofSetLineWidth(0.5);
                for(int j = 0; j < numberOfLinks; j++){
                    ofDrawLine(points[i + j*numberOfLinksMultiplier], points[i]);
                }
            }
        }
    }

    void onModeChange(int mode){

    }

    void onKick(float amp){

        cycleMode();

        for(int i = 0; i < pointNumber; i++){
            switch(mode){
                case 0:
                pointsTarget[i] = ofVec3f(
                    ofSignedNoise((float) (i+fftBin[i]) )*1200,
                    ofSignedNoise((float) (i+fftBin[i]+1000) )*1200,
                    ofSignedNoise((float) (i+fftBin[i]+2000) )*1200
                );
                break;

                case 1:
                pointsTarget[i] = ofVec3f(
                    ofSignedNoise(1,(float) (i)/50 )*200,
                    ofSignedNoise(2,(float) (i)/50 )*200,
                    ofSignedNoise(3,(float) (i)/50 )*200
                );
            }
        }
    }
    
    void onSnare(float amp){
        snareCounter++;
        ofLog(OF_LOG_VERBOSE) << "PointCloud Snare Active" << snareCounter << ", " << doLinks;
        if(snareCounter > 8){
            doLinks = !doLinks;
            snareCounter = 0;
        }
    }
};
#endif