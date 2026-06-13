#define GLFW_INCLUDE_NONE

#include "DesktopApp.h"
#include "ConsoleManager.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "imgui/imgui-master/imgui.h"
#include "imgui/imgui-master/backends/imgui_impl_glfw.h"
#include "imgui/imgui-master/backends/imgui_impl_opengl2.h"

void DesktopApp::setWindowTitle(const std::string& title) {
    windowTitle = title;
}

void DesktopApp::setDesktopName(const std::string& name) {
    desktopName = name;
}

bool DesktopApp::run() {
    if (!initialize()) {
        shutdown();
        return false;
    }

    while (windowHandle != nullptr && !glfwWindowShouldClose(windowHandle)) {
        renderFrame();
    }

    shutdown();
    return true;
}

bool DesktopApp::initialize() {
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    windowHandle = glfwCreateWindow(1280, 720, windowTitle.c_str(), nullptr, nullptr);
    if (windowHandle == nullptr) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(windowHandle);
    glfwSwapInterval(1);
    glfwMaximizeWindow(windowHandle);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 12.0f;
    style.FrameRounding = 8.0f;
    style.ScrollbarRounding = 10.0f;

    if (!ImGui_ImplGlfw_InitForOpenGL(windowHandle, true)) {
        return false;
    }

    if (!ImGui_ImplOpenGL2_Init()) {
        return false;
    }

    ConsoleManager::initialize();

    return true;
}

void DesktopApp::shutdown() {
    ConsoleManager::destroy();

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (windowHandle != nullptr) {
        glfwDestroyWindow(windowHandle);
        windowHandle = nullptr;
    }

    glfwTerminate();
}

void DesktopApp::renderFrame() {
    glfwPollEvents();

    ConsoleManager::getInstance()->process();

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    renderDesktop();

    ImGui::Render();

    int displayWidth = 0;
    int displayHeight = 0;
    glfwGetFramebufferSize(windowHandle, &displayWidth, &displayHeight);

    if (displayWidth > 0 && displayHeight > 0) {
        glViewport(0, 0, displayWidth, displayHeight);
        glClearColor(0.08f, 0.10f, 0.16f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(windowHandle);
    }
}

void DesktopApp::renderDesktop() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 viewportPos = viewport->Pos;
    const ImVec2 viewportSize = viewport->Size;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddRectFilledMultiColor(
        viewportPos,
        ImVec2(viewportPos.x + viewportSize.x, viewportPos.y + viewportSize.y),
        IM_COL32(19, 38, 82, 255),
        IM_COL32(12, 20, 54, 255),
        IM_COL32(7, 14, 40, 255),
        IM_COL32(28, 54, 108, 255));

    drawList->AddRectFilled(
        viewportPos,
        ImVec2(viewportPos.x + viewportSize.x, viewportPos.y + viewportSize.y),
        IM_COL32(0, 0, 0, 48));

    ImGui::SetNextWindowPos(viewportPos);
    ImGui::SetNextWindowSize(viewportSize);
    ImGuiWindowFlags rootFlags = ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoBackground;

    ImGui::Begin("DesktopRoot", nullptr, rootFlags);

    ImGui::SetCursorPos(ImVec2(20.0f, 20.0f));
    if (ImGui::Button("PWR", ImVec2(90.0f, 40.0f))) {
        glfwSetWindowShouldClose(windowHandle, GLFW_TRUE);
    }

    ImGui::SetCursorPos(ImVec2(viewportSize.x - 260.0f, 18.0f));
    if (ImGui::BeginChild("ClockPanel", ImVec2(240.0f, 80.0f), true)) {
        ImGui::TextUnformatted(desktopName.c_str());
        ImGui::Separator();
        ImGui::TextUnformatted(currentTimeText().c_str());
    }
    ImGui::EndChild();

    ConsoleManager::getInstance()->drawConsole();

    ImGui::End();
}

std::string DesktopApp::currentTimeText() const {
    using clock = std::chrono::system_clock;
    const auto now = clock::now();
    const std::time_t rawTime = clock::to_time_t(now);

    std::tm localTime{};
#if defined(_MSC_VER)
    localtime_s(&localTime, &rawTime);
#else
    localTime = *std::localtime(&rawTime);
#endif

    std::ostringstream stream;
    stream << std::put_time(&localTime, "%I:%M:%S %p");
    return stream.str();
}
