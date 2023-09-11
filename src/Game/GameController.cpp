
#include "GameController.h"
#include "../Console/ConsoleMessage.h"
#include "../Static.h"


void Game::Manager::runLoop() {
    while (*Game::isRunning && !Game::hasError()) {
        components->timeController->frameStart();
        components->eventController->handleEvents(ball, paddle1, paddle2, components->screenController->dims->height,
                                                  components->screenController->dims->width);
        components->screenController->update(ball, paddle1, paddle2, components->timeController->deltaTime);
        components->screenController->render(ball, paddle1, paddle2);
        components->timeController->frameEnd();
    }

    if (Game::hasError()) {
        std::string errorMessage = std::string(Game::getError()->message);
        ConsoleMessage::ERROR(errorMessage);
    }

}

Game::Manager::Manager(Game::InitParameters params) : ball(), paddle1(), paddle2() {
    Game::isRunning = new bool(true);
    Game::gameError = new StandardError();
    components = new Components();
    setComponents(params.screen, params.time, params.event);
}

void Game::Manager::init() {
    components->screenController->init();
}

void Game::Manager::setup() {
    auto dims = components->screenController->dims;

    paddle1.h = 100;
    paddle1.w = 20;
//    paddle1.x = (dims->width / 2) - (paddle1.w / 2); // This paints exactly in the middle
    paddle1.x = 0;
    paddle1.y = (dims->height / 2) - (paddle1.h / 2);

    paddle2.h = 100;
    paddle2.w = 20;
    paddle2.x = dims->width - paddle2.w;
    paddle2.y = (dims->height / 2) - (paddle2.h / 2);

    ball.w = 15;
    ball.h = 15;
    ball.x = (dims->width / 2) - (ball.w / 2);
    ball.y = (dims->height / 2) - (ball.h / 2);

//    int decorationWorkingArea = dims->height - 20;
//    SDL_Rect firstDecor;
//    firstDecor.w = 3;
//    firstDecor.x = (dims->width / 2) - (firstDecor.w / 2);
//    decorations[0] = firstDecor;
//    for (int i = 0)
//
//        decorations[0].x =


}

Game::Manager::~Manager() {
    delete components->screenController;
}

void Game::Manager::setTime(Game::Time::Time *time) {
    if (time) {
        components->timeController = time;

        if (components->timeController->errorIsSet()) {
            std::string warningMessage = "A time manager with an existing error controller has overridden the previous error manager. Possible memory leak.";
            ConsoleMessage::WARN(warningMessage);
        }
        components->timeController->setErrorManager(Game::getError());

    } else {
        ConsoleMessage::INFO((char *) "Using default parameters for \"Time\"");

        components->timeController = Game::Time::New(60, Game::Time::Options{Game::getError()});
    }
}

void Game::Manager::setEventManager(Game::EventManager::EventManager *eventManager) {
    if (eventManager) {
        components->eventController = eventManager;

        if (components->eventController->errorIsSet()) {
            std::string warningMessage = "EventManager manager had an error manager already, but a new one has been set. Possible memory leak.";
            ConsoleMessage::WARN(warningMessage);
        }
        components->eventController->setErrorManager(Game::getError());

    } else {
        ConsoleMessage::INFO("Using default parameters for \"EventManager\"");
        components->eventController = Game::EventManager::New(
                new Game::EventManager::EventManagerOptions(Game::getError()));

    }
}

void Game::Manager::setScreen(Game::Screen::Screen *screen) {
    if (screen) {
        components->screenController = screen;

        if (components->screenController->errorIsSet()) {
            std::string warningMessage = "New screen \"";
            warningMessage += screen->title;
            warningMessage += " \" had an error manager already existing, but a new one has been set.";
            ConsoleMessage::WARN(warningMessage);
        }
        components->screenController->setErrorManager(Game::getError());

    } else {
        ConsoleMessage::INFO((char *) "Using default parameters for \"Screen\"");
        components->screenController = Game::Screen::New("New Game",
                                                         800,
                                                         600,
                                                         Game::Screen::ScreenOptions{Game::getError()}
        );
    }
}

void
Game::Manager::setComponents(Game::Screen::Screen *screen, Game::Time::Time *time, Game::EventManager::EventManager *event) {
    setScreen(screen);
    setTime(time);
    setEventManager(event);

}

Game::Time::Time *Game::Components::getTimeController() {
    return timeController;
}

Game::EventManager::EventManager *Game::Components::getEventController() {
    return eventController;
}

Game::Screen::Screen *Game::Components::getScreenController() {
    return screenController;
}
