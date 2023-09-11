#ifndef PONGPROJECT_STATIC_H
#define PONGPROJECT_STATIC_H

#include "Error/Error.h"
#include "Console/ConsoleMessage.h"
namespace Game {
    static bool *isRunning;
    static StandardError *gameError;
    static bool hasError() {
        if (gameError) return gameError->exists;
        ConsoleMessage::WARN("Trying to access a static memory address for gameError somewhere, but it doesn't exist.");
        return false;
    };
    static StandardError* getError() {
        return gameError;
    }

} // Game

#endif //PONGPROJECT_STATIC_H
