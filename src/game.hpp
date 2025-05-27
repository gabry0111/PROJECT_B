#include "enum_objects.hpp"
#include "map.hpp"

namespace Baba_Is_Us{
    class Game {
        public:
            Game() = default;
            void update(sf::RenderWindow &);
            void render(sf::RenderWindow &, TileMap &);
            

        };
}

