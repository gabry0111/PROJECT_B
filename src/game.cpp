#include <SFML/Graphics.hpp>
#include <iostream>
#include "movement.hpp"
#include "game.hpp"

/* Avuta la mappa del livello corrente, verifica quali azioni sono possibili:
- verifica le proprietà di ciascun oggetto (sarà fatto nel Main Loop)
- resetta il livello se PlayState è Invalid
- gestisce il movimento del Player
- gestisce il movimento degli oggetti 
- 
*/
namespace Baba_Is_Us{
    std::pair<int, int> getPosition(){

    };
    void Game::update(sf::RenderWindow &window){

        //event handling
        sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();

                if (event.type == sf::Event::KeyPressed){
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            //std::cout<< "Esc\n";
                            window.close();
                            break;
                        case sf::Keyboard::W:
                            //movement_check(player.getPosition(), Direction::Up)
                            //movement(player.getPosition())
                            //checkRules 

                            break;
                        case sf::Keyboard::A:
                            break;
                        case sf::Keyboard::S:
                            break;
                        case sf::Keyboard::D:
                            break;
                        case sf::Keyboard::Space: 
                            //check se ha un oggetto in mano
                            //lancia oggetto
                            break;
                        default: break;
                    }

                }
            
                
            }
            
    }
    void Game::render(sf::RenderWindow &window, std::vector<sf::Sprite> sprites){
        // draw the map
        window.clear();
        for (const auto& sprite : sprites)
            window.draw(sprite);
        window.display();
    }
}
