#ifndef SHADER_TEST
#define SHADER_TEST

#include "ofMain.h"
#include "displays/Channel.h"
#include "globals.h"

class ShaderTest : public Channel {
public:
    std::string getChannelName(){ return "shader_test"; };
    std::string path = "shader";
    bool useShader = false;

    ofShader shader;

    float param1, param2, param3;
    ofVec2f shaderTranslate = ofVec2f(0.5, 0.5);
    void setup(){
        setupChannelGui();
        getChannelGui()->addTextInput("path", path);
        getChannelGui()->getTextInput("path")->setTextUpperCase(false);
        getChannelGui()->addButton("Reload");

        getChannelGui()->addFolder("Parameters");
        getChannelGui()->getFolder("Parameters")->addSlider("param1", 0.0001, 10,0.3);
        getChannelGui()->getFolder("Parameters")->addSlider("param2", 0.0001, 10,0.3);
        getChannelGui()->getFolder("Parameters")->addSlider("param2", 0.0001, 10,0.3);
        getChannelGui()->onSliderEvent(this, &ShaderTest::onSliderEvent);

        getChannelGui()->add2dPad("transform",ofRectangle(0, 0, 1, -1));
        getChannelGui()->onTextInputEvent(this, &ShaderTest::onTextInputEvent);
        getChannelGui()->onButtonEvent(this, &ShaderTest::onButtonEvent);
        getChannelGui()->on2dPadEvent(this, &ShaderTest::on2dPadEvent);

        param1 = param2 = param3 = 0;
        
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

        shader.begin(); 
        shader.setUniform2f("u_resolution", 1024, 768);
        shader.setUniform2f("u_mouse", ofGetMouseX(), ofGetMouseY());
        shader.setUniform1f("u_time", ofGetElapsedTimef());
        shader.setUniform1f("pulse", volume);
        shader.setUniform1f("param1", param1);
        shader.setUniform1f("param2", param2);
        shader.setUniform1f("param3", param3);

        shader.setUniform1f("kick", kickAmp);
        shader.setUniform1f("snare", snareAmp);
        shader.setUniform1f("hihat", hatAmp);

        shader.setUniform2f("u_translate", shaderTranslate);

        float cx = ofGetWidth() / 2.0;
        float cy = ofGetHeight() / 2.0;

        // the plane is being position in the middle of the screen,
        // so we have to apply the same offset to the mouse coordinates before passing into the shader.
        float mx = ofGetMouseX() - cx;
        float my = ofGetMouseY() - cy;

        // we can pass in a single value into the shader by using the setUniform1 function.
        // if you want to pass in a float value, use setUniform1f.
        // if you want to pass in a integer value, use setUniform1i.
        shader.setUniform1f("mouseRange", 150); // SET A UNIFORM

        // we can pass in two values into the shader at the same time by using the setUniform2 function.
        // inside the shader these two values are set inside a vec2 object.


        //ofRectangle(-200, -200, 400, 400);
        ofDrawSphere(0,0,0,200);
        shader.end();
    }
    void onTextInputEvent(ofxDatGuiTextInputEvent e){
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

    void onSliderEvent(ofxDatGuiSliderEvent e){
        if(e.target->getLabel() == "param1"){
             param1 = e.value;
        } else if(e.target->getLabel() == "param2"){
            param2 = e.value;
        } else if(e.target->getLabel() == "param3"){
            param3 = e.value;
        }
    }

    void on2dPadEvent(ofxDatGui2dPadEvent e){
        shaderTranslate.x = e.x;
        shaderTranslate.y = e.y;
    }
};

#endif