#ifndef FFT_DISPLAY_BEAT
#define FFT_DISPLAY_BEAT

#include "globals.h"

#include "ofMain.h"
#include "control/ControlComponent.h"
#include "engine/AudioAnalyser.h"
#include "engine/aa_components/BeatAnalyser.cpp"
#include "engine/aa_components/BeatAnalyserManager.cpp"

class FftDisplayBeat : public ControlComponent {
public:
    AudioAnalyser* aa;
    int beatKey = -1;
    int fftPos = -1;
    //display variables
    int componentHeight, componentWidth;;
    std::string name;
    int fftPlotPos = -1;
    int fftPlotRadius = -1;
    float fftScale;
    bool isHover = false;

    //output variables
    float amplitude = -1;
    void setup(AudioAnalyser* _aa, std::string _name, int _beatKey){
        aa = _aa;
        name = _name;
        beatKey = _beatKey;
        fftPos = aa->beats[beatKey]->getFftPosition();
        fftScale = bufferSize/getWidth();
        fftPlotPos = fftPos * fftScale; 
        fftPlotRadius = aa->beats[beatKey]->getRadius()*fftScale;
    }

    void update(){
        amplitude = aa->beats[beatKey]->getAmplitude();
    }

    void draw(){
        ofFill();
        ofSetColor(255);
        if(isHover){
            ofSetLineWidth(4);
        } else {
            ofSetLineWidth(2);
        }
        ofDrawBitmapString(name, getX() + fftPlotPos, getY() + 12);
        ofDrawLine(getX() + fftPlotPos, getY(), getX()+fftPlotPos, getY() + getHeight());
        if(isHover){
            ofSetLineWidth(2);
        } else {
            ofSetLineWidth(1);
        }
        ofSetColor(255,0,0,100);
        ofDrawRectangle(getX() + fftPlotPos-fftPlotRadius, getY()+getHeight(), fftPlotRadius*2, -amplitude*getHeight());
        ofSetColor(255,0,0);
        ofNoFill();
        ofDrawRectangle(getX() + fftPlotPos-fftPlotRadius, getY()+getHeight(), fftPlotRadius*2, -amplitude*getHeight());
    }

    int getPlotPos(){ return fftPlotPos; }
    int getPlotRadius(){ return fftPlotRadius; }
    string getName(){ return name; }
    int getBeatKey(){ return beatKey; }

    void setPlotPos(int _fftPlotPos){
        fftPlotPos = _fftPlotPos;
        aa->beats[beatKey]->setFftPositon(_fftPlotPos);    
    }
    void setPlotRadius(int _fftPlotRadius){
        fftPlotRadius = _fftPlotRadius;
    }
    void setHover(bool _isHover){ isHover = _isHover; }
};

#endif