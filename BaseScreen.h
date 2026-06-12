#pragma once
#include "AConsole.h"

class BaseScreen : public AConsole {
public:
    BaseScreen(String name) : AConsole(name) {}

    void onEnabled() override {}
    void display()   override {}
    void process()   override {}
};