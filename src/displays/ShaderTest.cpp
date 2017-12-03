#ifndef SHADER_TEST
#define SHADER_TEST

#include "ofMain.h"
#include "displays/Channel.h"

class ShaderTest : public Channel {
public:
    std::string getChannelName(){ return "shader_test"; };
    std::string path = "shader";
    bool useShader = false;

    ofShader shader;
    void setup(){
        setupChannelGui();
        getChannelGui()->addLabel("starts inside of ./shaders/");
        getChannelGui()->addTextInput("path", path);
        getChannelGui()->getTextInput("path")->setTextUpperCase(false);
        getChannelGui()->addButton("Reload Shader");
        getChannelGui()->addToggle("Use Shader");
        getChannelGui()->onButtonEvent(this, &ShaderTest::onButtonEvent);
        getChannelGui()->onToggleEvent(this, &ShaderTest::onToggleEvent);
        
        #ifdef TARGET_OPENGLES
            shader.load("shaders/shadersES2/shader");
        #else
            if(ofIsGLProgrammableRenderer()){
                shader.load("shaders/shadersGL3/shader");
            }else{
                shader.load("shaders/shadersGL2/shader");
            }
        #endif

    }
    void update(){

    }
    void draw(){        
        ofFill();
        ofSetLineWidth(4);
        ofSetColor(255);

        if(useShader){
            shader.begin(); 
        }
        //ofRectangle(-200, -200, 400, 400);
        ofDrawSphere(0,0,0,200);
        if(useShader){ shader.end(); }
    }
    void onButtonEvent(ofxDatGuiButtonEvent e){
        path = "shaders/";

        #ifdef TARGET_OPENGLES
            path += "shadersES2/";
        #else
            if(ofIsGLProgrammableRenderer()){
                path += "shadersGL3/";
            }else{
                path += "shadersGL2/";
            }
        #endif
        path += getChannelGui()->getTextInput("path")->getText();
        shader.load(path);
        ofLogNotice() << "path is " << path << " abs path is " << ofFilePath::getAbsolutePath(path, true) << " alt abs path is " << ofToDataPath(path, true) << endl;

        ofLog(OF_LOG_NOTICE) << "ShaderTest::onButtonEvent reloading shader! shaders/"+path+".vert/.frag";
    }

    void onToggleEvent(ofxDatGuiToggleEvent e){
        useShader = e.target->getChecked();
    }
};

#endif