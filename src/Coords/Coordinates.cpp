#include "Coordinates.h"

namespace Game {

    /**
     * Checks if a point is to the left
     * @param point
     * @return
     */
    bool Line::isToTheRightOf(Coordinates point) const {
        return from.isToTheRightOf(point) && to.isToTheRightOf(point);
    }

    bool Line::isToTheLeftOf(Coordinates point) const {
        return from.isToTheLeftOf(point) && to.isToTheLeftOf(point);
    }

    bool Line::isOverOf(Coordinates point) const {
        return from.isOnTopOf(point) && to.isOnTopOf(point);
    }

    bool Line::isUnderOf(Coordinates point) const {
        return from.isUnderneathOf(point) && to.isUnderneathOf(point);
    }


    bool Line::isToTheRightOf(Line line) const {
        return isToTheRightOf(line.from) && isToTheRightOf(line.to);;
    }

    bool Line::isToTheLeftOf(Line line) const {
        return from.isToTheLeftOf(line.from) && to.isToTheLeftOf(line.to);
    }

    bool Line::isOnTopOf(Line line) const {
        return from.isOnTopOf(line.from) && to.isOnTopOf(line.to);
    }

    bool Line::isUnderneathOf(Line line) const {
        return from.isUnderneathOf(line.from) && to.isUnderneathOf(line.to);
    }


    bool Coordinates::isToTheRightOf(Coordinates point) const {
        return point.x < x;
    }

    bool Coordinates::isToTheLeftOf(Coordinates point) const {
        return x < point.x;
    }

    bool Coordinates::isOnTopOf(Coordinates point) const {
        return y < point.y; // These cords are inverted
    }

    bool Coordinates::isUnderneathOf(Coordinates point) const {
        return point.y < y; // These cords are inverted
    }

    bool Coordinates::isSame(Coordinates point) const {
        return isSameX(point) && isSameY(point);
    }

    bool Coordinates::isSameX(Coordinates point) const {
        return point.x == x;
    }

    bool Coordinates::isSameY(Coordinates point) const {
        return point.y == y;
    }
} // Game