
#include "Entity.h"

namespace Game {
    Entity::Entity(int p_width, int p_height, int p_x, int p_y): self() {
        entityDimensions = new EntityDimensions(p_width, p_height);
        entityPosition = new EntityPosition(p_x, p_y);

        self.h = entityDimensions->height;
        self.w = entityDimensions->width;
        self.x = entityPosition->x;
        self.y = entityPosition->y;
    }

    Entity::~Entity() {
        delete entityPosition;
        delete entityDimensions;
    }
} // Game