#include <SFML/Graphics.hpp>
#include "enum_objects.hpp"
#include "map.hpp"
#include "rules.hpp"
#include "objects.hpp"
#include <iostream>
using Position = std::pair<std::size_t, std::size_t>;

namespace Baba_Is_Us{

    Map::Map(std::string_view filename)  {
        std::ifstream map_file {filename.data()}; //comincia dall'inizio di file.txt bidimensionale
        int value{};
        std::cout<<"gay\n";
        for (std::size_t iii=0; iii < MapSize::height * MapSize::width; ++iii) {
            map_file >> value;
            std::cerr << "ciao\n";
            
            
            if(value > +Type::ICON_NOUN_TYPE && value != +Type::VERB_TYPE && value != +Type::PROPERTY_TYPE){
                std::cerr << "if e solo if -1-1-1-1\n";
                std::vector<Type> current{};
                std::cerr << "if e solo if 00000\n";
                m_grid[1][iii/MapSize::height][iii%MapSize::width] = +Type::Block;
                std::cerr << "if e solo if 050505\n";
                m_grid[0][iii/MapSize::height][iii%MapSize::width] = value;
                std::cerr << "if e solo if\n";
                current.emplace_back(Type::Block);
                std::cerr << "if e solo if 22222\n";
                current.emplace_back(intToType(value));
                std::cerr << "if e solo if 33333 \n";
                m_objects[iii/MapSize::height][iii%MapSize::width] = current;
            }
            else{
                std::cerr << "else \n";
                std::vector<Type> current{};
                m_grid[1][iii/MapSize::height][iii%MapSize::width] = value;
                m_grid[0][iii/MapSize::height][iii%MapSize::width] = value;
                current.emplace_back(intToType(value));
                m_objects[iii/MapSize::height][iii%MapSize::width] = current;
                std::cerr << "else e solo else\n";
            }
            
            
        }
        std::cout<<"no gay\n";
       
    }

    

    const std::array<MapGrid2D, MapSize::depth>& Map::getm_grid() {
        return m_grid;
    }
    
    void Map::setTextures(){
        for (auto& path : tilePaths) {
            sf::Texture texture;
            if (!texture.loadFromFile(path)) {
                std::cerr << "Failed to load " << path << "\n";
                continue;
            }
            int width = static_cast<int>(texture.getSize().x); // 72
            int frames = std::max(1, width / MapSize::TILE_SIZE);       // 3
            textures.emplace_back(texture);
            frameCounts.emplace_back(frames);
            current_frame_per_tile_ID.push_back(0); // ogni tile ID partirà dal frame n° 0
        }
    }

    void Map::setSprites(){
        // converti le tileID in sprites

        for (std::size_t i = 0; i < MapSize::n_tiles; ++i) {
            int tileID {m_grid[0][i / MapSize::height][i % MapSize::width]}; // typing convenience
            if (tileID < 0 || tileID >= static_cast<int>(textures.size())) continue;
            sf::Sprite sprite;
            //metto la texture sullo sprite
            sprite.setTexture(textures[static_cast<std::size_t>(tileID)]);

            sprite.setTextureRect({0, 0, MapSize::TILE_SIZE, MapSize::TILE_SIZE}); //snip snip 32x32

            int x = (static_cast<int> (i) % MapSize::width) * MapSize::TILE_SIZE;    // = 0, 32, 64, ... 255*32 
            int y = (static_cast<int> (i) / MapSize::height) * MapSize::TILE_SIZE;
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));

            //non riesco a capire counter -> 4
            tileSprites.emplace_back(sprite); // alla fine avrà level.size() elementi, ognuno con una sprite (<- quella che si beve?)

        }
    }

    void Map::redraw(sf::Clock &clock){
        //
        if (clock.getElapsedTime().asMilliseconds() >= MapSize::FRAME_TIME_MS) {

            //change the current frame of every individual texture
            //it could be different across textures if we add more detailed spritesheets or more frames per animation
            for (std::size_t i{}; i < frameCounts.size(); ++i) {
                if (frameCounts[i] > 1) { // se in i c'è un'animazione
                    current_frame_per_tile_ID[i] = (current_frame_per_tile_ID[i] + 1) % frameCounts[i]; //frameCounts[i] sarà sempre 3 se è animazione, quindi prova a calcolare
                }
            }
            clock.restart();
        }
        //resize and draw
        for (std::size_t i{}; i < tileSprites.size(); ++i) {
            int tileID {m_grid[0][i/MapSize::height][i%MapSize::width]};
            int frame = current_frame_per_tile_ID[static_cast<size_t> (tileID)];
            tileSprites[i].setTextureRect({frame * MapSize::TILE_SIZE, 0,MapSize::TILE_SIZE, MapSize::TILE_SIZE});
            
        }
    }

    std::vector<sf::Sprite> Map::getTileSprites(){
        return tileSprites;
    }
    
    sf::Sprite Map::getWhichSpriteIsInPosition(Position& position){
        std::size_t index {position.second * MapSize::width + position.first};
        sf::Sprite sprite {tileSprites[index]};
        return sprite;
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
                std::cout<<"boh\n";
                if (m_objects[y][x].objectHasType(type)){
                    std::cout<<"daje ";
                    positions_with_type.emplace_back(Position(x, y));
                    std::cout<<"roma\n";
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

} //anmespace Baba_Is_Us