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
#include "ImgSeqCrop.h"

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
    void setTextureDimensions(TextureAtlasDrawer::TextureDimensions _td);
    TextureAtlasDrawer::TexQuad getParalelogramForRect(const ofRectangle & r,float widthPerc, float fromLeft, float fromMiddle);
    
    TextureAtlasDrawer::TexQuad getParalelogramForRect_Croped(const ofRectangle & r, float offset, float widthPerc);
    
    vector<ImgSeqCrop*> crops;
    
    // FILEPATHS //////////////////////////////////
    void setFramesPath(int index, string _framesPath);
    
    //id
    void setId(int _uid);
    
    // TWO CROPS
    bool getDoubleCrop();
    float getCropPercNewX1();
    float getCropPercNewX2();
    void setDoubleCrop(bool _doubleCrop);
    
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
    
    //call backs
    void onCropFadeOutFinish(ofxAnimatable::AnimationEvent & event); 
    
};
