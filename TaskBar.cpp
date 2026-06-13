#include "TaskBar.h"
#include "imgui/imgui-master/imgui.h"

#include <GLFW/glfw3.h>

namespace {
    constexpr ImVec4 kTaskbarBackground = ImVec4(0.10f, 0.10f, 0.12f, 0.96f);
    constexpr ImVec4 kTopEdge = ImVec4(0.22f, 0.47f, 0.92f, 1.0f);
    constexpr ImVec4 kNotepadWindow = ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
    constexpr ImVec4 kNotepadHeader = ImVec4(0.13f, 0.15f, 0.18f, 1.0f);
    constexpr ImVec4 kNotepadEditor = ImVec4(0.06f, 0.07f, 0.08f, 1.0f);
    constexpr ImVec4 kNotepadText = ImVec4(0.93f, 0.95f, 0.98f, 1.0f);
    constexpr ImVec4 kTerminalBg = ImVec4(0.04f, 0.05f, 0.06f, 1.0f);
}

void TaskBar::render() {
    ensureItemsInitialized();

    const ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    const float taskbarHeight = HEIGHT;

    ImGui::SetNextWindowPos(ImVec2(0.0f, displaySize.y - taskbarHeight));
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, taskbarHeight));

    ImGui::Begin(
        "Taskbar",
        nullptr,
        ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoSavedSettings);

    renderBackground();
    renderItems();
    renderClock();
    renderPowerButton();

    ImGui::End();

    renderNotepadWindow();
    renderTerminalWindow();

    if (taskManagerOpen) {
        ImGui::SetNextWindowSize(ImVec2(360.0f, 220.0f), ImGuiCond_FirstUseEver);
        ImGui::Begin("Task Manager", &taskManagerOpen, ImGuiWindowFlags_NoCollapse);
        ImGui::TextUnformatted("Task Manager placeholder");
        ImGui::Separator();
        ImGui::TextWrapped("Reserved for Component 3.");
        ImGui::End();
    }
}

void TaskBar::renderBackground() {
    const ImVec2 windowPos = ImGui::GetWindowPos();
    const ImVec2 windowSize = ImGui::GetWindowSize();
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    drawList->AddRectFilled(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y), ImColor(kTaskbarBackground));
    drawList->AddRectFilled(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + 4.0f), ImColor(kTopEdge));
}

void TaskBar::renderItems() {
    ImGui::SetCursorPos(ImVec2(8.0f, 4.0f));

    if (ImGui::Button("Notepad", ImVec2(96.0f, 32.0f))) {
        notepadOpen = true;
    }

    ImGui::SameLine();
    if (ImGui::Button("Terminal", ImVec2(96.0f, 32.0f))) {
        terminalOpen = true;
    }

    ImGui::SameLine();
    if (ImGui::Button("TM", ImVec2(64.0f, 32.0f))) {
        taskManagerOpen = true;
    }
}

void TaskBar::renderClock() {
    const ImVec2 windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPos(ImVec2(windowSize.x - 160.0f, 9.0f));
    ImGui::TextDisabled("Component 2");
}

void TaskBar::renderPowerButton() {
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 56.0f, 4.0f));
    if (ImGui::Button("PWR", ImVec2(48.0f, 32.0f))) {
        if (targetWindow != nullptr) {
            glfwSetWindowShouldClose(targetWindow, GLFW_TRUE);
        }
    }
}

void TaskBar::setTargetWindow(GLFWwindow* window) {
    targetWindow = window;
}

void TaskBar::renderNotepadWindow() {
    if (!notepadOpen) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(540.0f, 420.0f), ImGuiCond_FirstUseEver);
    ImGui::Begin("Notepad", &notepadOpen, ImGuiWindowFlags_NoCollapse);

    ImGui::PushStyleColor(ImGuiCol_TitleBg, IM_COL32(18, 20, 24, 255));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, IM_COL32(28, 31, 36, 255));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, kNotepadWindow);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kNotepadEditor);
    ImGui::PushStyleColor(ImGuiCol_Text, kNotepadText);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(24, 27, 31, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(34, 38, 44, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(42, 47, 54, 255));
    ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(64, 74, 88, 255));
    ImGui::BeginChild("NotepadHeader", ImVec2(0.0f, 56.0f), true);
    ImGui::TextUnformatted("Untitled - Notepad");
    ImGui::TextDisabled("File   Edit   Format   View   Help");
    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::BeginChild("NotepadEditorPanel", ImVec2(0.0f, -28.0f), true, ImGuiWindowFlags_HorizontalScrollbar);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    ImGui::InputTextMultiline("##notepad_text", notepadBuffer.data(), notepadBuffer.size(), ImVec2(-1.0f, -1.0f));
    ImGui::PopStyleVar();
    ImGui::EndChild();

    ImGui::TextDisabled("Ready");
    ImGui::PopStyleColor(9);
    ImGui::End();
}

void TaskBar::renderTerminalWindow() {
    if (!terminalOpen) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(580.0f, 360.0f), ImGuiCond_FirstUseEver);
    ImGui::Begin("Terminal", &terminalOpen, ImGuiWindowFlags_NoCollapse);

    ImGui::PushStyleColor(ImGuiCol_TitleBg, IM_COL32(18, 20, 24, 255));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, IM_COL32(28, 31, 36, 255));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kTerminalBg);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(120, 255, 120, 255));
    ImGui::BeginChild("TerminalHistory", ImVec2(0.0f, 230.0f), true, ImGuiWindowFlags_HorizontalScrollbar);
    for (const std::string& line : terminalHistory) {
        ImGui::TextUnformatted(line.c_str());
    }
    ImGui::TextUnformatted("C:\\MockDesktopOS>");
    ImGui::SameLine();
    ImGui::TextDisabled("placeholder shell");
    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::InputText("Command", terminalBuffer.data(), terminalBuffer.size());
    ImGui::SameLine();
    if (ImGui::Button("Enter")) {
        if (terminalBuffer[0] != '\0') {
            terminalHistory.emplace_back(std::string("C:\\MockDesktopOS> ") + terminalBuffer.data());
            terminalHistory.emplace_back("Output: this is only a visual placeholder.");
            terminalBuffer.fill('\0');
        }
    }

    ImGui::PopStyleColor(4);
    ImGui::End();
}

void TaskBar::ensureItemsInitialized() {
    if (itemsInitialized) {
        return;
    }

    itemsInitialized = true;
    items.push_back({"Notepad", "App1", false});
    items.push_back({"Terminal", "App2", false});
    items.push_back({"Task Manager", "TaskManager", false});
}

void TaskBar::addItem(const std::string& label, const std::string& screenName) {
    items.push_back({label, screenName, false});
}

void TaskBar::setActiveItem(const std::string& screenName) {
    activeScreenName = screenName;
    for (auto& item : items) {
        item.isActive = (item.screenName == screenName);
    }
}
