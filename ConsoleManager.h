#pragma once
#include <memory>
#include <unordered_map>
#include "AConsole.h"
#include "TypeDefs.h"

class BaseScreen;

inline const String MARQUEE_CONSOLE = "MARQUEE_SCREEN";

class ConsoleManager {
public:
    typedef std::unordered_map<String, std::shared_ptr<AConsole>> ConsoleTable;

    static ConsoleManager* getInstance();
    static void initialize();
    static void destroy();

    void drawConsole() const;
    void process()     const;
    void switchConsole(String consoleName);

    void registerScreen(std::shared_ptr<BaseScreen> screenRef);
    void switchToScreen(String screenName);
    void unregisterScreen(String screenName);

    void returnToPreviousConsole();
    void exitApplication();
    bool isRunning() const;


private:
    ConsoleManager();
    ~ConsoleManager() = default;
    ConsoleManager(ConsoleManager const&) = delete;
    ConsoleManager& operator=(ConsoleManager const&) = delete;

    static ConsoleManager* sharedInstance;

    ConsoleTable consoleTable;
    std::shared_ptr<AConsole> currentConsole;
    std::shared_ptr<AConsole> previousConsole;

    bool running = true;
};