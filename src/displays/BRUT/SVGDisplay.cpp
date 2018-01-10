#ifndef SVG_DISPLAY
#define SVG_DISPLAY

#include "ofMain.h"
#include "displays/Channel.h"
#include "globals.h"
#include "ofxSvg.h"

class SVGDisplay : public Channel{
public:
    std::string getChannelName(){ return "svg_display"; };
    
    float step = 0;
    ofxSVG svg;
    bool hasLoadedFlag = false;
    vector<ofPolyline> outlines;


    void setup(){
        svg.load("svgs/HOWDYGADGE.svg");

        for (int i = 0; i < svg.getNumPath(); i++){
            ofPath p = svg.getPathAt(i);
            // svg defaults to non zero winding which doesn't look so good as contours
            p.setPolyWindingMode(OF_POLY_WINDING_ODD);
            vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
            for(int j=0;j<(int)lines.size();j++){
                outlines.push_back(lines[j].getResampledBySpacing(1));
            }
        }
    }

    void update(){
        step += 0.001;
        if (step > 1) {
            step -= 1;
        }
    }

    void draw(){
        ofPushMatrix();
        ofTranslate(-svg.getWidth()/2, -svg.getHeight()/2);
        if(ofGetMousePressed()) {
            ofNoFill();
            for (int i = 0; i < (int)outlines.size(); i++){
                ofPolyline & line = outlines[i];

                int num = step * line.size();

                ofBeginShape();
                for (int j = 0; j < num; j++){
                    ofVertex(line[j]);
                }
                ofEndShape();
            }
        } else {
            svg.draw();
        }
        ofPopMatrix();
    }

    void recKeyDown(int key){
        if(key == OF_KEY_BACKSPACE){
            ofLog(OF_LOG_NOTICE) << "SVGDisplat::recKeyDown("<<key<<")  --  reloading svgs/HOWDYGADGE";
            svg.load("svgs/HOWDYGADGE.svg");
            ofLog(OF_LOG_NOTICE) << "SVGDisplat::recKeyDown("<<key<<")  --  DONE! number of paths: " << svg.getNumPath();
        }
        if(key == 't'){
            ofLog(OF_LOG_NOTICE) << "SVGDisplat::recKeyDown("<<key<<")  --  reloading svgs/tiger";
            svg.load("svgs/tiger.svg");
            ofLog(OF_LOG_NOTICE) << "SVGDisplat::recKeyDown("<<key<<")  --  DONE! number of paths: " << svg.getNumPath();
        }
    }
};

#endif