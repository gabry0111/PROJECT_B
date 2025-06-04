#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "game.hpp"
#include "rules.hpp"
#include <iostream>

namespace Baba_Is_Us{


    Map::Map(){
    m_objects.reserve(MapSize::width * MapSize::height);
    //std::cerr<< m_objects.size() << m_objects[50].objectHasType(Type::Void); //testato: funziona
    };

    constexpr void Map::loadAndReset(std::vector<std::vector<int>>& map_grid) {
        Type value {};
        for(std::size_t iii{}; iii<MapSize::height; ++iii) {
            for(std::size_t jjj{}; jjj<MapSize::width; ++jjj) {
                value = static_cast<Type>(map_grid[iii][jjj]);
                if(value != m_objects[iii * jjj].getTypes()[0]) m_objects[iii * MapSize::width * jjj].getTypes()[0] = value;
            }
        }
    }


}


