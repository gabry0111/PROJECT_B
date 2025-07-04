#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

using Position = std::pair<std::size_t, std::size_t>;

namespace Baba_Is_Us {

std::size_t findLastNoun(const std::vector<Type>& types) {
  std::size_t last {};
  for (std::size_t i{}; i < types.size(); ++i) {
      if (+types[i] > +Type::Void && +types[i] < +Type::ICON_NOUN_TYPE) { 
          last = i;
      }
  }
  return static_cast<std::size_t>(+(types[last])); 
}

Map::Map(std::string_view filename) {
  std::ifstream map_file{
      filename.data()}; // comincia dall'inizio di file.txt bidimensionale
  if (!map_file) {
    throw(std::runtime_error("Level invalid\n"));
  }
  int value{};

  // Si presuppone che valori in level.txt corrispondano ai Type dell'enum Class
  // (fino a Type::VERB_TYPE)
  for (std::size_t iii = 0; iii < MapSize::height * MapSize::width; ++iii) {
    map_file >> value;
    std::cerr << value;
    std::vector<Type> current{};

    // N.B: value si basa su enum_objects. Non esistono value == Block o
    // ==Icon_Void
    assert(value != +Type::NOUN_TYPE && value != +Type::ICON_NOUN_TYPE &&
           value != +Type::VERB_TYPE && value != +Type::PROPERTY_TYPE &&
           value != +Type::Block && value != +Type::Icon_Void &&
           "in Map(), level.txt there's an invalid value");

    if (value < +Type::ICON_NOUN_TYPE) { // NOUN_TYPE (+ Void)
      m_grid[1][iii / MapSize::width][iii % MapSize::width] = value;
      m_grid[0][iii / MapSize::width][iii % MapSize::width] = value;

      current.emplace_back(intToType(value));
      m_objects[iii / MapSize::width][iii % MapSize::width] = current;
    }

    else if (value > +Type::Icon_Void &&
             value < +Type::VERB_TYPE) { // Sono Blocks (non esiste Icon_Void)
      m_grid[1][iii / MapSize::width][iii % MapSize::width] = +Type::Block;
      m_grid[0][iii / MapSize::width][iii % MapSize::width] = value;

      current.emplace_back(Type::Block);
      current.emplace_back(intToType(value));
      m_objects[iii / MapSize::width][iii % MapSize::width] = current;
    } else
      throw(std::runtime_error("Map(): in level.txt not given a valid value "
                               "under +Type::VERB_TYPE"));
  }
  spriteOverlay();
}

void Map::spriteOverlay() {
  for (std::size_t i{}; i < MapSize::n_tiles; ++i) {
    Objects &obj = m_objects[i / MapSize::width][i % MapSize::height];
    if (obj.getTypes()[0] != Type::Block) {
      m_grid[0][i / MapSize::width][i % MapSize::height] =
          static_cast<int>(findLastNoun(obj.getTypes()));
    }
  }
}
const std::array<MapGrid2D, MapSize::depth> &Map::getm_grid() const {
  return m_grid;
}
std::array<MapGrid2D, MapSize::depth> &Map::accessm_grid() { return m_grid; }
const std::array<std::array<Objects, MapSize::width>, MapSize::height> &
Map::getm_objects() const {
  return m_objects;
}
std::array<std::array<Objects, MapSize::width>, MapSize::height> &
Map::accessm_objects() {
  return m_objects;
}

void Map::setTextures() {
  std::size_t iii {};
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

void Map::setSprites() {
  sf::Sprite sprite;
  std::size_t iii{};
  for (const auto &texture : textures) {
    sprite.setTexture(texture);

    sprite.setTextureRect({0, 0, MapSize::TILE_SIZE, MapSize::TILE_SIZE});

    // gli indici saranno sempre nell'ordine di tilePaths
    tileSprites[iii] = sprite; // alla fine avrà tilePaths.size()
                                      // elementi, ognuno con una sprite
    ++iii;
  }
}

void Map::redraw(sf::Clock &clock) {
  if (clock.getElapsedTime().asMilliseconds() >= MapSize::FRAME_TIME_MS) {
    // change the current frame of every individual texture
    // it could be different across textures if we add more detailed
    // spritesheets or more frames per animation
    // le animazioni sono sempre composte da 3 frame
    nth_frame = (nth_frame + 1) % MapSize::FRAMES_PER_ANIMATION;

    clock.restart();
  }
  // resize and draw
  for (std::size_t i{}; i < tileSprites.size(); ++i) {
    tileSprites[i].setTextureRect({nth_frame * MapSize::TILE_SIZE, 0,
                                   MapSize::TILE_SIZE, MapSize::TILE_SIZE});
  }
}

const std::array<sf::Sprite, tilePaths.size()> &Map::getTileSprites() const {
  return tileSprites;
}

sf::Sprite &Map::accessWhichSpriteIsInPosition(Position &position) {
  std::size_t index{static_cast<std::size_t>(
      getm_grid()[0][position.second][position.first])};

  assert(index < tileSprites.size() &&
         "accessWhichSpriteIsInPosition() has index too high");
  return tileSprites[index];
}

void Map::Reset(const std::array<std::array<int, MapSize::width>,
                                 MapSize::height> &map_grid) {
  if (MapSize::height * MapSize::width != m_grid.size())
    throw std::runtime_error("Map::Reset(): sizes not equal");

  std::size_t iii{};
  for (auto &rows : map_grid) {
    for (auto &eee : rows) {
      if (+(m_objects[iii / MapSize::width][iii % MapSize::width]
                .getTypes()[0]) != eee)
        m_objects[iii / MapSize::width][iii % MapSize::width].getTypes()[0] =
            static_cast<Type>(eee);
      ++iii;
    }
  }
}

Objects &Map::At(std::size_t x, std::size_t y) { return m_objects[y][x]; }
const Objects &Map::At(std::size_t x, std::size_t y) const {
  return m_objects[y][x];
}
Objects &Map::At(Position position) {
  return m_objects[position.second][position.first];
}

const std::vector<Position> Map::getPositions(Type type) const {
  std::vector<Position> positions_with_type{};
  for (std::size_t y = 0; y < MapSize::height; ++y) {
    for (std::size_t x = 0; x < MapSize::width; ++x) {
      if (m_objects[y][x].objectHasType(type)) {
        Position pos{x, y};
        positions_with_type.emplace_back(pos);
      }
    }
  }
  return positions_with_type;
}

bool Map::isOutOfBoundary(std::size_t x, std::size_t y) const {
  return ((x > MapSize::width - 1) || (y > MapSize::height - 1));
}

void Map::addObject(Position position, Type type) {
  m_objects[position.first][position.second].addType(type);
}
void Map::resetObject(Position position) {
  m_objects[position.second][position.first] = {{Type::Void}};
}

void Map::pathFinder(Position start, Direction dir,
                     const std::array<Direction, 4> &directions,
                     bool to_activate) {

  if (isOutOfBoundary(start.first, start.second)) {
    return;
  }
  Position up{start.first, start.second - 1};
  Position right{start.first + 1, start.second};
  Position down{start.first, start.second + 1};
  Position left{start.first - 1, start.second};

  const std::array<Position, 4> adjacents{up, right, down, left};

  // convertiamo la direzione di provenienza (dir) nella direzione da non
  // controllare
  const Direction dir_to_avoid{
      static_cast<Direction>((+dir + 2) % 4)}; // formula divina

  for (const auto each : directions) {
    if (each == dir_to_avoid)
      continue;
    Position target_pos{adjacents[static_cast<std::size_t>(+each)]};
    Objects &target_obj{At(target_pos)};

    if (target_obj.objectHasType(Type::Gear) &&
        !target_obj.objectHasType(Type::Spin) && to_activate == true) {
      target_obj.addType(Type::Spin);
      pathFinder(target_pos, each, directions, true);
    } else if (target_obj.objectHasType(Type::Spin) && to_activate == false) {
      target_obj.removeType(Type::Spin);
      pathFinder(target_pos, each, directions, false);
    } else if (target_obj.objectHasType(Type::Shut)) {
      target_obj.resetObject();
      m_grid[0][target_pos.second][target_pos.first] = +Type::Void;
      m_grid[1][target_pos.second][target_pos.first] = +Type::Void;
      break;
    }
  }
}
} // namespace Baba_Is_Us