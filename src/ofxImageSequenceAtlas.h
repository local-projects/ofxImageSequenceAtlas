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
#include "ofxAnimatableFloat.h"

class ofxImageSequenceAtlas{
public:
    ofxImageSequenceAtlas();
    ~ofxImageSequenceAtlas();
    
    void setup(ofVec2f _pos, ofVec2f _size, int _column, int _row);
    void update(float dt);
    void playSequence(int _startFrame, bool loop);
    
    void drawDebug(); 
    
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
    void setTextureDimensions(TextureAtlasDrawer::TextureDimensions _td);
    TextureAtlasDrawer::TexQuad getParalelogramForRect(const ofRectangle & r,float widthPerc, float fromLeft);
    TextureAtlasDrawer::TexQuad texQuad;
    
    // FILEPATHS //////////////////////////////////
    void setNumFrames(int _numFrames);
    void setFramesPath(string _framesPath);
    
    // MOTION //////////////////////////////////
    void setupMotion();
    ofxAnimatableFloat reveal;
    float animationDuration = 1.0f;
    
    //reveal
    void resetReveal(ofVec2f fromTo, float delay);
    bool shouldReveal = false;
    void calculateCropRight(ofVec2f cropPerc);
    void calculateCropLeft(ofVec2f cropPerc);
    bool left = false; 
    
    //Motion States
    enum AnimState{
        IDLE,
        REVEAL,
        LOOP,
        NUM_ANIMATION_STATES
    };
    
    AnimState animState = AnimState::IDLE;
    void setMotionState(AnimState _animState);
    
    int column = 0;
    int row = 0; 
    
private:
    
    // ATTRIBUTES //////////////////////////////////
    ofVec2f pos = ofVec2f(0,0);
    ofVec2f size = ofVec2f(100,100);
    ofVec2f sizeOrg; //original size
    
    // STATES //////////////////////////////////
    States state = States::PLAY_ONCE;
    
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
