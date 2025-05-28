#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "map.hpp"
#include <iostream>
/* Avuta la mappa del livello corrente, verifica quali azioni sono possibili:
- verifica le proprietà di ciascun oggetto (sarà fatto nel Main Loop)
- resetta il livello se PlayState è Invalid
- gestisce il movimento del Player
- gestisce il movimento degli oggetti 
- 
*/
namespace Baba_Is_Us{

    void Game::update(sf::RenderWindow &window){

        //change png of every gif

        //event handling
        sf::Event event;

            while (window.pollEvent(event))
            {
                /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) window.close();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) window.close();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) window.close();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) window.close();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) window.close();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) window.close();
                */
                if (event.type == sf::Event::Closed) window.close();

                if (event.type == sf::Event::KeyPressed){
                    
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            //std::cout<< "Esc\n";
                            window.close();
                            break;
                        case sf::Keyboard::W:
                            std::cout<<"W\n";
                            //chiama la funzione che controlla tutto rigurado al movimento
                            //movement_check(player.getPosition(), 'W);
                            //movement(player.getPosition(), 'W');
                            window.close();
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
    void Game::render(sf::RenderWindow &window, TileMap &map){
        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }
}
