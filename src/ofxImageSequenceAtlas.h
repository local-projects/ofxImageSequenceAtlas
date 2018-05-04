//
//  ImageSequence.hpp
//  FFG_Shop
//
//  Created by Nicole Messier on 4/30/18.
//
//

#pragma once
#include "ofMain.h"
#include "TextureAtlasDrawer.h"

class ImageSequence{
public:
    ImageSequence();
    ~ImageSequence();
    
    void setup(ofVec2f _pos, ofVec2f _size);
    void update(float dt);
    void playSequence(int _startFrame, bool loop);
    
    // ATTRIBUTES //////////////////////////////////
    ofVec2f getPos();
    ofVec2f getSize();
    
    // STATES //////////////////////////////////
    enum States{
        PLAY_ONCE,
        PLAY_LOOPING,
        STOPPED
    };
    
    void setState(States _state);
    
    // ATLAS //////////////////////////////////
    void drawInBatch(TextureAtlasDrawer* atlas);
    TextureAtlasDrawer::TexQuad getParalelogramForRect(const ofRectangle & r,float widthPerc);
    TextureAtlasDrawer::TexQuad texQuad;
    
    // FILEPATHS //////////////////////////////////
    void setNumFrames(int _numFrames);
    void setFramesPath(string _framesPath); 
    
private:
    
    // ATTRIBUTES //////////////////////////////////
    ofVec2f pos = ofVec2f(0,0);
    ofVec2f size = ofVec2f(100,100);
    
    // STATES //////////////////////////////////
    States state = States::PLAY_LOOPING;
    
    // FRAMERATE //////////////////////////////////
    string textureFile;
    int frameCounter = 0;
    int frameRateDivisor = 2;
    int frameRateCounter = frameRateDivisor;
    
    // FILEPATHS //////////////////////////////////
    string frontPath = "frame-";
    string framesPath = "imageSequences/wash4/";
    int numFrames = 0;
};
