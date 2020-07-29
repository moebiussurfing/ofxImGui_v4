#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //required call
    gui.setup();
    
    //ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;//to use when non docking brancj
    
    ImGui::GetIO().MouseDrawCursor = false;
    //backgroundColor is stored as an ImVec4 type but can handle ofColor
    backgroundColor = ofColor(114, 144, 154);
    
    floatValue = 0.0f;

    // Initialization
    static const char* buttons[] = { "Abort", "Cancel", "Please No", NULL };
    msgbox.Init( "Clear log?", NULL, "Are you really really sure you want to delete the entire log history and loose all that information forever?", buttons, true );

    _line.setLimits(0, 255);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    //backgroundColor is stored as an ImVec4 type but is converted to ofColor automatically
    
    ofSetBackgroundColor(backgroundColor);
    
    //required to call this at beginning
    gui.begin();
    
    //In between gui.begin() and gui.end() you can use ImGui as you would anywhere else
    
    // 1. Show a simple window
    {
        //ImGui::Text("Hello, world!");
        //ImGui::SliderFloat("Float", &floatValue, 0.0f, 1.0f);

        // Drawing
        if ( ImGui::Button( "Clear log" ) )
        {
            ImGui::OpenPopup( "Clear log?" );
        }
        int selected = msgbox.Draw();
//        switch ( selected )
//        {
//            case 0: // No button pressed
//            case 1: // First button pressed and so forth
//            case 2: // Second button pressed, and so forth...
//        }
        
		ImGui::Checkbox("enable button", &bButtonEnable);
        ImGuiAl::Button("play", bButtonEnable, ImVec2( 200, 30 ) );


        int value =(int)255*ofNoise(ofGetLastFrameTime());
        //int value =(int)255*ofRandom(1);
//        uint8_t value =10;
        _line.add(value);
        cout <<value<<endl;
        ImVec2 max = ImGui::GetContentRegionAvail();
        _line.draw("plotting", max);
    }
    
    //required to call this at end
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
