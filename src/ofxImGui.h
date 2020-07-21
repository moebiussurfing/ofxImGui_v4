#pragma once

#include "ofMain.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "imgui.h"
#include "opengl/imgui_impl_glfw.h"
#include "opengl/imgui_impl_opengl3.h"

#include "Helper.h"

//NOTE: ofxImGui do not let to use helpers like this, 
//if we do not create the window with the helper
//so this seems better bc we can use more raw code

namespace ofxImGui {
class Gui 
{
public:
	void setup();
	void exit(ofEventArgs& args);
	void begin();
	void end();
private:
	void remapToGLFWConvention(int& button);
	void onMousePressed(ofMouseEventArgs& event);
	void onMouseReleased(ofMouseEventArgs& event);
	void onKeyPressed(ofKeyEventArgs& event);
	void onKeyReleased(ofKeyEventArgs& event);

	float lastTime;
	bool mousePressed[5] = { false };
	ImGuiContext* context;
};
}
