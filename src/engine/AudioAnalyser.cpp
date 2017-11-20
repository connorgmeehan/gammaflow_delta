#include "engine/AudioAnalyser.h"

//DECLARE GLOBAL VARS FOR AUDIO ANALYSER
std::vector<float> fftBin;
int bufferSize = 512;
float volume;

bool isKick, isSnare, isHat;
float kickAmp, snareAmp, hatAmp;

vector<bool> isBeats;
vector<float> beatsAmp;


void AudioAnalyser::setup(int _deviceId){
    ofLog(OF_LOG_NOTICE) << "ofApp.AudioAnalyser::setup() - @"<< ofGetElapsedTimef() << "s";
    fftLive.setup(_deviceId);

    fftLive.setPeakDecay(0.5);
    fftLive.setMaxDecay(0.95);
}

void AudioAnalyser::update(){
    fftLive.update();
    fftBin = fftLive.getFftPeakData();
    beats.update(&fftBin);

    isKick = beats[0]->getBeat();
    isSnare = beats[1]->getBeat();
    isHat = beats[2]->getBeat();
    kickAmp = beats[0]->getAmplitude();
    snareAmp = beats[1]->getAmplitude();
    hatAmp = beats[2]->getAmplitude();

    for(int i = 0; i < beats.getBeatAnalyserSize(); i++){
        isBeats[i] = beats[i]->getBeat();
        beatsAmp[i] = beats[i]->getAmplitude();
    }

    volume = 0;
    for(vector<float>::size_type i = 0; i < fftBin.size(); i++){
        volume+=fftBin[i];
    }
    volume/=fftBin.size();

}

void AudioAnalyser::drawFFT(int x, int y, int width, int height){
    fftLive.draw(x,y,width,height);
}