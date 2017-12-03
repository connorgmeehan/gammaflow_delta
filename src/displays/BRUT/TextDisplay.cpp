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
    virtual std::string getChannelName(){ return ofToString("text_displays"); }

    void setup(){
        font.load("fonts/OpenSans-ExtraBold.ttf",72,true,true,true);
        setupChannelGui();
        getChannelGui()->addTextInput("Dictonary: ", "type here");
        getChannelGui()->onTextInputEvent(this, &TextDisplay::onTextInputEvent);
    }
    void update(){
        
    }
    void draw(){
        ofSetColor(255);
        ofFill();
        if(dictionary.size() > 0){
            font.drawStringAsShapes(dictionary[dictionaryIndex],-font.stringWidth(dictionary[dictionaryIndex])/2, -72+yOffset);
            if(isHat){
                ofDrawRectangle(font.getStringBoundingBox(dictionary[dictionaryIndex],-font.stringWidth(dictionary[dictionaryIndex])/2, -72+yOffset));
            }
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

    void onTextInputEvent(ofxDatGuiTextInputEvent args){
        ofLog(OF_LOG_NOTICE) << "TextDisplay::onTextInputEvent( args.text = " << args.text << " ) ";
        dictionary = vector<string>{""};
        int dictionaryCounter = 0;

        for(int i = 0; i < args.text.length(); i++){
            if(args.text[i]== ' ' ){
                dictionary.push_back("");
                dictionaryCounter++;
            } else {
                dictionary[dictionaryCounter] += args.text[i];
            }
        }
        if(dictionaryIndex > dictionary.size()){
            dictionaryIndex = dictionary.size()-1;
        }
    }
};

#endif