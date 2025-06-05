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
    
    constexpr void Map::load(const std::vector<std::vector<int>>& new_map_grid) {
        assert(MapSize::height * MapSize::width == new_map_grid.size() && "Map::load(): sizes not equal");
        if(MapSize::height * MapSize::width != new_map_grid.size()) throw std::runtime_error("Map::load() sizes not equal"); 
    
        for (auto& rows : new_map_grid) {
            for (auto& eee : rows) {
                m_objects.emplace_back(std::vector<Type>{static_cast<Type>(eee)});
            }
        }
    }


    
    constexpr void Map::Reset(const std::vector<std::vector<int>>& new_map_grid) { 
        assert (MapSize::height * MapSize::width == new_map_grid.size() && "Map::Reset(): sizes not equal");
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


    std::vector<Position> Map::GetPositions(Type type) const {
        std::vector<std::reference_wrapper<Position>> positions_with_type {};
        for (std::size_t x = 0; x < MapSize::height; ++x)
        {
            for (std::size_t y = 0; y < MapSize::width; ++y)
            {
                if (At(Position(x, y)).objectHasType(type))
                {
                    positions_with_type.emplace_back(Position(x, y));
                }
            }
        }
    }


    constexpr void Map::AddObject(Position position, Type type) {
        m_objects.at(position.second * MapSize::width + position.first).add(type);
    }
    constexpr void Map::RemoveObject(Position position, Type type) {
        m_objects.at(position.second * MapSize::width + position.first).remove(type);
    }


}

