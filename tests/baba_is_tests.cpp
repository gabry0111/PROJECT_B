#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../src/enum_objects.hpp"
#include "../src/game.hpp"
#include "../src/map.hpp"
#include "../src/objects.hpp"
#include "../src/rules.hpp"
#include "doctest.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>


using namespace Baba_Is_Us;

TEST_CASE("Basic functions - objects.hpp") {
  Game game("../assets/levels/level_test1.txt");
  Map &my_map{game.accessMap()};
  CHECK(my_map.At(0, 0).objectHasType(Type::Block));
  CHECK(my_map.At(8, 8).objectHasType(Type::Void));
  CHECK(my_map.At(8, 7).objectHasType(Type::Baba));
  CHECK(my_map.At(9, 3).objectHasType(Type::Flag));

  std::vector<Type> types_block{my_map.At(0, 0).getTypes()};
  CHECK(types_block.size() == 2);
  CHECK(types_block[0] == Type::Block);
  CHECK(types_block[1] == Type::Icon_Baba);

  std::vector<Type> types_void{my_map.At(8, 8).getTypes()};
  CHECK(types_void.size() == 1);
  CHECK(types_void[0] == Type::Void);

  std::vector<Type> types_baba{my_map.At(8, 7).getTypes()};
  CHECK(types_baba.size() == 2);
  CHECK(types_baba[0] == Type::Baba);
  CHECK(types_baba[1] == Type::You);

  std::vector<Type> types_flag{my_map.At(9, 3).getTypes()};
  CHECK(types_flag.size() == 2);
  CHECK(types_flag[0] == Type::Flag);
  CHECK(types_flag[1] == Type::Win);

  game.accessMap().accessm_objects()[0][0].addType(Type::Push);
  types_block = my_map.At(0, 0).getTypes();
  CHECK(types_block.size() == 3);
  CHECK(types_block[0] == Type::Block);
  CHECK(types_block[1] == Type::Icon_Baba);
  CHECK(types_block[2] == Type::Push);

  game.accessMap().accessm_objects()[8][8].addType(Type::Push);
  types_void = my_map.At(8, 8).getTypes();
  CHECK(types_void.size() == 2);
  CHECK(types_void[0] == Type::Void);
  CHECK(types_void[1] == Type::Push);

  game.accessMap().accessm_objects()[7][8].addType(Type::Push);
  types_baba = my_map.At(8, 7).getTypes();
  CHECK(types_baba.size() == 3);
  CHECK(types_baba[0] == Type::Baba);
  CHECK(types_baba[1] == Type::You);
  CHECK(types_baba[2] == Type::Push);

  game.accessMap().accessm_objects()[3][9].addType(Type::Push);
  types_flag = my_map.At(9, 3).getTypes();
  CHECK(types_flag.size() == 3);
  CHECK(types_flag[0] == Type::Flag);
  CHECK(types_flag[1] == Type::Win);
  CHECK(types_flag[2] == Type::Push);

  game.accessMap().accessm_objects()[0][0].removeType(Type::Push);
  types_block = my_map.At(0,0).getTypes();
  CHECK(types_block.size() == 2);
  CHECK(types_block[0] == Type::Block);
  CHECK(types_block[1] == Type::Icon_Baba);

  game.accessMap().accessm_objects()[8][8].removeType(Type::Push);
  types_void = my_map.At(8, 8).getTypes();
  CHECK(types_void.size() == 1);
  CHECK(types_void[0] == Type::Void);

  game.accessMap().accessm_objects()[7][8].removeType(Type::Push);
  types_baba = my_map.At(8, 7).getTypes();
  CHECK(types_baba.size() == 2);
  CHECK(types_baba[0] == Type::Baba);
  CHECK(types_baba[1] == Type::You);

  game.accessMap().accessm_objects()[3][9].removeType(Type::Push);
  types_flag = my_map.At(9, 3).getTypes();
  CHECK(types_flag.size() == 2);
  CHECK(types_flag[0] == Type::Flag);
  CHECK(types_flag[1] == Type::Win);

  game.accessMap().accessm_objects()[0][0].resetObject();
  types_block = my_map.At(0, 0).getTypes();
  CHECK(types_block.size() == 1);

  game.accessMap().accessm_objects()[3][9].resetObject();
  types_flag = my_map.At(9, 3).getTypes();
  CHECK(types_flag.size() == 1);

  game.accessMap().accessm_objects()[8][8].resetObject();
  types_void = my_map.At(8, 8).getTypes();
  CHECK(types_void.size() == 1);

  game.accessMap().accessm_objects()[7][8].resetObject();
  types_baba = my_map.At(8, 7).getTypes();
  CHECK(types_baba.size() == 1);
}

TEST_CASE("Basic functions - rules.hpp") {
  Game game("../assets/levels/level_test2.txt");
  Map &my_map{game.accessMap()};
  CHECK(my_map.At(0, 0).getTypes()[0] == Type::Block);
  CHECK(my_map.At(8, 8).getTypes()[0] == Type::Wall);
  CHECK(my_map.At(8, 12).getTypes()[0] == Type::Baba);
  CHECK(my_map.At(9, 3).getTypes()[0] == Type::Flag);

  sf::RenderWindow window(sf::VideoMode({512, 512}), "Testing rules.hpp");
  game.accessMap().setTextures();
  game.accessMap().setSprites();
  sf::Clock clock;

  RuleManager rm{game.getRuleManager()};
  std::vector<Rule> &rules{rm.accessm_rules()};

  CHECK(rules[0].hasType(Type::Baba));
  CHECK(rules[0].hasType(Type::Is));
  CHECK(rules[0].hasType(Type::You));
  CHECK(rules[1].hasType(Type::Lava));
  CHECK(rules[1].hasType(Type::Is));
  CHECK(rules[1].hasType(Type::Hot));
  CHECK(rules[2].hasType(Type::Wall));
  CHECK(rules[2].hasType(Type::Is));
  CHECK(rules[2].hasType(Type::Stop));
  CHECK(rules[3].hasType(Type::Rock));
  CHECK(rules[3].hasType(Type::Is));
  CHECK(rules[3].hasType(Type::Defeat));
  CHECK(rules[4].hasType(Type::Flag));
  CHECK(rules[4].hasType(Type::Is));
  CHECK(rules[4].hasType(Type::Win));

  CHECK(rules[0].getm_rule()[0] == Type::Baba);
  CHECK(rules[0].getm_rule()[1] == Type::Is);
  CHECK(rules[0].getm_rule()[2] == Type::You);

  CHECK(rules[1].getm_rule()[0] == Type::Lava);
  CHECK(rules[1].getm_rule()[1] == Type::Is);
  CHECK(rules[1].getm_rule()[2] == Type::Hot);

  CHECK(rules[2].getm_rule()[0] == Type::Wall);
  CHECK(rules[2].getm_rule()[1] == Type::Is);
  CHECK(rules[2].getm_rule()[2] == Type::Stop);

  CHECK(rules[3].getm_rule()[0] == Type::Rock);
  CHECK(rules[3].getm_rule()[1] == Type::Is);
  CHECK(rules[3].getm_rule()[2] == Type::Defeat);

  CHECK(rules[4].getm_rule()[0] == Type::Flag);
  CHECK(rules[4].getm_rule()[1] == Type::Is);
  CHECK(rules[4].getm_rule()[2] == Type::Win);

  // check by modifying addRule()

  Rule new_rule{Type::Flag, Type::Is, Type::Hot};
  rm.addRule(new_rule);

  CHECK(rm.getm_rules().size() == 6);
  CHECK(rm.getm_rules()[5].getm_rule()[0] == Type::Flag);
  CHECK(rm.getm_rules()[5].getm_rule()[1] == Type::Is);
  CHECK(rm.getm_rules()[5].getm_rule()[2] == Type::Hot);

  rm.removeRule(new_rule);
  CHECK(rm.getm_rules().size() == 5);
  CHECK(my_map.At(9, 3).getTypes().size() == 2);
  CHECK(my_map.At(9, 3).getTypes()[0] == Type::Flag);
  CHECK(my_map.At(9, 3).getTypes()[1] == Type::Win);

  // check by modifying the map
  game.movement(window, clock, Direction::Down);
  CHECK(my_map.At(9, 3).getTypes().size() == 2);
  CHECK(my_map.At(9, 3).getTypes()[0] == Type::Flag);
  CHECK(my_map.At(9, 3).getTypes()[1] == Type::Hot);
  CHECK(!my_map.At(9, 3).objectHasType(Type::Win));

  CHECK(*rm.findPlayerType() == Type::Baba);
  CHECK(*rm.findPlayerType() != Type::Lava);

  rm.clearRules();
  CHECK(rm.getm_rules().size() == 0);
}

TEST_CASE("Basic functions - map.hpp") {
  Game game("../assets/levels/level_test1.txt");
  Map &my_map{game.accessMap()};
  CHECK(my_map.At(0, 0).getTypes()[0] == Type::Block);
  CHECK(my_map.At(8, 8).getTypes()[0] == Type::Void);
  CHECK(my_map.At(8, 7).getTypes()[0] == Type::Baba);
  CHECK(my_map.At(9, 3).getTypes()[0] == Type::Flag);

  const std::vector<Position> positions{my_map.getPositions(Type::You)};
  CHECK(positions.size() == 1);
  CHECK(positions[0].first == 8);
  CHECK(positions[0].second == 7);
  CHECK(positions[0].first != 7);
  CHECK(positions[0].second != 8);

  void addObject(Position position, Type type);
  CHECK(my_map.At(8, 7).getTypes().size() == 2);
  my_map.resetObject(positions[0]);
  CHECK(my_map.At(8, 7).getTypes().size() == 1);
  CHECK(my_map.At(8, 7).getTypes()[0] == Type::Void);

  CHECK(my_map.getm_grid()[0][0] == 13);
  CHECK(my_map.getm_objects()[0][0].getTypes()[0] == Type::Block);
  my_map.setTextures();
  my_map.setSprites();
  CHECK(my_map.getTileSprites().size() == tilePaths.size());

  CHECK(!my_map.isOutOfBoundary(15, 15));
  CHECK(my_map.isOutOfBoundary(16, 16));
}

TEST_CASE("Game - Basic movement and transformation between map_layers") {
  Game game("../assets/levels/level_test1.txt");
  Map &my_map{game.accessMap()};

  // il livello si è caricato bene, per le posizioni?
  CHECK(my_map.At(8, 7).objectHasType(Type::Baba));
  CHECK(my_map.At(9, 3).objectHasType(Type::Flag));
  CHECK(game.getRuleManager().getm_rules().size() == 5);
  for (const Rule &rule : game.getRuleManager().getm_rules()) {
    CHECK(+rule.getm_rule()[0] > +Type::NOUN_TYPE);
    CHECK(+rule.getm_rule()[0] < +Type::ICON_NOUN_TYPE);
    CHECK(+rule.getm_rule()[1] > +Type::VERB_TYPE);
    CHECK(+rule.getm_rule()[1] < +Type::PROPERTY_TYPE);
    CHECK([](Type type) {
      return (+type > +Type::PROPERTY_TYPE ||
              (+type > +Type::NOUN_TYPE && +type < +Type::ICON_NOUN_TYPE));
    }(rule.getm_rule()[2]));
  }
  for (const Position &pos : game.getPlayerPositions()) {
    CHECK(my_map.At(pos.first, pos.second).getTypes()[0] == Type::Baba);
    CHECK(my_map.getm_grid()[pos.second][pos.first] == +Type::Baba);
  }

  std::vector<Position> you_positions = my_map.getPositions(Type::You);
  CHECK(you_positions.size() == 1);
  CHECK(you_positions[0].first == 8);
  CHECK(you_positions[0].second == 7);

  sf::RenderWindow window(sf::VideoMode({512, 512}), "Testing movement");
  game.accessMap().setTextures();
  game.accessMap().setSprites();
  sf::Clock clock;

  // gli oggetti non si spostano in alto se baba non li tocca
  game.movement(window, clock, Direction::Up);
  CHECK(my_map.At(8, 6).objectHasType(Type::Baba));
  CHECK(my_map.At(8, 7).objectHasType(Type::Void));
  CHECK(my_map.At(8, 4).objectHasType(Type::Lava));
  CHECK(my_map.At(8, 6).objectHasType(intToType(+Type::Baba)));
  CHECK(my_map.At(8, 7).objectHasType(intToType(+Type::Void)));
  CHECK(my_map.At(8, 4).objectHasType(intToType(+Type::Lava)));

  CHECK(my_map.getm_grid()[6][8] == +Type::Baba);
  CHECK(my_map.getm_grid()[7][8] == +Type::Void);
  CHECK(my_map.getm_grid()[4][8] == +Type::Lava);


  // gli oggetti non si spostano in alto se baba non li tocca
  game.movement(window, clock, Direction::Up);
  CHECK(my_map.At(8, 5).objectHasType(Type::Baba));
  CHECK(my_map.At(8, 6).objectHasType(Type::Void));
  CHECK(my_map.At(8, 4).objectHasType(Type::Lava));
  CHECK(my_map.At(8, 5).objectHasType(intToType(+Type::Baba)));
  CHECK(my_map.At(8, 6).objectHasType(intToType(+Type::Void)));
  CHECK(my_map.At(8, 4).objectHasType(intToType(+Type::Lava)));

  CHECK(my_map.getm_grid()[5][8] == +Type::Baba);
  CHECK(my_map.getm_grid()[6][8] == +Type::Void);
  CHECK(my_map.getm_grid()[4][8] == +Type::Lava);


  // gli oggetti non si spostano in basso se baba non li tocca
  game.movement(window, clock, Direction::Down);
  CHECK(my_map.At(8, 6).objectHasType(Type::Baba));
  CHECK(my_map.At(8, 5).objectHasType(Type::Void));
  CHECK(my_map.At(8, 4).objectHasType(Type::Lava));
  CHECK(my_map.At(8, 6).objectHasType(intToType(+Type::Baba)));
  CHECK(my_map.At(8, 5).objectHasType(intToType(+Type::Void)));
  CHECK(my_map.At(8, 4).objectHasType(intToType(+Type::Lava)));

  CHECK(my_map.getm_grid()[6][8] == +Type::Baba);
  CHECK(my_map.getm_grid()[7][8] == +Type::Void);
  CHECK(my_map.getm_grid()[4][8] == +Type::Lava);


  game.movement(window, clock, Direction::Right);
  game.movement(window, clock, Direction::Right);
  game.movement(window, clock, Direction::Right);

  CHECK(my_map.At(11, 6).objectHasType(Type::Baba));
  CHECK(my_map.At(11, 6).objectHasType(Type::You));

  CHECK(my_map.At(2, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(2, 6).getTypes()[1] == (Type::Icon_Lava));

  CHECK(my_map.At(3, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(3, 6).getTypes()[1] == (Type::Icon_Is));

  CHECK(my_map.At(4, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(4, 6).getTypes()[1] == (Type::Icon_Hot));


  CHECK(my_map.getm_grid()[6][2] == +Type::Icon_Lava);
  CHECK(my_map.getm_grid()[6][3] == +Type::Icon_Is);
  CHECK(my_map.getm_grid()[6][4] == +Type::Icon_Hot);

  game.movement(window, clock, Direction::Left);
  game.movement(window, clock, Direction::Left);
  CHECK(my_map.At(9, 6).objectHasType(Type::Baba));
  CHECK(my_map.At(9, 6).objectHasType(Type::You));
  CHECK(my_map.At(2, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(2, 6).getTypes()[1] == (Type::Icon_Lava));

  CHECK(my_map.At(3, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(3, 6).getTypes()[1] == (Type::Icon_Is));

  CHECK(my_map.At(4, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(4, 6).getTypes()[1] == (Type::Icon_Hot));


  CHECK(my_map.getm_grid()[6][2] == +Type::Icon_Lava);
  CHECK(my_map.getm_grid()[6][3] == +Type::Icon_Is);
  CHECK(my_map.getm_grid()[6][4] == +Type::Icon_Hot);
}

TEST_CASE("Game - Rules changing") {
  Game game("../assets/levels/level_test1.txt");
  Map &my_map{game.accessMap()};

  // il livello si è caricato bene, per le posizioni?
  CHECK(my_map.At(8, 7).objectHasType(Type::Baba));
  CHECK(my_map.At(9, 3).objectHasType(Type::Flag));

  // il livello si è caricato bene, per le regole?
  CHECK(game.getRuleManager().getm_rules().size() == 5);
  for (const Rule &rule : game.getRuleManager().getm_rules()) {
    CHECK(+rule.getm_rule()[0] > +Type::NOUN_TYPE);
    CHECK(+rule.getm_rule()[0] < +Type::ICON_NOUN_TYPE);
    CHECK(+rule.getm_rule()[1] > +Type::VERB_TYPE);
    CHECK(+rule.getm_rule()[1] < +Type::PROPERTY_TYPE);
    CHECK([](Type type) {
      return (+type > +Type::PROPERTY_TYPE ||
              (+type > +Type::NOUN_TYPE && +type < +Type::ICON_NOUN_TYPE));
    }(rule.getm_rule()[2]));
  }

  const std::vector<Position> player_positions{game.getPlayerPositions()};
  const std::vector<Position> you_positions{my_map.getPositions(Type::You)};
  CHECK(player_positions.size() == you_positions.size());
  for (std::size_t iii{}; iii < player_positions.size(); ++iii) {
    CHECK(player_positions[iii].first == you_positions[iii].first);
    CHECK(player_positions[iii].second == you_positions[iii].second);
  }

  sf::RenderWindow window(sf::VideoMode({512, 512}), "Testing rules changing");
  game.accessMap().setTextures();
  game.accessMap().setSprites();
  sf::Clock clock;

  // gli oggetti non si spostano in alto se baba non li tocca
  game.movement(window, clock, Direction::Up);
  game.movement(window, clock, Direction::Up);
  CHECK(my_map.At(8, 5).objectHasType(Type::Baba));
  CHECK(my_map.At(8, 6).objectHasType(Type::Void));
  CHECK(my_map.At(8, 7).objectHasType(Type::Void));
  CHECK(my_map.At(8, 4).objectHasType(Type::Lava));

  // gli oggetti non si spostano in basso se baba non li tocca
  game.movement(window, clock, Direction::Down);
  CHECK(my_map.At(8, 6).objectHasType(Type::Baba));
  CHECK(my_map.At(8, 7).objectHasType(Type::Void));
  CHECK(my_map.At(8, 4).objectHasType(Type::Lava));

  // i blocchi non si spostano a dx se baba non li tocca
  game.movement(window, clock, Direction::Right);
  game.movement(window, clock, Direction::Right);
  game.movement(window, clock, Direction::Right);
  CHECK(my_map.At(11, 6).objectHasType(Type::Baba));
  CHECK(my_map.At(2, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(2, 6).getTypes()[1] == (Type::Icon_Lava));
  CHECK(my_map.At(3, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(3, 6).getTypes()[1] == (Type::Icon_Is));
  CHECK(my_map.At(4, 6).getTypes()[0] == (Type::Block));
  CHECK(my_map.At(4, 6).getTypes()[1] == (Type::Icon_Hot));

}

TEST_CASE("Game - Interact e pathFinder"){
  Game game("../assets/levels/level_test3.txt");
  Map &my_map{game.accessMap()};

  CHECK(game.getRuleManager().getm_rules().size() == 2);
  CHECK(game.getPlayerPositions().size() == 1);
  CHECK(my_map.At(0, 7).getTypes()[0] == Type::Baba);

  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 0);
  CHECK(my_map.getPositions(Type::Spin).size() == 0);

  sf::RenderWindow window(sf::VideoMode({512, 512}), "Testing Interact and pathFinder");
  sf::Clock clock;

  game.movement(window, clock, Direction::Right);
  CHECK(my_map.At(1, 7).getTypes()[0] == Type::Baba);
  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 1);
  CHECK(my_map.getPositions(Type::Spin).size() == 6);
  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 0);
  CHECK(my_map.getPositions(Type::Spin).size() == 0);

  game.movement(window, clock, Direction::Right);
  CHECK(my_map.At(2, 7).getTypes()[0]== Type::Baba);

  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 1);
  CHECK(my_map.getPositions(Type::Spin).size() == 0);
  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 0);
  CHECK(my_map.getPositions(Type::Spin).size() == 0);

  game.movement(window, clock, Direction::Right);
  CHECK(my_map.At(3, 7).getTypes()[0]== Type::Baba);

  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 1);
  CHECK(my_map.getPositions(Type::Spin).size() == 12);
  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 0);
  CHECK(my_map.getPositions(Type::Spin).size() == 0);

  game.movement(window, clock, Direction::Right);
  CHECK(my_map.At(4, 7).getTypes()[0]== Type::Baba);
  
  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 1);
  CHECK(my_map.getPositions(Type::Spin).size() == 4);
  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 0);
  CHECK(my_map.getPositions(Type::Spin).size() == 0);

  game.movement(window, clock, Direction::Right);
  CHECK(my_map.At(5, 7).getTypes()[0]== Type::Baba);

  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 1);
  CHECK(my_map.getPositions(Type::Spin).size() == 10);
  game.interact();
  CHECK(my_map.getPositions(Type::Switch).size() == 0);
  CHECK(my_map.getPositions(Type::Spin).size() == 0);

  game.movement(window, clock, Direction::Right);
  CHECK(my_map.At(6, 7).getTypes()[0]== Type::Baba);
  game.movement(window, clock, Direction::Right);
  CHECK(my_map.At(7, 7).getTypes()[0]== Type::Baba);
  CHECK(my_map.At(8, 7).getTypes()[0]== Type::Flag);
  CHECK(my_map.At(8, 7).getTypes()[1]== Type::Win);

  game.movement(window, clock, Direction::Right);
  CHECK(game.getm_state_of_game() == PlayState::Won);

}