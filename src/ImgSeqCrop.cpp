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

void ImgSeqCrop::setup(int _cropId, ofVec2f _pos, ofVec2f _sizeOrg){
    setupMotion();
    cropId = _cropId;
    pos = _pos;
    sizeOrg = _sizeOrg; 
    
    //FADE STATE
    fadeIn.reset(0.0);
    fadeIn.setRepeatType(PLAY_ONCE);
    fadeIn.setDuration(fadeDuration);
    fadeIn.setCurve(TANH);
    
    fadeOut.reset(0.0);
    fadeOut.setRepeatType(PLAY_ONCE);
    fadeOut.setDuration(fadeDuration);
    fadeOut.setCurve(TANH);
    
    ofAddListener(fadeIn.animFinished, this, &ImgSeqCrop::onFadeInFinish);
    ofAddListener(fadeOut.animFinished, this, &ImgSeqCrop::onFadeOutFinish);
    
}

void ImgSeqCrop::update(float dt){
    
    fadeIn.setDuration(fadeDuration);
    fadeIn.setCurve(fadeCurve);
    
    fadeOut.setDuration(fadeDuration);
    fadeOut.setCurve(fadeCurve);
    
    reveal.setDuration(revealDuration);
    reveal.setCurve(revealCurve);

    close.setDuration(closeDuration);
    close.setCurve(closeCurve);

    blend.setDuration(blendDuration);
    blend.setCurve(blendCurve);
    
    switch(revevalState){
        case ImgSeqCrop::IDLE: {
            break;
        }
        case ImgSeqCrop::REVEAL:{
            reveal.update(dt);

            break;
        }
        case ImgSeqCrop::CLOSE: {
            close.update(dt);
            blend.update(dt); 
            break;
        }
        default: break;
    }
    
    //Fade Durations
    fadeIn.update(dt);
    fadeOut.update(dt);
    
    switch(fadeState){
        case ImgSeqCrop::FADE_IN: {
            alpha = 255.0f * fadeIn.val();
            
            //ofLogNotice() << fadeIn.val();
            break;
        }
        case ImgSeqCrop::FADE_OUT:{
            alpha = 255.0f * fadeOut.val();
            break;
        }
        case ImgSeqCrop::VISIBLE: {
            alpha = 255.0f;
            break;
        }
        default: break;
    }
    
    if(sequence)
    {
        textureFile = framesPath+frontPath + ofToString(frameCounter) + ".png";
    }
    else
    {
        textureFile = fileName;
    }
    
}

void ImgSeqCrop::draw(){
    
}

void ImgSeqCrop::drawInBatch(TextureAtlasDrawer* atlas){
#ifdef TARGET_WIN32
        ofStringReplace(textureFile, "data\\", "");
#endif

    bool doesFileExist ;
    
    /*
     Check for files kills the framerate
     Need to do: add as debug
     */
    
    atlas->drawTextureInBatch(textureFile, texQuad,  ofColor(255, alpha));
}


#pragma mark LOOPING
void ImgSeqCrop::loopFrames(){
    if(frameCounter<numFrames-1 &&
       !(frameRateCounter%frameRateDivisor)){
        frameCounter++;
    } else if(frameCounter == numFrames-1){
        frameRateCounter = frameRateDivisor;
        frameCounter = 1;
    }
    
    frameRateCounter++;
}

#pragma mark MOTION
void ImgSeqCrop::setupMotion(){
    reveal.reset(1.0);
    reveal.setRepeatType(AnimRepeat::PLAY_ONCE);
    reveal.setDuration(revealDuration);
    reveal.setCurve(revealCurve);
    
    close.reset(0.0);
    close.setRepeatType(AnimRepeat::PLAY_ONCE);
    close.setDuration(closeDuration);
    close.setCurve(closeCurve);
    
    blend.reset(0.0);
    blend.setRepeatType(AnimRepeat::PLAY_ONCE);
    blend.setDuration(blendDuration);
    blend.setCurve(blendCurve);
    
    ofAddListener(close.animFinished, this, &ImgSeqCrop::onCloseFinish);
    
    //Only need one b/c reveal1 and reveal2 should end at the same time
    //ofAddListener(reveal1.animFinished, this, &ofxImageSequenceAtlas::onRevealFinish);
}

void ImgSeqCrop::resetReveal(ofVec2f fromTo, float delay, float duration){
    reveal.reset(fromTo.x);
    reveal.animateToAfterDelay(fromTo.y, delay);
    reveal.setDuration(revealDuration);
    setAnimationState(ImgSeqCrop::REVEAL);
}

void ImgSeqCrop::resetClose(ofVec2f fromTo, float delay, float duration){
    close.reset(fromTo.x);
    close.animateToAfterDelay(fromTo.y, delay);
    close.setDuration(closeDuration);
    
    blend.reset(0.0);
    blend.animateToAfterDelay(1.0, delay);
    blend.setDuration(blendDuration);
    setAnimationState(ImgSeqCrop::CLOSE);
}

void ImgSeqCrop::setAnimationParams(float _fadeDuration,
                        AnimCurve _fadeCurve,
                        float _blendDuration,
                        AnimCurve _blendCurve,
                        float _closeDuration,
                        AnimCurve _closeCurve,
                        float _revealDuration,
                        AnimCurve _revealCurve)
{
     fadeDuration = _fadeDuration;
     fadeCurve = _fadeCurve;
     blendDuration = _blendDuration;
     blendCurve = _blendCurve;
     closeDuration = _closeDuration;
     closeCurve = _closeCurve;
    revealDuration = _revealDuration;
     revealCurve = _revealCurve;
}

#pragma mark STATES
void ImgSeqCrop::setAnimationState(ImgSeqCrop::AnimationStates _state){
    revevalState = _state;
    
    switch(revevalState){
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
    return revevalState;
}

#pragma mark GET

int ImgSeqCrop::getCropId(){
    return cropId;
}

void ImgSeqCrop::setParentId(int _parentUID){
    parentUID = _parentUID;
}

ofVec2f ImgSeqCrop::getPos(){
    return pos;
}

ofVec2f ImgSeqCrop::getCenter(){
    ofVec2f center;
    center.x = pos.x + sizeOrg.x/2;
    center.y = pos.y + sizeOrg.y/2;
    return center;
}

int ImgSeqCrop::getFrameCounter(){
    return frameCounter; 
}

#pragma mark CALLBACKS
void ImgSeqCrop::onRevealFinish(ofxAnimatable::AnimationEvent & event){
    setAnimationState(REVEAL); 
}

void ImgSeqCrop::onCloseFinish(ofxAnimatable::AnimationEvent & event){
    setAnimationState(IDLE);
    close.reset(0.0f);
}

void ImgSeqCrop::onFadeInFinish(ofxAnimatable::AnimationEvent & event){
    setFadeState(ImgSeqCrop::VISIBLE);
}

void ImgSeqCrop::onFadeOutFinish(ofxAnimatable::AnimationEvent & event){
    setFadeState(ImgSeqCrop::FADE_IN);
    framesPath = framesPathRef;
    numFrames = numFramesRef; 
    
    //NEED TO DO: Sync this from master
    if(second)
    {
        frameCounter = 0;
        frameRateCounter = frameRateDivisor;
    }
    
}


#pragma mark SIDE
void ImgSeqCrop::setLeftSide(bool _leftSide){
    leftSide = _leftSide; 
}

bool ImgSeqCrop::getLeftSide(){
    return leftSide;
}

#pragma mark CROP PERCENT
void ImgSeqCrop::setCropPerc(float _cropPerc){
    cropPerc = _cropPerc; 
}

float ImgSeqCrop::getCropPerc(){
    return cropPerc;
}

#pragma mark FILEPATHS

void ImgSeqCrop::setFramesPath(string _framesPath){
    #ifdef TARGET_WIN32
        framesPathRef = _framesPath + "\\";
    #else
        framesPathRef = _framesPath;
    
    #endif

    
    if(useFadeOut)
    {
        setFadeState(ImgSeqCrop::FADE_OUT);
    }
    else
    {
        framesPath = framesPathRef;
        numFrames = numFramesRef;
        
        setFadeState(ImgSeqCrop::VISIBLE);
    }
    
    
}

void ImgSeqCrop::setFrameCounter(int _frameCounter){
    frameCounter = _frameCounter;
}

string ImgSeqCrop::getTextureFile()
{
    return textureFile; 
}

#pragma mark NUM FRAMES
void ImgSeqCrop::setNumFrames(int _numFrames){
    numFramesRef = _numFrames;
    
    
}

#pragma mark FRAME RATE
void ImgSeqCrop::setFrameRateDivisor(int _frameRateDivisor){
    frameRateDivisor = _frameRateDivisor; 
}

#pragma mark ANIMATION STATE
void ImgSeqCrop::setFadeState(FadeStates _fadeState){
    fadeState = _fadeState;
    
    switch(fadeState){
        case ImgSeqCrop::FADE_IN: {
            fadeIn.animateFromTo(0.0f, 1.0f);
            break;
        }
        case ImgSeqCrop::FADE_OUT:{
            fadeOut.animateFromTo(1.0f, 0.0f);
            transition = true;
            break;
        }
        case ImgSeqCrop::VISIBLE: {
            alpha = 255.0f;
            //transition = false;
            break;
        }
        default: break;
    }
    
}

bool ImgSeqCrop::getTransition()
{
    return transition;
}

void ImgSeqCrop::setTransition(bool _transition){
    transition = _transition; 
}

#pragma mark SECOND
void ImgSeqCrop::setIsSecond(bool _second){
    second = _second; 
}

#pragma mark DEBUG
string ImgSeqCrop::getFramesPathRef(){
    return framesPathRef; 
}

#pragma mark SEQUENCE
void ImgSeqCrop::setSequence(bool _sequence){
    sequence = _sequence;
}

void ImgSeqCrop::setFileName(string _fileName){
    fileName = _fileName; 
}

#pragma mark FADE OUT

void ImgSeqCrop::setUseFadeOut(bool _useFadeOut){
    useFadeOut = _useFadeOut;
}
