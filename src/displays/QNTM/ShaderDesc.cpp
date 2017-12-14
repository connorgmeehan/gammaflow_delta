#ifndef SHADER_DESC
#define SHADER_DESC

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class ShaderDesc : public Channel {
public:
    ofTrueTypeFont smallFont;
    ofTrueTypeFont largeFont;
    void setup(){
        gfNoUseCam();
        largeFont.load("fonts/OpenSans-ExtraBold.ttf",72,true,true,true);
        smallFont.load("fonts/OpenSans-ExtraBold.ttf",8,true,true,true);

    }
    void update(){}
    void draw(){
        largeFont.drawStringAsShapes("QNTM_001", -ofGetWidth()/2 + 40, -ofGetHeight()/2+120);
        smallFont.drawStringAsShapes("openGL 3.2 frag shader reacting to audio", ofGetWidth()/2-350, ofGetHeight()/2-20);
    }
};

#endif