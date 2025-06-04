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


}


