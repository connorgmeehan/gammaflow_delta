#ifndef TEXT_DISPLAY
#define TEXT_DISPLAY

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class TextDisplay : public Channel{
private:
    ofTrueTypeFont font;
    std::string toDisplay;
    vector<string> dictionary = {"the", "date", "doth", "change", "16-11", "16-11", "16-11", "16-11", "16-11"};
    int dictionaryIndex = 0;

    float outlineDuplicateScale = 5.0f;
    int yOffset = 0;
public:
    void setup(){
        font.load("fonts/Coco-Gothic-Alternate-Fat-Italic-trial.ttf",72,true,true,true);
    }
    void update(){
        
    }
    void draw(){
        ofSetColor(255);
        ofFill();

        font.drawStringAsShapes(dictionary[dictionaryIndex],-font.stringWidth(dictionary[dictionaryIndex])/2, -72+yOffset);
        ofNoFill();
        for(int i = 0; i < fftBin[10] * outlineDuplicateScale; i++){
            ofScale(1+i*0.01, -1-i*0.01);
        font.drawStringAsShapes(dictionary[dictionaryIndex],-font.stringWidth(dictionary[dictionaryIndex])/2, -72+yOffset);
        }
        ofScale(1,1,1);
    }

    void onHat(float amp){
        dictionaryIndex = (dictionaryIndex + 1) % dictionary.size();
    }
    void recKeyDown(int key){
        if(key == OF_KEY_UP){
            yOffset ++;
        }
        if(key == OF_KEY_DOWN){
            yOffset--;
        }
    }
};

#endif