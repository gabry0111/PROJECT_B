#include <SFML/Graphics.hpp>
#include "enum_objects.hpp"
#include "map.hpp"
#include "game.hpp"
#include "rules.hpp"
#include "objects.hpp"
#include <array>
#include <iostream>
using Position = std::pair<std::size_t, std::size_t>;

namespace Baba_Is_Us{

    Map::Map(const std::vector<std::vector<int>>& grid){
        // static_assert(MapSize::height * MapSize::width == grid.size() && "Map::load(): sizes not equal");
        if(MapSize::height * MapSize::width != grid.size())
            throw std::runtime_error("Map::load() sizes not equal"); // perché lo stesso errore due volte?
        m_objects.reserve(MapSize::n_tiles);
        //std::cerr<< m_objects.size() << m_objects[50].objectHasType(Type::Void); //testato: funziona

        for (auto& rows : grid) {
            for (auto& eee : rows) {
                m_objects.emplace_back(std::vector<Type>{static_cast<Type>(eee)}); 
                // aggiungere la logica per attributi di default 
                // e.g. Block ha per elementi [0] = Block (già presente), [1] = NOUN_TYPE, [2] = ICON_NOUN_TYPE (grafica del testo "Baba") e dopo = Push
                // e.g Flower ha [0] = Flower, [1] = Move ...
            }
        }
    } 
    
    void Map::Reset(const std::array<std::array<int,16>,16> grid) { 
        static_assert (MapSize::height * MapSize::width == grid.size() * grid[0].size() && "Map::Reset(): sizes not equal");
        if(MapSize::height * MapSize::width != grid.size())
            throw std::runtime_error("Map::Reset(): sizes not equal");

        std::size_t iii{};
        for (auto& rows : grid) {
            for (auto& eee : rows) {
                if(+(m_objects[iii/MapSize::height][iii%MapSize::width].getTypes()[0]) != eee) //se il NOUN_TYPE dell'oggetto nella mappa != corrispondente int di new_grid_map
                    m_objects[iii/MapSize::height][iii%MapSize::width].getTypes()[0] = static_cast<Type>(eee);
                ++iii;
            }
        }
    }

    
    const Objects& Map::At(std::size_t y, std::size_t x) const
    {
        return m_objects[y][x];
    }


    std::vector<Position> Map::getPositions(Type type) const {
        std::vector<Position> positions_with_type {};
        for (std::size_t x = 0; x < MapSize::height; ++x){
            for (std::size_t y = 0; y < MapSize::width; ++y){
                if (At(x, y).objectHasType(type)){
                    positions_with_type.emplace_back(Position(x, y));
                }
            }
        }
        return positions_with_type;
    }
/*
    constexpr void Map::addObject(Position position, Type type) {
        m_objects[position.second][position.first].addType(type);
    }
    constexpr void Map::resetObject(Position position) {
        m_objects[position.second][position.first] = {};
    }
*/

}

