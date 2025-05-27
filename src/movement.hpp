#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "game.hpp"

// Functions reguarding Baba's movement
                    ///
                    ///     ATTENZIONE : in alcuni casi il cpp usa size_t invece di int !!!!! 
bool movement_check(std::pair<int, int>);
bool move(std::pair<int, int>);

#endif