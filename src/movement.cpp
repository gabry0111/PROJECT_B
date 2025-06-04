#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "rules.hpp"
#include <iostream>

namespace Baba_Is_Us{
    std::pair<int, int> target; //tile that the player wants to move into

    //CREARE UNA FUNZIONE "(const e non const?) Objects& At(std::pair<int,int> position) (const e non const?)" CHE RESTITUISCE CHE OBJECT C'è IN QUEL PUNTO
    //CREARE UNA FUNZIONE "void removeObject(std::pair<int,int>, ObjectType type)" CHE CANCELLA QUELLA ICON GRAFICA DELL'OGGETTO SULLA MAPPA
    

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
       
        return (map_grid[target.second][target.first] != 6); // type Wall = 6

    };
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
        return true;
    };
}