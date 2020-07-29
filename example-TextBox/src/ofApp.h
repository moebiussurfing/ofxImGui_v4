#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "imguial_msgbox.h"
#include "imguial_sparkline.h"
#include "imguial_button.h"

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void mouseScrolled(float x, float y);
    
    ofxImGui::Gui gui;
    ImVec4 backgroundColor;
    
    float floatValue;

    ImGuiAl::MsgBox msgbox;
    ImGuiAl::Sparkline<uint8_t, 256> _line;

	bool bButtonEnable;
};
