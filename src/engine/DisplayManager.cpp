#include "engine/DisplayManager.h"

void DisplayManager::setup(){
    ofLog(OF_LOG_NOTICE) << "ofApp.DisplayManager::setup() - @"<< ofGetElapsedTimef() << "s";
    
    channelBank.push_back(&shaderTest);
    channelBank.push_back(&trigDeath);
    channelBank.push_back(&perlinOctopus);
    channelBank.push_back(&crystalButterfly);
    channelBank.push_back(&fftHistoryPlane);
    channelBank.push_back(&pointCloud);
    channelBank.push_back(&interfaceCircle);
    channelBank.push_back(&textDisplay);
}

void DisplayManager::update(){
    if(activePrimary!=nullptr){
        if(isKick){ activePrimary->onKick(kickAmp); }
        if(isSnare){ activePrimary->onSnare(snareAmp); }
        if(isHat){ activePrimary->onHat(hatAmp); }
        activePrimary->update();
    }
    if(activeSecondary!=nullptr){
        if(isKick){ activeSecondary->onKick(kickAmp); }
        if(isSnare){ activeSecondary->onSnare(snareAmp); }
        if(isHat){ activeSecondary->onHat(hatAmp); }
        activeSecondary->update();
    }
}

void DisplayManager::draw(){
    if(activePrimary!=nullptr){

        if(activePrimary->gfGetUseCam()){
            cam.begin();
        }
        ofPushMatrix();
        ofTranslate(activePrimary->getTranslate());
        activePrimary->draw();
        ofPopMatrix();

        if(activePrimary->gfGetUseCam()){
            cam.end();
        }

    }
    if(activeSecondary!=nullptr){

        if(activeSecondary->gfGetUseCam()){
            cam.begin();
        }

        ofPushMatrix();
        ofTranslate(activeSecondary->getTranslate());
        activeSecondary->draw();
        ofPopMatrix();
        if(activeSecondary->gfGetUseCam()){
            cam.end();
        }
    }  
}

void DisplayManager::setActivePrimary(int _bankID){
    activePrimary = channelBank[_bankID];
    activePrimary->setup();
}

void DisplayManager::setActiveSecondary(int _bankID){
    activeSecondary = channelBank[_bankID];
    activeSecondary->setup();
}

std::string DisplayManager::getChannelName(int _bankID){
    return channelBank[_bankID]->getChannelName();
}

int DisplayManager::getChannelBankSize(){
    return channelBank.size();
}

void DisplayManager::recKeyDown(int key){
    if(activePrimary != nullptr){
        activePrimary->recKeyDown(key);
    }
    if(activeSecondary != nullptr){
        activeSecondary->recKeyDown(key);
    }
}