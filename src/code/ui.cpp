#include "../headers/ui.hpp"

std::string Shortcutter(std::string input)
{
    std::string shortcut = PLATFORM_SUPERKEY + std::string("+") + input;
    return shortcut;
}

void UI::Init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    // Loading a really nice, clean looking font.
    io.Fonts->AddFontFromFileTTF("../UI/resources/Work Sans/WorkSans-Regular.ttf", 16.0f);
    /**
        LITERAL BLACK MAGIC
        - Scales UI based on DPI/random scale factor...
        - Have no clue what 13 is meant to represent but it works...(font size maybe??)
        - Figure out what this all means...
    */
    float globalScaleFactor = 1.3f;
    ImFontConfig fontConfig;
    fontConfig.SizePixels = 13 * globalScaleFactor;
    ImGui::GetIO().Fonts->AddFontDefault(&fontConfig)->FontSize = globalScaleFactor;
}

void UI::Prepare()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UI::MenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("New"))
            {
                if (ImGui::MenuItem("Project", "CTRL+N")) {}
                if (ImGui::MenuItem("Script", "CTRL+Shift+N")) {}
                if (ImGui::MenuItem("Shader", "CTRL+Alt+N")) {}
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Open Project", "CTRL+O")) {}
            if (ImGui::BeginMenu("Open Recent"))
            {
                if (ImGui::MenuItem("dummy_file_x")) {}
                if (ImGui::MenuItem("dummy_file_y")) {}
                if (ImGui::MenuItem("dummy_file_z")) {}
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Save", "CTRL+S")) {}
            if (ImGui::MenuItem("Save As", "CTRL+Shift+S")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "CTRL+Q")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Preferences", "CTRL+P")){}
            
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project"))
        {
            if (ImGui::MenuItem("Project Settings", "CTRL+K")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::MenuItem("Scene Settings", "CTRL+O")) 
            {

            }
            
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject"))
        {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Online Documentation", "CTRL+I")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void UI::SceneView(unsigned int colorBuffer)
{
    ImGui::ShowDemoWindow();

    ImGui::Begin("Scene");
    {
        ImGui::BeginChild("Renderer Viewport");

        ImGui::Text("Scene View");

		ImVec2 pos = ImGui::GetCursorScreenPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

		ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(intptr_t)colorBuffer, 
            ImVec2(pos), ImVec2(pos.x + windowSize.x, pos.y + windowSize.y), 
            ImVec2(-1, 0), ImVec2(0, 1));

        ImGui::EndChild();
        ImGui::End();
    }
}

void UI::Render(unsigned int colorBuffer)
{
    UI::MenuBar();
    UI::SceneView(colorBuffer);
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}