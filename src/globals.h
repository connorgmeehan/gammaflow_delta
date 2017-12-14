#ifndef GLOBALS
#define GLOBALS

#include "ofMain.h"

extern int screenWidth, screenHeight;

extern std::vector<float> fftBin;
extern int bufferSize;

extern bool mouseClick;
extern bool mouseUnclick;

extern float volume;

extern bool isKick, isSnare, isHat;
extern float kickAmp, snareAmp, hatAmp;
extern std::vector<bool> isBeats;
extern std::vector<float> beatsAmp;

#endif 