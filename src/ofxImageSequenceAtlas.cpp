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
        case AnimState::REVEAL: {
            reveal.update(dt);
            
            
            if(!left){
                calculateCropRight(ofVec2f(reveal.val(), 1.0f));
            } else {
                calculateCropLeft(ofVec2f(reveal.val(), 1.0f));
            }
            break;
        }
        case AnimState::CLOSE_REVEAL: {
            reveal.update(dt);
            if(!left){
                calculateCropRight(ofVec2f(reveal.val(), 1.0f));
            } else {
                calculateCropLeft(ofVec2f(reveal.val(), 1.0f));
            }
            
            break;
        }
        default: break;
    }

}

void ofxImageSequenceAtlas::drawDebug(){
    //ofDrawBitmapString("col: " + ofToString(column), pos.x, pos.y);
    ofDrawBitmapString("a: " + ofToString(animState)
                       + "\n s: " + ofToString(state),
                       pos.x, pos.y);
}

#pragma mark MOTION

void ofxImageSequenceAtlas::setMotionState(AnimState _animState){
    animState = _animState;
    
    switch(animState){
        case AnimState::IDLE: { break; }
        case AnimState::REVEAL:{ break; }
        case AnimState::CLOSE_REVEAL: {
            resetReveal(ofVec2f(reveal.val(), 1.0f), 0.0f);
            break;
        }
        default: break;
    }
}

void ofxImageSequenceAtlas::resetReveal(ofVec2f fromTo, float delay){
    reveal.reset(fromTo.x);
    reveal.animateToAfterDelay(fromTo.y, delay);
}

void ofxImageSequenceAtlas::setupMotion(){
    // MOTION VARIABLES //////////////////////////////
    reveal.reset(1.0);
    reveal.setRepeatType(AnimRepeat::PLAY_ONCE);
    reveal.setDuration(animationDuration);
    reveal.setCurve(TANH);
    
    ofAddListener(reveal.animFinished, this, &ofxImageSequenceAtlas::onRevealFinish);
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
    textureFile = framesPath+frontPath + ofToString(frameCounter) + ".png";
    //textureFile = framesPath+frontPath + ofToString(1) + ".png";
    atlas->drawTextureInBatch(textureFile, texQuad1);
    if(doubleCrop)
    {
        atlas->drawTextureInBatch(textureFile, texQuad2);
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
        quad.texCoords.tr = ofVec2f(0.5 - widthPerc, 0);
        quad.texCoords.br = ofVec2f(0.5 - widthPerc, 1);
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


void ofxImageSequenceAtlas::calculateCropRight(ofVec2f cropPerc){
    
    if(doubleCrop)
    {
        float cropPercNewX = cropPerc.x/2;
        ofVec2f cropSize = ofVec2f(sizeOrg.x*cropPercNewX, sizeOrg.y*cropPerc.y);
        
        //Set up first quad
        ofRectangle r = ofRectangle(getPos().x, getPos().y, cropSize.x, cropSize.y);
        TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, 1-cropPercNewX, false, false);
        texQuad1 = tq;
        
        //Set up second quad
        ofRectangle r2 = ofRectangle(getPos().x + sizeOrg.x/2, getPos().y, cropSize.x, cropSize.y);
        TextureAtlasDrawer::TexQuad tq2 = getParalelogramForRect(r2, cropPercNewX, false, true);
        texQuad2 = tq2;
        
    } else
    {
        ofVec2f cropSize = sizeOrg*cropPerc;
        ofRectangle r = ofRectangle(getPos().x, getPos().y, cropSize.x, cropSize.y);
        
        TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, 1-cropPerc.x, false, false);
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
    framesPath = _framesPath; 
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

