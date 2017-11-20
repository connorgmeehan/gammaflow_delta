#ifndef CONTROL_PANEL
#define CONTROL_PANEL

//GLOBALS
#include "globals.h"

//DEPENDENCIES
#include "ofMain.h"
#include "engine/AudioAnalyser.h"
#include "engine/DisplayManager.h"

//SUBCOMPONENTS
#include "control/ControlComponent.h"
#include "control/Dragable.cpp"

#include "control/components/FFTDisplay.cpp"
#include "control/components/ChannelBank.cpp"
#include "control/components/ChannelSelector.cpp"

class ControlPanel{
public:
    AudioAnalyser* aa;
    DisplayManager* dm;

    FFTDisplay fftDisplay;
    ChannelBank channelBank;
    ChannelSelector primarySelector;
    ChannelSelector secondarySelector;

    vector<ControlComponent*> controlComponents;

    bool mouseDownLastFrame = false;

    void setup(AudioAnalyser* _aa, DisplayManager* _dm);
    void update();
    void draw();
    void drawDragable();

    void onKeyPress(int key);
};

#endif