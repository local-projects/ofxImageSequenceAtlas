//
//  ofxImageSequenceAtlas.hpp
//  FFG_Shop
//
//  Created by Nicole Messier on 4/30/18.
//
//

#pragma once
#include "ofMain.h"
#include "TextureAtlasDrawer.h"
#include "ofxAnimatableFloat.h"
#include "ofxRemoteUIServer.h"

class ofxImageSequenceAtlas{
public:
    ofxImageSequenceAtlas();
    ~ofxImageSequenceAtlas();
    
    void setup(ofVec2f _pos, ofVec2f _size, int _column, int _row);
    void update(float dt);
    void playSequence(int _startFrame, bool loop);
    
    void drawDebug(); 
    
    // ATTRIBUTES //////////////////////////////////
    ofVec2f getPos();
    ofVec2f getSize();
    ofVec2f getSizeOrg();
    int getColumn();
    int getRow();
    
    // STATES //////////////////////////////////
    enum States{
        PLAY_ONCE,
        PLAY_LOOPING,
        STOPPED
    };
    
    void setState(States _state);
    ofxImageSequenceAtlas::States getState();
    
    // ATLAS //////////////////////////////////
    void calculateCropRight(ofVec2f cropPerc1, ofVec2f cropPerc2);
    void calculateCropLeft(ofVec2f cropPerc);
    void calculateCropLeftRight(ofVec2f cropPerc);
    void drawInBatch(TextureAtlasDrawer* atlas);
    void setTextureDimensions(TextureAtlasDrawer::TextureDimensions _td);
    TextureAtlasDrawer::TexQuad getParalelogramForRect(const ofRectangle & r,float widthPerc, float fromLeft, float fromMiddle);
    TextureAtlasDrawer::TexQuad texQuad1;
    TextureAtlasDrawer::TexQuad texQuad2;
    
    // FILEPATHS //////////////////////////////////
    void setNumFrames(int _numFrames);
    void setFramesPath(string _framesPath);
    
    // MOTION //////////////////////////////////
    void setupMotion();
    float animationDuration = 1.0f;
    
    //reveal
    ofxAnimatableFloat reveal1;
    ofxAnimatableFloat reveal2;
    void resetReveal1(ofVec2f fromTo, float delay);
    void resetReveal2(ofVec2f fromTo, float delay);
    bool left = false; 
    void onRevealFinish(ofxAnimatable::AnimationEvent & event);
    bool getAnimatingCrop1();
    bool getAnimatingCrop2();
    void setAnimatingCrop1(bool _animatingCrop1);
    void setAnimatingCrop2(bool _animatingCrop2);
    
    //close
    ofxAnimatableFloat close1;
    ofxAnimatableFloat close2;
    void resetClose1(ofVec2f fromTo, float delay);
    void resetClose2(ofVec2f fromTo, float delay);
    
    //Motion States
    enum AnimState{
        IDLE,
        REVEAL,
        CLOSE_REVEAL,
        NUM_ANIMATION_STATES
    };
    
    void setMotionState(AnimState _animState);
    AnimState getMotionState();
    
    //FRAMERATE
    void setFrameRateDivisor(int _frameRateDivisor);
    
    //id
    void setId(int _uid);
    
    // TWO CROPS
    bool getDoubleCrop();
    float getCropPercNewX1();
    float getCropPercNewX2();
    
    
private:
    
    // ATTRIBUTES //////////////////////////////////
    ofVec2f pos = ofVec2f(0,0);
    ofVec2f size = ofVec2f(100,100);
    ofVec2f sizeOrg; //original size
    int column = 0;
    int row = 0;
    
    // STATES //////////////////////////////////
    States state = States::PLAY_LOOPING;
    
    // ATLAS //////////////////////////////////
    string textureFile;
    TextureAtlasDrawer::TextureDimensions td;
    
    // FRAMERATE //////////////////////////////////
    int frameCounter = 0;
    int frameRateDivisor = 2;
    int frameRateCounter = frameRateDivisor;
    
    // FILEPATHS //////////////////////////////////
    string frontPath = "frame-";
    string framesPath = "imageSequences/wash4/";
    int numFrames = 0;
    
    //This is to put two crops into the same image.
    bool doubleCrop = true;
    bool debug = false;
    float widthPercDebug = 0.0;
    float textCropPerc = 0.0f;
    
    //2 crops
    float cropPercNewX2 = 1.0f;
    float cropPercNewX1 = 1.0f;

    //This is to handle the double crop!
    //Need to do: organize double crop system
    bool animatingCrop1 = false;
    bool animatingCrop2 = false;
    
    //id
    int uid=0;
    
    //Motion States
    AnimState animState = AnimState::IDLE;
    
};
