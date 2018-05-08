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

void ofxImageSequenceAtlas::setup(ofVec2f _pos, ofVec2f _size){
    pos = _pos;
    size = _size;
    sizeOrg = size;
    
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

}

void ofxImageSequenceAtlas::playSequence(int _startFrame, bool loop){
    if(loop){
        setState(States::PLAY_LOOPING);
    } else {
        setState(States::PLAY_ONCE);
    }
}

#pragma mark ATLAS
void ofxImageSequenceAtlas::drawInBatch(TextureAtlasDrawer* atlas){
    textureFile = framesPath+frontPath + ofToString(frameCounter) + ".png";
    //ofLogNotice("ofxImageSequenceAtlas") << "textureFile: " << textureFile;
    atlas->drawTextureInBatch(textureFile, texQuad);
}

TextureAtlasDrawer::TexQuad ofxImageSequenceAtlas::getParalelogramForRect(const ofRectangle & r,float widthPerc){
    
    
    TextureAtlasDrawer::TexQuad quad;
    
    quad.verts.tl = ofVec3f(r.x , r.y);
    quad.verts.tr = ofVec3f(r.x + r.width, r.y);
    quad.verts.br = ofVec3f(r.x + r.width, r.y + r.height);
    quad.verts.bl = ofVec3f(r.x, r.y + r.height);
    
    
    //uncomment for cropped
    quad.texCoords.tl = ofVec2f(0, 0);
    quad.texCoords.tr = ofVec2f(1 - widthPerc, 0);
    quad.texCoords.br = ofVec2f(1 - widthPerc, 1);
    quad.texCoords.bl = ofVec2f(0, 1);

    return quad; 
}

void ofxImageSequenceAtlas::calculateCrop(ofVec2f cropPerc){
    ofVec2f cropSize = sizeOrg*cropPerc;
    ofRectangle r = ofRectangle(getPos().x, getPos().y, cropSize.x, cropSize.y);
    
    TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, 1-cropPerc.x);
    texQuad = tq;
}

void ofxImageSequenceAtlas::setTextureDimensions(TextureAtlasDrawer::TextureDimensions _td){
    td = _td;
}

#pragma mark MOTION
void ofxImageSequenceAtlas::setupMotion(){
    // MOTION VARIABLES //////////////////////////////
    reveal.reset(1.0);
    reveal.setRepeatType(AnimRepeat::PLAY_ONCE);
    reveal.setDuration(animationDuration);
    reveal.setCurve(TANH);
}

void ofxImageSequenceAtlas::resetReveal(ofVec2f fromTo, float delay){
    reveal.reset(fromTo.x);
    reveal.animateToAfterDelay(fromTo.y, delay);
   
}

#pragma mark STATES

void ofxImageSequenceAtlas::setState(States _state){
    state = _state;
    
    switch(state){
        case States::PLAY_ONCE: {

            break ;
        }
        case States::PLAY_LOOPING: {
            
            break ;
        }
        case States::STOPPED: {break ;}
        default: break;
    }
}

#pragma mark FILE PATHS

void ofxImageSequenceAtlas::setFramesPath(string _framesPath){
    framesPath = _framesPath; 
}

void ofxImageSequenceAtlas::setNumFrames(int _numFrames){
    numFrames = _numFrames; 
}

#pragma mark ATTRIBUTES
ofVec2f ofxImageSequenceAtlas::getPos(){
    return pos;
}

ofVec2f ofxImageSequenceAtlas::getSize(){
    return size; 
}

