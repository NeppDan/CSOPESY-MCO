#include "TaskBar.h"
#include "imgui/imgui-master/imgui.h"

void TaskBar::render() {
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    float taskbarHeight = HEIGHT;

    // Position at bottom of screen 
    ImGui::SetNextWindowPos(ImVec2(0, displaySize.y - taskbarHeight)); 
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, taskbarHeight)); 

    ImGui::Begin("Taskbar", nullptr, 
        ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoScrollbar);
    
    addItem("App1", "App1");
    addItem("App2", "App2");
    addItem("TaskManager", "TaskManager");

    renderItems();


    ImGui::End();
    
}

void TaskBar::renderBackground() {}
void TaskBar::renderItems() {
    //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4.0f, 4.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.95f)); //

        if(ImGui::Button("App1", ImVec2(90.0f, 40.0f))){
            setActiveItem("App1");
            
        }
        ImGui::SameLine();

        if(ImGui::Button("App2", ImVec2(90.0f, 40.0f))){
            setActiveItem("App2");
        }

        ImGui::SameLine();
        if(ImGui::Button("TMG", ImVec2(90.0f, 40.0f))){
            setActiveItem("TaskManager");
        }

        // App 1
        if (items[0].isActive){
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
            ImGui::Begin("App1", &items[0].isActive);
            ImGui::Text("App 1 details go here!");
            ImGui::End();
        }

        // App 2
        if (items[1].isActive){
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);  
            ImGui::Begin("App2", &items[1].isActive);
            ImGui::Text("App 2 details go here!");
            ImGui::End();
        }

        // Task Manager
        if (items[2].isActive){
            // task manager here
        }
    
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);
}
void TaskBar::renderClock() {}
void TaskBar::renderPowerButton() {}

void TaskBar::addItem(const std::string& label, const std::string& screenName) {
    items.push_back({ label, screenName, false });
}

void TaskBar::setActiveItem(const std::string& screenName) {
    activeScreenName = screenName;
    for (auto& item : items) {
        item.isActive = (item.screenName == screenName);
    }
}