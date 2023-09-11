

#ifndef PONGPROJECT_GAMECONTROLLER_H
#define PONGPROJECT_GAMECONTROLLER_H

#include "../Controller/Controller.h"
#include "../Time/Time.h"
#include "../Events/EventManager.h"
#include "../Screen/Screen.h"
#include "../Error/Error.h"
#include <vector>

namespace Game {
    struct ScreenParams {
        int screen_width;
        int screen_height;
        const char *title;

        ScreenParams(const char *p_title, int p_width, int p_height) :
                title(p_title), screen_width(p_width), screen_height(p_height) {};
    };


    struct InitParameters {
        int FPS;
        Game::Screen::Screen *screen;
        Game::EventManager::EventManager *event;
        Game::Time::Time *time;
    };

    struct Components {

        Game::Time::Time *timeController;
        Game::EventManager::EventManager *eventController;
        Game::Screen::Screen *screenController;

        Game::Time::Time *getTimeController();

        Game::EventManager::EventManager *getEventController();

        Game::Screen::Screen *getScreenController();
    };


    class Manager {
    public:
        SDL_Rect ball;
        SDL_Rect paddle1;
        SDL_Rect paddle2;
        std::vector<SDL_Rect> decorations;
        int numOfDecorations = 5;

        explicit Manager(InitParameters params);

        ~Manager();

        void init();

        void setup();


        void runLoop();


    private:
        Components *components;

        void setComponents(Game::Screen::Screen *, Game::Time::Time *, Game::EventManager::EventManager *);

        void setScreen(Game::Screen::Screen *);

        void setTime(Game::Time::Time *);

        void setEventManager(Game::EventManager::EventManager *);


    };

}


#endif //PONGPROJECT_GAMECONTROLLER_H
