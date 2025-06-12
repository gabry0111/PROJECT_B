#ifndef GAME_HPP
#define GAME_HPP
#include "enum_objects.hpp"
#include "map.hpp"

using Position = std::pair<std::size_t, std::size_t>;
namespace Baba_Is_Us{
    
    class Game {
        public:
            Game() = default;
            void update(sf::RenderWindow &, Map &);
            void render(sf::RenderWindow &, std::vector<sf::Sprite>);
            Objects getObject(Position);
            bool movement_check(Map, Position, Direction); // aggiunto che riceva anche la mappa per controllarne gli objects
            bool movement_check(Map, std::vector<Position>, Direction);
            void rotate(Position, Direction);
            void movement(Map, Position, Direction);
            void movement(Map, std::vector<Position>);
        };
}

#endif