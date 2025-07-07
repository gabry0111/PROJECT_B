#include "game.hpp"

namespace Baba_Is_Us {

Game::Game(const std::string_view filename)
    : m_map3D{filename}, m_RM{}, m_players{} {
  m_RM.clearRules();
  constantProperties();
  parseRules();
  m_players = m_map3D.getPositions(Type::You);
}
const std::vector<Position> &Game::getPlayerPositions() const {
  return m_players;
}

///////////////////////////  Chapter: HandlingRules  ///////////////////////////

constexpr Type iconToAll(const Type type) {
  switch (type) {  // clang-format off
    case Type::Icon_Void:     return Type::Void;
    case Type::Icon_Baba:     return Type::Baba;
    case Type::Icon_Defeat:   return Type::Defeat;
    case Type::Icon_Door:     return Type::Door;
    case Type::Icon_Flag:     return Type::Flag;
    case Type::Icon_Gear:     return Type::Gear;
    case Type::Icon_Hot:      return Type::Hot;
    case Type::Icon_Is:       return Type::Is;
    case Type::Icon_Key:      return Type::Key;
    case Type::Icon_Lava:     return Type::Lava;
    case Type::Icon_Lever:    return Type::Lever;
    case Type::Icon_Melt:     return Type::Melt;
    case Type::Icon_Push:     return Type::Push;
    case Type::Icon_Rock:     return Type::Rock;
    case Type::Icon_Shut:     return Type::Shut;
    case Type::Icon_Stop:     return Type::Stop;
    case Type::Icon_Wall:     return Type::Wall;
    case Type::Icon_Win:      return Type::Win;
    case Type::Icon_You:      return Type::You;
    default:                  throw(std::runtime_error("iconToAll(): not given an ICON_TYPE"));
  }  // clang-format on
}

void Game::adjustAddingRules() {
  const std::vector<Rule> &rules{m_RM.getm_rules()};
  assert(rules.size() > 0);
  for (const Rule &each_rule : rules) {
    const Type noun_type{each_rule.getm_rule()[0]};
    assert(noun_type != Type::Block &&
           "adjustAddingRules(): noun_type == Type::Block");
    const Type prop_or_noun_type{each_rule.getm_rule()[2]};
    const std::vector<Position> &pos_of_types_with_rule{
        m_map3D.getPositions(noun_type)};

    assert(((+prop_or_noun_type > +Type::NOUN_TYPE &&
             +prop_or_noun_type < +Type::ICON_NOUN_TYPE) ||
            (+prop_or_noun_type > +Type::PROPERTY_TYPE)) &&
           "adjustAddingRules(): prop_or_noun_type not one of the two Types");
    for (const Position &each_pos : pos_of_types_with_rule) {
      Objects &obj{m_map3D.At(each_pos)};

      if (+prop_or_noun_type > +Type::PROPERTY_TYPE) {
        if (!obj.objectHasType(prop_or_noun_type)) {
          obj.addType(prop_or_noun_type);
        }
      } else {
        obj.addType(prop_or_noun_type);
        for (const Rule &iter_rules : m_RM.getm_rules()) {
          if (std::find(iter_rules.getm_rule().begin(),
                        iter_rules.getm_rule().end(),
                        prop_or_noun_type) != iter_rules.getm_rule().end()) {
            obj.addType(iter_rules.getm_rule()[2]);
          }
        }
      }
    }
  }
}

void Game::createRule(const std::vector<Type> &word1,
                      const std::vector<Type> &word2,
                      const std::vector<Type> &word3) {
  assert(!word2.empty() && !word3.empty() && "createRule()");

  const Type type1{iconToAll(word1[1])};
  const Type type2{iconToAll(word2[1])};
  const Type type3{iconToAll(word3[1])};
  if (+type1 > +Type::NOUN_TYPE && +type1 < +Type::ICON_NOUN_TYPE &&
      +type2 > +Type::VERB_TYPE && +type2 < +Type::PROPERTY_TYPE &&
      (+type3 > +Type::PROPERTY_TYPE ||
       (+type3 > +Type::NOUN_TYPE && +type3 < +Type::ICON_NOUN_TYPE))) {
    const bool already_exists{std::any_of(
        m_RM.getm_rules().begin(), m_RM.getm_rules().end(),
        [&](const Rule &rule) {
          return rule.getm_rule()[0] == type1 && rule.getm_rule()[1] == type2 &&
                 rule.getm_rule()[2] == type3;
        })};
    if (!already_exists) m_RM.addRule({type1, type2, type3});
  }
}

void Game::adjustRemovingRules() {
  // tolgo ogni le proprietà date SOLO dalle regole che non siano il primo tipo
  for (const Rule &rule : m_RM.getm_rules()) {
    const Type &first_type{rule.getm_rule()[0]};
    for (const Position &pos : m_map3D.getPositions(rule.getm_rule()[0])) {
      Objects &obj{m_map3D.At(pos)};
      for (const Type type : obj.getTypes())
        if (type != first_type) obj.removeType(type);
    }
  }
}

void Game::parseRules() {
  if (!m_RM.getm_rules().empty()) {
    adjustRemovingRules();
  }
  m_RM.clearRules();
  const std::vector<Position> &block_pos{m_map3D.getPositions(Type::Block)};

  for (const Position &pos : block_pos) {
    if (!m_map3D.isOutOfBoundary(pos.first, pos.second + 2)) {
      const auto &word1{m_map3D.At(pos.first, pos.second).getTypes()};
      const auto &word2{m_map3D.At(pos.first, pos.second + 1).getTypes()};
      const auto &word3{m_map3D.At(pos.first, pos.second + 2).getTypes()};

      if (word2[0] == Type::Block && word3[0] == Type::Block)
        createRule(word1, word2, word3);
    }

    if (!m_map3D.isOutOfBoundary(pos.first + 2, pos.second)) {
      const auto &word1{m_map3D.At(pos.first, pos.second).getTypes()};
      const auto &word2{m_map3D.At(pos.first + 1, pos.second).getTypes()};
      const auto &word3{m_map3D.At(pos.first + 2, pos.second).getTypes()};

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
  m_map3D.spriteOverlay();
}

void Game::constantProperties() {
  for (std::size_t i{}; i < MapSize::n_tiles; ++i) {
    Objects &obj{m_map3D.At(i % MapSize::height, i / MapSize::width)};
    std::optional<Type> type_to_add{std::nullopt};
    for (const Type &type : obj.getTypes()) {
      switch (type) {  // clang-format off
        case Type::Door:  type_to_add = Type::Stop;  break;
        case Type::Key:   type_to_add = Type::Open;  break;
        default:                                     break;
      }  // clang-format on
    }
    if (!type_to_add)
      continue;
    else
      obj.addType(*type_to_add);
  }
}

///////////////// Chapter: Handling Movement and KeyPressing //////////////////

constexpr const Position getShift(const Direction dir) {
  switch (dir) {  // clang-format off
    case Direction::Up:     return {0, -1};
    case Direction::Down:   return {0, 1};
    case Direction::Left:   return {-1, 0};
    case Direction::Right:  return {1, 0};
    default:                throw(std::runtime_error("getShift(): not given a valid direction"));
  }  // clang-format on
}
// N.B: data una fila verticale di oggetti attaccati e la direzione Up,
// l'oggetto Tail è quello più in basso
bool isTailOfLine(const Position pos, const Map &map,
                        const Direction dir) {
  const Type type{map.At(pos).getTypes()[0]};
  const std::size_t dx{getShift(dir).first};
  const std::size_t dy{getShift(dir).second};
  if (map.isOutOfBoundary(pos.first - dx, pos.second - dy)) {
    return true;
  }
  return (type != map.At(pos.first - dx, pos.second - dy).getTypes()[0]);
}

const std::vector<Position> Game::getTailMovingPosition(
    const Direction direction) const {
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
const std::optional<Position> getMismatch(const Map &map, const Direction dir,
                                          const Position &start) {
  std::optional<Position> result{};
  const Position &shift{getShift(dir)};
  std::size_t x{start.first};
  std::size_t y{start.second};
  const int value{+map.getm_objects()[y][x].getTypes()[0]};

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

PlayState Game::processMove(Objects &tail, Objects &target,
                                  const Direction direction,
                                  const Position start) {
  const Position &shift{getShift(direction)};
  const Position &pos_mism{start.first + shift.first,
                           start.second + shift.second};
  const Position &pos_next_mism{pos_mism.first + shift.first,
                                pos_mism.second + shift.second};
  // per fermare la scansione degli oggetti
  if (target.objectHasType(Type::Void))
    return PlayState::Playing;
  else if (target.objectHasType(Type::Block))
    m_RM.block_moved = true;

  const PlayState state{conditions(tail, target)};

  if (tail.objectHasType(Type::Void)) {
    m_map3D.accessm_grid()[start.second][start.first] = +Type::Void;
  }
  if (target.objectHasType(Type::Void)) {
    m_map3D.accessm_grid()[pos_mism.second][pos_mism.first] = +Type::Void;
  }

  if (state == PlayState::Invalid) {
    return PlayState::Invalid;
  } else if (state == PlayState::Won) {
    return PlayState::Won;
  }

  if (m_map3D.isOutOfBoundary(pos_next_mism.first, pos_next_mism.second))
    return PlayState::Invalid;

  if (processMove(target, m_map3D.At(pos_next_mism), direction, pos_mism) ==
      PlayState::Invalid)
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

void Game::movement(sf::RenderWindow &window, sf::Clock &clock,
                    const Direction direction) {
  const Position &shift{getShift(direction)};
  const std::size_t dx{shift.first};
  const std::size_t dy{shift.second};
  const std::vector<Position> &tail_pos{getTailMovingPosition(direction)};

  for (auto &each : tail_pos) {
    std::size_t player_move_index{static_cast<std::size_t>(+direction + 1)};
    std::size_t player_idle_index{static_cast<std::size_t>(+direction + 5)};
    std::size_t index_player_sprite{
        indexToBeDrawn(m_map3D.getm_grid()[each.second][each.first])};
    sf::Sprite &player_sprite{m_map3D.tileSprites[index_player_sprite]};

    // solo Baba (in tilePaths con indice da 1 a 8) ha varianti nelle texture.
    // Per prima cosa, giriamo la sprite.
    if (index_player_sprite >= 1 && index_player_sprite <= 8) {
      player_sprite.setTexture(m_map3D.textures[player_idle_index]);
    } else {
      player_move_index = index_player_sprite;
      player_idle_index = index_player_sprite;
    }
    m_map3D.redraw(clock);
    render(window, m_map3D.tileSprites);

    if (!getMismatch(m_map3D, direction, each)) continue;
    const Position pos_mismatch{*getMismatch(m_map3D, direction, each)};
    const std::size_t delta_x{pos_mismatch.first - each.first};
    const std::size_t delta_y{pos_mismatch.second - each.second};
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
    Objects &obj_tail{m_map3D.At(each)};
    Objects &obj_mismatch{m_map3D.At(pos_mismatch)};

    if (obj_mismatch.objectHasType(Type::Block) &&
        m_map3D.isOutOfBoundary(pos_mismatch.first + dx,
                                pos_mismatch.second + dy)) {
      continue;
    }

    const PlayState state{processMove(obj_tail, obj_mismatch, direction, each)};
    m_players = m_map3D.getPositions(Type::You);
    if (state == PlayState::Won) {
      m_state_of_game = PlayState::Won;
      return;
    } else if (m_players.size() == 0) {
      m_state_of_game = PlayState::Lose;
      return;
    }
    if (state == PlayState::Playing) {
      if (obj_mismatch.objectHasType(Type::Void)) {
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
}

void Game::interact() {
  for (const auto &pos : m_players) {
    const Position &up{pos.first, pos.second - 1};
    const Position &right{pos.first + 1, pos.second};
    const Position &down{pos.first, pos.second + 1};
    const Position &left{pos.first - 1, pos.second};
    const std::array<Position, 4> &adjacents{up, right, down, left};
    const std::array<Direction, 4> &directions{
        Direction::Up, Direction::Right, Direction::Down, Direction::Left};

    for (const auto each : directions) {
      if (m_map3D.isOutOfBoundary(
              adjacents[static_cast<std::size_t>(+each)].first,
              adjacents[static_cast<std::size_t>(+each)].second)) {
        continue;
      }
      Objects &target{m_map3D.At(adjacents[static_cast<std::size_t>(+each)])};

      if (target.objectHasType(Type::Lever) &&
          !target.objectHasType(Type::Switch)) {
        target.addType(Type::Switch);
        m_map3D.pathFinder(adjacents[static_cast<std::size_t>(+each)], each,
                           directions, true);
      } else if (target.objectHasType(Type::Lever) &&
                 target.objectHasType(Type::Switch)) {
        target.removeType(Type::Switch);
        m_map3D.pathFinder(adjacents[static_cast<std::size_t>(+each)], each,
                           directions, false);
      }
    }
  }
}

void Game::update(sf::RenderWindow &window, sf::Clock &clock) {
  sf::Event event;
  Direction direction;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();

    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
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
      if (m_players.size() == 0) m_state_of_game = PlayState::Lose;
      if (m_state_of_game == PlayState::Lose) {
        std::cout << "Hai perso :(\n";
        window.close();
      }
      if (m_state_of_game == PlayState::Won) {
        std::cout << "Hai vinto! :)\n";
        window.close();
      }
    }
  }
}

///////////////////////// Chapter: Handling Displaying /////////////////////////
void Game::render(sf::RenderWindow &window,
                  std::array<sf::Sprite, tilePaths.size()> &sprites) {
  window.clear();
  std::size_t x;
  std::size_t y;
  std::size_t count{};
  for (auto &rows : m_map3D.getm_grid()) {
    for (const int i : rows) {
      assert(i != +Type::NOUN_TYPE && i != +Type::ICON_NOUN_TYPE &&
             i != +Type::VERB_TYPE && i != +Type::PROPERTY_TYPE &&
             i != +Type::Block && i != +Type::Icon_Void &&
             "in render() not given tail valid value in m_grid[0]\n");
      if (indexToBeDrawn(i) > tilePaths.size()) continue;

      const std::size_t nth_sprite_to_be_drawn{indexToBeDrawn(i)};
      assert(nth_sprite_to_be_drawn < tilePaths.size() &&
             "render()'s nth_sprite... is beyond tilePaths.size()");

      if (nth_sprite_to_be_drawn < tilePaths.size()) {
        x = (count % MapSize::width) * MapSize::TILE_SIZE;
        y = (count / MapSize::height) * MapSize::TILE_SIZE;
        sprites[nth_sprite_to_be_drawn].setPosition(static_cast<float>(x),
                                                    static_cast<float>(y));
        // flippo lo sprite delle leve che sono state attivate
        if (m_map3D.At(count % MapSize::width, count / MapSize::height)
                .objectHasType(Type::Switch))
          sprites[nth_sprite_to_be_drawn].setTextureRect(
              {(m_map3D.nth_frame + 1) * MapSize::TILE_SIZE, 0,
               -MapSize::TILE_SIZE, MapSize::TILE_SIZE});
        window.draw(sprites[nth_sprite_to_be_drawn]);
      }
      ++count;
    }
  }
  window.display();
}

}  // namespace Baba_Is_Us