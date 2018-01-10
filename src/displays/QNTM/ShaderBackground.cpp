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
    
    std::string basePath = "";
    std::string extensionPath = "./";
    ofDirectory activeDirectory;
    vector<ofShader> shaders;
    int shaderIndex = 0;

    ofVec3f kickMom, snareMom, hihatMom; // stores a 3d vector of the momentum of a beat in a randomised direction;
    ofVec3f kickPos, snarePos, hihatsPos; // stores a 3d vector of the momentum of a beat in a randomised direction;

    ofParameter<int> triggerInterval;

    void setup(){
        ofLog(OF_LOG_NOTICE) << "ShaderBackground::setup() ("<< ofGetElapsedTimef() << ");";
        
        #ifdef TARGET_OPENGLES
            basePath = "shaders/shadersES2/";
        #else
            if(ofIsGLProgrammableRenderer()){
                basePath = "shaders/shadersGL3/";
            }else{
                basePath = "shaders/shadersGL2/";
            }
        #endif
        
        setupModes(0);

        loadShaders(basePath + extensionPath);

        setupChannelGui();
        getChannelGui()->addTextInput("FolderPath","./");
        getChannelGui()->getTextInput("FolderPath")->setTextUpperCase(false);
        getChannelGui()->onTextInputEvent(this, &ShaderBackground::onTextInputEvent);
        getChannelGui()->addButton("Reload");
        getChannelGui()->onButtonEvent(this, &ShaderBackground::onButtonEvent);
        getChannelGui()->addSlider(triggerInterval.set("Trigger Interval", 4, 1, 4));
        getChannelGui()->onSliderEvent(this, &ShaderBackground::onSliderEvent);

        kickMom = snareMom = hihatMom = ofVec3f(0,0,0);
    }
    void update(){

    }
    void draw(){
        if(getMode()  < shaders.size()){
            ofFill();
            shaders[ getMode() ].begin();
            shaders[ getMode() ].setUniform2f("u_resolution", 1024, 768);

            shaders[ getMode() ].setUniform2f("u_mouse", ofGetMouseX(), ofGetMouseY());
            shaders[ getMode() ].setUniform1f("u_time", ofGetElapsedTimef());

            shaders[ getMode() ].setUniform1f("pulse", volume);

            shaders[ getMode() ].setUniform1f("kick", kickAmp);
            shaders[ getMode() ].setUniform1f("snare", snareAmp);
            shaders[ getMode() ].setUniform1f("hihat", hatAmp);

            shaders[ getMode() ].setUniform3f("kickmom", kickMom);
            shaders[ getMode() ].setUniform3f("snaremom", snareMom);
            shaders[ getMode() ].setUniform3f("hihatmom", hihatMom);

            shaders[ getMode() ].setUniform2f("u_translate", shaderTranslate);
            ofDrawSphere(0,0,1000);
            shaders[ getMode() ].end();
        }

        for(int i = 0; i < activeDirectory.size(); i++){
            std::string currentShader = activeDirectory.getPath(i);
            if( getMode()  == i){
                currentShader+= " *";
            }
        }
    }

    string loadShaders(std::string _inputPath){
        ofLog(OF_LOG_NOTICE) << "ShaderBackground::loadShaders(_inputPath = " << _inputPath << ");";
        //reset shader buffer to clear all old shaders
        shaders.resize(0);
        //search only for .frag files
        activeDirectory = ofDirectory(_inputPath);

        if(!activeDirectory.isDirectory()){
            return std::string("NOT VALID DIRECTORY");
        }

        activeDirectory.allowExt("frag");
        activeDirectory.listDir();

        for(int i = 0; i < activeDirectory.size(); i++){
            ofLog() << activeDirectory.getPath(i);
            //remove the .frag part of the shader path, load it and push it to the shader buffer
            std::string formattedPath = activeDirectory.getPath(i).substr(0, activeDirectory.getPath(i).size()-5);
            ofShader tempShader;
            tempShader.load(formattedPath);
            shaders.push_back(tempShader);

            // If a shader did not load, delete it.
            if(!shaders[i].isLoaded()){
                shaders.pop_back();
            } 
        }

        setModeLength(activeDirectory.size());

        return std::string("loaded!");
    }

    void onTextInputEvent(ofxDatGuiTextInputEvent e){
        extensionPath = getChannelGui()->getTextInput("FolderPath")->getText();
        string result = loadShaders(basePath + extensionPath);
        ofLog() << "ShaderBackground::onTextInputEvent /*loading a shader*/ result = " << result;
    }

    void onButtonEvent(ofxDatGuiButtonEvent e){
        extensionPath = getChannelGui()->getTextInput("FolderPath")->getText();
        string result = loadShaders(basePath + extensionPath);
        ofLog() << "ShaderBackground::onTextInputEvent /*loading a shader*/ result = " << result;
    }

    void onKick(float amp){

        shuffleMode();
        kickMom = ofVec3f(ofRandomf() * amp, ofRandomf() * amp, ofRandomf() * amp);
    }
    void onSnare(float amp){
        snareMom = ofVec3f(ofRandomf() * amp, ofRandomf() * amp, ofRandomf() * amp);
    }
    void onHat(float amp){
        snareMom = ofVec3f(ofRandomf() * amp, ofRandomf() * amp, ofRandomf() * amp);
    }
};

#endif