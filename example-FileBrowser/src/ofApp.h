#pragma once

//https://github.com/aiekick/ImGuiFileDialog
//https://github.com/AirGuanZ/imgui-filebrowser -> another alternative


#include "ofMain.h"
#include "ofxImGui.h"
#include "MyTheme.h"
#include "ImGuiFileDialog.h"



class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

	void drawGui_FileDialog()
	{
		// open Dialog Simple
		if (ImGui::Button("Open File Dialog"))
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".xml\0.json\0.*\0\0", ".", 0);
		//,0 multiselection

		// display
		if (ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
		{
			// action if OK
			if (ImGuiFileDialog::Instance()->IsOk == true)
			{
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilepathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				// action
			}
			// close CANCEL
			ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");

			//TODO:
			//set folder (not file)
			if (ImGui::Button("SET DIR"))
			{
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				cout << "filePath:"<<endl;
				//ImGuiFileDialog::Instance()->DirectoryNameBuffer();
			}
		}
	}

	////static bool canValidateDialog = false;
	//bool canValidateDialog = false;

	//inline void InfosPane(std::string vFilter, bool *vCantContinue) // if vCantContinue is false, the user cant validate the dialog
	//{
	//	ImGui::TextColored(ImVec4(0, 1, 1, 1), "Infos Pane");
	//	ImGui::Text("Selected Filter : %s", vFilter.c_str());
	//	ImGui::Checkbox("if not checked you cant validate the dialog", &canValidateDialog);
	//	if (vCantContinue)
	//		*vCantContinue = canValidateDialog;
	//}

	//void drawGui_FileDialog()
	//{
	//	// open Dialog with Pane
	//	if (ImGui::Button("Open File Dialog with a custom pane"))
	//		ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp\0.h\0.hpp\0\0",//?
	//			".", "", std::bind(&InfosPane, std::placeholders::_1, std::placeholders::_2), 350, "InfosPane");

	//	// display and action if ok
	//	if (ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
	//	{
	//		if (ImGuiFileDialog::Instance()->IsOk == true)
	//		{
	//			std::string filePathName = ImGuiFileDialog::Instance()->GetFilepathName();
	//			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
	//			// action
	//		}
	//		// close
	//		ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
	//	}
	//}

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
};
