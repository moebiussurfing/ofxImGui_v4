#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);

	ofSetLogLevel(OF_LOG_VERBOSE);

	//0. our app parameters
	params.setName("paramsGroup");//main (target) group
	params.add(shapeType.set("shapeType", 1, 1, 2));
	params.add(numShapes.set("numShapes", 1, 1, 24));
	params.add(separation.set("separation", 5, 1, 100));
	params.add(shapeSide.set("shapeSide", 50, 5, 200));

	paramsNested.setName("styleGroup");//another nested group
	paramsNested.add(fill.set("fill", false));
	paramsNested.add(color.set("floatColor", ofFloatColor(0, 1), ofFloatColor(0, 0), ofFloatColor(1, 1)));
	//paramsNested.add(color.set("color", ofColor(0, 255), ofColor(0, 0), ofColor(255, 255)));
	paramsNested.add(lineWidth.set("lineWidth", 1, 0.1, 10));

	//params.add(paramsNested);//main preset settings container

	//required call
	gui.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(ofFloatColor(backgroundColor.x, backgroundColor.y, backgroundColor.z));
	//ofBackground(color.get());

	//required to call this at beginning
	gui.begin();
	{
		//knob widget
		if (ofxImGui::MyKnob("myKnob", &myKnob, 0.f, 10.f))
		{
			ofLogNotice(__FUNCTION__) << "MyKnob:" << myKnob;
		}

		//color picker
		//ImVec4 myCol = ImVec4(0.75f, 0.75f, 0.75f, 1.f);
		//if (ofxImGui::ColorSelector2("myColorPicker", myCol)) {//not working
		//	//ofLogNotice(__FUNCTION__) << "ColorSelector:" << ofToString(myCol);
		//}

		ImGui::Text("Hello, world!");
		ImGui::ColorEdit3("Background Color", (float*)&backgroundColor);
		ImGui::SliderFloat("Float", &floatValue, 0.0f, 1.0f);

		if (ImGui::Checkbox("Demo Window", &b))
		{
		}
		if (b) ImGui::ShowDemoWindow();

		//int i = ofxImGui::openConfirmationPopup("popup", "really?", true);

		//test helpers
		ofxImGui::AddGroup(params);
		ofxImGui::AddGroup(paramsNested);

		ofxImGui::DrawParamSaveWindow(params);
	}
	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	ofLogNotice(__FUNCTION__) << key;
	switch (key)
	{

	case 's':
	{
		break;
	}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	ofLogVerbose(__FUNCTION__) << key;

}


void ofApp::mouseScrolled(float x, float y)
{
	ofLogVerbose(__FUNCTION__) << "x: " << x << " y: " << y;
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
