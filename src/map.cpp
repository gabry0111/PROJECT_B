#include "map.hpp"

namespace Baba_Is_Us {

std::size_t findLastNoun(const std::vector<Type> &types) {
  std::size_t last{};
  for (std::size_t i{}; i < types.size(); ++i) {
    if (+types[i] > +Type::Void && +types[i] < +Type::ICON_NOUN_TYPE) {
      last = i;
    }
  }
  return static_cast<std::size_t>(+(types[last]));
}

Map::Map(const std::string_view filename) {
  std::ifstream map_file{filename.data()};
  if (!map_file) {
    throw(std::runtime_error("Level invalid\n"));
  }
  int value{};

  // Si presuppone che valori in level.txt corrispondano ai Type dell'enum Class
  // (fino a Type::VERB_TYPE)
  for (std::size_t iii{}; iii < MapSize::height * MapSize::width; ++iii) {
    map_file >> value;
    std::vector<Type> current{};

    // N.B: value si basa su enum_objects. Non esistono value == Block o
    // == Icon_Void
    assert(value != +Type::NOUN_TYPE && value != +Type::ICON_NOUN_TYPE &&
           value != +Type::VERB_TYPE && value != +Type::PROPERTY_TYPE &&
           value != +Type::Block && value != +Type::Icon_Void &&
           "in Map(), level.txt there's an invalid value");

    if (value < +Type::ICON_NOUN_TYPE) {
      m_grid[iii / MapSize::width][iii % MapSize::height] = value;

      current.emplace_back(intToType(value));
      m_objects[iii / MapSize::width][iii % MapSize::height] = current;
    }

    else if (value > +Type::Icon_Void && value < +Type::VERB_TYPE) {
      m_grid[iii / MapSize::width][iii % MapSize::height] = value;
      current.emplace_back(Type::Block);
      current.emplace_back(intToType(value));
      m_objects[iii / MapSize::width][iii % MapSize::height] = current;
    } else
      throw(
          std::runtime_error("Map(): in level.txt not given a valid value "
                             "under +Type::VERB_TYPE"));
  }
  spriteOverlay();
}

void Map::spriteOverlay() {
  for (std::size_t i{}; i < MapSize::n_tiles; ++i) {
    const Objects &obj{m_objects[i / MapSize::width][i % MapSize::height]};
    if (obj.getTypes()[0] != Type::Block) {
      m_grid[i / MapSize::width][i % MapSize::height] =
          static_cast<int>(findLastNoun(obj.getTypes()));
    }
  }
}

void Map::placeTextures() {
  std::size_t iii{};
  for (auto &path : tilePaths) {
    sf::Texture texture;
    if (!texture.loadFromFile(static_cast<std::string>(path))) {
      throw(std::runtime_error("Failed to load file\n"));
      continue;
    }
    textures[iii] = texture;
    ++iii;
  }
}

void Map::placeSprites() {
  sf::Sprite sprite;
  std::size_t iii{};
  for (const auto &texture : textures) {
    sprite.setTexture(texture);
    sprite.setTextureRect({0, 0, MapSize::TILE_SIZE, MapSize::TILE_SIZE});
    // N.B: gli indici saranno sempre nell'ordine di tilePaths
    // alla fine avrà tilePaths.size() elementi, ognuno con una sprite diversa
    tileSprites[iii] = sprite;
    ++iii;
  }
}

void Map::redraw(sf::Clock &clock) {
  if (clock.getElapsedTime().asMilliseconds() >= MapSize::FRAME_TIME_MS) {
    // le animazioni sono sempre composte da 3 frame
    // cambia il frame per ogni texture nel suo successivo
    nth_frame = (nth_frame + 1) % MapSize::FRAMES_PER_ANIMATION;
    clock.restart();
  }
  for (std::size_t i{}; i < tileSprites.size(); ++i) {
    tileSprites[i].setTextureRect({nth_frame * MapSize::TILE_SIZE, 0,
                                   MapSize::TILE_SIZE, MapSize::TILE_SIZE});
  }
}

const std::vector<Position> Map::getPositions(const Type type) const {
  std::vector<Position> positions_with_type{};
  for (std::size_t y{}; y < MapSize::height; ++y) {
    for (std::size_t x{}; x < MapSize::width; ++x) {
      if (m_objects[y][x].objectHasType(type))
        positions_with_type.emplace_back(x, y);
    }
  }
  return positions_with_type;
}

void Map::addObject(const Position position, const Type type) {
  m_objects[position.first][position.second].addType(type);
}
void Map::resetObject(const Position position) {
  m_objects[position.second][position.first] = {{Type::Void}};
}

void Map::pathFinder(const Position start, const Direction dir,
                     const std::array<Direction, 4> &directions,
                     const bool to_activate) {
  if (isOutOfBoundary(start.first, start.second)) {
    return;
  }
  const Position &up{start.first, start.second - 1};
  const Position &right{start.first + 1, start.second};
  const Position &down{start.first, start.second + 1};
  const Position &left{start.first - 1, start.second};
  const std::array<Position, 4> &adjacents{up, right, down, left};
  // convertiamo la direzione di provenienza (dir) nella direzione da non
  // controllare
  const Direction dir_to_avoid{static_cast<Direction>((+dir + 2) % 4)};

  for (const Direction each : directions) {
    if (each == dir_to_avoid) continue;
    const Position &target_pos{adjacents[static_cast<std::size_t>(+each)]};
    if (isOutOfBoundary(target_pos.first, target_pos.second)) {
      continue;
    }
    Objects &target_obj{At(target_pos)};
    if (target_obj.objectHasType(Type::Gear) &&
        !target_obj.objectHasType(Type::Spin) && to_activate == true) {
      target_obj.addType(Type::Spin);
      pathFinder(target_pos, each, directions, true);
    } else if (target_obj.objectHasType(Type::Spin) && to_activate == false) {
      target_obj.removeType(Type::Spin);
      pathFinder(target_pos, each, directions, false);
    }
    if (target_obj.objectHasType(Type::Shut)) {
      target_obj.resetObject();
      m_grid[target_pos.second][target_pos.first] = +Type::Void;
      break;
    }
  }
}
}  // namespace Baba_Is_Us