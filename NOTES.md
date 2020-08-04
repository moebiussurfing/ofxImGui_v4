
## Change or use multiple fonts

https://github.com/ocornut/imgui/issues/1397
// Test loading 2 fonts during init:

// Load Fonts
ImGuiIO& io = ImGui::GetIO();
ImFont* font1 = io.Fonts->AddFontDefault();
ImFont* font2 = io.Fonts->AddFontFromFileTTF("../../extra_fonts/Ruda-Bold.ttf", 16.0f);

//Then in main loop:
ImGui::Begin("Test #1397");
ImGui::Text("Hello!");
ImGui::PushFont(font2);
ImGui::Text("Hello!");
ImGui::PopFont();
ImGui::End();

//--

# example

//setup()
//Change font in ofxImGui/ImGui
//https://forum.openframeworks.cc/t/change-font-in-ofximgui/28841
ImGuiIO& io = ImGui::GetIO();
ImFontConfig config;
config.OversampleH = 3;
config.OversampleV = 1;
config.GlyphExtraSpacing.x = 1.0f;

const char* myPath;
string inputPath;

inputPath = ofFilePath::getAbsolutePath("fonts/malgun_console.ttf");
myPath = inputPath.c_str();
font1 = io.Fonts->AddFontFromFileTTF(myPath, 15.0f, &config);

inputPath = ofFilePath::getAbsolutePath("fonts/msjh_boot.ttf");
myPath = inputPath.c_str();
font2 = io.Fonts->AddFontFromFileTTF(myPath, 20.0f, &config);

inputPath = ofFilePath::getAbsolutePath("fonts/msyh_console.ttf");
myPath = inputPath.c_str();
font3 = io.Fonts->AddFontFromFileTTF(myPath, 20.0f, &config);

//--

//draw()
ImGui::Text("Hello, world!");
ImGui::ColorEdit3("Background Color", (float*)&backgroundColor);
ImGui::PushFont(font2);
ImGui::Text("Hello!");
ImGui::PopFont();
ImGui::SliderFloat("Float", &floatValue, 0.0f, 1.0f);
ImGui::PushFont(font3);
if (ImGui::Checkbox("Demo Window", &b))
    if (b) ImGui::ShowDemoWindow();
ImGui::PopFont();

//--

//draw. select default font         
        
// combo with fonts added to ImGui
ImGuiIO& io = ImGui::GetIO();
ImFont* font_current = ImGui::GetFont();
if (ImGui::BeginCombo("Fonts", font_current->GetDebugName())) {
    for (auto font : io.Fonts->Fonts) {
        if (ImGui::Selectable(font->GetDebugName(), font == font_current)) {
            io.FontDefault = font;
        }
    }
    ImGui::EndCombo();
}

//--

//fixes to macOS path problems
ofFilePath::getAbsolutePath("fonts/malgun_console.ttf")
"fonts/Verdana.ttf"
"/Users/David/Openframeworks/apps/myApps/imGui/bin/data/fonts/Telefonica-Regular.ttf"


//--

## Docking info

https://github.com/ocornut/imgui/issues/2109