#include <memory>
#include "ConsoleManager.h"

int main() {
    ConsoleManager::initialize();

    while (ConsoleManager::getInstance()->isRunning()) {
        ConsoleManager::getInstance()->process();
        ConsoleManager::getInstance()->drawConsole();
    }

    ConsoleManager::destroy();
    return 0;
}