//
//  ofxImageSequenceAtlas.hpp
//  FFG_Shop
//
//  Created by Nicole Messier on 4/30/18.
//
//

#pragma once
#include "ofMain.h"
#include "TextureAtlasDrawer.h"

class ofxImageSequenceAtlas{
public:
    ofxImageSequenceAtlas();
    ~ofxImageSequenceAtlas();
    
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
    void calculateCrop(ofVec2f cropPerc);
    void setTextureDimensions(TextureAtlasDrawer::TextureDimensions _td);
    TextureAtlasDrawer::TexQuad getParalelogramForRect(const ofRectangle & r,float widthPerc);
    TextureAtlasDrawer::TexQuad texQuad;
    
    // FILEPATHS //////////////////////////////////
    void setNumFrames(int _numFrames);
    void setFramesPath(string _framesPath); 
    
private:
    
    // ATTRIBUTES //////////////////////////////////
    ofVec2f pos = ofVec2f(0,0);
    ofVec2f size = ofVec2f(100,100);
    ofVec2f sizeOrg; //original size
    
    // STATES //////////////////////////////////
    States state = States::PLAY_LOOPING;
    
    // ATLAS //////////////////////////////////
    string textureFile;
    TextureAtlasDrawer::TextureDimensions td;
    
    // FRAMERATE //////////////////////////////////
    int frameCounter = 0;
    int frameRateDivisor = 2;
    int frameRateCounter = frameRateDivisor;
    
    // FILEPATHS //////////////////////////////////
    string frontPath = "frame-";
    string framesPath = "ofxofxImageSequenceAtlasAtlass/wash4/";
    int numFrames = 0;
};
