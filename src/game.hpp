#ifndef GAME_HPP
#define GAME_HPP
#include "enum_objects.hpp"
#include "objects.hpp"
#include "rules.hpp"
#include "map.hpp"

#include <iostream>

using Position = std::pair<std::size_t, std::size_t>;
namespace Baba_Is_Us {

class Game {
private:
  Map m_map3D;
  RuleManager m_RM;
  std::vector<Position> m_players;
  PlayState m_state_of_game{PlayState::Playing};

public:
  Game(std::string_view);
  const std::vector<Position> &getPlayerPositions();
  const RuleManager &getRuleManager();
  const Map &getMap();
  Map &accessMap();
  const PlayState &getm_state_of_game();
  PlayState &accessm_state_of_game();
  
  void createRule(const std::vector<Type> &, const std::vector<Type> &,
                  const std::vector<Type> &);

  // chiamata quando una parola logica è mossa: se era parte di una regola,
  // modifica m_rules. N.B: le regole si creeranno solo da sx a dx e da alto a basso
  void parseRules();

  // add properties to door, key, gear and lever (constant, don't depend by the
  // rules)
  void constantProperties();
  
  // le seguenti adjust..() NON CONTROLLANO se un blocco ha creato o tolto una
  // regola
  void adjustAddingRules(); 
  void adjustRemovingRules();
  std::vector<Position> getTailMovingPosition(Direction);
  void update(sf::RenderWindow &, sf::Clock &);
  void render(sf::RenderWindow &, std::array<sf::Sprite, tilePaths.size()>&);
  
  void interact();
  void movement(sf::RenderWindow &, sf::Clock &, Direction);
  PlayState processMove(Objects &, Objects &, Direction, Position);
};

} // namespace Baba_Is_Us

#endif