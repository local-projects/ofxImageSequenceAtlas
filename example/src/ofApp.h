#pragma once

#include "ofMain.h"
#include "TextureAtlasCreator.h"
#include "TextureAtlasDrawer.h"
#include "ofxSequenceManager.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // ATLAS SETUP //////////////////////////
    TextureAtlasCreator atlasCreator;
    TextureAtlasDrawer atlasManager;
    bool atlasLoaded = false;
    bool createAtlas = false;
    vector<string> filesToDraw;
    
    // SEQUENCEMANAGER SETUP //////////////////////////
    ofxSequenceManager *seqMan;
    
    // CALLBACKS //////////////////////////
    void onAtlasCreationFinished(bool & arg);
    void onAtlasesLoaded(bool &);
    
};
