#ifndef CRYSTAL_BUTTERFLY
#define CRYSTAL_BUTTERFLY

#include "ofMain.h"
#include "displays/Channel.h"
#include "globals.h"

class CrystalButterfly : public Channel {
public:
    virtual std::string getChannelName(){ return ofToString("cryst_butterfly"); }
    
    ofMesh temp;    

    float noiseOffset = 0;

    int mode = 0;

    int linesNo = 60;
    int vertexNo = 36;
    int vertexWidth = ofGetWindowWidth() / vertexNo;
    int vertexHeight = ofGetWindowHeight() / linesNo;
    float angleMultiplier = 360/vertexNo;
    float RADIAN = PI/180;
    void setup(){
        temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        setupModes(2);        
    }
    void update(){
        noiseOffset += 0.01;
    }
    void draw(){
        ofColor(255);
        ofNoFill();

        
        float zCalcAngle;
        float xyCalcAngle;
        float theta;
        int fftIndex;
        float radiusMultiplier;
        float noiseMultiplier;

        for(int layer = 0; layer < linesNo; layer++){

            for(int angle = 0; angle <= vertexNo; angle++){
                
                //float perlinRadius = ofNoise((float) sin((float) xyCalcAngle)*angle/20,ofGetElapsedTimef()/5);
                xyCalcAngle = angle*angleMultiplier*PI/180;
                if(getMode() == 0){
                    zCalcAngle = angle*angleMultiplier*TWO_PI/180;
                } else if(getMode() == 1) {
                    zCalcAngle = 0;
                }
                theta = angle/vertexNo*360*PI/180+noiseOffset;
                fftIndex = abs(angle-vertexNo/2); 
                if(getMode() == 0){
                    radiusMultiplier = fftBin[fftIndex]*10 + 5;
                    noiseMultiplier = (layer) * 5 + fftBin[fftIndex]*5;
                } else if(getMode() == 1){
                    radiusMultiplier = fftBin[fftIndex]*10 + 5;
                    noiseMultiplier = (layer) * 10;
                }

                temp.addVertex( ofVec3f(
                    sin(xyCalcAngle) * ofSignedNoise(sin((float) theta), (float) layer/20) * noiseMultiplier + sin(xyCalcAngle)*fftBin[fftIndex]*radiusMultiplier,
                    cos(xyCalcAngle) * ofSignedNoise(cos((float) theta), (float) layer/20) * noiseMultiplier + cos(xyCalcAngle)*fftBin[fftIndex]*radiusMultiplier,
                    sin(zCalcAngle) * ofSignedNoise(cos((float) theta), (float) layer/20) * noiseMultiplier + cos(zCalcAngle)*fftBin[fftIndex]*radiusMultiplier                    
                ) );

                temp.addVertex( ofVec3f(
                    sin(xyCalcAngle) * ofSignedNoise(sin((float) theta), (float) layer/20) * noiseMultiplier + sin(xyCalcAngle)*fftBin[fftIndex]*(radiusMultiplier+1),
                    cos(xyCalcAngle) * ofSignedNoise(cos((float) theta), (float) layer/20) * noiseMultiplier + cos(xyCalcAngle)*fftBin[fftIndex]*(radiusMultiplier+1),
                    sin(zCalcAngle) * ofSignedNoise(cos((float) theta), (float) layer/20) * noiseMultiplier + cos(zCalcAngle)*fftBin[fftIndex]*(radiusMultiplier+1)                    
                ) );
            }
            temp.draw();
            temp.clear();

        }

    }
};
#endif