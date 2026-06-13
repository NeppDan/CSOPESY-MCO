#pragma once

#include <string>
#include "ConsoleManager.h"
#include "TaskBar.h"   

struct GLFWwindow;

class DesktopApp {
public:
    void setWindowTitle(const std::string& title);
    void setDesktopName(const std::string& name);

    bool run();

private:
    bool initialize();
    void shutdown();
    void renderFrame();
    void renderDesktop();
    std::string currentTimeText() const;

    std::string windowTitle = "Mock Desktop OS";
    std::string desktopName = "CSOPESY Desktop";
    GLFWwindow* windowHandle = nullptr;
    TaskBar taskBar;
};