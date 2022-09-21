ofxImGui_v4
=============================

## Notes by @moebiusSurfing:  

#### DEPRECATED
Currently I am using this fork:  
https://github.com/moebiussurfing/ofxSurfingImGui  

https://github.com/Daandelange/ofxImGui/tree/ofParameters-Helpers-Test  
* Multicontext/instances
* ImGui 1.80+
-------------------------------------------------

### *NOT READY TO USE YET. STILL VERY BUGGY. I AM HAVING PROBLEMS TO ADD HELPERS TO HANDLE ofParameters*  


### About    
*Currently updated to docking branch on Jul 17, 2020*  
https://github.com/ocornut/imgui/tree/docking  
https://github.com/ocornut/imgui/commit/3d4af15d1d5f5d3746b69859308949c357e0c21e  
folder `/v1.77` includes `/libs` and `/opengl` folders to easy switch to non-docking 1.77 release version.  


**/example-demo**  

![image](https://github.com/moebiussurfing/ofxImGui_v4/blob/master/readme_images/screenshot1.PNG?raw=true "readme_images/screenshot1.PNG")  

![image](https://github.com/moebiussurfing/ofxImGui_v4/blob/master/readme_images/screenshot2.PNG?raw=true "readme_images/screenshot2.PNG")  

**This is a splitted-fork from**  
https://github.com/yumataesu/ofxImGui_v3  
Author of the addon: **@yumataesu**  
Using some of the OF helper funtions.  

## Why this fork?
Simpler and easy to update than the `official` addon:  
https://github.com/jvcleave/ofxImGui  
My main idea here is to have a simpler wrapper but with some helper methods useful for openFrameworks, mainly to easy handle `ofParameter/ofParameterGroup`.  
Besides ofxImGui: it allows helpesr using native begin/end, not required ofxImgui:Begin/End  
Like `ofxImGuiSimple` or `ofxImGui_v3`, intended to *use the more pure ImGui code as possible*.  
I will add some related personal notes, interesting links and examples (focused in OF).  


https://github.com/ocornut/imgui/releases/tag/v1.77  

### Thanks to  
**@yumataesu** -> for the original code!  
And thanks to all the coders of the below links.  

### Tested System  
**OF 0.11** / **Windows10** / **VS2017**  

### TODO
- Collect all helpers and useful examples in the same place.  
- Add node patching repositories with OF examples.  
- Any help about how to add node pacthing engines will be appreciated!  
- Looking to port guizmo too.  

## Related links  

**WHY A SIMPLER WRAPPER?**  
https://github.com/PlaymodesStudio/ofxImGuiSimple/issues/2  
https://github.com/pjulien21/ofImGuiApp/issues/1  

**OF IMGUI CODE**  
https://github.com/PlaymodesStudio/ofxImGuiSimple -> simple but without helpers  
https://github.com/yasuhirohoshino/ofxPBRHelper -> cool addon that uses ImGui to scene handle and store/recall settings  
https://github.com/sebasobotka/ofxImGui -> Combo and ListBox which can take a vector<string> and customize fonts ( + .otf)  
https://github.com/MacFurax/ofxImGui -> nice theme, custom widgets kind of sound synth device like circular knob...  
https://github.com/pjulien21/ofImGuiApp -> simple but modifiying main.app  
https://github.com/yumataesu/ImGui_Widgets -> kind of vj widgets  
https://github.com/Iwanaka/ofxMyUtil/blob/master/src/utils/ofxMyUtilImGui.h -> OF helpers.  
https://github.com/geekowll/imdesigner -> tools to create and deep customize widgets  
https://github.com/katotetsuro/ofxImGui/tree/multiwindow -> simple code to allow multiwindow/contexts without crash  
https://github.com/memo/ofxMSAControlFreakImGui  
https://github.com/rystylee/ofxImGui-docking  
https://github.com/Akira-Hayasaka/ofxImGui_SplineEditor  
https://github.com/d3cod3/ofxImGui/commit/a288774a4ff2bd395a47e7720d9cdb487e23fc94 -> customize fonts  

**RAW IMGUI CODE**  
https://github.com/ocornut/imgui_club -> main examples  
https://github.com/aiekick/ImGuiFileDialog -> files browsers  
https://github.com/AirGuanZ/imgui-filebrowser  
https://github.com/CedricGuillemet/ImGuizmo -> gizmos  
https://github.com/BrutPitt/imGuIZMO.quat  
https://github.com/john-chapman/im3d  

**NODE PATCHING**  
https://github.com/thedmd/imgui-node-editor -> looking to port nodes into OF..  
https://github.com/Nelarius/imnodes  
https://github.com/rokups/ImNodes  
https://github.com/JoshuaBatty/ofxNodeGraph -> old OF example  
https://github.com/sphaero/ofNodeEditor -> old OF example  
