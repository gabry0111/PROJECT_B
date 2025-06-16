#include <SFML/Graphics.hpp>
#include "enum_objects.hpp"
#include "map.hpp"
#include "rules.hpp"
#include "objects.hpp"
#include <iostream>
#include <algorithm>
using Position = std::pair<std::size_t, std::size_t>;

namespace Baba_Is_Us{

    int parseToEnums(int tileID) {
        int result {};
        switch(tileID) {
        case 0: result = 0;
            break;
        case 1: 
        case 2:
        case 3: 
        case 4: 
        case 5:
        case 6: 
        case 7:
        case 8: result = 1;             // baba's sprites
            break;
        case 9: 
        case 10: 
        case 11: 
        case 12: result = tileID - 6;   // other NOUN_TYPE objects
            break;
        case 13: 
        case 14: 
        case 15: 
        case 16: 
        case 17: 
        case 18: 
        case 19: 
        case 20: 
        case 21:
        case 22:
        case 23:
        case 24:
        case 25: result = tileID - 4;   // text blocks
            break;
        default: 
            std::cerr << tileID << '\n';
            throw (std::runtime_error("in level.txt not given a valid int"));
            break;
        }
        return result;
    }

    Map::Map(std::string_view filename)  {
        std::ifstream map_file {filename.data()}; //comincia dall'inizio di file.txt bidimensionale
        if (! map_file){
                std::cerr << "Error! can't open level";
            }
        int value {};
        for (std::size_t iii=0; iii < MapSize::height * MapSize::width; ++iii) {
            map_file >> value;
            std::cerr << value;
            
            if(value > +Type::ICON_NOUN_TYPE && value != +Type::VERB_TYPE && value != +Type::PROPERTY_TYPE){
                //initialize block tile value
                m_grid[1][iii/MapSize::height][iii%MapSize::width] = +Type::Block;
                m_grid[0][iii/MapSize::height][iii%MapSize::width] = value;

                //initialize block object in tile
                std::vector<Type> current{};
                current.emplace_back(Type::Block);
                current.emplace_back(intToType(parseToEnums(value)));
                m_objects[iii/MapSize::height][iii%MapSize::width] = current;
            }
            else{
                //initialize tile value
                m_grid[1][iii/MapSize::height][iii%MapSize::width] = value;
                m_grid[0][iii/MapSize::height][iii%MapSize::width] = value;

                //initialize object in tile
                std::vector<Type> current{};
                current.emplace_back(intToType(parseToEnums(value)));
                m_objects[iii/MapSize::height][iii%MapSize::width] = current;
            }
            
            
        }
        std::cout<<"\nno gay\n";
        for (auto& col : m_objects) {
            for (auto& row : col) {
                std::cerr << +row.getTypes()[0] << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << "----------------------------\n";
        for (auto& col : m_grid[0]) {
            for (auto& row : col) {
                std::cerr << row << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << "----------------------------\n";
        for (auto& col : m_grid[1]) {
            for (auto& row : col) {
                std::cerr << row << ' ';
            }
            std::cerr << '\n';
        }
    }

    const std::array<MapGrid2D, MapSize::depth>& Map::getm_grid() {
        return m_grid;
    }
    std::array<MapGrid2D, MapSize::depth>& Map::accessm_grid() {
        return m_grid;
    }
    const std::array<std::array<Objects, MapSize::height>, MapSize::width>& Map::getm_objects(){
        return m_objects;
    }
    
    void Map::setTextures(){
        for (auto& path : tilePaths) {
            sf::Texture texture;
            if (!texture.loadFromFile(path)) { //il bastardo non vuole string_view
                std::cerr << "Failed to load " << path << "\n";
                continue;
            }
            textures.emplace_back(texture);
            }
        std::cerr << nth_frame << ' ' << textures.size() << ' ' << '\n'; // tutte 25, testato
    }
    
    

    void Map::setSprites(){
        // converti le path in sprites
        sf::Sprite sprite;
        
        for (const auto& texture : textures) {
            //metto la texture sullo sprite
            sprite.setTexture(texture);

            sprite.setTextureRect({0, 0, MapSize::TILE_SIZE, MapSize::TILE_SIZE}); //snip snip 32x32

            //non riesco a capire counter -> 4
            tileSprites.emplace_back(sprite); // alla fine avrà level.size() elementi, ognuno con una sprite (<- quella che si beve?)

        }
        std::cerr << tileSprites.size() << " loaded sprites\n";
    }
    // SE ESISTE ALMENO UNA NON ANIMAZIONE, SIAMO FOTTUTI
    void Map::redraw(sf::Clock &clock){

        if (clock.getElapsedTime().asMilliseconds() >= MapSize::FRAME_TIME_MS) {

            //change the current frame of every individual texture
            //it could be different across textures if we add more detailed spritesheets or more frames per animation
            nth_frame = (nth_frame + 1) % MapSize::FRAMES_PER_ANIMATION; //le animazioni sono sempre composte da 3 frame

            clock.restart();
        }
        //resize and draw
        for (std::size_t i{}; i < tileSprites.size(); ++i) {
            tileSprites[i].setTextureRect({nth_frame * MapSize::TILE_SIZE, nth_frame, MapSize::TILE_SIZE, MapSize::TILE_SIZE});
        }
    }

    std::vector<sf::Sprite> Map::getTileSprites(){
        return tileSprites;
    }
    
    const sf::Sprite& Map::getWhichSpriteIsInPosition(Position& position){
        std::size_t index {position.second * MapSize::width + position.first};
        return tileSprites[index];
    }


    void Map::Reset(const std::array<std::array<int,MapSize::height>, MapSize::width> &map_grid) { 
        // static_assert (MapSize::height * MapSize::width == map_grid.size() * map_grid[0].size() && "Map::Reset(): sizes not equal");
        if(MapSize::height * MapSize::width != m_grid.size())
            throw std::runtime_error("Map::Reset(): sizes not equal");

        std::size_t iii{};
        for (auto& rows : map_grid) {
            for (auto& eee : rows) {
                if(+(m_objects[iii/MapSize::height][iii%MapSize::width].getTypes()[0]) != eee) //se il NOUN_TYPE dell'oggetto nella mappa != corrispondente int di new_grid_map
                    m_objects[iii/MapSize::height][iii%MapSize::width].getTypes()[0] = static_cast<Type>(eee);
                ++iii;
            }
        }
    }

    Objects& Map::At(std::size_t y, std::size_t x) 
    {
        return m_objects[y][x];
    }
    const Objects& Map::At(std::size_t y, std::size_t x) const
    {
        return m_objects[y][x];
    }

    std::vector<Position> Map::getPositions(Type type) const {
        std::vector<Position> positions_with_type {};
        for (std::size_t x = 0; x < MapSize::height; ++x){
            for (std::size_t y = 0; y < MapSize::width; ++y){
                if (m_objects[y][x].objectHasType(type)){
                    std::cout<<"daje ";
                    positions_with_type.emplace_back(Position(x, y));
                    std::cout<<"roma\n";
                }
            }
        }
        return positions_with_type;
    }

    bool Map::isWithinBoundary(std::size_t x, std::size_t y) const {
        return (x <= MapSize::width - 1) || (y <= MapSize::height - 1);
    }

    void Map::addObject(Position position, Type type) {
        m_objects[position.second][position.first].addType(type);
    }
    void Map::resetObject(Position position) {
        m_objects[position.second][position.first] = {};
    }


} //anmespace Baba_Is_Us