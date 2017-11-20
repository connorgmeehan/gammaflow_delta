#ifndef AUDIO_ANALYSER
#define AUDIO_ANALYSER

#include "ofxFFTLive.h"
#include "engine/aa_components/BeatAnalyserManager.cpp"


class AudioAnalyser{
public:
    void setup(int _deviceId);
    void update();

    void drawFFT(int x, int y, int width, int height);

    ofxFFTLive fftLive;
    BeatAnalyserManager beats;
};

#endif