#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.hpp"
#include "game.hpp"
#include "objects.hpp"

/* Avuta la mappa del livello corrente, verifica quali azioni sono possibili:
- verifica le proprietà di ciascun oggetto (sarà fatto nel Main Loop)
- resetta il livello se PlayState è Invalid
- gestisce il movimento del Player
- gestisce il movimento degli oggetti 
- 
*/
namespace Baba_Is_Us{
    
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
                            //rotate(player.getPosition(), Direction::Up)
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

    std::pair<int, int> target; //tile that the player wants to move into

    bool movement_check(std::pair<int, int> &player_position, Direction direction){
        switch(direction){
            case Direction::Up:
                target.first=player_position.first-1;
                target.second=player_position.second;
                break;
            case Direction::Left:
                target.first=player_position.first;
                target.second=player_position.second-1;
                break;
            case Direction::Down:
                target.first=player_position.first+1;
                target.second=player_position.second;
                break;
            case Direction::Right:
                target.first=player_position.first;
                target.second=player_position.second+1;
                break;
            default: break;
        }

        return true; // check the type of the object in that position

    }
    void rotate(std::pair<int, int> &player_position, Direction direction){
        player_position.first = player_position.first;
        player_position.second = player_position.second;
        switch(direction){
            //due opzioni
            //1. chiamiamo loadFromFile() in base alla direzione
            //2. creiamo il parametro Direction nella classe player e qui lo modifichiamo
            //      ma quando si chiama loadFromFile() bisogna inviare il path corrispondente al file 
            //      orientato in quel modo
            case Baba_Is_Us::Direction::Up:
            case Baba_Is_Us::Direction::Down:
            case Baba_Is_Us::Direction::Left:
            case Baba_Is_Us::Direction::Right:
                break;
            default: break;
        }
    }
    bool movement(std::pair<int, int> &position, Direction direction){

        /*  
        divide movement in 3rds, for each frame of the animation:
            - change the player's sprite position by 1/3 towards the target's position
            - if target is pushable, call movement(target, direction)
        SI PUò FARE ANCHE PER OGGETTI CHE DEVONO ESSERE DISTRUTTI?
        COME FARE A VEDERE DOVE STA GUARDANDO PLAYER? (PER ROCK) (togliamo launch e mettiamoci gradino?)
        */ 

        // 1/3
        
        // 2/3 

        // 3/3 

        position.first = target.first;
        position.second = target.second;
        direction = Direction::Up; // dopo che avremo implementato il player, qui settiamo la sua direzione
        if (direction==Direction::Down) return false;
        return true;
    }
}
