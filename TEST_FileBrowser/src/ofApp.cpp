#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    gui.setup();
    
    ImGui::GetIO().MouseDrawCursor = false;
    backgroundColor = ofColor(114, 144, 154);
    
    ofDirectory dataDirectory(ofToDataPath("", true));
}

//--------------------------------------------------------------
void ofApp::update(){
}
    
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(backgroundColor);

    gui.begin();
    
	drawGui_FileDialog();
	    
    gui.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    ofLogVerbose(__FUNCTION__) << key;
    switch (key)
    {
        case 's':
        {
            break;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    ofLogVerbose(__FUNCTION__) << key;
    
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(float x, float y)
{
    ofLogVerbose(__FUNCTION__) << "x: " << x << " y: " << y;
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
