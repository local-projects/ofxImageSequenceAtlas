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
    
    void setup(int _cropId);
    void update(float dt);
    void draw();
    
    // MOTION //////////////////////////////////
    void setupMotion();
    
    //reveal
    ofxAnimatableFloat reveal;
    void resetReveal(ofVec2f fromTo, float delay);
    void onRevealFinish(ofxAnimatable::AnimationEvent & event);
     void onCloseFinish(ofxAnimatable::AnimationEvent & event);
    
    //close
    ofxAnimatableFloat close;
    void resetClose(ofVec2f fromTo, float delay);
    
    // STATES //////////////////////////////////
    enum AnimationStates{
        IDLE,
        REVEAL,
        CLOSE,
        NUM_ANIMATION_STATES
    };
    
    void setAnimationState(AnimationStates _state);
    AnimationStates getState();
    
    // ATLAS //////////////////////////////////
    TextureAtlasDrawer::TexQuad texQuad;
    
    int getCropId();
    
    void setLeftSide(bool _leftSide);
    bool getLeftSide();
private:
    // STATES //////////////////////////////////
    AnimationStates state = IDLE;
    
    // MOTION //////////////////////////////////
    float animationDuration = 1.0f;
    int cropId = 0;
    bool leftSide = false;
};