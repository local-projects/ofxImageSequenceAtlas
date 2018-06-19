//
//  ofxofxofxImageSequenceAtlasAtlasAtlas.cpp
//  FFG_Shop
//
//  Created by Nicole Messier on 4/30/18.
//
//

#include "ofxImageSequenceAtlas.h"

ofxImageSequenceAtlas::ofxImageSequenceAtlas(){
    
}

ofxImageSequenceAtlas::~ofxImageSequenceAtlas(){
    
}

void ofxImageSequenceAtlas::setup(ofVec2f _pos, ofVec2f _size, int _column, int _row){
    pos = _pos;
    size = _size;
    sizeOrg = size;
    column = _column;
    row = _row;
    
    setupMotion();
    
    RUI_SHARE_PARAM(widthPercDebug, 0, 1);
    RUI_SHARE_PARAM(textCropPerc, 0, 1);
    
}

void ofxImageSequenceAtlas::setId(int _uid){
    uid = _uid; 
}

void ofxImageSequenceAtlas::update(float dt){
    
    switch(state){
        case States::PLAY_ONCE: {
            if(frameCounter<numFrames-1 &&
               !(frameRateCounter%frameRateDivisor)){
                frameCounter++;
            } else if(frameCounter == numFrames-1){
                setState(States::STOPPED);
            }
            
            frameRateCounter++;
            break ;
        }
        case States::PLAY_LOOPING: {
            if(frameCounter<numFrames-1 &&
               !(frameRateCounter%frameRateDivisor)){
                frameCounter++;
            } else if(frameCounter == numFrames-1){
                frameRateCounter = frameRateDivisor;
                frameCounter = 1;
            }
            
            frameRateCounter++;
            break ;
        }
        case States::STOPPED: {break ;}
        default: break;
    }
    
    switch(animState){
        case AnimState::IDLE: { break; }
        case AnimState::REVEAL:{
            reveal1.update(dt);
            reveal2.update(dt);
            break;
        }
        case AnimState::CLOSE_REVEAL: {
            reveal1.update(dt);
            reveal2.update(dt);
            break;
        }
        default: break;
    }
}

void ofxImageSequenceAtlas::drawDebug(){
    //ofDrawBitmapString("col: " + ofToString(column), pos.x, pos.y);
    ofDrawBitmapString("a: " + ofToString(animState)
                       + "\n uid: " + ofToString(uid),
                       pos.x, pos.y);
}

#pragma mark MOTION

void ofxImageSequenceAtlas::setMotionState(AnimState _animState){
    animState = _animState;
    
    switch(animState){
        case AnimState::IDLE: {
            animatingCrop1 = false;
            animatingCrop2 = false;
            break;
        }
        case AnimState::REVEAL:{
            break;
        }
        case AnimState::CLOSE_REVEAL: {
            
            break;
        }
        default: break;
    }
}

ofxImageSequenceAtlas::AnimState ofxImageSequenceAtlas::getMotionState(){
    return animState;
}

void ofxImageSequenceAtlas::resetReveal1(ofVec2f fromTo, float delay){
    
    reveal1.reset(fromTo.x);
    reveal1.animateToAfterDelay(fromTo.y, delay);
    setMotionState(AnimState::REVEAL);
    animatingCrop1 = true;
}

void ofxImageSequenceAtlas::resetReveal2(ofVec2f fromTo, float delay){
    
    reveal2.reset(fromTo.x);
    reveal2.animateToAfterDelay(fromTo.y, delay);
    setMotionState(AnimState::REVEAL);
    animatingCrop2 = true;
}

void ofxImageSequenceAtlas::resetClose1(ofVec2f fromTo, float delay){
    reveal1.reset(fromTo.x);
    reveal1.animateToAfterDelay(fromTo.y, delay);
    setMotionState(AnimState::CLOSE_REVEAL);
}

void ofxImageSequenceAtlas::resetClose2(ofVec2f fromTo, float delay){
    reveal2.reset(fromTo.x);
    reveal2.animateToAfterDelay(fromTo.y, delay);
    setMotionState(AnimState::CLOSE_REVEAL);
}

void ofxImageSequenceAtlas::setupMotion(){
    // MOTION VARIABLES //////////////////////////////
    reveal1.reset(1.0);
    reveal1.setRepeatType(AnimRepeat::PLAY_ONCE);
    reveal1.setDuration(animationDuration);
    reveal1.setCurve(TANH);
    
    reveal2.reset(1.0);
    reveal2.setRepeatType(AnimRepeat::PLAY_ONCE);
    reveal2.setDuration(animationDuration);
    reveal2.setCurve(TANH);
    
    close1.reset(1.0);
    close1.setRepeatType(AnimRepeat::PLAY_ONCE);
    close1.setDuration(animationDuration);
    close1.setCurve(TANH);
    
    close2.reset(1.0);
    close2.setRepeatType(AnimRepeat::PLAY_ONCE);
    close2.setDuration(animationDuration);
    close2.setCurve(TANH);
    
    //Only need one b/c reveal1 and reveal2 should end at the same time
    ofAddListener(reveal1.animFinished, this, &ofxImageSequenceAtlas::onRevealFinish);
}

void ofxImageSequenceAtlas::playSequence(int _startFrame, bool loop){
    if(loop){
        setState(States::PLAY_LOOPING);
    } else {
        setState(States::PLAY_ONCE);
    }
}

void ofxImageSequenceAtlas::onRevealFinish(ofxAnimatable::AnimationEvent & event){
    switch(animState){
        case AnimState::IDLE: { break; }
        case AnimState::REVEAL:{ break; }
        case AnimState::CLOSE_REVEAL: {
            setMotionState(AnimState::IDLE);
            left = false;
            break;
        }
        default: break;
    }
}
void ofxImageSequenceAtlas::setFrameRateDivisor(int _frameRateDivisor){
    frameRateDivisor = _frameRateDivisor;
    
}


#pragma mark ATLAS
void ofxImageSequenceAtlas::drawInBatch(TextureAtlasDrawer* atlas){
	string temp = framesPath + frontPath + ofToString(frameCounter) + ".png";

#ifdef TARGET_WIN32
	ofStringReplace(textureFile, "data\\", "");
#endif
    textureFile = framesPath+frontPath + ofToString(frameCounter) + ".png";
    
    atlas->drawTextureInBatch(textureFile, texQuad1, uid);
    if(doubleCrop)
    {
        atlas->drawTextureInBatch(textureFile, texQuad2, uid);
    }
    
    if(debug)
    {
        ofSetColor(0, 255, 0);
        ofNoFill();
        {
            
            float width = texQuad1.verts.tl.x - texQuad1.verts.tr.x;
            float height = texQuad1.verts.bl.y - texQuad1.verts.tl.y;
            ofDrawRectangle(texQuad1.verts.tl.x, texQuad1.verts.tr.y, fabs(width), fabs(height));
            
            
            ofSetColor(255, 0, 0);
            float width2 = texQuad2.verts.tl.x - texQuad2.verts.tr.x;
            float height2 = texQuad2.verts.bl.y - texQuad2.verts.tl.y;
            ofDrawRectangle(texQuad2.verts.tl.x, texQuad2.verts.tr.y, fabs(width), fabs(height));
            
        }
        ofSetColor(255);
        ofFill();
    }
}

TextureAtlasDrawer::TexQuad ofxImageSequenceAtlas::getParalelogramForRect(const ofRectangle & r,float widthPerc, float fromLeft, float fromMiddle){
    
   
    TextureAtlasDrawer::TexQuad quad;
    
    quad.verts.tl = ofVec3f(r.x , r.y);
    quad.verts.tr = ofVec3f(r.x + r.width, r.y);
    quad.verts.br = ofVec3f(r.x + r.width, r.y + r.height);
    quad.verts.bl = ofVec3f(r.x, r.y + r.height);
    
    if(fromLeft){
        
        quad.texCoords.tl = ofVec2f(1 - widthPerc, 0);
        quad.texCoords.tr = ofVec2f(1, 0);
        quad.texCoords.br = ofVec2f(1, 1);
        quad.texCoords.bl = ofVec2f(1 - widthPerc, 1);
    } else if(fromMiddle)
    {
        quad.texCoords.tl = ofVec2f(0.5, 0);
        quad.texCoords.tr = ofVec2f(1 - (0.5 - widthPerc), 0);
        quad.texCoords.br = ofVec2f(1 - (0.5 - widthPerc), 1);
        quad.texCoords.bl = ofVec2f(0.5, 1);
    }else {
        //uncomment for cropped
        quad.texCoords.tl = ofVec2f(0, 0);
        quad.texCoords.tr = ofVec2f(1 - widthPerc, 0);
        quad.texCoords.br = ofVec2f(1 - widthPerc, 1);
        quad.texCoords.bl = ofVec2f(0, 1);
    }

    return quad;
}

void ofxImageSequenceAtlas::calculateCropLeftRight(ofVec2f cropPerc){
    ofVec2f cropSize = sizeOrg*cropPerc;
    ofVec2f leftOver = (sizeOrg - cropSize);
    ofRectangle r = ofRectangle(getPos().x + leftOver.x/2, getPos().y, cropSize.x, cropSize.y);
    
    
    TextureAtlasDrawer::TexQuad quad;
    
    quad.verts.tl = ofVec3f(r.x , r.y);
    quad.verts.tr = ofVec3f(r.x + r.width, r.y);
    quad.verts.br = ofVec3f(r.x + r.width, r.y + r.height);
    quad.verts.bl = ofVec3f(r.x, r.y + r.height);
    
    float newPerc = 1 - cropPerc.x;
    quad.texCoords.tl = ofVec2f(newPerc/2, 0);
    quad.texCoords.tr = ofVec2f(1 - newPerc/2, 0);
    quad.texCoords.br = ofVec2f(1 - newPerc/2, 1);
    quad.texCoords.bl = ofVec2f(newPerc/2, 1);
    
    
    texQuad1 = quad;
}

void ofxImageSequenceAtlas::calculateCropLeft(ofVec2f cropPerc){
    ofVec2f cropSize = sizeOrg*cropPerc;
    ofRectangle r = ofRectangle((getPos().x + size.x) - cropSize.x, getPos().y, cropSize.x, cropSize.y);
    
    TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, cropPerc.x, true, false);
    texQuad1 = tq;
}


void ofxImageSequenceAtlas::calculateCropRight(ofVec2f cropPerc1, ofVec2f cropPerc2){
    
    if(doubleCrop)
    {
        cropPercNewX1 = cropPerc1.x/2;
        ofVec2f cropSize = ofVec2f(sizeOrg.x*cropPercNewX1, sizeOrg.y*cropPerc1.y);
        
        //Set up first quad
        ofRectangle r = ofRectangle(getPos().x, getPos().y, cropSize.x, cropSize.y);
        TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, 1-cropPercNewX1, false, false);
        texQuad1 = tq;
        
        cropPercNewX2 = cropPerc2.x/2;
        ofVec2f cropSize2 = ofVec2f(sizeOrg.x*cropPercNewX2, sizeOrg.y*cropPerc2.y);
        
        //Set up second quad
        ofRectangle r2 = ofRectangle(getPos().x + sizeOrg.x/2, getPos().y, cropSize2.x, cropSize2.y);
        TextureAtlasDrawer::TexQuad tq2 = getParalelogramForRect(r2, cropPercNewX2, false, true);
        texQuad2 = tq2;
        
    } else
    {
        cropPercNewX1 = cropPerc1.x;
        ofVec2f cropSize = sizeOrg*cropPercNewX1;
        ofRectangle r = ofRectangle(getPos().x, getPos().y, cropSize.x, cropSize.y);
        TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, 1-cropPercNewX1, false, false);
        
        texQuad1 = tq;
    }
}

void ofxImageSequenceAtlas::setTextureDimensions(TextureAtlasDrawer::TextureDimensions _td){
    td = _td;
}

#pragma mark STATES

ofxImageSequenceAtlas::States ofxImageSequenceAtlas::getState(){
    return state;
}

void ofxImageSequenceAtlas::setState(States _state){
    state = _state;
    
    switch(state){
        case States::PLAY_ONCE: {
             //ofLogNotice("ofxImageSequenceAtlas") << "set state to PLAY_ONCE" ;
            break ;
        }
        case States::PLAY_LOOPING: {
            //ofLogNotice("ofxImageSequenceAtlas") << "set state to PLAY_LOOPING" ;
            break ;
        }
        case States::STOPPED: {
            //ofLogNotice("ofxImageSequenceAtlas") << "set state to STOPPED" ;
            break ;
        }
        default: break;
    }
}

#pragma mark FILE PATHS

void ofxImageSequenceAtlas::setFramesPath(string _framesPath){
#ifdef TARGET_WIN32
	framesPath = _framesPath + "\\";
#else 
    framesPath = _framesPath ; 

#endif
}

void ofxImageSequenceAtlas::setNumFrames(int _numFrames){
    numFrames = _numFrames;
    frameCounter = 0;
    frameRateCounter = frameRateDivisor;
}

#pragma mark ATTRIBUTES
ofVec2f ofxImageSequenceAtlas::getPos(){
    return pos;
}

ofVec2f ofxImageSequenceAtlas::getSize(){
    return size; 
}

ofVec2f ofxImageSequenceAtlas::getSizeOrg(){
    return sizeOrg;
}


int ofxImageSequenceAtlas::getColumn(){
    return column;
}

int ofxImageSequenceAtlas::getRow(){
    return row;
}

void ofxImageSequenceAtlas::setAnimatingCrop1(bool _animatingCrop1){
    animatingCrop1 = _animatingCrop1;
}

void ofxImageSequenceAtlas::setAnimatingCrop2(bool _animatingCrop2){
    animatingCrop2 = _animatingCrop2;
}

#pragma mark GET
bool ofxImageSequenceAtlas::getDoubleCrop()
{
    return doubleCrop;
}

float ofxImageSequenceAtlas::getCropPercNewX1(){
    return cropPercNewX1;
}

float ofxImageSequenceAtlas::getCropPercNewX2(){
    return cropPercNewX2;
}

bool ofxImageSequenceAtlas::getAnimatingCrop1(){
    return animatingCrop1;
}

bool ofxImageSequenceAtlas::getAnimatingCrop2(){
    return animatingCrop2; 
}
