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
	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha = true);
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
	
	
	//---

	//alternative color picker
	//not working...

	//bool ColorSelector2(const char* pLabel, ImVec4& oRGBA)
	//{
	//	const ImU32 c_oColorGrey = ImGui::ColorConvertFloat4ToU32(ImVec4(0.75f, 0.75f, 0.75f, 1.f));
	//	const ImU32 c_oColorBlack = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	//	const ImU32 c_oColorBlackTransparent = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.f));
	//	const ImU32 c_oColorWhite = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

	//	ImGui::PushID(pLabel);
	//	bool bRet = false;
	//	ImGuiID iID = ImGui::GetID(pLabel);
	//	ImGuiWindow* pWindow = ImGui::GetCurrentWindow();

	//	const ImGuiID iStorageOpen = iID + ImGui::GetID("ColorSelector_Open");

	//	const ImGuiID iStorageStartColorR = iID + ImGui::GetID("ColorSelector_StartColor_R");
	//	const ImGuiID iStorageStartColorG = iID + ImGui::GetID("ColorSelector_StartColor_G");
	//	const ImGuiID iStorageStartColorB = iID + ImGui::GetID("ColorSelector_StartColor_B");
	//	const ImGuiID iStorageStartColorA = iID + ImGui::GetID("ColorSelector_StartColor_A");

	//	const ImGuiID iStorageCurrentColorH = iID + ImGui::GetID("ColorSelector_CurrentColor_H");
	//	const ImGuiID iStorageCurrentColorS = iID + ImGui::GetID("ColorSelector_CurrentColor_S");
	//	const ImGuiID iStorageCurrentColorV = iID + ImGui::GetID("ColorSelector_CurrentColor_V");
	//	const ImGuiID iStorageCurrentColorA = iID + ImGui::GetID("ColorSelector_CurrentColor_A");


	//	//pWindow->StateStorage.SetFloat(iID);

	//	ImDrawList* pDrawList = ImGui::GetWindowDrawList();

	//	if (ImGui::InvisibleButton("Picker", ImVec2(16, 16)))
	//	{
	//		pWindow->StateStorage.SetInt(iStorageOpen, 1);

	//		pWindow->StateStorage.SetFloat(iStorageStartColorR, oRGBA.x);
	//		pWindow->StateStorage.SetFloat(iStorageStartColorG, oRGBA.y);
	//		pWindow->StateStorage.SetFloat(iStorageStartColorB, oRGBA.z);
	//		pWindow->StateStorage.SetFloat(iStorageStartColorA, oRGBA.w);

	//		float fHue, fSat, fVal;
	//		ImGui::ColorConvertRGBtoHSV(oRGBA.x, oRGBA.y, oRGBA.z, fHue, fSat, fVal);

	//		pWindow->StateStorage.SetFloat(iStorageCurrentColorH, fHue);
	//		pWindow->StateStorage.SetFloat(iStorageCurrentColorS, fSat);
	//		pWindow->StateStorage.SetFloat(iStorageCurrentColorV, fVal);
	//		pWindow->StateStorage.SetFloat(iStorageCurrentColorA, oRGBA.w);
	//	}

	//	for (int iX = 0; iX < 2; ++iX)
	//	{
	//		for (int iY = 0; iY < 2; ++iY)
	//		{
	//			ImVec2 oA(ImGui::GetItemRectMin().x + iX * 8.f, ImGui::GetItemRectMin().y + iY * 8.f);
	//			ImVec2 oB(ImGui::GetItemRectMin().x + (1 + iX) * 8.f, ImGui::GetItemRectMin().y + (1 + iY) * 8.f);
	//			pDrawList->AddRectFilled(oA, oB, (0 == (iX + iY) % 2) ? c_oColorGrey : c_oColorWhite);
	//		}
	//	}

	//	pDrawList->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImGui::ColorConvertFloat4ToU32(oRGBA));

	//	ImVec2 oRectMin = ImGui::GetItemRectMin();
	//	ImVec2 oRectMax = ImGui::GetItemRectMax();

	//	const ImVec2 oPopupSize(175, 350);
	//	//ImGui::SetNextWindowSize(oPopupSize, ImGuiSetCond_Always);
	//	ImGui::SetNextWindowPos(ImVec2(oRectMin.x, oRectMax.y + 5), ImGuiCond_FirstUseEver);
	//	if (pWindow->StateStorage.GetInt(iStorageOpen, 0) == 1 && ImGui::Begin("Color picker", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
	//	{
	//		bRet = false;
	//		const int iCheckboardTileSize = 10;

	//		ImDrawList* pDrawList = ImGui::GetWindowDrawList();

	//		ImVec2 oColorPreviewSize(160, 20);
	//		ImGui::Dummy(oColorPreviewSize);
	//		ImVec2 oColorAreaMin = ImGui::GetItemRectMin();
	//		ImVec2 oColorAreaMax = ImGui::GetItemRectMax();

	//		int iTileHCount = (int)oColorPreviewSize.x / iCheckboardTileSize;
	//		int iTileVCount = (int)oColorPreviewSize.y / iCheckboardTileSize;

	//		for (int iX = 0; iX < iTileHCount; ++iX)
	//		{
	//			for (int iY = 0; iY < iTileVCount; ++iY)
	//			{
	//				pDrawList->AddRectFilled(
	//					ImVec2(oColorAreaMin.x + iX * iCheckboardTileSize, oColorAreaMin.y + iY * iCheckboardTileSize),
	//					ImVec2(oColorAreaMin.x + (1 + iX) * iCheckboardTileSize, oColorAreaMin.y + (1 + iY) * iCheckboardTileSize),
	//					(0 == (iX + iY) % 2) ? c_oColorGrey : c_oColorWhite);
	//			}
	//		}

	//		pDrawList->AddRectFilled(oColorAreaMin, oColorAreaMax, ImGui::ColorConvertFloat4ToU32(oRGBA));

	//		float fHue = pWindow->StateStorage.GetFloat(iStorageCurrentColorH);
	//		float fSat = pWindow->StateStorage.GetFloat(iStorageCurrentColorS);
	//		float fVal = pWindow->StateStorage.GetFloat(iStorageCurrentColorV);

	//		ImGui::Text("HSV");
	//		ImGui::Separator();
	//		{
	//			//Saturation
	//			{
	//				const ImVec2 oSaturationAreaSize(128, 128);
	//				ImGui::InvisibleButton("##SaturationArea", oSaturationAreaSize);
	//				ImVec2 oSaturationAreaMin = ImGui::GetItemRectMin();
	//				ImVec2 oSaturationAreaMax = ImGui::GetItemRectMax();

	//				if (ImGui::IsItemActive())
	//				{
	//					bRet = true;
	//					ImVec2 oCursorPos = ImGui::GetMousePos();
	//					ImVec2 oNewValue((oCursorPos.x - oSaturationAreaMin.x) / oSaturationAreaSize.x, (oCursorPos.y - oSaturationAreaMin.y) / oSaturationAreaSize.y);
	//					//oNewValue.x = Math::Clamp(oNewValue.x, 0.f, 1.f);
	//					//oNewValue.y = Math::Clamp(oNewValue.y, 0.f, 1.f);
	//					oNewValue.x = ofClamp(oNewValue.x, 0.f, 1.f);
	//					oNewValue.y = ofClamp(oNewValue.y, 0.f, 1.f);
	//					fSat = oNewValue.x;
	//					fVal = 1.f - oNewValue.y;
	//					ImGui::ColorConvertHSVtoRGB(fHue, fSat, fVal, oRGBA.x, oRGBA.y, oRGBA.z);

	//					ImVec4 oToolTipColor = oRGBA;
	//					oToolTipColor.w = 1.f;

	//					ImGui::BeginTooltip();
	//					ImGui::Dummy(ImVec2(32, 32));
	//					ImVec2 oDummyAreaMin = ImGui::GetItemRectMin();
	//					ImVec2 oDummyAreaMax = ImGui::GetItemRectMax();
	//					ImDrawList* pDummyDrawList = ImGui::GetWindowDrawList();
	//					pDummyDrawList->AddRectFilled(oDummyAreaMin, oDummyAreaMax, ImGui::ColorConvertFloat4ToU32(oToolTipColor));
	//					ImGui::EndTooltip();
	//				}

	//				ImVec2 pos = ImVec2(0, 0);
	//				ImVec4 c00(1, 1, 1, 1);
	//				ImVec4 c01(1, 1, 1, 1);
	//				ImVec4 c10(1, 1, 1, 1);
	//				ImVec4 c11(1, 1, 1, 1);

	//				ImVec4 cHueValue(1, 1, 1, 1);
	//				ImGui::ColorConvertHSVtoRGB(fHue, 1, 1, cHueValue.x, cHueValue.y, cHueValue.z);
	//				ImU32 oHueColor = ImGui::ColorConvertFloat4ToU32(cHueValue);

	//				pDrawList->AddRectFilledMultiColor(
	//					oSaturationAreaMin,
	//					oSaturationAreaMax,
	//					c_oColorWhite,
	//					oHueColor,
	//					oHueColor,
	//					c_oColorWhite
	//				);

	//				pDrawList->AddRectFilledMultiColor(
	//					oSaturationAreaMin,
	//					oSaturationAreaMax,
	//					c_oColorBlackTransparent,
	//					c_oColorBlackTransparent,
	//					c_oColorBlack,
	//					c_oColorBlack
	//				);

	//				pDrawList->AddCircle(ImVec2(oSaturationAreaMin.x + oSaturationAreaSize.x * fSat, oSaturationAreaMin.y + oSaturationAreaSize.y * (1.f - fVal)), 4, c_oColorBlack, 6);
	//			}
	//			ImGui::SameLine();
	//			//Hue
	//			{
	//				const ImVec2 oHueAreaSize(20, 128);
	//				ImGui::InvisibleButton("##HueArea", oHueAreaSize);
	//				//TODO tooltip
	//				ImVec2 oHueAreaMin = ImGui::GetItemRectMin();
	//				ImVec2 oHueAreaMax = ImGui::GetItemRectMax();

	//				if (ImGui::IsItemActive())
	//				{
	//					bRet = true;
	//					fHue = (ImGui::GetMousePos().y - oHueAreaMin.y) / oHueAreaSize.y;
	//					fHue = ofClamp(fHue, 0.f, 1.f);
	//					//fHue = Math::Clamp(fHue, 0.f, 1.f);
	//					ImGui::ColorConvertHSVtoRGB(fHue, fSat, fVal, oRGBA.x, oRGBA.y, oRGBA.z);

	//					ImGui::BeginTooltip();
	//					ImGui::Dummy(ImVec2(32, 32));
	//					ImVec2 oDummyAreaMin = ImGui::GetItemRectMin();
	//					ImVec2 oDummyAreaMax = ImGui::GetItemRectMax();
	//					ImDrawList* pDummyDrawList = ImGui::GetWindowDrawList();
	//					ImVec4 oNewHueRGB;
	//					oNewHueRGB.w = 1.f;
	//					ImGui::ColorConvertHSVtoRGB(fSat, 1.f, 1.f, oNewHueRGB.x, oNewHueRGB.y, oNewHueRGB.z);
	//					pDummyDrawList->AddRectFilled(oDummyAreaMin, oDummyAreaMax, ImGui::ColorConvertFloat4ToU32(oNewHueRGB));
	//					ImGui::EndTooltip();
	//				}

	//				ImVec2 pos = ImVec2(0, 0);
	//				ImVec4 c0(1, 1, 1, 1);
	//				ImVec4 c1(1, 1, 1, 1);

	//				const int iStepCount = 8;
	//				for (int iStep = 0; iStep < iStepCount; iStep++)
	//				{
	//					float h0 = (float)iStep / (float)iStepCount;
	//					float h1 = (float)(iStep + 1.f) / (float)iStepCount;
	//					ImGui::ColorConvertHSVtoRGB(h0, 1.f, 1.f, c0.x, c0.y, c0.z);
	//					ImGui::ColorConvertHSVtoRGB(h1, 1.f, 1.f, c1.x, c1.y, c1.z);

	//					pDrawList->AddRectFilledMultiColor(
	//						ImVec2(oHueAreaMin.x, oHueAreaMin.y + oHueAreaSize.y * h0),
	//						ImVec2(oHueAreaMax.x, oHueAreaMin.y + oHueAreaSize.y * h1),
	//						ImGui::ColorConvertFloat4ToU32(c0),
	//						ImGui::ColorConvertFloat4ToU32(c0),
	//						ImGui::ColorConvertFloat4ToU32(c1),
	//						ImGui::ColorConvertFloat4ToU32(c1)
	//					);
	//				}

	//				pDrawList->AddLine(
	//					ImVec2(oHueAreaMin.x, oHueAreaMin.y + oHueAreaSize.y * fHue),
	//					ImVec2(oHueAreaMax.x, oHueAreaMin.y + oHueAreaSize.y * fHue),
	//					c_oColorWhite
	//				);
	//			}
	//		}

	//		//RGBA Sliders
	//		ImGui::Text("RGBA");
	//		ImGui::Separator();
	//		{
	//			int r = (int)(ImSaturate(oRGBA.x)*255.f);
	//			int g = (int)(ImSaturate(oRGBA.y)*255.f);
	//			int b = (int)(ImSaturate(oRGBA.z)*255.f);
	//			int a = (int)(ImSaturate(oRGBA.w)*255.f);
	//			bool bChange = false;
	//			ImGui::PushItemWidth(130.f);
	//			bChange |= ImGui::SliderInt("R", &r, 0, 255);
	//			bChange |= ImGui::SliderInt("G", &g, 0, 255);
	//			bChange |= ImGui::SliderInt("B", &b, 0, 255);
	//			bChange |= ImGui::SliderInt("A", &a, 0, 255);
	//			ImGui::PopItemWidth();
	//			if (bChange)
	//			{
	//				bRet = true;
	//				oRGBA.x = (float)r / 255.f;
	//				oRGBA.y = (float)g / 255.f;
	//				oRGBA.z = (float)b / 255.f;
	//				oRGBA.w = (float)a / 255.f;

	//				ImGui::ColorConvertRGBtoHSV(oRGBA.x, oRGBA.y, oRGBA.z, fHue, fSat, fVal);
	//			}
	//		}

	//		if (bRet)
	//		{
	//			pWindow->StateStorage.SetFloat(iStorageCurrentColorH, fHue);
	//			pWindow->StateStorage.SetFloat(iStorageCurrentColorS, fSat);
	//			pWindow->StateStorage.SetFloat(iStorageCurrentColorV, fVal);
	//			pWindow->StateStorage.SetFloat(iStorageCurrentColorA, oRGBA.w);
	//		}

	//		if (ImGui::Button("Ok"))
	//		{
	//			pWindow->StateStorage.SetInt(iStorageOpen, 0);
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Cancel"))
	//		{
	//			pWindow->StateStorage.SetInt(iStorageOpen, 0);
	//			oRGBA.x = pWindow->StateStorage.GetFloat(iStorageStartColorR);
	//			oRGBA.y = pWindow->StateStorage.GetFloat(iStorageStartColorG);
	//			oRGBA.z = pWindow->StateStorage.GetFloat(iStorageStartColorB);
	//			oRGBA.w = pWindow->StateStorage.GetFloat(iStorageStartColorA);

	//			bRet = true;
	//		}
	//		ImGui::End();
	//	}

	//	ImGui::SameLine();

	//	float fValues[4] = { oRGBA.x, oRGBA.y, oRGBA.z, oRGBA.w };
	//	if (ImGui::DragFloat4(pLabel, fValues, 0.01f))
	//	{
	//		oRGBA.x = fValues[0];
	//		oRGBA.y = fValues[1];
	//		oRGBA.z = fValues[2];
	//		oRGBA.w = fValues[3];
	//		bRet = true;
	//	}

	//	ImGui::PopID();
	//	return bRet;
	//}

}//namespace ofxImGui

