//
//  ofxSequenceManager.cpp
//  FFG_Shop
//
//  Created by Nicole Messier on 5/1/18.
//
//

#include "ofxSequenceManager.h"

ofxSequenceManager::ofxSequenceManager(){
    
}

ofxSequenceManager::~ofxSequenceManager(){
    
}

void ofxSequenceManager::setup(vector<string> dir){
    //Set up directories
    SequenceDirectory * dir0 = new SequenceDirectory;
    dir0->path = "imageSequences/wash4/";
    directories.push_back(dir0);
    
    SequenceDirectory * dir1 = new SequenceDirectory;
    dir1->path = "imageSequences/care1/";
    directories.push_back(dir1);
    
    // GRID SETUP //////////////////////////
    float width = ofGetWidth()/numRows;
    float height = imgSize.y/imgSize.x*width;
    int numColumns = ofGetHeight()/height;
    
    for(int i=0; i<numRows;i++){
        for(int j=0; j<numColumns; j++){
            ofxImageSequenceAtlas *temp = new ofxImageSequenceAtlas();
            temp->setup(ofVec2f(i*width, j*height), ofVec2f(width, height));
            sequences.push_back(temp);
        }
    }
}

void ofxSequenceManager::update(float dt){
    switch(state){
        case States::PLAY_FRAMES: {
            for(auto &seq : sequences){
                seq->update(dt);
            }
            break;
        }
        case States::STOP_FRAMES: { break;}
        default: break;
            
    }
}

void ofxSequenceManager::draw(){
    switch(state){
        case States::PLAY_FRAMES: {
            
            Global::one().atlasManager.beginBatchDraw();
            
            
            for(auto &seq : sequences){
                seq->drawInBatch(&Global::one().atlasManager);
            }
            
            Global::one().atlasManager.endBatchDraw(Global::one().debug);

            
            break;
        }
        case States::STOP_FRAMES: { break;}
        default: break;
            
    }
}

#pragma mark GET
vector<ofxImageSequenceAtlas*> ofxSequenceManager::getSequences(){
    return sequences;
}

int ofxSequenceManager::getNumDirectories(){
    return directories.size();
}

vector<SequenceDirectory*> ofxSequenceManager::getDirectories(){
    return directories;
}

#pragma mark STATES
void ofxSequenceManager::setState(States _state){
    state = _state;
    
    switch(state){
        case States::PLAY_FRAMES: {
            for(auto &img : sequences){
                img->setFramesPath(directories[visualCounter]->path);
                img->setNumFrames(directories[visualCounter]->numFiles);
                
            }
            
            (visualCounter < directories.size() - 1) ? visualCounter++ : visualCounter = 0;
            
            break;
        }
        case States::STOP_FRAMES: { break;}
        default: break;
            
    }
}