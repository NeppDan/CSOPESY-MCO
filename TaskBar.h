#pragma once
#include <array>
#include <string>
#include <vector>

struct GLFWwindow;

struct TaskBarItem {
    std::string label;
    std::string screenName;  
    bool isActive = false;
};

class TaskBar {
public:
    TaskBar() = default;

    void setTargetWindow(GLFWwindow* window);
    void render();
    void addItem(const std::string& label, const std::string& screenName);
    void setActiveItem(const std::string& screenName);

    static constexpr float HEIGHT = 40.0f;

private:
    void renderBackground();
    void renderItems();
    void renderClock();
    void renderPowerButton();
    void renderNotepadWindow();
    void renderTerminalWindow();
    void ensureItemsInitialized();

    std::vector<TaskBarItem> items;
    std::string activeScreenName;
    bool itemsInitialized = false;
    bool notepadOpen = false;
    bool terminalOpen = false;
    bool taskManagerOpen = false;
    std::array<char, 4096> notepadBuffer{};
    std::array<char, 256> terminalBuffer{};
    std::vector<std::string> terminalHistory;
    GLFWwindow* targetWindow = nullptr;
};