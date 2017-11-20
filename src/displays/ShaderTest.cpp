#ifndef SHADER_TEST
#define SHADER_TEST

#include "ofMain.h"
#include "displays/Channel.h"

class ShaderTest : public Channel {
public:
    std::string getChannelName(){ return "shader_test"; };

    ofShader shader;
    void setup(){
        shader.load("shaders/shader");
    }
    void update(){

    }
    void draw(){        
        ofSetColor(255);
        shader.begin();
        ofRectangle(-200, -200, 400, 400);
        //ofDrawSphere(0,0,0,200);
        shader.end();
    }
};

#endif