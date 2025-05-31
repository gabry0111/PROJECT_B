#ifndef GAME_HPP
#define GAME_HPP
#include "enum_objects.hpp"


namespace Baba_Is_Us{
    
    class Game {
        public:
            Game() = default;
            void update(sf::RenderWindow &);
            void render(sf::RenderWindow &, std::vector<sf::Sprite>);
        };
}

#endif