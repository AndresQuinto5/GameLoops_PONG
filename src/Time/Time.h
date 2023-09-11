

#ifndef PONGPROJECT_TIME_H
#define PONGPROJECT_TIME_H

#include <SDL.h>
#include "../Error/Error.h"

namespace Game::Time {

    struct Options : AllowError {
        explicit Options(StandardError *error) : AllowError(error) {}
    };

    class Time : public ErrorSupport {
    public:
        explicit Time(int FPS, Game::Time::Options);

        ~Time();

        void frameStart();

        float deltaTime;

        void frameEnd();

    private:
        int FPS;
        Uint32 frameStartTimestamp;
        Uint32 frameEndTimestamp;
        Uint32 frameTicks;
        Uint32 currentTicks;
        Uint32 tick;

    };

    Time *New(int FPS, Game::Time::Options);

} // Game

#endif //PONGPROJECT_TIME_H
