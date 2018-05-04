#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // SEQUENCE MANAGER //////////////////////
    vector<string> imgDirs;
    string path1 = "imageSequences/wash4/";
    string path2 = "imageSequences/care1/";
    
    seqMan = new ofxSequenceManager();
    seqMan->setup(imgDirs);
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = 1/60.0f;
   seqMan->update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
    seqMan->draw();
}

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
