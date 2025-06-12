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
    
    void Game::update(sf::RenderWindow &window, Map &map){

        //event handling
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::W:
                        //movement_check(player.getPosition(), Direction::Up);
                        //rotate(player.getPosition(), Direction::Up);
                        //movement(player.getPosition());
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

    Position target;        //tile that the player wants to move into
    Position next_target;   //tile after the target, in case something gets pushed

    std::vector<Position> targets;
    std::vector<Position> next_targets;

    bool movement_check(Map &map, Position &player_position, Direction direction){
        switch(direction){     
            case Direction::Up:
                //if(player_position.first==0) return false;
                target.first=player_position.first-1;
                target.second=player_position.second;

                //if (target.first==0) return true; 
                next_target.first=player_position.first-2;
                next_target.second=player_position.second;
                break;
            case Direction::Left:
                //if(player_position.second==0) return false;
                target.first=player_position.first;
                target.second=player_position.second-1;

                //if(target.second==0) return false;
                next_target.first=player_position.first;
                next_target.second=player_position.second-2;
                break;
            case Direction::Down:
                //if(player_position.first==15) return false;
                target.first=player_position.first+1;
                target.second=player_position.second;

                //if (target.first==15) return true; 
                next_target.first=player_position.first+2;
                next_target.second=player_position.second;
                break;
            case Direction::Right:
                //if(player_position.second==15) return false;
                target.first=player_position.first;
                target.second=player_position.second+1;
                
                //if(target.second==15) return false;
                next_target.first=player_position.first;
                next_target.second=player_position.second+2;
                break;
            default: break;
        }
        Objects temp1 = map.At(target.second, target.first);
        Objects temp2 = map.At(next_target.second, next_target.first);
        if (temp1.objectHasType(Type::Push))
            if(temp2.objectHasType(Type::Move))
                return true;
        else if (temp1.objectHasType(Type::Move))
            return true;
        return false;
        /* what if
         int a=static_cast<int> (temp.objectHasType(Type::Push) );
         int b=static_cast<int> (temp.objectHasType(Type::Move) );
         if (a+b==2)
            return true;
        */

    }
    //overload
    bool movement_check(Map &map, std::vector<Position> &player_positions, Direction directions){
        switch(directions){     
            case Direction::Up:
                //if(player_position.first==0) return false;
                for (size_t i={0}; i<player_positions.size(); ++i){
                    targets[i].first=player_positions[i].first-1;
                    targets[i].second=player_positions[i].second;
                }
                

                //if (target.first==0) return true; 
                for (size_t i={0}; i<player_positions.size(); ++i){
                    next_targets[i].first=player_positions[i].first-2;
                    next_targets[i].second=player_positions[i].second;
                }
                
                break;
            case Direction::Left:
                //if(player_position.second==0) return false;
                for (size_t i={0}; i<player_positions.size(); ++i){
                    targets[i].first=player_positions[i].first;
                    targets[i].second=player_positions[i].second-1;
                }

                //if(target.second==0) return false;
                for (size_t i={0}; i<player_positions.size(); ++i){
                    next_targets[i].first=player_positions[i].first;
                    next_targets[i].second=player_positions[i].second-2;
                }
                break;
            case Direction::Down:
                //if(player_position.first==15) return false;
                for (size_t i={0}; i<player_positions.size(); ++i){
                    targets[i].first=player_positions[i].first+1;
                    targets[i].second=player_positions[i].second;
                }

                //if (target.first==15) return true; 
                for (size_t i={0}; i<player_positions.size(); ++i){
                    next_targets[i].first=player_positions[i].first+2;
                    next_targets[i].second=player_positions[i].second;
                }
                break;
            case Direction::Right:
                //if(player_position.second==15) return false;
                for (size_t i={0}; i<player_positions.size(); ++i){
                    targets[i].first=player_positions[i].first;
                    targets[i].second=player_positions[i].second+1;
                }
                
                //if(target.second==15) return false;
                for (size_t i={0}; i<player_positions.size(); ++i){
                    next_targets[i].first=player_positions[i].first;
                    next_targets[i].second=player_positions[i].second+2;
                }
                break;
            default: break;
        }
        Objects temp1 = map.At(target.second, target.first);
        Objects temp2 = map.At(next_target.second, next_target.first);
        if (temp1.objectHasType(Type::Push))
            if(temp2.objectHasType(Type::Move))
                return true;
        else if (temp1.objectHasType(Type::Move))
            return true;
        return false;
        /* what if
         int a=static_cast<int> (temp.objectHasType(Type::Push) );
         int b=static_cast<int> (temp.objectHasType(Type::Move) );
         if (a+b==2)
            return true;
        */

    }
    void rotate(Position &player_position, Direction direction){
        player_position.first = player_position.first;
        player_position.second = player_position.second;
        switch(direction){
            case Baba_Is_Us::Direction::Up:
                
            case Baba_Is_Us::Direction::Down:
            case Baba_Is_Us::Direction::Left:
            case Baba_Is_Us::Direction::Right:
                break;
            default: break;
        }
    }

    bool movement(Map &map, Position &position){

        /*  
        divide movement in 3rds, for each frame of the animation:
            - change the player's sprite position by 1/3 towards the target's position
            - if target is pushable, game::update chiamerà anche movement(target, direction)
        SI PUò FARE ANCHE PER OGGETTI CHE DEVONO ESSERE DISTRUTTI?
        COME FARE A VEDERE DOVE STA GUARDANDO PLAYER? (PER ROCK) (togliamo launch e mettiamoci gradino?)
        */ 
        
        // 1/3
        
        // 2/3 

        // 3/3 
        position.first = target.first;
        position.second = target.second;
    
        return true;
    }
    //overload
    bool movement(Map &map, std::vector<Position> &positions){

        /*  
        divide movement in 3rds, for each frame of the animation:
            - change the player's sprite position by 1/3 towards the target's position
            - if target is pushable, game::update chiamerà anche movement(target, direction)
        SI PUò FARE ANCHE PER OGGETTI CHE DEVONO ESSERE DISTRUTTI?
        COME FARE A VEDERE DOVE STA GUARDANDO PLAYER? (PER ROCK) (togliamo launch e mettiamoci gradino?)
        */ 
        
        // 1/3
        
        // 2/3 

        // 3/3 
        for (size_t i={0}; i<positions.size(); ++i){
            positions[i].first = targets[i].first;
            positions[i].second = targets[i].second;
        }
    
        return true;
    }

    // check se intorno a target delle rules sono state cambiate, in tal caso reverse the effects of that rule
}
