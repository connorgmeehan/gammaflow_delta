#ifndef BEAT_ANALYSER_MANAGER
#define BEAT_ANALYSER_MANAGER

#include "ofMain.h"
#include "globals.h"
#include "engine/aa_components/BeatAnalyser.cpp"

class BeatAnalyserManager{
public:
    std::vector<BeatAnalyser> beatAnalysers;

    void update(vector<float>* input){
        for(vector<BeatAnalyser>::size_type i = 0; i < beatAnalysers.size(); i++){
            beatAnalysers[i].update(input);
        }
    }

    void addBeatAnalyser(int _fftPosition, int _radius){
        ofLog(OF_LOG_NOTICE) << "ofApp.AudioAnalyser.BeatAnalyserManager::addBeatZone( _fftPosition "<<_fftPosition<<", _radius"<<_radius<<");";

        BeatAnalyser temp;
        temp.setup(_fftPosition, _radius);
        beatAnalysers.push_back(temp);
        isBeats.push_back(false);
        beatsAmp.push_back(0.0f);
    }

    int getBeatAnalyserSize(){
        return beatAnalysers.size();
    }

    BeatAnalyser* operator[](int i){
        return &beatAnalysers[i];
    }


};

#endif