#include "AConsole.h"

AConsole::AConsole(String name) : name(name) {}

String AConsole::getName() const {
	return name;
}
