//
//  SequenceManager.hpp
//  FFG_Shop
//
//  Created by Nicole Messier on 5/1/18.
//
//

#pragma once
#include "ofMain.h"
#include "ImageSequence.h"
#include "TextureAtlasDrawer.h"
#include "ShopStructs.h"
#include "Global.h"
#include "ofxTimeMeasurements.h"

class SequenceManager{
public:
    SequenceManager();
    ~SequenceManager();
    
    void setup(vector<string> dir);
    void update(float dt);
    void draw();
    
    // STATES //////////////////////////
    enum States{
        PLAY_FRAMES,
        STOP_FRAMES
    };
    
    void setState(States _state);
    
    // IMAGE SEQUENCE //////////////////////////
    vector<ImageSequence*> getSequences();
    
    // SEQUENCE DIRECTORIES //////////////////////////
    
    int getNumDirectories();
    vector<Shop::SequenceDirectory*> getDirectories();
    
private:
    // GRID //////////////////////////
    int numRows = 35;
    ofVec2f imgSize = ofVec2f(320, 180);
    
    //  IMAGE SEQUENCE //////////////////////////
    vector<ImageSequence*> sequences;
    vector<Shop::SequenceDirectory*> directories;
    
    // STATES //////////////////////////
    States state = States::STOP_FRAMES;
    
    // VISUAL COUNTER //////////////////////////
    int visualCounter = 0;
};
