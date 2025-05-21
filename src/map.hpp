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
    
class TileMap: public sf::Drawable, public sf::Transformable{
    public:
        

        bool load(const std::string&, sf::Vector2u, const int*, unsigned int, unsigned int);

    private:
        virtual void draw(sf::RenderTarget&, sf::RenderStates&) const;

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
};

}

#endif