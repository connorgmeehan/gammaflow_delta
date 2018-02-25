#include "engine/DisplayManager.h"

void DisplayManager::setup(){

    ofLog(OF_LOG_NOTICE) << "ofApp.DisplayManager::setup() - @"<< ofGetElapsedTimef() << "s";
    
    ofFbo::Settings settings;
    settings.width = 1024;
    settings.height = 768;
    settings.textureTarget = GL_TEXTURE_2D;
    settings.internalformat = GL_RGBA;

    backgroundFbo.allocate(settings);
    backgroundTexture.allocate(1024,768,GL_RGBA);
    shaderBackground.setup();

    primaryFbo.allocate(settings);
    primaryTexture.allocate(1024,768,GL_RGBA);
    secondaryFbo.allocate(settings);
    secondaryTexture.allocate(1024,768,GL_RGBA);

    rotateColourShader.load("shaders/shadersGL3/rotateColour");
    rotate2ColourShader.load("shaders/shadersGL3/rotate2Colour");

    channelBank.push_back(&shaderTest);
    channelBank.push_back(&trigDeath);
    channelBank.push_back(&perlinOctopus);
    channelBank.push_back(&crystalButterfly);
    channelBank.push_back(&fftHistoryPlane);
    channelBank.push_back(&pointCloud);
    channelBank.push_back(&interfaceCircle);
    channelBank.push_back(&textDisplay);
    channelBank.push_back(&textFloat);
    channelBank.push_back(&shaderBackground);
    channelBank.push_back(&shaderDesc);
    channelBank.push_back(&svgDisplay);
    channelBank.push_back(&imageDisplay);

    orbitVector = ofVec3f(0,0,0);
    currentOrbit = ofVec3f(0,0,200);
}

void DisplayManager::update(){
    
    if(isKick){ shaderBackground.onKick(kickAmp); }
    if(isSnare){ shaderBackground.onSnare(snareAmp); }
    if(isHat){ shaderBackground.onHat(hatAmp); }

    shaderBackground.update();

    currentOrbit += orbitVector;
    cam.orbit(currentOrbit.x, currentOrbit.y, currentOrbit.z);

    if(isSnare){
        orbitBeatIndex++;
        if(orbitBeatIndex == orbitResetThreshold){
            orbitBeatIndex = 0;
            currentOrbit = ofVec3f(0,0,800);
            orbitVector = ofVec3f(ofRandomf()*2, ofRandomf()*2, 0);
        }
    }

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

    backgroundFbo.allocate(1024,768,GL_RGBA);
    backgroundFbo.begin();
    shaderBackground.draw();
    backgroundFbo.end();
    backgroundTexture = backgroundFbo.getTexture();
    backgroundTexture.getTextureData().bFlipTexture = true;
    backgroundFbo.draw(0,0);

    //DRAW PRIMARY
    if(activePrimary!=nullptr){

	    primaryFbo.allocate(1024,768, GL_RGBA);
        primaryFbo.begin();

        if(activePrimary->gfGetUseCam()){
            cam.begin();
        }

        rotateColourShader.begin();
        rotateColourShader.setUniformTexture("tex", backgroundTexture, 0);

        ofPushMatrix();
            ofTranslate(activePrimary->getTranslate());
            activePrimary->draw();
        ofPopMatrix();
        
        rotateColourShader.end();

        if(activePrimary->gfGetUseCam()){
            cam.end();
        }
	
        primaryFbo.end();


        primaryTexture.getTextureData().bFlipTexture = true;
        primaryTexture = primaryFbo.getTexture();
        primaryFbo.draw(0,0);
    }

    //DRAW SECONDARY
    if(activeSecondary!=nullptr){

        secondaryFbo.allocate(1024,768,GL_RGBA);
        


        if(activeSecondary->gfGetUseCam()){
            cam.begin();
        }

        rotate2ColourShader.begin();
        rotate2ColourShader.setUniformTexture("tex", backgroundTexture, 0);
        rotate2ColourShader.setUniformTexture("tex0", primaryTexture, 1);
        
        ofPushMatrix();
            ofTranslate(activeSecondary->getTranslate());
            activeSecondary->draw();
        ofPopMatrix();

        rotate2ColourShader.end();

        if(activeSecondary->gfGetUseCam()){
            cam.end();
        }



        secondaryFbo.draw(0,0);

    }  

    if(useShader){
        //ofDrawBitmapString("Shader in use", 950, 740);
    }
}

void DisplayManager::setActivePrimary(int _bankID){
    activePrimary = channelBank[_bankID];
    if(!activePrimary->getHasBeenSetup()){
        activePrimary->setup();
        activePrimary->setHasBeenSetup(true);
    }
}

void DisplayManager::setActiveSecondary(int _bankID){
    activeSecondary = channelBank[_bankID];
    if(!activeSecondary->getHasBeenSetup()){
        activeSecondary->setup();
        activeSecondary->setHasBeenSetup(true);
    }
}

std::string DisplayManager::getChannelName(int _bankID){
    return channelBank[_bankID]->getChannelName();
}

int DisplayManager::getChannelBankSize(){
    return channelBank.size();
}

void DisplayManager::recKeyDown(int key){
    if(key == OF_KEY_BACKSPACE){
        useShader = !useShader;
    }

    if(key == '+'){
        rotateColourShader.load("shaders/shadersGL3/rotateColour");
        rotate2ColourShader.load("shaders/shadersGL3/rotate2Colour");
    }

    if(activePrimary != nullptr){
        activePrimary->recKeyDown(key);
    }
    if(activeSecondary != nullptr){
        activeSecondary->recKeyDown(key);
    }
}

bool DisplayManager::hasGui(int _channelIndex){
    return channelBank[_channelIndex]->hasGui();
}
ofxDatGui* DisplayManager::getChannelGui(int _channelIndex){
    return channelBank[_channelIndex]->getChannelGui();
}