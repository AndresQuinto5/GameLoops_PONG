
#include "Screen.h"
#include "../Console/ConsoleMessage.h"
#include <SDL2/SDL.h>
#include "../Coords/Coordinates.h"
#include "../Misc.h"
#include "../Structs/Geometry.h"
#include "../Structs/Borrowed.h"

using namespace std;

namespace Game::Screen {

    int sx = 50;
    int sy = 50;
//    int sx = -0;
//    int sy = 0;

    void Screen::init() {
        if (!SDL_Init(SDL_INIT_EVERYTHING)) {
            window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dims->getWidth(),
                                      dims->getHeight(), 0);
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (!(window && renderer)) {
                setNewError("Could not initialize window or renderer", FATAL);
            }
        } else {
            setNewError("Could not initialize SDL", PANIC);
        }
    }

    Screen::Screen(string &p_title, Borrowing<Geometry::Dimensions *> *p_dims, Borrowing<ScreenOptions *> *p_options)
            : ErrorSupport(p_options->get()->error, "Screen") {
        title = move(p_title);
        masterError = p_options->get()->error;
        dims = Geometry::Dimensions::New(p_dims->get()->getWidth(), p_dims->get()->getHeight());
        window = nullptr;
        renderer = nullptr;

        delete p_dims;
        delete p_options;
    }

    Screen::~Screen() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();

        delete dims;
    };

    Screen::Screen(string &p_title, int p_width, int p_height, Borrowing<ScreenOptions *> *options)
            : ErrorSupport(
            options->get()->error, "Screen") {

        auto opts = options->get()->error;
        title = move(p_title);
        masterError = options->get()->error;
        dims = Geometry::Dimensions::New(p_width, p_height);
        window = nullptr;
        renderer = nullptr;

        delete options;
    }

    void Screen::update(SDL_Rect &ball, SDL_Rect &paddle1, SDL_Rect &paddle2, float dT) {

        /**
        *
        *  (0, 0)                    (SCREEN_WIDTH, 0)
        *  ____________________________________
        * |                                    |
        * |                                    |
        * |                                    |
        * |                                    |
        * |____________________________________|
        * (0, SCREEN_HEIGHT)      (SCREEN_WIDTH, SCREEN_HEIGHT)
        *
        */

        /**
         * Colliders
         */

        auto ballCollider = rectangularDimensions(ball);
        auto paddle1Collider = rectangularDimensions(paddle1);
        auto paddle2Collider = rectangularDimensions(paddle2);
        auto screenCollider = rectangularDimensions(0, 0, dims->getWidth(), dims->getHeight());

        /**
         * Screen
         */
        // A point of the ball is not contained in the screen
        if (!screenCollider.contains(ballCollider.corners.topLeft) ||
            !screenCollider.contains(ballCollider.corners.bottomRight)) {

            // The ball is trying to get out of the screen via the Y axis
            if (!screenCollider.containsY(ballCollider.corners.topLeft) ||
                !screenCollider.containsY(ballCollider.corners.bottomLeft)) {

                Math::invert(sy);
                sy *= 1.1f;
            }

            // ATTENTION. THIS FAILS IF BOTH POINTS ARE OUTSIDE THE SCREEN AT THE SAME TIME, AND THE GAME WILL THINK BOTH PLAYERS WON.
            // TO FIX IT: Make it so that it checks if x <= 0 or x >= SCREEN_WIDTH instead. Nevertheless, the current solution is more elegant.
            // The ball is trying to get out of the screen via the X axis (win-lose condition)
            // Right side wins
            if (screenCollider.sides.left.isToTheRightOf(ballCollider.sides.right)) {
                ConsoleMessage::INFO("Right Player Wins!");
                setNewError("Game Ended. Right Player won.", ERROR_TYPE::FATAL);
            }
            // Left side wins
            if (screenCollider.sides.right.isToTheLeftOf(ballCollider.sides.left)) {
                ConsoleMessage::INFO("Left Player Wins!");
                setNewError("Game Ended. Left Player won.", ERROR_TYPE::FATAL);
            }
        }

        /**
         * Paddle
         */
        // The ball hits the paddle

        /**
         * (0, 0) (paddle->w, 0)
         *           _________
         *          |        |      Outside when:
         *          |        |          - ball->x           >   paddle->x + paddle->w
         *          |        |          - ball->y           >   paddle->y + paddle->h
         *          |        |          - ball->y + ball->h <   paddle->y
         *          |        |      ---------
         *          |        |      |       |
         *          | paddle |      | Ball  |
         *          |        |      |       |
         *          |        |      ---------
         *          |        |
         *          |        |
         *          |        |
         *          |        |
         *          |________|
         *   (0, paddle->h)  (paddle->w, paddle->h)
         *
         *
         *           _________
         *          |        |
         *          |        |
         *          |     ---------
         *          |     |       |
         *          | padd| Ball  |
         *          |     |       |
         *          |     ---------
         *          |        |
         *          |        |
         *          |        |              Inside when:
         *          |        |                  - paddle->y + paddle->h     >   ball->y     >   paddle->y
         *          |________|                  - paddle->x                 <   ball->x     <   paddle->x + paddle->w
         *
         */


        // The ball collided against a paddle
        if (// Left Paddle
                paddle1Collider.contains(ballCollider.corners.topLeft) ||
                paddle1Collider.contains(ballCollider.corners.bottomLeft) ||
                // Right Paddle
                paddle2Collider.contains(ballCollider.corners.topRight) ||
                paddle2Collider.contains(ballCollider.corners.bottomRight)) {

            Game::Math::invert(sx);
            sx *= 1.1f;

        }

        ball.x += sx * dT;
        ball.y += sy * dT;

        ConsoleMessage::DEBUG(
                "X: " + std::to_string(ball.x) +
                " Y: " + std::to_string(ball.y) +
                " dT: " + std::to_string(dT));

    }

    void Screen::render(SDL_Rect &ball, SDL_Rect &paddle1, SDL_Rect &paddle2) const {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        SDL_RenderFillRect(renderer, &ball);
        SDL_RenderFillRect(renderer, &paddle1);
        SDL_RenderFillRect(renderer, &paddle2);

        SDL_RenderPresent(renderer);
    }


    Screen *New(string title, Borrowing<Geometry::Dimensions *> *dimensions, Borrowing<ScreenOptions *> *options) {
        return new Screen(title, dimensions, options);
    }

    Screen *New(const char *title, int width, int height, Borrowing<ScreenOptions *> *options) {
        auto borrowed = borrowedVar<Geometry::Dimensions *>(Geometry::Dimensions::New(width, height));
        return New(title, borrowed, options);
    }

    ScreenOptions::ScreenOptions(StandardError *error) : AllowError(error) {

    }

    ScreenOptions::ScreenOptions() : AllowError(nullptr) {

    }
}