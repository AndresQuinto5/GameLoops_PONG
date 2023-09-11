#ifndef PONGPROJECT_COORDINATES_H
#define PONGPROJECT_COORDINATES_H

#include <SDL2/SDL.h>

namespace Game {

    struct Coordinates {
        int x;
        int y;

        explicit Coordinates(int p_x, int p_y) {
            x = p_x;
            y = p_y;
        }

        static Coordinates from(Coordinates toCopy) {
            return Coordinates(toCopy.x, toCopy.y);
        }

        /**
         * Checks if a point is to the left of this point
         * @example
         *
         *          ^
         *          |
         *          |
         *          |
         *----------|----------------------------------------> x
         *          |
         *          |   p .(x1, y)          this . (x2, y)
         *          |
         *          v y
         *
         * p.x = x1
         * this.x = x2 where x2 > x1
         * p.x < this.x
         *
         * @param point
         * @return True if it is. False if not.
         */
        bool isToTheRightOf(Coordinates point) const;

        /**
         * Checks if a point is to the left of this point
         * @example
         *
         *          ^
         *          |
         *          |
         *          |
         *----------|----------------------------------------> x
         *          |
         *          |   p .(x1, y)          this . (x2, y)
         *          |
         *          |
         *          v y
         *
         * p.x = x2 where x2 > x1
         * this.x = x1
         * this.x < p.x
         *
         * @param point
         * @return True if it is. False if not.
         */
        bool isToTheLeftOf(Coordinates point) const;

        /**
         * Checks if a point is to the left of this point
         * @example
         *
         *          ^
         *          |
         *          |
         *          |
         *----------|----------------------------------------> x
         *          | this . (x, y2)
         *          |
         *          |    p .(x, y1)
         *          |
         *          |
         *          v y
         *
         *
         * p.y = y1
         * this.y = y2 where y2 < y1
         * p.y > this.y
         *
         * @param point
         * @return True if it is. False if not.
         */

        bool isOnTopOf(Coordinates point) const;

        /**
         * Checks if a point is to the left of this point
         * @example
         *
         *          ^
         *          |
         *          |
         *          |
         *----------|----------------------------------------> x
         *          |       p . (x, y2)
         *          |
         *          |    this .(x, y1)
         *          |
         *          |
         *          v y
         *
         *
         * p.y = y2
         * this.x = y1 where y1 > y2
         * p.x < this.x
         *
         * @param point
         * @return True if it is. False if not.
         */
        bool isUnderneathOf(Coordinates point) const;

        bool isSame(Coordinates point) const;

        bool isSameX(Coordinates point) const;

        bool isSameY(Coordinates point) const;
    };

    struct Line {
        Coordinates from;
        Coordinates to;

        Line(int p_from_x, int p_from_y, int p_to_x, int p_to_y) :
                Line(Coordinates(p_from_x, p_from_y), Coordinates(p_to_x, p_to_y)) {}

        Line(Coordinates p_from, Coordinates p_to) :
                from(Coordinates::from(p_from)),
                to(Coordinates::from(p_to)) {}

        bool isToTheRightOf(Coordinates point) const;

        bool isToTheLeftOf(Coordinates point) const;

        bool isOverOf(Coordinates point) const;

        bool isUnderOf(Coordinates point) const;

        bool isToTheRightOf(Line line) const;

        bool isToTheLeftOf(Line line) const;

        bool isOnTopOf(Line line) const;

        bool isUnderneathOf(Line line) const;

    };

    struct Corners {
        Coordinates topLeft;
        Coordinates topRight;
        Coordinates bottomLeft;
        Coordinates bottomRight;

        explicit Corners(SDL_Rect rect) :
                topLeft(Coordinates(rect.x, rect.y)),
                topRight(Coordinates(topLeft.x + rect.w, topLeft.y)),
                bottomLeft(Coordinates(topLeft.x, topLeft.y + rect.h)),
                bottomRight(Coordinates(topRight.x, topRight.y + rect.h)) {}

        Corners(int p_x, int p_y, int p_width, int p_height) :
                topLeft(p_x, p_y),
                topRight(p_x + p_width, p_y),
                bottomLeft(p_x, p_y + p_height),
                bottomRight(p_x + p_width, p_y + p_height) {}
    };

    struct Sides {
        Line left;
        Line right;
        Line bottom;
        Line top;

        explicit Sides(Corners corners) :
                left(Line(corners.topLeft, corners.bottomLeft)),
                top(Line(corners.topLeft, corners.topRight)),
                right(Line(corners.topRight, corners.bottomRight)),
                bottom(Line(corners.bottomLeft, corners.bottomRight)) {}
    };

    struct rectangularDimensions {
        Corners corners;
        Sides sides;

        int width;
        int height;

        explicit rectangularDimensions(SDL_Rect rect) :
                width(rect.w),
                height(rect.h),
                corners(rect),
                sides(corners) {};


        rectangularDimensions(int p_x, int p_y, int p_width, int p_height) :
                width(p_width),
                height(p_height),
                corners(p_x, p_y, p_width, p_height),
                sides(corners) {
        }

        bool contains(Coordinates point) const {
            return containsY(point) && containsX(point);
        }


        bool containsY(Coordinates point) const {
            return sides.top.isOverOf(point) && sides.bottom.isUnderOf(point);
        }

        bool containsX(Coordinates point) const {
            return sides.left.isToTheLeftOf(point) && sides.right.isToTheRightOf(point);
        }
    };

} // Game

#endif //PONGPROJECT_COORDINATES_H
