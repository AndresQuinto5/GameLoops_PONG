
#ifndef PONGPROJECT_ENTITY_H
#define PONGPROJECT_ENTITY_H

#include <SDL.h>

namespace Game {
    struct EntityDimensions {
        int width;
        int height;

        EntityDimensions(int p_width, int p_height) {
            width = p_width;
            height = p_height;
        }
    };

    struct EntityPosition {
        int y;
        int x;

        EntityPosition(int p_x, int p_y) {
            x = p_x;
            y = p_y;
        }
    };

    class Entity {
        SDL_Rect self;
        EntityDimensions* entityDimensions;
        EntityPosition* entityPosition;
        Entity(int p_width, int p_height, int p_x, int p_y);
        ~Entity();
    };

} // Game

#endif //PONGPROJECT_ENTITY_H
