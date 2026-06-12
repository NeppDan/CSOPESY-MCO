#include <Windows.h>
#include "DesktopApp.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    DesktopApp app;
    app.setWindowTitle("Mock Desktop OS");
    app.setDesktopName("CSOPESY Desktop");

    if (!app.run()) {
        return 1;
    }

    return 0;
}