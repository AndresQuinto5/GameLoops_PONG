#ifndef PONGPROJECT_MISC_H
#define PONGPROJECT_MISC_H

namespace Game {

    struct Math {
        static void invert(int &i) ;

        static void invert(bool &i);

        static void toggle(bool &i);
    };

} // Game

#endif //PONGPROJECT_MISC_H
