#ifndef GAME_HPP
#define GAME_HPP
#include "enum_objects.hpp"


namespace Baba_Is_Us{
    
    class Game {
        public:
            Game() = default;
            void update(sf::RenderWindow &);
            void render(sf::RenderWindow &, std::vector<sf::Sprite>);
            Objects getObject(std::pair<int, int>);
            bool movement_check(Map, std::pair<int, int>, Direction); // aggiunto che riceva anche la mappa per controllarne gli objects
            void rotate(std::pair<int, int>, Direction);
            void movement(Map, std::pair<int, int>, Direction);
        };
}

#endif