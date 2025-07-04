#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

namespace Baba_Is_Us {

Game::Game(std::string_view filename) : m_map3D{filename}, m_RM{}, m_players{} {
  m_RM.clearRules();
  parseRules();
  constantProperties();
  m_players = m_map3D.getPositions(Type::You);
}
const std::vector<Position> &Game::getPlayerPositions() { return m_players; }
const RuleManager &Game::getRuleManager() { return m_RM; }
const Map &Game::getMap() { return m_map3D; }
Map &Game::accessMap() { return m_map3D; }

const PlayState &Game::getm_state_of_game() { return m_state_of_game; }
PlayState &Game::accessm_state_of_game() { return m_state_of_game; }

///////////////////////////////////  Chapter: HandlingRules  //////////////////////////////////////

Type iconToAll(Type type) {
  switch (type) { //clang-format off
    case Type::Icon_Void:   return Type::Void;
    case Type::Icon_Baba:   return Type::Baba;
    case Type::Icon_Defeat: return Type::Defeat;
    case Type::Icon_Door:   return Type::Door;
    case Type::Icon_Flag:   return Type::Flag;
    case Type::Icon_Gear:   return Type::Gear;
    case Type::Icon_Hot:    return Type::Hot;
    case Type::Icon_Is:     return Type::Is;
    case Type::Icon_Key:    return Type::Key;
    case Type::Icon_Lava:   return Type::Lava;
    case Type::Icon_Lever:  return Type::Lever;
    case Type::Icon_Melt:   return Type::Melt;
    case Type::Icon_Push:   return Type::Push;
    case Type::Icon_Rock:   return Type::Rock;
    case Type::Icon_Shut:   return Type::Shut;
    case Type::Icon_Stop:   return Type::Stop;
    case Type::Icon_Wall:   return Type::Wall;
    case Type::Icon_Win:    return Type::Win;
    case Type::Icon_You:    return Type::You;
    default:  throw(std::runtime_error("iconToAll(): not given an ICON_TYPE"));
  } //clang-format on
}

void Game::adjustAddingRules() {
  std::vector<Rule> rules{m_RM.getm_rules()};
  assert(rules.size() > 0);
  for (const Rule &each_rule : m_RM.getm_rules()) { 
    Type noun_type{
        each_rule.getm_rule()[0]};
    assert(noun_type != Type::Block &&
           "adjustAddingRules(): noun_type == Type::Block");
    Type prop_or_noun_type{
        each_rule.getm_rule()[2]};
    std::vector<Position> pos_of_types_with_rule{
        m_map3D.getPositions(noun_type)};

    assert(((+prop_or_noun_type > +Type::NOUN_TYPE &&
             +prop_or_noun_type < +Type::ICON_NOUN_TYPE) ||
            (+prop_or_noun_type > +Type::PROPERTY_TYPE)) &&
           "adjustAddingRules(): prop_or_noun_type not one of the two Types");
    for (const Position &each_pos :
         pos_of_types_with_rule) { 
      Objects &obj{m_map3D.At(each_pos.first, each_pos.second)};
      
      if (+prop_or_noun_type >
          +Type::PROPERTY_TYPE) { 
        if (!obj.objectHasType(prop_or_noun_type)) { 
          obj.addType(prop_or_noun_type); 
        }
      } else { 
        obj.addType(prop_or_noun_type);
        for (const Rule &iter_rules : m_RM.getm_rules()) {
          if (std::find(iter_rules.getm_rule().begin(),
                        iter_rules.getm_rule().end(),
                        prop_or_noun_type) != iter_rules.getm_rule().end()) {
            obj.addType(
                iter_rules
                    .getm_rule()[2]); 
          }
        }
      }
    }
  }
}

void Game::createRule(const std::vector<Type> &word1,
                      const std::vector<Type> &word2,
                      const std::vector<Type> &word3) {
 
  assert(!word2.empty() && !word3.empty() &&
         "createRule()"); 

  Type type1{iconToAll(word1[1])};
  Type type2{iconToAll(word2[1])};
  Type type3{iconToAll(word3[1])};
  if (+type1 > +Type::NOUN_TYPE 
      && +type1 < +Type::ICON_NOUN_TYPE && +type2 > +Type::VERB_TYPE &&
      +type2 < +Type::PROPERTY_TYPE &&
      (+type3 > +Type::PROPERTY_TYPE ||
       (+type3 > +Type::NOUN_TYPE && +type3 < +Type::ICON_NOUN_TYPE))) {
    bool already_exists {
        std::any_of(m_RM.getm_rules().begin(), m_RM.getm_rules().end(),
                    [&](const Rule &rule) {
                      return rule.getm_rule()[0] == type1 &&
                             rule.getm_rule()[1] == type2 &&
                             rule.getm_rule()[2] == type3;
                    })
      };
    if (!already_exists) {
      Rule new_rule{type1, type2, type3};
      m_RM.addRule(new_rule);
    }
  }
}

void Game::adjustRemovingRules() {
  //rimuovo tutte le proprietà date dalle regole
  for (const Rule rule : m_RM.getm_rules()) { 
    const Type &first_type = rule.getm_rule()[0];

    for (const Position &pos : m_map3D.getPositions(rule.getm_rule()[0])) {
      Objects &obj = m_map3D.At(pos.first, pos.second);
      for (const Type type : obj.getTypes())
        if (type != first_type)
          obj.removeType(type);
    }
  }
}

void Game::parseRules() {
  if (!m_RM.getm_rules().empty()) {
    adjustRemovingRules();
  }
  m_RM.clearRules();
  std::vector<Position> block_pos{m_map3D.getPositions(Type::Block)};

  for (const Position &pos : block_pos) {
    if (!m_map3D.isOutOfBoundary(pos.first, pos.second + 2)) {
      const auto &word1 = m_map3D.At(pos.first, pos.second).getTypes();
      const auto &word2 = m_map3D.At(pos.first, pos.second + 1).getTypes();
      const auto &word3 = m_map3D.At(pos.first, pos.second + 2).getTypes();

      if (word2[0] == Type::Block && word3[0] == Type::Block)
        createRule(word1, word2, word3);
    }

    if (!m_map3D.isOutOfBoundary(pos.first + 2, pos.second)) {
      const auto &word1 = m_map3D.At(pos.first, pos.second).getTypes();
      const auto &word2 = m_map3D.At(pos.first + 1, pos.second).getTypes();
      const auto &word3 = m_map3D.At(pos.first + 2, pos.second).getTypes();

      if (word2[0] == Type::Block && word3[0] == Type::Block)
        createRule(word1, word2, word3);
    }
  }
  // Controlla se c'è la regola .. is you, altrimenti il gioco si ferma
  if (m_RM.getm_rules().size() == 0 || !m_RM.findPlayerType().has_value()) {
    
    m_state_of_game = PlayState::Lose;
    return;
  }
  adjustAddingRules();
  constantProperties();
  m_map3D.spriteOverlay();
}

void Game::constantProperties() {
  std::vector<Position> constant_prop_positions{};
  for (std::size_t i{}; i < MapSize::n_tiles; ++i) {
    Objects &obj{m_map3D.At(i / MapSize::height, i % MapSize::width)};
    switch (obj.getTypes()[0]) {
    case Type::Block:
      break;
    case Type::Door:
      obj.addType(Type::Shut);
      obj.addType(Type::Stop);
      break;
    case Type::Gear:
      obj.addType(Type::Push);
      break;
    case Type::Key:
      obj.addType(Type::Open);
      obj.addType(Type::Push);
      break;
    case Type::Lever:
      obj.addType(Type::Push);
      break;

    default:
      break;
    }
  }
}

/////////////////////////////////// Chapter: Handling Movement and KeyPressing //////////////////////////////////////

Position getShift(Direction dir) {
  switch (dir) { //clang-format off
  case Direction::Up:     return {0, -1};
  case Direction::Down:   return {0, 1};
  case Direction::Left:   return {-1, 0};
  case Direction::Right:  return {1, 0};
  default:                throw(std::runtime_error("getShift(): not given a valid direction"));
  } //clang-format on
}
// N.B: data una fila verticale di oggetti attaccati e la direzione Up,
// l'oggetto Tail è quello più in basso
bool isTailOfLine(
    Position pos, Map &map,
    Direction dir) { 
  Type type{map.At(pos.first, pos.second).getTypes()[0]};
  std::size_t dx = getShift(dir).first;
  std::size_t dy = getShift(dir).second;
  if (map.isOutOfBoundary(pos.first - dx, pos.second - dy)) {
    return true;
  }
  return (type != map.At(pos.first - dx, pos.second - dy).getTypes()[0]);
}
std::vector<Position> Game::getTailMovingPosition(Direction direction) {
  std::vector<Position> pos_to_be_moved{};
  assert(m_players.size() > 0);
  for (const Position &pos : m_players) {
    if (isTailOfLine(pos, m_map3D, direction)) {
      pos_to_be_moved.emplace_back(pos);
    }
  }
  return pos_to_be_moved;
}
// fallisce solo se è OutOfBoundary
std::optional<Position> getMismatch(const Map& map, Direction dir, Position start) {
  std::optional<Position> result{};
  Position shift{getShift(dir)};
  std::size_t x{start.first};
  std::size_t y{start.second};
  int value = +map.getm_objects()[y][x].getTypes()[0];
  
  while (x < MapSize::width && y < MapSize::height) {
    if (+map.getm_objects()[y][x].getTypes()[0] != value) {
      result = {x, y};
      return result;
    }

    x += shift.first;
    y += shift.second;
  }
  return std::nullopt;
}

PlayState Game::handlePush(Objects &tail, Objects &target, Direction direction, Position start) {
  Position shift{getShift(direction)};
  Position pos_mism{start.first + shift.first, start.second + shift.second};
  Position pos_next_mism{pos_mism.first + shift.first, pos_mism.second + shift.second};

  if (target.objectHasType(Type::Void)) // per fermare la scansione degli oggetti
    return PlayState::Playing;

  if (target.objectHasType(Type::Block))
    m_RM.block_moved = true;
  
  PlayState state = conditions(tail, target);
  std::cerr << "State == " << +state << '\n';

  if (tail.objectHasType(Type::Void)){
    m_map3D.accessm_grid()[start.second][start.first] = +Type::Void;
  }
  if (target.objectHasType(Type::Void)){
    m_map3D.accessm_grid()[pos_mism.second][pos_mism.first] = +Type::Void;
  }

  if (state == PlayState::Invalid){
    return PlayState::Invalid;
  }
  if (state == PlayState::Won) {
    return PlayState::Won;
  }

  if (m_map3D.isOutOfBoundary(pos_next_mism.first, pos_next_mism.second))
    return PlayState::Invalid;

  if (handlePush(target, m_map3D.At(pos_next_mism.first, pos_next_mism.second), direction, pos_mism) == PlayState::Invalid)
    return PlayState::Invalid;
  else {
    m_map3D.accessm_grid()[pos_next_mism.second][pos_next_mism.first] =
        m_map3D.getm_grid()[pos_mism.second][pos_mism.first];
    m_map3D.accessm_grid()[pos_mism.second][pos_mism.first] =
        m_map3D.getm_grid()[start.second][start.first];

    m_map3D.accessm_objects()[pos_next_mism.second][pos_next_mism.first] =
        target;
    m_map3D.accessm_objects()[pos_mism.second][pos_mism.first] = tail;
    return PlayState::Playing;
  }
}

void Game::movement(sf::RenderWindow &window, sf::Clock &clock, Direction direction) {
  Position shift = getShift(direction);
  std::size_t dx{shift.first};
  std::size_t dy{shift.second};
  std::vector<Position> tail_pos{getTailMovingPosition(direction)};


  for (auto& each : tail_pos){ 
    
    std::size_t player_move_index{static_cast<std::size_t>(+direction + 1)};
    std::size_t player_idle_index{static_cast<std::size_t>(+direction + 5)};
    std::size_t index_player_sprite;
    index_player_sprite = indexToBeDrawn(m_map3D.getm_grid()[each.second][each.first]);
    std::cerr << "index_player_sprite: " << index_player_sprite <<'\n';
    sf::Sprite& player_sprite = m_map3D.tileSprites[index_player_sprite];
    
    // solo Baba (in tilePaths con indice da 1 a 8) ha varianti nelle texture.
    // Per prima cosa, giriamo la sprite.
    if (index_player_sprite >= 1 && index_player_sprite <= 8){
      player_sprite.setTexture(m_map3D.textures[player_idle_index]);
    } else {
      player_move_index = index_player_sprite;
      player_idle_index = index_player_sprite;
    }
    m_map3D.redraw(clock);
    render(window, m_map3D.tileSprites);

    if (!getMismatch(m_map3D, direction, each))
      continue;
    Position pos_mismatch =
        *getMismatch(m_map3D, direction, each);

    std::size_t delta_x = pos_mismatch.first - each.first;
    std::size_t delta_y = pos_mismatch.second - each.second;
    if (m_map3D.isOutOfBoundary(each.first + delta_x, each.second + delta_y)) {
      continue;
    }

    //////////// movimento visivo
    if (!getMismatch(m_map3D, direction, each).has_value()) {
      continue;
    } else {
      player_sprite = m_map3D.tileSprites[player_move_index];
      player_sprite.setTexture(m_map3D.textures[player_move_index]);
      player_sprite.move(static_cast<float>(dx * 11),
                        static_cast<float>(dy * 11));
      m_map3D.redraw(clock);
      render(window, m_map3D.tileSprites);
    }
    Objects &obj_tail = m_map3D.At(each.first, each.second);
    Objects &obj_mismatch = m_map3D.At(pos_mismatch.first, pos_mismatch.second);
    std::cerr << "Tail has types: "; 
    for (Type type : obj_tail.getTypes()) {std::cerr << type << '\n' ;}
    std::cerr << "Mismatch has types: "; 
    for (Type type : obj_mismatch.getTypes()) {std::cerr << type << '\n';}

    
    if (obj_mismatch.objectHasType(Type::Block) &&
        m_map3D.isOutOfBoundary(pos_mismatch.first + dx,
                                pos_mismatch.second + dy)) {continue;}

    PlayState state {handlePush(obj_tail, obj_mismatch, direction, each)};
    m_players = m_map3D.getPositions(Type::You);
    if (state == PlayState::Won){
      m_state_of_game = PlayState::Won;
      return ;
    }
    else if (m_players.size() == 0){
      m_state_of_game = PlayState::Lose;
      return ;
    }
    if (state == PlayState::Playing) {
      if(obj_mismatch.objectHasType(Type::Void)) {
        m_map3D.accessm_grid()[pos_mismatch.second][pos_mismatch.first] =
              m_map3D.getm_grid()[each.second][each.first];
          m_map3D.accessm_grid()[each.second][each.first] = +Type::Void;

          m_map3D.accessm_objects()[pos_mismatch.second][pos_mismatch.first] =
              obj_tail;
          m_map3D.resetObject(each);
      } else {
        m_map3D.resetObject(each);
        m_map3D.accessm_grid()[each.second][each.first] = +Type::Void;
      }
    }
    
    if (m_RM.block_moved) {
      parseRules();
      m_RM.block_moved = false;
    }

    //////////// movimento visivo
    if (state == PlayState::Playing) {
      player_sprite.move(static_cast<float>(dx * 11),
                        static_cast<float>(dy * 11));
      m_map3D.redraw(clock);
      render(window, m_map3D.tileSprites);
      player_sprite.move(static_cast<float>(dx * 11),
                        static_cast<float>(dy * 11));
      m_map3D.redraw(clock);
      render(window, m_map3D.tileSprites);

    } else if (state == PlayState::Invalid) {
      player_sprite = m_map3D.tileSprites[player_move_index];
      player_sprite.move(static_cast<float>(dx) * -11,
                        static_cast<float>(dy) * -11);
      m_map3D.redraw(clock);
      render(window, m_map3D.tileSprites);
    } else if (state == PlayState::Won)
      m_state_of_game = PlayState::Won;

    player_sprite = m_map3D.tileSprites[player_idle_index];
    player_sprite.setTexture(m_map3D.textures[player_idle_index]);
    m_map3D.redraw(clock);
    render(window, m_map3D.tileSprites);
  }
  m_players = m_map3D.getPositions(Type::You);
  std::cerr << "Fine movement(): m_players.size() == " << m_players.size() << '\n';
}


void Game::interact(){
  for (const auto& pos : m_players){
    Position up {pos.first, pos.second -1};
    Position right {pos.first +1, pos.second};
    Position down {pos.first, pos.second +1};
    Position left {pos.first -1, pos.second};

    // i vector directions e adjacents fanno corrispondere direzione e casella adiacente
    const std::array<Position, 4> adjacents {up, right, down, left};
    const std::array<Direction, 4> directions {Direction::Up, Direction::Right, Direction::Down, Direction::Left};

    for (const auto each : directions){
      if (m_map3D.isOutOfBoundary(adjacents[static_cast<std::size_t>(+each)].first, adjacents[static_cast<std::size_t>(+each)].second)){
        continue;
      }
      Objects& target {m_map3D.At(adjacents[static_cast<std::size_t>(+each)])};

      if (target.objectHasType(Type::Lever) && !target.objectHasType(Type::Switch)){
        target.addType(Type::Switch);
        std::cerr << "interact(): lever_pos: " << adjacents[static_cast<std::size_t>(+each)].first << adjacents[static_cast<std::size_t>(+each)].second << ' ';
        m_map3D.pathFinder(adjacents[static_cast<std::size_t>(+each)], each, directions, true);
      } else if (target.objectHasType(Type::Lever) && target.objectHasType(Type::Switch)) {
        target.removeType(Type::Switch);
        m_map3D.pathFinder(adjacents[static_cast<std::size_t>(+each)], each, directions, false);
      }
    }
  }
}

void Game::update(sf::RenderWindow &window, sf::Clock &clock) {
  sf::Event event;
  Direction direction;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();

    if (event.type == sf::Event::KeyPressed){
        switch(event.key.code){
            case sf::Keyboard::Escape:
                window.close();
                break;
            case sf::Keyboard::W:
                direction = Direction::Up;
                movement(window, clock, direction);
                break;
            case sf::Keyboard::A:
                direction = Direction::Left;
                movement(window, clock, direction);
                break;
            case sf::Keyboard::S:
                direction = Direction::Down;
                movement(window, clock, direction);
                break;
            case sf::Keyboard::D:
                direction = Direction::Right;
                movement(window, clock, direction);
                break;
            case sf::Keyboard::Space: 
                interact();
                break;
            default: 
                break;
        }
        if(m_players.size() == 0) m_state_of_game = PlayState::Lose;
        if (m_state_of_game == PlayState::Lose) {
            std::cerr << "Hai perso :(\n";
            window.close();}
        if (m_state_of_game == PlayState::Won) {
            std::cerr << "Hai vinto! :)\n";
            window.close();}
    }
  }
}
    
    /////////////////////////////////// Chapter: Handling Displaying ///////////////////////////////////
    void Game::render(sf::RenderWindow &window, std::array<sf::Sprite, tilePaths.size()>& sprites){
      window.clear();
      std::size_t x;
      std::size_t y;
      std::size_t count{};
      for (auto& rows : m_map3D.getm_grid()){

          for (auto &i : rows){
            
            assert (i != +Type::NOUN_TYPE && i != +Type::ICON_NOUN_TYPE 
                  && i != +Type::VERB_TYPE && i != +Type::PROPERTY_TYPE 
                  && i != +Type::Block     && i != +Type::Icon_Void && "in render() not given tail valid value in m_grid[0]\n");
            if(indexToBeDrawn(i) > tilePaths.size()) continue;

            std::size_t nth_sprite_to_be_drawn {indexToBeDrawn(i) };
            assert(nth_sprite_to_be_drawn < tilePaths.size() 
                && "render()'s nth_sprite... is beyond tilePaths.size()");

            if (nth_sprite_to_be_drawn < tilePaths.size()) {
              // posiziona e disegna ogni sprite
              
              x = (count % MapSize::width) * MapSize::TILE_SIZE; 
              y = (count / MapSize::height) * MapSize::TILE_SIZE; // = 0, 32, 64, ... 15*32

              sprites[nth_sprite_to_be_drawn].setPosition(static_cast<float>(x),
                                                          static_cast<float>(y));
              // flippo lo sprite delle leve che sono state attivate
              if (m_map3D.At(count % MapSize::width, count / MapSize::height).objectHasType(Type::Switch)) 
                sprites[nth_sprite_to_be_drawn].setTextureRect({(m_map3D.nth_frame + 1) * MapSize::TILE_SIZE, 0, -MapSize::TILE_SIZE, MapSize::TILE_SIZE});
              window.draw(sprites[nth_sprite_to_be_drawn]);
            }
        ++count;
      }
  }
  window.display();
}

/////////////////////////////////// Chapter: Handling Interactions //////////////////////////////////////
PlayState handleDefeat(Objects &tail) {
  if (tail.objectHasType(Type::You)) {
    tail.resetObject();
    return PlayState::Invalid;
  }
  return PlayState::Playing;
}
PlayState handleWin(Objects &tail, Objects &mismatch) {
  if (mismatch.objectHasType(Type::Defeat)) {
    handleDefeat(tail);
  }
  return PlayState::Won;
}
PlayState handleHot(Objects &tail) {
  if (!tail.objectHasType(Type::Push)) {
    tail.resetObject();
    return PlayState::Invalid;
  }
  return PlayState::Playing;
}
PlayState handleMelt(Objects &tail) { 
  tail.resetObject();
  return PlayState::Invalid;
}
PlayState handleShut(Objects &tail, Objects &mismatch) {
  if (!tail.objectHasType(Type::Open)) {
    tail.resetObject();
    return PlayState::Invalid;
  }
  mismatch.resetObject();
  tail.resetObject();
  return PlayState::Playing;
}
PlayState handleSpin (Objects& tail, Objects& mismatch) {
  if (mismatch.objectHasType(Type::Win)) {
    return handleWin(tail, mismatch);
  }
  else if (mismatch.objectHasType(Type::Defeat)) {
    return handleDefeat(tail);
  }
  return PlayState::Invalid;
}
PlayState handleStop(Objects &tail) {
  if (!tail.objectHasType(Type::Push)) {
    return PlayState::Invalid;
  }
  return PlayState::Playing;
}

PlayState Game::conditions(Objects &tail, Objects &mismatch) {
  PlayState result {PlayState::Playing};
  if(mismatch == tail) return result;

  for (Type mism_type : mismatch.getTypes()) { 
  
    if (+mism_type <= +Type::PROPERTY_TYPE) {
      continue;
    }
    switch (mism_type) { // clang-format off
    case Type::Defeat:  return handleDefeat(tail);
    case Type::Hot:     if (tail.objectHasType(Type::Melt)){    
                          result = handleMelt(tail); 
                          break;
                        } else {
                          result = handleHot(tail);
                          break;
                        }
    case Type::Melt:    break; // Melt influenza solo se chi si muove incontra Hot
    case Type::Shut:    result = handleShut(tail, mismatch); break;
    case Type::Spin:    return handleSpin(tail, mismatch);
    case Type::Stop:    result = handleStop(tail); break;

    case Type::Switch:
    case Type::Push:
    case Type::Open:
    case Type::You:     break;

    case Type::Win:     return handleWin(tail, mismatch); // verrebbe sovrascritto
    default:  throw(std::runtime_error("conditions(): default statement")); break;
    } // clang-format on
    if (result == PlayState::Invalid) return PlayState::Invalid;
  }
  return result;
}
} // namespace Baba_Is_Us