#ifndef TRIG_DEATH
#define TRIG_DEATH

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class TrigDeath : public Channel {
public:
    virtual std::string getChannelName(){ return ofToString("trig_death"); }
    ofMesh temp;
    int mode = 0;

    int latNo = 32;
    int longNo = 100;
    int radius = -1;
    int baseRadius = 400;
    int radiusMultiplier = 400;

    float angleMult = 360/latNo;

    void setup(){
        gfNoUseCam();
        temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }

    void update(){
        
    }

    ofVec3f vec;
    void draw(){
        if(mode == 0){
            draw1();
        } else {
            draw2();
        }
    }

        void draw1(){
        for(int layer = 0; layer < latNo; layer++){
            temp.clear();
            radius = baseRadius + fftBin[layer] * radiusMultiplier;
            for(int vert = 0; vert < longNo; vert++){

                if(ofSignedNoise((float) layer/10, (float) vert/10, ofGetElapsedTimef()/2) * 4 < volume * 4){
                    temp.draw();
                    temp.clear();
                    continue;
                }
                vec.x = cos(ofDegToRad(layer*angleMult)) * cos(ofDegToRad(vert*angleMult));
                vec.y = cos(ofDegToRad(layer*angleMult)) * sin(ofDegToRad(vert*angleMult));
                vec.z = sin(ofDegToRad(-layer*angleMult/2));
                temp.addVertex(vec * radius);
                temp.addVertex(vec * (radius+5));
            }
            temp.draw();
        }
    }
        void draw2(){
        for(int layer = 0; layer < latNo; layer++){
            temp.clear();
            radius = baseRadius + fftBin[layer] * radiusMultiplier;
            for(int vert = 0; vert < longNo; vert++){

                if(ofSignedNoise((float) layer/10, (float) vert/10, ofGetElapsedTimef()/2) * 4 < volume * 4){
                    temp.draw();
                    temp.clear();
                    continue;
                }
                vec.x = cos(ofDegToRad(layer*angleMult)) * cos(ofDegToRad(vert*angleMult));
                vec.y = cos(ofDegToRad(layer*angleMult)) * sin(ofDegToRad(vert*angleMult));
                vec.z = sin(ofDegToRad(-layer*angleMult/2));
                temp.addVertex(vec * radius);
                temp.addVertex(vec * (radius+5));
            }
            temp.draw();
        }
    }
};

#endif