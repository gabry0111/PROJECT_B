#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "map.hpp"
#include <iostream>

namespace Baba_Is_Us{
    bool movement_check(std::pair<int, int> &player_position, Direction direction){
        std::pair<int, int> target; //tile that the player wants to move into
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

    };
    bool movement(std::pair<int, int> &player_position, Direction direction){
        // 1/3 of movement
        // move
        
        // 2/3 of movement


        // 3/3 of movement


    };
}