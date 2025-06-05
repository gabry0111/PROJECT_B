#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "game.hpp"
#include "rules.hpp"
#include <iostream>
using Position = std::pair<std::size_t, std::size_t>;

namespace Baba_Is_Us{


    Map::Map(){
    m_objects.reserve(MapSize::n_tiles);
    //std::cerr<< m_objects.size() << m_objects[50].objectHasType(Type::Void); //testato: funziona

    };
    
    constexpr void Map::load(const std::vector<std::vector<int>>& new_map_grid) {
        assert(MapSize::height * MapSize::width == new_map_grid.size() && "Map::load(): sizes not equal");
        if(MapSize::height * MapSize::width != new_map_grid.size()) throw std::runtime_error("Map::load() sizes not equal"); 
    
        for (auto& rows : new_map_grid) {
            for (auto& eee : rows) {
                m_objects.emplace_back(std::vector<Type>{static_cast<Type>(eee)});

    }

    constexpr void Map::loadAndReset(std::vector<std::vector<int>>& map_grid) {
        Type value {};
        for(std::size_t iii{}; iii<MapSize::height; ++iii) {
            for(std::size_t jjj{}; jjj<MapSize::width; ++jjj) {
                value = static_cast<Type>(map_grid[iii][jjj]);
                if(value != m_objects[iii * jjj].getTypes()[0]) m_objects[iii * MapSize::width * jjj].getTypes()[0] = value;

            }
        }
    }
    //CREARE UNA FUNZIONE "(const e non const?) Objects& At(std::pair<int,int> position) (const e non const?)" CHE RESTITUISCE CHE OBJECT C'è IN QUEL PUNTO
    Objects& Map::At(Position position){
        return m_objects[position.first*16 + position.second];
    }
    //CREARE UNA FUNZIONE "void removeObject(std::pair<int,int>, ObjectType type)" CHE CANCELLA QUELLA ICON GRAFICA DELL'OGGETTO SULLA MAPPA
    /*
    void removeObject(Position position, Type type){
        //idk yet, definiamo map_grid prima
    }
        */


    
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

