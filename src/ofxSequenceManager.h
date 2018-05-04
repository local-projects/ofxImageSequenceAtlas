//
//  ofxofxSequenceManager.hpp
//  FFG_Shop
//
//  Created by Nicole Messier on 5/1/18.
//
//

#pragma once
#include "ofMain.h"
#include "ofxImageSequenceAtlas.h"
#include "TextureAtlasDrawer.h"

class ofxSequenceManager{
public:
    ofxSequenceManager();
    ~ofxSequenceManager();
    
    void setup(vector<string> dir);
    void update(float dt);
    void drawFrames(TextureAtlasDrawer _atlasMan);
    
    
    // STRUCTS /////////////////////////
    struct SequenceDirectory{
        int numFiles;
        string path;
    };
    
    // STATES //////////////////////////
    enum States{
        PLAY_FRAMES,
        STOP_FRAMES
    };
    
    void setState(States _state);
    
    // IMAGE SEQUENCE //////////////////////////
    vector<ofxImageSequenceAtlas *> getSequences();
    
    // SEQUENCE DIRECTORIES //////////////////////////
    
    int getNumDirectories();
    vector<SequenceDirectory*> getDirectories();
    
private:
    // GRID //////////////////////////
    int numRows = 35;
    ofVec2f imgSize = ofVec2f(320, 180);
    
    //  IMAGE SEQUENCE //////////////////////////
    vector<ofxImageSequenceAtlas*> sequences;
    vector<SequenceDirectory*> directories;
    
    // STATES //////////////////////////
    States state = States::STOP_FRAMES;
    
    // VISUAL COUNTER //////////////////////////
    int visualCounter = 0;
    
    bool debug = false;
};
