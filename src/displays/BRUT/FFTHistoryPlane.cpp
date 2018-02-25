#ifndef FFT_HISTORY_PLANE
#define FFT_HISTORY_PLANE

#include "ofMain.h"
#include "displays/Channel.h"
#include "globals.h"

class FFTHistoryPlane : public  Channel {  
public:
    std::string getChannelName(){ return "fft_hist_plane"; };

    vector<vector<float>> fftHistory;
    int historyLength = 100;
    int width = 1200;
    int height = 1000;
    int pointWidth = width/historyLength;
    int pointHeight = height / bufferSize;
    int resolutionDivider = 8;

    float sinMod = 0.0;
    float cosMod = 0.0;

    ofMesh landscapeMesh;

    void setup(){
        setupModes(3);
        setTriggerInterval(4);

        landscapeMesh.setMode(OF_PRIMITIVE_POINTS);

        setTranslate(ofPoint(0, -ofGetHeight()/3, 0));
        fftHistory.resize(historyLength);
        for(vector<vector<float>>::size_type i = 0; i < fftHistory.size(); i++){
            for(vector<float>::size_type j = 0; j < (unsigned int) bufferSize/resolutionDivider; j++){
                fftHistory[i].push_back(0.0f);
            }
        }
    }
    
    void update(){
        fftHistory.insert(fftHistory.begin(), fftBin);
        fftHistory.pop_back();
        sinMod+= 0.01;

    }

    void draw(){
        ofFill();
        ofSetCircleResolution(4);
        ofSetColor(255);
        landscapeMesh.clear();
        for(int xDir = -1; xDir < 3; xDir+=2){
            for(vector<vector<float>>::size_type i = 0; (int) i < historyLength; i++){
                
                for(vector<float>::size_type j = 0; (int) j <  bufferSize/resolutionDivider; j++){
                    switch(getMode()){
                        case 0:
                        landscapeMesh.addVertex( ofPoint(
                            (int) i*pointWidth*xDir,
                            (int) j*pointHeight*resolutionDivider + sin(i/historyLength*360*DEG_TO_RAD)*200,
                            fftHistory[i][j]*200
                        ) );
                        
                        break;
                        case 1:
                        landscapeMesh.addVertex( ofPoint(
                            (float) i*pointWidth*xDir,
                            cos(ofNoise((float) i/historyLength +sinMod)*360*DEG_TO_RAD)*200 + j * pointHeight*resolutionDivider + sin((float) i/historyLength +sinMod + 20)*300,
                            sin(ofNoise((float) i/historyLength +sinMod + 20)*360*DEG_TO_RAD)*200 + fftHistory[i][j]*100
                        ) );
                        break;
                        case 2:
                        landscapeMesh.addVertex( ofPoint(
                            sinf((float) i / historyLength * 360 * DEG_TO_RAD)*100 + cosf((float) i / historyLength * 360 * DEG_TO_RAD)*fftHistory[i][j]*150,
                            cosf((float) i / historyLength * 360 * DEG_TO_RAD)*100 + cosf((float) i / historyLength * 360 * DEG_TO_RAD)*fftHistory[i][j]*150,
                            j*pointHeight*xDir
                        ) );
                        break;
                    }
                }
            }
        }

        landscapeMesh.draw();
    }

    void onKick(float amp){
        shuffleMode();
    }

};
#endif