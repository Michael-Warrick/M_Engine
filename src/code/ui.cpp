#include "../headers/ui.hpp"

void UI::Init(GLFWwindow *window) 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    /**
        LITERAL BLACK MAGIC 
        - Scales UI based on DPI/random scale factor...
        - Have no clue what 13 is meant to represent but it works...(font size maybe??)
        - Figure out what this all means...
    */

    float globalScaleFactor = 1.0f;
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

void UI::Render() 
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New")) 
            {
                if (ImGui::MenuItem("Project")){}
                if (ImGui::MenuItem("Script")) {}
                if (ImGui::MenuItem("Shader")) {}
                ImGui::EndMenu();
            }
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
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::Destroy() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}