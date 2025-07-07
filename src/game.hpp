#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>

#include "enum_objects.hpp"
#include "map.hpp"
#include "objects.hpp"
#include "rules.hpp"

using Position = std::pair<std::size_t, std::size_t>;
namespace Baba_Is_Us {

class Game {
 private:
  Map m_map3D;
  RuleManager m_RM;
  std::vector<Position> m_players;
  PlayState m_state_of_game{PlayState::Playing};

 public:
  Game() = delete;
  Game(const std::string_view);
  const std::vector<Position> &getPlayerPositions() const;
  constexpr const RuleManager &getRuleManager() const { return m_RM; }
  constexpr const Map &getMap() const { return m_map3D; }
  constexpr Map &accessMap() { return m_map3D; }
  constexpr const PlayState &getm_state_of_game() { return m_state_of_game; }
  constexpr PlayState &accessm_state_of_game() { return m_state_of_game; }

  void createRule(const std::vector<Type> &, const std::vector<Type> &,
                  const std::vector<Type> &);
  // N.B: le regole si creeranno solo da sx a dx e da alto a basso
  void parseRules();
  // aggiungi proprietà costanti che non verranno mai modificate
  void constantProperties();
  void adjustAddingRules();
  void adjustRemovingRules();
  const std::vector<Position> getTailMovingPosition(const Direction) const;
  void update(sf::RenderWindow &, sf::Clock &);
  void render(sf::RenderWindow &, std::array<sf::Sprite, tilePaths.size()> &);
  // è la funzione che gestisce le interazioni tra You, Lever, Gear e Shut con
  // Map::pathFinder()
  void interact();
  void movement(sf::RenderWindow &, sf::Clock &, const Direction);
  const PlayState processMove(Objects &, Objects &, const Direction,
                              const Position);
};

}  // namespace Baba_Is_Us

#endif