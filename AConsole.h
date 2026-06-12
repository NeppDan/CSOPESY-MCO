#pragma once
#include "TypeDefs.h"

class AConsole {
public:
    AConsole(String name);
    virtual ~AConsole() = default;

    String getName() const;

    virtual void onEnabled() = 0;
    virtual void display() = 0;
    virtual void process() = 0;

private:
    String name;
    friend class ConsoleManager;
};