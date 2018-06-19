//
//  ImgSeqCrop.cpp
//  ShopMotionInteraction
//
//  Created by Nicole Messier on 6/19/18.
//
//

#include "ImgSeqCrop.h"

ImgSeqCrop::ImgSeqCrop(){
    
}

ImgSeqCrop::~ImgSeqCrop(){
    
}

void ImgSeqCrop::setup(int _cropId){
    setupMotion();
    cropId = _cropId; 
}

void ImgSeqCrop::update(float dt){
    
    switch(state){
        case ImgSeqCrop::IDLE: {
            break;
        }
        case ImgSeqCrop::REVEAL:{
            reveal.update(dt);

            break;
        }
        case ImgSeqCrop::CLOSE: {
            close.update(dt);
            
            break;
        }
        default: break;
    }
}

void ImgSeqCrop::draw(){
    
}

#pragma mark MOTION
void ImgSeqCrop::setupMotion(){
    reveal.reset(1.0);
    reveal.setRepeatType(AnimRepeat::PLAY_ONCE);
    reveal.setDuration(animationDuration);
    reveal.setCurve(TANH);
    
    close.reset(1.0);
    close.setRepeatType(AnimRepeat::PLAY_ONCE);
    close.setDuration(animationDuration);
    close.setCurve(TANH);
    
    ofAddListener(close.animFinished, this, &ImgSeqCrop::onCloseFinish);
    
    //Only need one b/c reveal1 and reveal2 should end at the same time
    //ofAddListener(reveal1.animFinished, this, &ofxImageSequenceAtlas::onRevealFinish);
}

void ImgSeqCrop::resetReveal(ofVec2f fromTo, float delay){
    reveal.reset(fromTo.x);
    reveal.animateToAfterDelay(fromTo.y, delay);
    setAnimationState(ImgSeqCrop::REVEAL);
}

void ImgSeqCrop::resetClose(ofVec2f fromTo, float delay){
    close.reset(fromTo.x);
    close.animateToAfterDelay(fromTo.y, delay);
    setAnimationState(ImgSeqCrop::CLOSE);
}


#pragma mark STATES
void ImgSeqCrop::setAnimationState(ImgSeqCrop::AnimationStates _state){
    state = _state;
    
    switch(state){
        case ImgSeqCrop::IDLE: {
            break;
        }
        case ImgSeqCrop::REVEAL:{

            break;
        }
        case ImgSeqCrop::CLOSE: {

            break;
        }
        default: break;
    }

}

ImgSeqCrop::AnimationStates ImgSeqCrop::getState(){
    return state; 
}

#pragma mark GET

int ImgSeqCrop::getCropId(){
    return cropId;
}

#pragma mark CALLBACKS
void ImgSeqCrop::onRevealFinish(ofxAnimatable::AnimationEvent & event){
    setAnimationState(REVEAL); 
}

void ImgSeqCrop::onCloseFinish(ofxAnimatable::AnimationEvent & event){
    setAnimationState(IDLE);
}

#pragma mark SIDE
void ImgSeqCrop::setLeftSide(bool _leftSide){
    leftSide = _leftSide; 
}

bool ImgSeqCrop::getLeftSide(){
    return leftSide;
}