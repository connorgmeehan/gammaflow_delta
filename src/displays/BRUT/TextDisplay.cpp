#ifndef TEXT_DISPLAY
#define TEXT_DISPLAY

#include "ofMain.h"
#include "globals.h"
#include "displays/Channel.h"

class TextDisplay : public Channel{
private:
    ofTrueTypeFont font;
    std::string toDisplay;
    vector<string> dictionary = {"hey", "sorry", "i", "fucked", "the", "dates", ":((((", "watch", "this", "space", "tho"};
    int dictionaryIndex = 0;

    float outlineDuplicateScale = 5.0f;
    int yOffset = 0;
public:
    void setup(){
        font.load("fonts/OpenSans-ExtraBold.ttf",72,true,true,true);
    }
    void update(){
        
    }
    void draw(){
        ofSetColor(255);
        ofFill();
        font.drawStringAsShapes(dictionary[dictionaryIndex],-font.stringWidth(dictionary[dictionaryIndex])/2, -72+yOffset);
        if(isHat){
            ofDrawRectangle(font.getStringBoundingBox(dictionary[dictionaryIndex],-font.stringWidth(dictionary[dictionaryIndex])/2, -72+yOffset));
        }
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