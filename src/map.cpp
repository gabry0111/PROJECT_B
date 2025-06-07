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

    constexpr Map::Map(){
    m_objects.reserve(MapSize::n_tiles);
    //std::cerr<< m_objects.size() << m_objects[50].objectHasType(Type::Void); //testato: funziona

    }
    
    void Map::load(const std::vector<std::vector<int>>& new_map_grid) {
        static_assert(MapSize::height * MapSize::width == new_map_grid.size() && "Map::load(): sizes not equal");
        if(MapSize::height * MapSize::width != new_map_grid.size())
            throw std::runtime_error("Map::load() sizes not equal"); // perché lo stesso errore due volte?
    
        for (auto& rows : new_map_grid) {
            for (auto& eee : rows) {
                m_objects.emplace_back(std::vector<Type>{static_cast<Type>(eee)});
            }
        }
    }
    
    void Map::Reset(const std::array<std::array<int,16>,16> new_map_grid) { 
        static_assert (MapSize::height * MapSize::width == new_map_grid.size() * new_map_grid[0].size() && "Map::Reset(): sizes not equal");
        if(MapSize::height * MapSize::width != new_map_grid.size()) throw std::runtime_error("Map::Reset(): sizes not equal");

        std::size_t iii{};
        for (auto& rows : new_map_grid) {
            for (auto& eee : rows) {
                if(+(m_objects[iii].getTypes()[0]) != eee) //se il NOUN_TYPE dell'oggetto nella mappa != corrispondente int di new_grid_map
                    m_objects[iii].getTypes()[0] = static_cast<Type>(eee);
                ++iii;
            }
        }
    }

    
    const Objects& Map::At(Position position) const
    {
        return m_objects.at(position.second * MapSize::width + position.first); // disegnatelo, è più semplice vederlo
    }


    std::vector<Position> Map::getPositions(Type type) const {
        std::vector<Position> positions_with_type {};
        for (std::size_t x = 0; x < MapSize::height; ++x){
            for (std::size_t y = 0; y < MapSize::width; ++y){
                if (At(Position(x, y)).objectHasType(type)){
                    positions_with_type.emplace_back(Position(x, y));
                }
            }
        }
        return positions_with_type;
    }


    constexpr void Map::AddObject(Position position, Type type) {
        m_objects.at(position.second * MapSize::width + position.first).add(type);
    }
    constexpr void Map::RemoveObject(Position position, Type type) {
        m_objects.at(position.second * MapSize::width + position.first).remove(type);
    }


}

