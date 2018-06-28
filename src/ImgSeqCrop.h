//
//  ImgSeqCrop.hpp
//  ShopMotionInteraction
//
//  Created by Nicole Messier on 6/19/18.
//
//

#pragma once
#include "ofMain.h"
#include "TextureAtlasDrawer.h"
#include "ofxAnimatableFloat.h"
#include "ofxRemoteUIServer.h"

class ImgSeqCrop{
public:
    ImgSeqCrop();
    ~ImgSeqCrop();
    
    void setup(int _cropId, ofVec2f _pos);
    void update(float dt);
    void draw();
    void drawInBatch(TextureAtlasDrawer* atlas);
    
    // MOTION //////////////////////////////////
    void setupMotion();
    
    //reveal
    ofxAnimatableFloat reveal;
    void resetReveal(ofVec2f fromTo, float delay, float duration);
    void onRevealFinish(ofxAnimatable::AnimationEvent & event);
     void onCloseFinish(ofxAnimatable::AnimationEvent & event);
    
    //close
    ofxAnimatableFloat close;
    ofxAnimatableFloat blend;
    void resetClose(ofVec2f fromTo, float delay, float duration);
    
    // REVEAL STATES //////////////////////////////////
    enum AnimationStates{
        IDLE,
        REVEAL,
        CLOSE,
        NUM_ANIMATION_STATES
    };
    
    void setAnimationState(AnimationStates _state);
    AnimationStates getState();
    
    // FADE STATE //////////////////////////////////
    enum FadeStates{
        FADE_IN,
        FADE_OUT,
        VISIBLE
    };
    
    void setFadeState(FadeStates _fadeState);
    FadeStates getFadeState();
    
    // ATLAS //////////////////////////////////
    TextureAtlasDrawer::TexQuad texQuad;
    
    int getCropId();
    
    void setLeftSide(bool _leftSide);
    bool getLeftSide();
    
    // ATTRIBUTES //////////////////////////////////
    ofVec2f getPos();
    
     // CROP PERCENT //////////////////////////////////
    void setCropPerc(float _cropPerc);
    float getCropPerc();
    
    // FILEPATHS //////////////////////////////////
    void setFramesPath(string _framesPath);
    void setFrameCounter(int _frameCounter);
    string getTextureFile();
    
    // NUMFRAMES //////////////////////////////////
    void setNumFrames(int _numFrames);
    
    //FRAMERATE
    void setFrameRateDivisor(int _frameRateDivisor);
    
    bool getTransition();
    
private:
    // STATES //////////////////////////////////
    AnimationStates revevalState = IDLE;
    
    // FADE STATE //////////////////////////////////
    FadeStates fadeState = VISIBLE;
    float alpha = 0.0f;
    ofxAnimatableFloat fadeIn;
    ofxAnimatableFloat fadeOut;
    float fadeDuration = 1.0f;
    
    void onFadeInFinish(ofxAnimatable::AnimationEvent & event);
    void onFadeOutFinish(ofxAnimatable::AnimationEvent & event);
    
    // MOTION //////////////////////////////////
    float animationDuration = 1.0f;
    int cropId = 0;
    bool leftSide = false;
    
    // ATTRIBUTES //////////////////////////////////
    ofVec2f pos;
    
    // CROP PERCENT //////////////////////////////////
    float cropPerc;
    
    // FILEPATHS //////////////////////////////////
    string frontPath = "frame-";
    string framesPath = "imageSequences/wash4/";
    string textureFile = "";
    
    string framesPathRef = "";
    int numFramesRef = 0;

    // NUMFRAMES //////////////////////////////////
    int numFrames = 0;
    
    // FRAMERATE //////////////////////////////////
    int frameCounter = 0;
    int frameRateDivisor = 2;
    int frameRateCounter = frameRateDivisor;
    int uid = 0;
    
    bool transition = false;
};