//
//  ImageSequence.cpp
//  FFG_Shop
//
//  Created by Nicole Messier on 4/30/18.
//
//

#include "ImageSequence.h"

ImageSequence::ImageSequence(){
    
}

ImageSequence::~ImageSequence(){
    
}

void ImageSequence::setup(ofVec2f _pos, ofVec2f _size){
    pos = _pos;
    size = _size;
}

void ImageSequence::update(float dt){
    
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

void ImageSequence::playSequence(int _startFrame, bool loop){
    if(loop){
        setState(States::PLAY_LOOPING);
    } else {
        setState(States::PLAY_ONCE);
    }
}

#pragma mark ATLAS
void ImageSequence::drawInBatch(TextureAtlasDrawer* atlas){
    textureFile = framesPath+frontPath + ofToString(frameCounter) + ".png";
    atlas->drawTextureInBatch(textureFile, texQuad);
}

TextureAtlasDrawer::TexQuad ImageSequence::getParalelogramForRect(const ofRectangle & r,float widthPerc){
    
    
    TextureAtlasDrawer::TexQuad quad;
    
    quad.verts.tl = ofVec3f(r.x , r.y);
    quad.verts.tr = ofVec3f(r.x + r.width, r.y);
    quad.verts.br = ofVec3f(r.x + r.width, r.y + r.height);
    quad.verts.bl = ofVec3f(r.x, r.y + r.height);
    
    //uncomment for cropped
    quad.texCoords.tl = ofVec2f((1-widthPerc)/2, 0);
    quad.texCoords.tr = ofVec2f((1 + widthPerc)/2, 0);
    quad.texCoords.br = ofVec2f((1 + widthPerc)/2, 1);
    quad.texCoords.bl = ofVec2f((1-widthPerc)/2, 1);
    
    return quad; 
}

#pragma mark STATES

void ImageSequence::setState(States _state){
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

void ImageSequence::setFramesPath(string _framesPath){
    framesPath = _framesPath; 
}

void ImageSequence::setNumFrames(int _numFrames){
    numFrames = _numFrames; 
}

#pragma mark ATTRIBUTES
ofVec2f ImageSequence::getPos(){
    return pos;
}

ofVec2f ImageSequence::getSize(){
    return size; 
}

