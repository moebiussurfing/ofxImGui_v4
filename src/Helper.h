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

	//-

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

	//---

	//knob widget

	//https://github.com/ocornut/imgui/issues/942#issuecomment-268369298
	//put code into ofApp.cpp and use between begin/end:
	//float myKnob;
	//if (MyKnob("attack", &myKnob, 0.f, 10.f))
	//{
	//	cout << "knob:" << myKnob << endl;
	//}

	// Implementing a simple custom widget using the public API.
	// You may also use the <imgui_internal.h> API to get raw access to more data/helpers, however the internal API isn't guaranteed to be forward compatible.
	// FIXME: Need at least proper label centering + clipping (internal functions RenderTextClipped provides both but api is flaky/temporary)
	static bool MyKnob(const char* label, float* p_value, float v_min, float v_max)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		float radius_outer = 20.0f;
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 center = ImVec2(pos.x + radius_outer, pos.y + radius_outer);
		float line_height = ImGui::GetTextLineHeight();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float ANGLE_MIN = 3.141592f * 0.75f;
		float ANGLE_MAX = 3.141592f * 2.25f;

		ImGui::InvisibleButton(label, ImVec2(radius_outer * 2, radius_outer * 2 + line_height + style.ItemInnerSpacing.y));
		bool value_changed = false;
		bool is_active = ImGui::IsItemActive();
		bool is_hovered = ImGui::IsItemActive();
		if (is_active && io.MouseDelta.x != 0.0f)
		{
			float step = (v_max - v_min) / 200.0f;
			*p_value += io.MouseDelta.x * step;
			if (*p_value < v_min) *p_value = v_min;
			if (*p_value > v_max) *p_value = v_max;
			value_changed = true;
		}

		float t = (*p_value - v_min) / (v_max - v_min);
		float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
		float angle_cos = cosf(angle), angle_sin = sinf(angle);
		float radius_inner = radius_outer * 0.40f;
		draw_list->AddCircleFilled(center, radius_outer, ImGui::GetColorU32(ImGuiCol_FrameBg), 16);
		draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner), ImVec2(center.x + angle_cos * (radius_outer - 2), center.y + angle_sin * (radius_outer - 2)), ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);
		draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
		draw_list->AddText(ImVec2(pos.x, pos.y + radius_outer * 2 + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), label);

		if (is_active || is_hovered)
		{
			ImGui::SetNextWindowPos(ImVec2(pos.x - style.WindowPadding.x, pos.y - line_height - style.ItemInnerSpacing.y - style.WindowPadding.y));
			ImGui::BeginTooltip();
			ImGui::Text("%.3f", *p_value);
			ImGui::EndTooltip();
		}

		return value_changed;
	}
}//namespace ofxImGui

