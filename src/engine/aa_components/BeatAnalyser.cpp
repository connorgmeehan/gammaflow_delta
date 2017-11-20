#ifndef BEAT_ANALYSER
#define BEAT_ANALYSER

#include "ofMain.h"

class BeatAnalyser{
    
    //settings
    int fftPosition = 0; //where on fft does this analyser around
    int radius = 5; //rangle (left and right from fftPos) to analyse
    float scale;
    float triggerVelocity = 0.5;
    float beatCooldown = 0.2; // in seconds
    int historyLength = 5;

    //variables
    float lastBeatTime = 0;
    
    //outputs
    vector<float> beatHistory;
    float amplitude = 0;
    float velocity = 0;
    bool isBeat = false;

public:
    void setup(int _fftPosition, int _radius){
        fftPosition = _fftPosition;
        radius = _radius;
        beatHistory.resize(historyLength);
        lastBeatTime = ofGetElapsedTimef();
    }

    void update(vector<float>* input){
        int lowerBounds = fftPosition - radius;
        int upperBounds = fftPosition + radius;

        if(lowerBounds < 0){
            lowerBounds = 0;
        }
        if(upperBounds >= input->size()){
            upperBounds = input->size()-1;
        }

        //calc amp
        amplitude = 0;
        for(vector<float>::size_type i = lowerBounds; i < upperBounds; i++){
            amplitude += input->at(i);
        }
        amplitude /= upperBounds-lowerBounds;

        beatHistory.insert(beatHistory.begin(), amplitude);
        beatHistory.pop_back();

        velocity = 0.0;
        float c = 0.0;
        for(vector<float>::size_type i = 0; i < beatHistory.size() - 1; i++){
            float y = beatHistory[i] - c;
            float t = velocity + y;
            c = (t - velocity) - y;
            velocity = t;
        }

        if(velocity > triggerVelocity && ofGetElapsedTimef() > (lastBeatTime + beatCooldown)){
            isBeat = true;
            lastBeatTime = ofGetElapsedTimef();
        } else {
            isBeat = false;
        }
    }

    //GET SETTINGS
    int getFftPosition(){ return fftPosition; }
    int getRadius(){ return radius; }
    float getTriggerVelocity(){ return triggerVelocity; }
    int getHistoryLength(){ return historyLength; }
    float getScale(){ return scale; }
    //GET OUTPUTS
    float getAmplitude(){ return amplitude; }
    float getVelocity(){ return velocity; }
    bool getBeat(){ return isBeat; }

    //SET
    void setFftPositon(int _fftPosition){fftPosition = _fftPosition; }
    void setScale( float _scale ){ scale = _scale; }


};

#endif