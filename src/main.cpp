#include <iostream>

#include "./Game/GameController.h"
#include "./Console/ConsoleMessage.h"


#define SCREEN_FPS 60


using namespace Game;

int main() {

    ConsoleLogging.setLoggingLevel(ConsoleLevel::OFF);
    ConsoleMessage::INFO("Trying");
    auto mainWindow = Screen::New();
    auto event = EventManager::New();
    auto time = Time::New(SCREEN_FPS, Time::Options{nullptr});
    auto params = InitParameters{
            .FPS = SCREEN_FPS,
            .screen = mainWindow,
            .event = event,
            .time = time
    };
    auto *game = new Game::Manager(params);
    game->setup();

    game->init();
    game->runLoop();

    return 0;
}
