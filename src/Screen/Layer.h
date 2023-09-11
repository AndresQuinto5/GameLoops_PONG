
#ifndef PONGPROJECT_LAYER_H
#define PONGPROJECT_LAYER_H

#include <vector>
#include <string>
#include "../Entity/Entity.h"

namespace Game {
    struct LayerOptions {
        std::string opt_layerName;

    };
    class Layer {
    public:
        std::vector<Game::Entity *> layerEntities;
        std::string layerName;

        Layer(std::string layerName);

        ~Layer();
    };

} // Game

#endif //PONGPROJECT_LAYER_H
