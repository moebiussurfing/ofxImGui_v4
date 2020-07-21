#pragma once
#include "imgui.h"
#include "imconfig.h"
#include "imgui_internal.h"

#include "ofParameter.h"
#include "ofFbo.h"
#include "ofTexture.h"
#include "ofJson.h"

////1.77
#include "ofMain.h"//to avoid glm ptr errors...

namespace ofxImGui
{
	bool isUsing();
	const char* GetUniqueName(ofAbstractParameter& parameter);
	const char* GetUniqueName(const std::string& candidate);

	struct WindowOpen
	{
		std::stack<std::vector<std::string>> usedNames;
		std::shared_ptr<ofParameter<bool>> parameter;
		bool value;
	};
	static WindowOpen windowOpen;

	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values);

	void AddGroup(const ofParameterGroup& group);

	bool AddParameter(ofParameter<float>& parameter);
	bool AddParameter(ofParameter<int>& parameter);
	bool AddParameter(ofParameter<bool>& parameter);

	bool AddParameter(ofParameter<glm::tvec2<int>>& parameter);
	bool AddParameter(ofParameter<glm::tvec3<int>>& parameter);
	bool AddParameter(ofParameter<glm::tvec4<int>>& parameter);
	bool AddParameter(ofParameter<glm::vec2>& parameter);
	bool AddParameter(ofParameter<glm::vec3>& parameter);
	bool AddParameter(ofParameter<glm::vec4>& parameter);
	bool AddParameter(ofParameter<ofVec2f>& parameter);
	bool AddParameter(ofParameter<ofVec3f>& parameter);
	bool AddParameter(ofParameter<ofVec4f>& parameter);
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha = true);
	bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars, bool multiline);
	bool AddParameter(ofParameter<void>& parameter);

	bool ImageButton(const ofFbo& src, float scale);
	bool ImageButton(const ofTexture& src, float scale);

	void Begin(const std::string& name);
	void End();

	void DrawParamSaveWindow(const ofParameterGroup& parameter);

	//-

	//some helpers:
	////copyied from:
	////https://github.com/sebasobotka/ofxImGui/blob/master/src/ImGuiExtension.h
	////example here:
	//https://github.com/sebasobotka/ofxImGui/blob/master/example-imgviewer/src/ofApp.cpp

	//namespace ImGui {
	//static auto vector_getter = [](void* vec, int idx, const char** out_text)
	//{
	//	auto& vector = *static_cast<std::vector<std::string>*>(vec);
	//	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	//	*out_text = vector.at(idx).c_str();
	//	return true;
	//};

	//inline bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	//{
	//	if (values.empty()) { return false; }
	//	return Combo(label, currIndex, vector_getter,
	//		static_cast<void*>(&values), values.size());
	//}

	//inline bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height_in_items = -1)
	//{
	//	if (values.empty()) { return false; }
	//	return ListBox(label, currIndex, vector_getter,
	//		static_cast<void*>(&values), values.size(), height_in_items);
	//}

	////inline bool InputRect(const char* label, ofRect* rectPtr,
	////	int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0)
	////{
	////	ImGui::PushID(label);
	////	ImGui::BeginGroup();

	////	bool valueChanged = false;

	////	std::array<float*, 4> arr = { &rectPtr->x, &rectPtr->y,
	////		&rectPtr->w, &rectPtr->h };

	////	for (auto& elem : arr) {
	////		ImGui::PushID(elem);
	////		ImGui::PushItemWidth(64.f);
	////		valueChanged |= ImGui::InputFloat("##arr", elem, 0, 0,
	////			decimal_precision, extra_flags);
	////		ImGui::PopID();
	////		ImGui::SameLine();
	////	}

	////	ImGui::SameLine();
	////	ImGui::TextUnformatted(label);
	////	ImGui::EndGroup();

	////	ImGui::PopID(); // pop label id;

	////	return valueChanged;
	////}
	//}


	////https://github.com/memo/ofxMSAControlFreakImGui/blob/master/src/ofxMSAControlFreakImGui.cpp
	//int openConfirmationPopup(std::string title, std::string message, bool showCancel) {
	//	int ret = 0;

	//	if (!ImGui::IsPopupOpen(title.c_str())) ImGui::OpenPopup(title.c_str());

	//	if (ImGui::BeginPopupModal(title.c_str()))
	//	{
	//		ImGui::Text(message.c_str());
	//		//ImGui::SetNextItemWidth(-1.0f);

	//		if (ImGui::Button("Yes", ImVec2(80, 0))) {
	//			ret = 1;
	//			ImGui::CloseCurrentPopup();
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("No", ImVec2(80, 0))) {
	//			ret = 2;
	//			ImGui::CloseCurrentPopup();
	//		}
	//		if (showCancel) {
	//			ImGui::SameLine();
	//			if (ImGui::Button("Cancel", ImVec2(80, 0))) {
	//				ret = 3;
	//				ImGui::CloseCurrentPopup();
	//			}
	//		}
	//		ImGui::EndPopup();
	//	}
	//	return ret;
	//}

}//namespace ofxImGui

