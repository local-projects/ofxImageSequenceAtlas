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
    
    //RUI_SHARE_PARAM(widthPercDebug, 0, 1);
    //RUI_SHARE_PARAM(textCropPerc, 0, 1);
    
    //set up crops
    int numCrops;
    
    (doubleCrop) ? numCrops = 2 : numCrops = 1;
    for(int i=0; i<numCrops; i++)
    {
        ImgSeqCrop * temp = new ImgSeqCrop();
        ofVec2f cropPos;
        
        (i == 0) ? cropPos = pos : cropPos = ofVec2f(pos.x + size.x/2, pos.y);
        temp->setup(i, cropPos, ofVec2f(sizeOrg.x/2, sizeOrg.y));
        temp->setParentId(uid); 
        crops.push_back(temp);
        
        if(i == 1)
        {
            crops[i]->setIsSecond(true);
        }
        else if (i == 0 ) {
            //The two crops need to always be in sync, and the way the system is set up. The second crop will fade out first. once the first crop is finishing fade out, we need to make sure the crops are in sync.
            ofAddListener(crops[i]->fadeOut.animFinished, this, &ofxImageSequenceAtlas::onCropFadeOutFinish);
        }
        
    }
    
    
}

void ofxImageSequenceAtlas::setId(int _uid){
    uid = _uid; 
}

void ofxImageSequenceAtlas::update(float dt){
    
    switch(state){
        case States::PLAY_ONCE: {
            
            break ;
        }
        case States::PLAY_LOOPING: {
            for(auto &crop : crops)
            {
                crop->loopFrames();
            }
            break ;
        }
        case States::STOPPED: {break ;}
        default: break;
    }
    
    for(auto &crop : crops)
    {
        crop->update(dt);
    }

}

void ofxImageSequenceAtlas::drawDebug(){
    //ofDrawBitmapString("col: " + ofToString(column), pos.x, pos.y);
    ofDrawBitmapString("\n uid: " + ofToString(uid),
                       pos.x, pos.y);
    
    ofSetColor(ofColor::red);
    ofNoFill();
    
    ofDrawRectangle(getPos().x, getPos().y, getSize().x/2, getSize().y/2);
    ofDrawRectangle(getPos().x + getSize().x/2, getPos().y + getSize().y/2, getSize().x/2, getSize().y/2);
    
    ofSetColor(ofColor::white);
    ofFill();
}

void ofxImageSequenceAtlas::drawRect()
{
    ofSetColor(ofColor::red, 100);
    ofDrawRectangle(getPos().x, getPos().y, getSize().x, getSize().y);
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

TextureAtlasDrawer::TexQuad ofxImageSequenceAtlas::getParalelogramForRect_Croped(const ofRectangle & r, float widthPerc){
    
    TextureAtlasDrawer::TexQuad quad;
    
    quad.verts.tl = ofVec3f(r.x , r.y);
    quad.verts.tr = ofVec3f(r.x + r.width, r.y);
    quad.verts.br = ofVec3f(r.x + r.width, r.y + r.height);
    quad.verts.bl = ofVec3f(r.x, r.y + r.height);
    
    quad.texCoords.tl = ofVec2f(offset, 0);
    quad.texCoords.tr = ofVec2f(offset + widthPerc, 0);
    quad.texCoords.br = ofVec2f(offset + widthPerc, 1);
    quad.texCoords.bl = ofVec2f(offset, 1);
    
    return quad;
}

void ofxImageSequenceAtlas::setOffset(float _offset){
    offset = _offset;
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
    
    
    crops[0]->texQuad = quad;
}

void ofxImageSequenceAtlas::calculateCropLeft(ofVec2f cropPerc){
    ofVec2f cropSize = sizeOrg*cropPerc;
    ofRectangle r = ofRectangle((getPos().x + size.x) - cropSize.x, getPos().y, cropSize.x, cropSize.y);
    
    TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, cropPerc.x, true, false);
    crops[0]->texQuad = tq;
}


void ofxImageSequenceAtlas::calculateCropRight(ofVec2f cropPerc1, ofVec2f cropPerc2){
    
    if(doubleCrop)
    {
        cropPercNewX1 = cropPerc1.x/2;
        crops[0]->setCropPerc(cropPercNewX1);
        ofVec2f cropSize = ofVec2f(sizeOrg.x*cropPercNewX1, sizeOrg.y*cropPerc1.y);
        
        //Set up first quad
        ofRectangle r = ofRectangle(getPos().x, getPos().y, cropSize.x, cropSize.y);
        TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, 1-cropPercNewX1, false, false);
        crops[0]->texQuad = tq;
        
        cropPercNewX2 = cropPerc2.x/2;
        crops[1]->setCropPerc(cropPercNewX2);
        ofVec2f cropSize2 = ofVec2f(sizeOrg.x*cropPercNewX2, sizeOrg.y*cropPerc2.y);
        
        //Set up second quad
        ofRectangle r2 = ofRectangle(getPos().x + sizeOrg.x/2, getPos().y, cropSize2.x, cropSize2.y);
        TextureAtlasDrawer::TexQuad tq2 = getParalelogramForRect(r2, cropPercNewX2, false, true);
        crops[1]->texQuad = tq2;
        
    }
    else
    {
        cropPercNewX1 = cropPerc1.x;
        crops[0]->setCropPerc(cropPercNewX1);
        ofVec2f cropSize = sizeOrg*cropPercNewX1;
        ofRectangle r = ofRectangle(getPos().x, getPos().y, cropSize.x, cropSize.y);
        TextureAtlasDrawer::TexQuad tq = getParalelogramForRect(r, 1-cropPercNewX1, false, false);
        
        crops[0]->texQuad = tq;
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


void ofxImageSequenceAtlas::setFramesPath(int index, string _framesPath){
    crops[index]->setFramesPath(_framesPath);
    
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

void ofxImageSequenceAtlas::setDoubleCrop(bool _doubleCrop){
    doubleCrop = _doubleCrop;
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

#pragma mark CALL BACKS
void ofxImageSequenceAtlas::onCropFadeOutFinish(ofxAnimatable::AnimationEvent & event){
    if(doubleCrop)
    {
        crops[0]->setFrameCounter(crops[1]->getFrameCounter());
    }
}

