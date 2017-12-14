#ifndef DISPLAY_MANAGER
#define DISPLAY_MANAGER

#include "ofMain.h"

#include "globals.h"

#include "displays/Channel.h"
#include "ofxDatGui.h"
#include "displays/ShaderTest.cpp"

#include "displays/BRUT/TrigDeath.cpp"
#include "displays/BRUT/FFTHistoryPlane.cpp"
#include "displays/BRUT/PointCloud.cpp"
#include "displays/BRUT/CrystalButterfly.cpp"
#include "displays/BRUT/PerlinOctopus.cpp"
#include "displays/BRUT/InterfaceCircle.cpp"
#include "displays/BRUT/TextDisplay.cpp"
#include "displays/VIBE/TextFloat.cpp"

#include "displays/QNTM/ShaderBackground.cpp"
#include "displays/QNTM/ShaderDesc.cpp"


class DisplayManager{
public:
    ofEasyCam cam;

    bool fullscreen = false;

    Channel* activePrimary = nullptr;
    Channel* activeSecondary = nullptr;

    vector<Channel*> channelBank;
    
    ShaderTest shaderTest;
    //Add individual channel objects here
    TrigDeath trigDeath;
    FFTHistoryPlane fftHistoryPlane;
    PointCloud pointCloud;
    CrystalButterfly crystalButterfly;
    PerlinOctopus perlinOctopus;
    InterfaceCircle interfaceCircle;
    TextDisplay textDisplay;
    TextFloat textFloat;   

    ShaderBackground shaderBackground; 
    ShaderDesc shaderDesc;
    void setup();
    void update();
    void draw();

    void setActivePrimary(int _bankID);
    void setActiveSecondary(int _bankID);

    void recKeyDown(int key);
    
    bool hasGui(int _channelIndex);
    ofxDatGui* getChannelGui(int _channelIndex);
    void setChannelGuiPosition();
    std::string getChannelName(int _bankID);
    int getChannelBankSize();

};

#endif