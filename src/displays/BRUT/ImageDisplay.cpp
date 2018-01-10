#ifndef IMAGE_DISPLAY
#define IMAGE_DISPLAY

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class ImageDisplay : public Channel {
    ofImage img;
public:
    std::string getChannelName(){ return "img_display"; };
    
    void setup(){
        img.load("images/HOWDYGADGE.png");
    }
    void update(){}
    void draw(){
        img.draw(0, 0, 1024, 768);
    }
};

#endif