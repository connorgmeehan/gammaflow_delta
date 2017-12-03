#ifndef CONTROL_COMPONENT
#define CONTROL_COMPONENT

#include "ofMain.h"

class ControlComponent{
public:
    std::string name;
    ofVec2f transform;
    ofVec2f dimensions;
    int topGap = 20;
    virtual void pre_setup(std::string _name, int x, int y, int width, int height){
        name = _name;
        transform.x = x;
        transform.y = y;
        dimensions.x = width;
        dimensions.y = height;
    }
    virtual void setup(){
        ofLog(OF_LOG_WARNING) << "ControlComponent (" << name << ").setup() is being run but this class is in its general form.";                
    };
    virtual void update(){
        ofLog(OF_LOG_WARNING) << "ControlComponent (" << name << ").update() is being run but this class is in its general form.";        
    };
    virtual void pre_draw(){

            //DRAWS BOX AROUND WINDOW
            ofSetColor(20);
            ofFill();
            ofSetLineWidth(2);
            ofDrawRectangle(transform.x,transform.y,dimensions.x,dimensions.y);
            
            //DRAWS TOP BAR W/ TITLE ETC
            ofSetColor(70);
            ofSetLineWidth(1);
            ofDrawRectangle(transform.x,transform.y,dimensions.x,topGap);

            ofSetColor(255);
            ofDrawBitmapString(name, transform.x+4,transform.y + topGap/2+4);

            //MOVES RENDER CONTEXT DOWN SO 0,0 is top left inside of window
            
    };
    virtual void draw(){
        ofLog(OF_LOG_WARNING) << "ControlComponent (" << name << ").draw() is being run but this class is in its general form.";                
    };

    virtual void onKeyPress(int key){};

    virtual int getWidth(){ return (int) dimensions.x; }
    virtual int getHeight(){ return (int) dimensions.y - topGap; }
    virtual int getX(){ return transform.x; }
    virtual int getY(){ return transform.y+topGap; }
    virtual int getTopGap(){ return topGap; }
    virtual void setName(string _name){ name = _name; }
};

#endif