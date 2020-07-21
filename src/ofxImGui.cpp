#include "ofxImGui.h"

//all this code come from the example
//imgui-docking\examples\example_glfw_opengl3\main.cpp

namespace ofxImGui {
void Gui::setup() {

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//1.77
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();

	//-

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	//1.77
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	//TODO:
	const char* glsl_version = "#version 410";
	ofAppGLFWWindow* window = (ofAppGLFWWindow*)ofGetWindowPtr();
	
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window->getGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	//--

	// Override listeners
	ofAddListener(ofEvents().mousePressed, this, &Gui::onMousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &Gui::onMouseReleased);
	ofAddListener(ofEvents().keyReleased, this, &Gui::onKeyReleased);
	ofAddListener(ofEvents().keyPressed, this, &Gui::onKeyPressed);
	ofAddListener(ofEvents().exit, this, &Gui::exit);
}


void Gui::exit(ofEventArgs& args) {
	//test for 1.77
	// Cleanup 
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext(context);

	//-

	ofRemoveListener(ofEvents().mousePressed, this, &Gui::onMousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &Gui::onMouseReleased);
	ofRemoveListener(ofEvents().keyReleased, this, &Gui::onKeyReleased);
	ofRemoveListener(ofEvents().keyPressed, this, &Gui::onKeyPressed);
	ofRemoveListener(ofEvents().exit, this, &Gui::exit);
}


void Gui::begin() {
	ImGuiIO& io = ImGui::GetIO();

	float currentTime = ofGetElapsedTimef();
	if (lastTime > 0.f)
	{
		io.DeltaTime = currentTime - lastTime;
	}
	else
	{
		io.DeltaTime = 1.0f / 60.f;
	}
	lastTime = currentTime;

	// Update settings
	io.MousePos = ImVec2((float)ofGetMouseX(), (float)ofGetMouseY());
	for (int i = 0; i < 5; i++) {
		io.MouseDown[i] = mousePressed[i];
	}

	//glfwPollEvents();?

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}


void Gui::end() {
	ofAppGLFWWindow* window = (ofAppGLFWWindow*)ofGetWindowPtr();
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window->getGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	//glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	////1.77
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		////1.77
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}


void Gui::remapToGLFWConvention(int& button)
{
	switch (button)
	{

	case 0:
	{
		break;
	}
	case 1:
	{
		button = 2;
		break;
	}
	case 2:
	{
		button = 1;
		break;
	}
	}
}

void Gui::onMousePressed(ofMouseEventArgs& event) {
	int button = event.button;
	if (button >= 0 && button < 5)
	{
		remapToGLFWConvention(button);
		mousePressed[button] = true;
	}
}

void Gui::onMouseReleased(ofMouseEventArgs& event) {
	int button = event.button;
	if (button >= 0 && button < 5)
	{
		remapToGLFWConvention(button);
		mousePressed[button] = false;
	}
}

void Gui::onKeyPressed(ofKeyEventArgs& event) {
	int key = event.keycode;
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[key] = true;
	//io->AddInputCharacter((unsigned short)event.codepoint);
}

void Gui::onKeyReleased(ofKeyEventArgs& event) {
	int key = event.keycode;
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[key] = false;

	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
}
}