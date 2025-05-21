#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "map.hpp"
/* Avuta la mappa del livello corrente, verifica quali azioni sono possibili:
- verifica le proprietà di ciascun oggetto (sarà fatto nel Main Loop)
- resetta il livello se PlayState è Invalid
- gestisce il movimento del Player
- gestisce il movimento degli oggetti 
- 
*/
namespace Baba_Is_Us{

    void Game::update(sf::RenderWindow &window){
        sf::Event event;

            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
            }
    }
    void Game::render(sf::RenderWindow &window, TileMap &map){
        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }
}
