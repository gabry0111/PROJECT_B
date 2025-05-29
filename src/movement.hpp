#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#include <SFML/Graphics.hpp>
#include "game.hpp"
using namespace Baba_Is_Us;
// Functions reguarding Baba's movement
                    ///
                    ///     ATTENZIONE : in alcuni casi c++ uses size_t instead of int !!!!! 
bool movement_check(std::pair<int, int> &, Direction);
bool move(std::pair<int, int> &);

#endif