// ImGui - standalone example application for DirectX 11
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

//#pragma once

#include <fstream>
#include <streambuf>

#include "ofMain.h"

#include "imgui.h"
#include "TextEditor.h"

class TextEditorDemo {

public:

	//std::string *textContent;

//    static const char* fileToEdit;// = "text.txt";// = "text.txt";
     char* fileToEdit;// = "text.txt";// = "text.txt";

    TextEditor editor;
    ImVec4 clear_col = ImColor(114, 144, 154);

    TextEditor::TextEditor::LanguageDefinition lang = TextEditor::LanguageDefinition::CPlusPlus();

    //TextEditor::ErrorMarkers markers;
	
    void setup(){

        // Load Fonts
        // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
		//        ImVec4 clear_col = ImColor(114, 144, 154);

		//        editor.SetLanguageDefinition(lang);
        //editor.SetPalette(TextEditor::GetLightPalette());

  //      // error markers
		////        TextEditor::ErrorMarkers markers;
  //      markers.insert(std::make_pair<int, std::string>(6, "Example error here:\nInclude file not found: \"TextEditor.h\""));
  //      markers.insert(std::make_pair<int, std::string>(41, "Another example error"));

  //      editor.SetErrorMarkers(markers);

        // "breakpoint" markers
        //TextEditor::Breakpoints bpts;
        //bpts.insert(24);
        //bpts.insert(47);
        //editor.SetBreakpoints(bpts);
		
		//--

		//TODO:
		//load content:
		//problems on char / string types... 

        //std::string _name = "text.txt";
       	//ofLog()<<"(&ofToDataPath(_name)[0]):" << ofToString((&ofToDataPath(_name)[0]));

		//string inputPath = ofFilePath::getAbsolutePath("input");
		//ofStringReplace(inputPath, "/", "\\");
		
		//fileToEdit = (&_name.c_str());
		
		//-

        //hardcoded text
       	//static const char* fileToEdit = "text.txt";
		fileToEdit = (char*)("text.txt");
  //      editor.SetText("erwerwerwer");

		//char *s = "constant string";

		//-

		//TODO:
		//this works on macOS
        //fileToEdit = (&ofToDataPath(_name)[0]);

		//-

		//if (false)
        {
			ofLogNotice()<<"load ifstream fileToEdit: "<<ofToString(fileToEdit);
            //std::ifstream t("text.txt");
            std::ifstream t(fileToEdit);
            if (t.good())
            {
                std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
                editor.SetText(str);
				ofLogNotice() << "loaded file: "<<ofToString(fileToEdit);
            }
            else{
				ofLogNotice() << "file not found! "<<ofToString(fileToEdit);
            }
        }
    }
	

    void draw(){

        auto cpos = editor.GetCursorPosition();
        ImGui::Begin("Text Editor Demo", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
        ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Save"))
                {
                    auto textToSave = editor.GetText();
                    /// save text....
                }
//                if (ImGui::MenuItem("Quit", "Alt-F4"))
//                    break;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                bool ro = editor.IsReadOnly();
                if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                    editor.SetReadOnly(ro);
                ImGui::Separator();

                if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
                    editor.Undo();
                if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
                    editor.Redo();

                ImGui::Separator();

                if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
                    editor.Copy();
                if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
                    editor.Cut();
                if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
                    editor.Delete();
                if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                    editor.Paste();

                ImGui::Separator();

                if (ImGui::MenuItem("Select all", nullptr, nullptr))
                    editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Dark palette"))
                    editor.SetPalette(TextEditor::GetDarkPalette());
                if (ImGui::MenuItem("Light palette"))
                    editor.SetPalette(TextEditor::GetLightPalette());
                if (ImGui::MenuItem("Retro blue palette"))
                    editor.SetPalette(TextEditor::GetRetroBluePalette());
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
                    editor.IsOverwrite() ? "Ovr" : "Ins",
                    editor.CanUndo() ? "*" : " ",
                    editor.GetLanguageDefinition().mName.c_str(), fileToEdit);

        editor.Render("TextEditor");
        ImGui::End();

    }

};
