


#include "Time.h"
#include "../Console/ConsoleMessage.h"
#include <SDL2/SDL.h>

namespace Game::Time {
    void Time::frameStart() {
        frameStartTimestamp = SDL_GetTicks();
        // Expect frameEndTimestamp to never be 0
        if (frameEndTimestamp) {
//            auto difference = frameEndTimestamp - frameStartTimestamp;
//            deltaTime = difference / 1000.0f; // FIXME: This is not giving good values
            deltaTime = 0.07;
            auto separator = std::string("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            auto debugMessage =  \
//            "diff\t" + std::to_string(difference) +
                                "\ndT\t" + std::to_string(deltaTime) +
                                "\nfS\t" + std::to_string(frameStartTimestamp) +
                                "\nfE\t" + std::to_string(frameEndTimestamp);

            ConsoleMessage::DEBUG(separator + debugMessage);
        } else deltaTime = 0;
    }

    void Time::frameEnd() {
        // Right now
        frameEndTimestamp = SDL_GetTicks();
        currentTicks = frameEndTimestamp - frameStartTimestamp;
        if (currentTicks < frameTicks) {
            SDL_Delay(frameTicks - currentTicks);
//            ConsoleMessage::INFO("Delaying...");
        }
        tick++;
    }

    Time::Time(int p_FPS, Game::Time::Options options) : ErrorSupport(options.error, (char *) "Time Manager") {
        FPS = p_FPS;
        frameStartTimestamp = 0;
        frameEndTimestamp = 0;
        deltaTime = 0;
        currentTicks = 0;
        tick = 0;
        // Drop everything under the milliseconds
        frameTicks = (Uint32)((1.0f / (float) p_FPS) * 1000.0f); // Data value is an int. It will drop the data.

        // Frames will be measured in ticks. A frame will be n ticks.

    }

    Time *New(int FPS, Game::Time::Options options) {
        return new Time(FPS, options);
    }


    Time::~Time() = default;
} // Game