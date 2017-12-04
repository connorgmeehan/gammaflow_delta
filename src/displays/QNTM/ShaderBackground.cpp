#ifndef SHADER_BACKGROUND
#define SHADER_BACKGROUND

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class ShaderBackground : public Channel{
public:
    std::string getChannelName(){ return "shader_background"; };
    ofShader shader;
    ofVec2f shaderTranslate = ofVec2f(0.5, -0.5);
    void setup(){
        shader.load("shaders/shadersGL3/quantum/interference");
    }
    void update(){}
    void draw(){
        shader.begin();
        shader.setUniform2f("u_resolution", 1024, 768);

        shader.setUniform2f("u_mouse", ofGetMouseX(), ofGetMouseY());
        shader.setUniform1f("u_time", ofGetElapsedTimef());

        shader.setUniform1f("pulse", volume);

        shader.setUniform1f("kick", kickAmp);
        shader.setUniform1f("snare", snareAmp);
        shader.setUniform1f("hihat", hatAmp);

        shader.setUniform2f("u_translate", shaderTranslate);
        ofDrawRectangle(-4000,-4000,4000,4000);
        shader.end();
    }
};

#endif