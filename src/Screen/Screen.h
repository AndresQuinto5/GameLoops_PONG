
#ifndef PONGPROJECT_SCREEN_H
#define PONGPROJECT_SCREEN_H

#include <SDL.h>
#include "../Error/Error.h"
#include "../Structs/Geometry.h"
#include "../Structs/Borrowed.h"
#include <string>

using namespace Paradigm;
using namespace std;
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

namespace Game::Screen {

    // Entities.
    // TODO: Make these into individual entities



    struct ScreenOptions : AllowError {

        explicit ScreenOptions(StandardError *error);
        ScreenOptions();
        ~ScreenOptions() = default;
    };

    /**
     * Takes care of the screen. Renders a window.
     */
    class Screen : public ErrorSupport {
    public:
        void update(SDL_Rect &ball, SDL_Rect &paddle1, SDL_Rect &paddle2, float dT);

        void render(SDL_Rect &ball, SDL_Rect &paddle1, SDL_Rect &paddle2) const;

        void init();

        Screen(string &title, int width, int height, Borrowing<ScreenOptions *> *options);

        Screen(string &title, Borrowing<Geometry::Dimensions *> *dims, Borrowing<ScreenOptions *> *p_options);

        ~Screen();

        string title;
        SDL_Window *window;
        SDL_Renderer *renderer;
        Geometry::Dimensions *dims;
    };

    Screen *New(std::string title = "My Game",
                Borrowing<Geometry::Dimensions *> * = borrowedVar<Geometry::Dimensions *>(
                        Geometry::Dimensions::New(SCREEN_WIDTH, SCREEN_HEIGHT)),
                Borrowing<ScreenOptions *> * = borrowedVar<ScreenOptions *>(nullptr));

    Screen *New(std::string title = "My Game",
                int width = SCREEN_WIDTH,
                int height = SCREEN_HEIGHT,
                Borrowing<ScreenOptions *> * = borrowedVar<ScreenOptions *>(nullptr));

} // Game

#endif //PONGPROJECT_SCREEN_H
