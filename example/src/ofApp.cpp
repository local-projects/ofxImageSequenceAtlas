#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // SEQUENCE MANAGER //////////////////////
    vector<string> imgDirs;
    string path1 = "imageSequences/wash4/";
    string path2 = "imageSequences/care1/";
    imgDirs.push_back(path1);
    imgDirs.push_back(path2);
    
    seqMan = new ofxSequenceManager();
    seqMan->setup(imgDirs);
    
    //Set up atlas
    
    //Create a list of all files
    vector<string> fileList;
    for(auto &dir : seqMan->getDirectories()){
        ofDirectory d;
        d.allowExt("jpg");
        d.allowExt("png");
        d.listDir(dir->path); //you are expected to put a ton of images in there.
        d.sort();
        
        dir->numFiles = d.numFiles();
        
        for(int i = 0; i < d.numFiles(); i++){
            fileList.push_back(d.getPath(i));
        }
        
    }
    
    atlasCreator.createAtlases(	fileList,
                               4096, 	//fbo/atlas size
                               GL_RGB, //internal format
                               ofVec2f(200,200), //maxItemSideSize
                               2.0,	//padding
                               true, //mipmaps
                               -0.9 //mipmap bias
                               );
    
    ofAddListener(atlasCreator.eventAtlasCreationFinished, this, &ofApp::onAtlasCreationFinished);
    ofAddListener(atlasCreator.eventAllAtlasesLoaded, this, &ofApp::onAtlasesLoaded);

}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = 1/60.0f;
   seqMan->update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(atlasLoaded){
        seqMan->drawFrames(atlasManager);
    } else {
        ofDrawBitmapStringHighlight("loading image sequence Progress: " + ofToString(atlasCreator.getPercentDone() * 100,1), 30, 50);
    }
}

#pragma mark - ADDONS

//////// CALLBACKS //////////////////////////////////////

void ofApp::onAtlasesLoaded(bool &){
    ofLogNotice() << "atlasCreator loaded!";
    atlasCreator.registerWithManager(atlasManager);
    atlasLoaded = true;
    
    //get all the files that were in all the atlas when they were created
    filesToDraw = atlasCreator.getAllImagePaths();
    
    //Create thumbnails
    TextureAtlasDrawer::TextureDimensions td;
    
    
    if(filesToDraw.size()){
        //Theoretically all files should be the same size
        td = atlasManager.getTextureDimensions(filesToDraw[1]);
    } else {
        return;
    }
    
    
    for(auto &seq : seqMan->getSequences()){
        ofRectangle r = ofRectangle(seq->getPos().x, seq->getPos().y, seq->getSize().x, seq->getSize().y);
        
        float scaleWidth = seq->getSize().y / seq->getSize().y * seq->getSize().x;
        float percWidth = (scaleWidth - seq->getSize().x)/scaleWidth;
        
        
        TextureAtlasDrawer::TexQuad tq = seq->getParalelogramForRect(r, 1 - percWidth);
        seq->texQuad = tq;
    }
    
    seqMan->setState(ofxSequenceManager::States::PLAY_FRAMES);
}

void ofApp::onAtlasCreationFinished(bool & arg){
    //once atlases are created, save them to disk, so that we can load them next time
    //without having to recreate them
    atlasCreator.saveToDisk("textureCache", "png"); //save in a folder named "textureCache", in png format
    
    atlasCreator.loadAtlasesFromDisk(GL_RGBA, //internal format
                                                   "textureCache", //dir
                                                   "png", //image format
                                                   true, //gen mipmaps
                                                   -0.9 //mipmap bias
                                                   );
}

#pragma mark - INTERACTIONS

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
