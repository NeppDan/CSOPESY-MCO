#pragma once
#include <string>
#include <vector>

struct TaskBarItem {
    std::string label;
    std::string screenName;  
    bool isActive = false;
};

class TaskBar {
public:
    TaskBar() = default;

    void render();
    void addItem(const std::string& label, const std::string& screenName);
    void setActiveItem(const std::string& screenName);

    static constexpr float HEIGHT = 40.0f;

private:
    void renderBackground();
    void renderItems();
    void renderClock();
    void renderPowerButton();

    std::vector<TaskBarItem> items;
    std::string activeScreenName;
};