#ifndef PERLIN_OCTOPUS
#define PERLIN_OCTOPUS

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class PerlinOctopus : public Channel {
public:
    std::string getChannelName(){ return "perlin_octopus(TODO)"; };
    
    int numberOfTentacles = 10;
    int pointsPerTentacle = 20;

    float displayScale = 1600;
    float pointSpacing = 40;

    ofMesh tempTentacle;
    void setup(){
        ofSetCircleResolution(4);
        ofSetSphereResolution(4);
        tempTentacle.setMode(OF_PRIMITIVE_LINE_STRIP);
    }

    void update(){
        pointSpacing = fftBin[3]*displayScale;
        pointsPerTentacle = fftBin[0]*displayScale/2;
    }

    void draw(){
        ofSetColor(255);
        for(int i = 0; i < numberOfTentacles; i++){
            tempTentacle.clear();
            for(int p = 0 ; p < pointsPerTentacle; p++){
                tempTentacle.addVertex( ofVec3f(
                    ofSignedNoise(i+1,(float) (i)/100 )*pointSpacing,
                    ofSignedNoise(i+2,(float) (i)/100 )*pointSpacing,
                    ofSignedNoise(i+3,(float) (i)/100 )*pointSpacing
                ) );
            }
            tempTentacle.draw();
        }
    }
};

#endif