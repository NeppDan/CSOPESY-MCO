#include "TaskBar.h"
#include "imgui/imgui-master/imgui.h"

void TaskBar::render() {
 
}

void TaskBar::renderBackground() {}
void TaskBar::renderItems() {}
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