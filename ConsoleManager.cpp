#include "ConsoleManager.h"
#include "BaseScreen.h"
#include <iostream>

ConsoleManager* ConsoleManager::sharedInstance = nullptr;

ConsoleManager* ConsoleManager::getInstance() {
    if (sharedInstance == nullptr) {
        sharedInstance = new ConsoleManager();
    }
    return sharedInstance;
}

void ConsoleManager::initialize() {
    if (sharedInstance == nullptr) {
        sharedInstance = new ConsoleManager();
    }
}

void ConsoleManager::destroy() {
    delete sharedInstance;
    sharedInstance = nullptr;
}

void ConsoleManager::drawConsole() const {
    if (currentConsole != nullptr) {
        currentConsole->display();
    }
}

void ConsoleManager::process() const {
    if (currentConsole != nullptr) {
        currentConsole->process();
    }
}

void ConsoleManager::switchConsole(String consoleName) {
    if (consoleTable.find(consoleName) != consoleTable.end()) {
        previousConsole = currentConsole;
        currentConsole = consoleTable[consoleName];
        currentConsole->onEnabled();
    }
    else {
        std::cerr << "Console not found: " << consoleName << std::endl;
    }
}

void ConsoleManager::returnToPreviousConsole() {
    if (previousConsole != nullptr) {
        currentConsole = previousConsole;
        previousConsole = nullptr;
        currentConsole->onEnabled();
    }
}

void ConsoleManager::exitApplication() {
    running = false;
}

bool ConsoleManager::isRunning() const {
    return running;
}

void ConsoleManager::registerScreen(std::shared_ptr<BaseScreen> screenRef) {
    consoleTable[screenRef->getName()] = screenRef;
}

void ConsoleManager::switchToScreen(String screenName) {
    switchConsole(screenName);
}

void ConsoleManager::unregisterScreen(String screenName) {
    consoleTable.erase(screenName);
}

HANDLE ConsoleManager::getConsoleHandle() const {
    return consoleHandle;
}