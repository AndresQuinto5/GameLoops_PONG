

#include "Misc.h"

namespace Game {
    void Math::invert(int &i) {
        i = -i;
    }

    void Math::invert(bool &i) {
        i = !i;
    }

    void Math::toggle(bool &i) {
        return invert(i);
    }
} // Game