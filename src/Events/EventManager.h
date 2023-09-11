
#ifndef PONGPROJECT_EVENTMANAGER_H
#define PONGPROJECT_EVENTMANAGER_H

#include "../Error/Error.h"
#include <SDL2/SDL.h>
#include <vector>

namespace Game::EventManager {

    struct EventManagerOptions {
        StandardError *parentError;
        EventManagerOptions();
        explicit EventManagerOptions(StandardError* opt_parentError);
        ~EventManagerOptions();
    };

    class EventManager : public ErrorSupport {
    public:
        void handleEvents(SDL_Rect &ball, SDL_Rect &paddle1, SDL_Rect &paddle2, int screenHeight, int screenWidth);

        explicit EventManager(EventManagerOptions *options);
    };

    EventManager *New(EventManagerOptions* = new EventManagerOptions());
} // Game

#endif //PONGPROJECT_EVENTMANAGER_H
