#ifndef FFT_DISPLAY
#define FFT_DISPALY

//GLOBALS
#include "globals.h"

//DEPENDENCIES
#include "ofMain.h"
#include "ofxDatGui.h"
#include "control/ControlComponent.h"
#include "control/Dragable.cpp"
#include "engine/AudioAnalyser.h"
#include "engine/aa_components/BeatAnalyser.cpp"
#include "engine/aa_components/BeatAnalyserManager.cpp"
#include "ofxFFTLive.h"

//CHILDREN
#include "control/components/FFTDisplayBeat.cpp"


class FFTDisplay : public ControlComponent {
public:
    AudioAnalyser* aa;

    float fftWidthScale;
    float fftHeightScale;

    ofParameter<float> audioThresholdParam;
    ofParameter<float> audioPeakDecayParam;
    ofParameter<float> audioMaxDecayParam;

    ofxDatGuiSlider* audioThresholdSlider;
    ofxDatGuiSlider* audioPeakDecaySlider;
    ofxDatGuiSlider* audioMaxDecaySlider;

    vector<FftDisplayBeat> fftDisplayBeats;

    bool mouseHover = false;

    void setup(AudioAnalyser* _aa){
        ofLog(OF_LOG_NOTICE) << "ofApp.ControlPanel.FFTDisplay::setup() - @"<< ofGetElapsedTimef() << "s";

        aa = _aa;
        fftWidthScale = fftBin.size()/getWidth();
        fftHeightScale = getHeight()/1;

        audioThresholdSlider = new ofxDatGuiSlider(audioThresholdParam.set("audio threshold", 1.0f, 0.0f, 1.0f));
        audioThresholdSlider->setWidth(250, .3); // make label area 20% of width //
        audioThresholdSlider->setPosition(getX()+getWidth()-250, getY());
        audioThresholdParam.addListener(this, &FFTDisplay::onAudioThresholdChange);

        audioPeakDecaySlider = new ofxDatGuiSlider(audioPeakDecayParam.set("audio peak decay", 0.5f, 0.0f, 1.0f));
        audioPeakDecaySlider->setWidth(250, .3); // make label area 20% of width //
        audioPeakDecaySlider->setPosition(getX()+getWidth()-250, getY()+20);
        audioPeakDecayParam.addListener(this, &FFTDisplay::onAudioPeakDecay);

        audioMaxDecaySlider = new ofxDatGuiSlider(audioMaxDecayParam.set("audio max decay", 0.995f, 0.0f, 1.0f));
        audioMaxDecaySlider->setWidth(250, .3); // make label area 20% of width //
        audioMaxDecaySlider->setPosition(getX()+getWidth()-250, getY()+40);
        audioMaxDecayParam.addListener(this, &FFTDisplay::onAudioMaxDecay);
        //setup beat analysers
        
        addBeatAnalyser(ofToString("Kick"), bufferSize*0.05, 10);

        addBeatAnalyser(ofToString("Snare"), bufferSize*0.15, 20);

        addBeatAnalyser(ofToString("Hat"), bufferSize*0.3, 30);

    }
    void update(){   

        for(vector<FftDisplayBeat>::size_type i = 0; i < fftDisplayBeats.size(); i++){
            fftDisplayBeats[i].update();
        }

        calculateMouseLogic(ofGetMouseX()-getX(), ofGetMouseY() - getY());

        audioMaxDecaySlider->update();
        audioPeakDecaySlider->update();
        audioThresholdSlider->update();
    }
    void draw(){
        ofSetColor(255);
        ofSetLineWidth(fftWidthScale);
        aa->drawFFT(getX(),getY(), getWidth(), getHeight());

        for(vector<FftDisplayBeat>::size_type i = 0; i < fftDisplayBeats.size(); i++){
            fftDisplayBeats[i].draw();
        }

        audioMaxDecaySlider->draw();
        audioPeakDecaySlider->draw();
        audioThresholdSlider->draw();
    }

    void addBeatAnalyser(std::string _name, int _fftPositon, int _radius){
        aa->beats.addBeatAnalyser(_fftPositon,_radius);
        int beatAnalyserKey = aa->beats.getBeatAnalyserSize()-1;
        FftDisplayBeat temp;
        temp.pre_setup(_name, getX(), getY(), getWidth(), getHeight());
        temp.setup(aa, _name, beatAnalyserKey);
        fftDisplayBeats.push_back(temp);
    }

    void calculateMouseLogic(int mx, int my){
        if(mx > 0 && mx < getWidth() && my > 0 && my < getHeight()){
            mouseHover = true;

            if(dragable.getDragType() == DRAG_BEAT_ZONE_INDEX){
                fftDisplayBeats[dragable.getValue()].setPlotPos(mx);            
            } else {
                for(vector<FftDisplayBeat>::size_type i = 0; i < fftDisplayBeats.size(); i++){
                    if(mx > fftDisplayBeats[i].getPlotPos() - fftDisplayBeats[i].getPlotRadius() && mx < fftDisplayBeats[i].getPlotPos() + fftDisplayBeats[i].getPlotRadius()){
                        fftDisplayBeats[i].setHover(true);

                        if(mouseClick){
                            dragable.setup(DRAG_BEAT_ZONE_INDEX, fftDisplayBeats[i].getName(), fftDisplayBeats[i].getBeatKey());
                        }

                    } else {
                        fftDisplayBeats[i].setHover(false);
                    }
                }
            }

        } else {
            mouseHover = false;
        }
    }

    void onAudioMaxDecay(float & f){
        aa->fftLive.setMaxDecay(f);    
    }

    void onAudioPeakDecay(float & f){
        aa->fftLive.setPeakDecay(f);
    }

    void onAudioThresholdChange(float & f){
        aa->fftLive.setThreshold(f);
    }
};

#endif