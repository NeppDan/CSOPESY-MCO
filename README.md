# Mock Desktop OS

Desktop-style OS mockup for CSOPESY using GLFW + OpenGL + Dear ImGui.

## Prerequisites

Install these on the machine:

- MSYS2 UCRT64
- `g++` from MSYS2
- GLFW from MSYS2

Recommended MSYS2 package command:

```powershell
C:\msys64\usr\bin\pacman.exe -S mingw-w64-ucrt-x86_64-glfw
```

You do not need to install Dear ImGui separately because the source is already included in the repository under `imgui/imgui-master/`.

## Build and run

Open PowerShell in the project folder and run:

```powershell
g++ -std=c++20 -mwindows -Iimgui/imgui-master -Iimgui/imgui-master/backends MockDesktopOS.cpp DesktopApp.cpp AConsole.cpp BaseScreen.cpp ConsoleManager.cpp TaskBar.cpp imgui/imgui-master/imgui.cpp imgui/imgui-master/imgui_draw.cpp imgui/imgui-master/imgui_tables.cpp imgui/imgui-master/imgui_widgets.cpp imgui/imgui-master/backends/imgui_impl_glfw.cpp imgui/imgui-master/backends/imgui_impl_opengl2.cpp -LC:/msys64/ucrt64/lib -lglfw3 -lopengl32 -lgdi32 -lgdiplus -luser32 -lkernel32 -lole32 -luuid -lshell32 -o MockDesktopOS.exe 2>
MockDesktopOS.exe
```

If `glfw3.dll` is not found when launching, make sure this folder is on PATH:

```powershell
C:\msys64\ucrt64\bin
```

If you want to set it temporarily in the current shell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path
```
