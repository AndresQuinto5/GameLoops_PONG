
#include "Geometry.h"

namespace Game::Geometry {
    Dimensions::Dimensions(int p_width, int p_height) {
        width = p_width;
        height = p_height;
    }

    Dimensions *Dimensions::New(int p_width, int p_height) {
        return new Dimensions(p_width, p_height);
    }

    int Dimensions::getWidth() const {
        return width;
    }

    int Dimensions::getHeight() const {
        return height;
    }
} // Game