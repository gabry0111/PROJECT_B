#ifndef MAP.HPP
#define MAP.HPP

#include "enum_objects.hpp"
//#include "objects.hpp"
#include <array>
#include <algorithm>
#include <SFML/Graphics.hpp>

/* map.cpp gestisce e conosce tutte le posizioni degli oggetti in ogni livello
- getWidth / Height
- addObjcet / remove
- getPosition //per sapere posizione di ogni oggetto e Player
- at() //per sapere la nuova posizione di ogni oggetto
- load() //in futuro se vogliamo fare lettura da file
*/

namespace Baba_Is_Us{
using position = std::pair<int,int>;
using grid = std::array<std::array<int, 16>, 16>;
class Map: sf::Drawable,  sf::Transformable{
    private : 
    grid m_level {};
    std::size_t m_width {};
    std::size_t m_length{};

    public : 
    Map() = default;
    Map(grid& level) : m_level{level} {};
    void load(const std::array<int, 16*16>&) ;

}
;

}

#endif