#include "map.hpp"
#include "enum_objects.hpp"
#include "objects.hpp"
#include "rules.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
using Position = std::pair<std::size_t, std::size_t>;

namespace Baba_Is_Us {

Map::Map(std::string_view filename) {
  std::ifstream map_file{
      filename.data()}; // comincia dall'inizio di file.txt bidimensionale
  if (!map_file) {
    std::cerr << "Error! can't open level";
  }
  int value{};

  // Questo for parte dal presupposto che level.txt abbia valori corrispondenti
  // ad enum_objects.hpp (minori di VERB_TYPE (altrimento li skippa quando
  // disegna e viene tutto traslato)), e non valori corrispondenti a tilePaths.
  for (std::size_t iii = 0; iii < MapSize::height * MapSize::width; ++iii) {
    map_file >> value;
    std::cerr << value;
    std::vector<Type> current{};

    // N.B: value si basa su enum_objects. NON DEVE ESISTERE VALUE == BLOCK Nè
    // Icon_Void
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

    // Così come è ora valgono anche le PROPERTY_TYPE
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

  std::cout << "\nno gay\n";
}

void Map::spriteOverlay() {
  for (std::size_t i{}; i < MapSize::n_tiles; ++i) {
    Objects &obj = m_objects[i / MapSize::width][i % MapSize::height];
    if (obj.getTypes()[0] != Type::Block) {
      m_grid[0][i / MapSize::width][i % MapSize::height] =
          static_cast<int>(findLastNoun(obj.getTypes()));
    }
  }
  std::cerr << "----------------------------\n";
  for (auto &col : m_grid[0]) {
    for (auto &row : col) {
      std::cerr << row << ' ';
    }
    std::cerr << '\n';
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
  for (auto &path : tilePaths) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) { // il bastardo non vuole string_view
      std::cerr << "Failed to load " << path << "\n";
      continue;
    }
    textures.emplace_back(texture);
  }
  std::cerr << nth_frame << ' ' << textures.size() << ' '
            << '\n'; // tutte 25, testato
}

void Map::setSprites() {
  // converti le path in sprites
  sf::Sprite sprite;

  for (const auto &texture : textures) {
    // metto la texture sullo sprite
    sprite.setTexture(texture);

    sprite.setTextureRect(
        {0, 0, MapSize::TILE_SIZE, MapSize::TILE_SIZE}); // snip snip 32x32

    // gli indici saranno sempre nell'ordine di tilePaths
    tileSprites.emplace_back(
        sprite); // alla fine avrà tilePaths.size() elementi, ognuno con una
                 // sprite (<- quella che si beve?)
  }
  std::cerr << tileSprites.size() << " loaded sprites\n";
}

// SE ESISTE ALMENO UNA NON ANIMAZIONE, SIAMO FOTTUTI
void Map::redraw(sf::Clock &clock) {

  if (clock.getElapsedTime().asMilliseconds() >= MapSize::FRAME_TIME_MS) {

    // change the current frame of every individual texture
    // it could be different across textures if we add more detailed
    // spritesheets or more frames per animation
    nth_frame = (nth_frame + 1) %
                MapSize::FRAMES_PER_ANIMATION; // le animazioni sono sempre
                                               // composte da 3 frame

    clock.restart();
  }
  // resize and draw
  for (std::size_t i{}; i < tileSprites.size(); ++i) {
    tileSprites[i].setTextureRect({nth_frame * MapSize::TILE_SIZE, nth_frame,
                                   MapSize::TILE_SIZE, MapSize::TILE_SIZE});
  }
}

const std::vector<sf::Sprite> &Map::getTileSprites() const {
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
  // static_assert (MapSize::height * MapSize::width == map_grid.size() *
  // map_grid[0].size() && "Map::Reset(): sizes not equal");
  if (MapSize::height * MapSize::width != m_grid.size())
    throw std::runtime_error("Map::Reset(): sizes not equal");

  std::size_t iii{};
  for (auto &rows : map_grid) {
    for (auto &eee : rows) {
      if (+(m_objects[iii / MapSize::width][iii % MapSize::width]
                .getTypes()[0]) !=
          eee) // se il NOUN_TYPE dell'oggetto nella mappa != corrispondente int
               // di new_grid_map
        m_objects[iii / MapSize::width][iii % MapSize::width].getTypes()[0] =
            static_cast<Type>(eee);
      ++iii;
    }
  }
}

// At(y,x) getPos.. pos{y,x} if(m_obj[y][x]) QUASI GIUSTO, INVERTE BLOCK CON
// BABA At(y,x) getPos.. pos{x,y} if(m_obj[y][x]) NO C'è BLOCK IS YOU E BABA DA
// SOLA, SCAMBIATI At(y,x) getPos.. pos{x,y} if(m_obj[x][y]) NO C'è BLOCK IS E
// BABA YOU, SCAMBIATI (se l'ultimo m_obj resta[y][x] BABA è DA SOLA) At(y,x)
// getPos.. pos{y,x} if(m_obj[x][y]) NO C'è BLOCK IS YOU E BABA DA SOLA,
// SCAMBIATI At(x,y) getPos.. pos{y,x} if(m_obj[y][x]) NO At(x,y) getPos..
// pos{x,y} if(m_obj[y][x]) NO At(x,y) getPos.. pos{y,x} if(m_obj[x][y]) NO
// At(x,y) getPos.. pos{x,y} if(m_obj[x][y]) NO C'è BLOCK IS YOU E BLOCK IS,
// SCAMBIATI
//  Modificato --------------
// At(y,x) getPos.. pos{y,x} if(m_obj[y][x]) BLOCK IS, BABA YOU SCAMBIATI,
// VERTICALE <-> ORIZZONTALE At(y,x) getPos.. pos{x,y} if(m_obj[y][x]) BLOCK IS
// YOU, BABA SCAMBIATI, VERTICALE <-> ORIZZONTALE At(y,x) getPos.. pos{y,x}
// if(m_obj[x][y]) BLOCK IS YOU, BABA SCAMBIATI, VERTICALE <-> ORIZZONTALE
// At(y,x) getPos.. pos{x,y} if(m_obj[x][y]) BLOCK IS, BABA YOU SCAMBIATI,
// VERTICALE <-> ORIZZONTALE At(x,y) getPos.. pos{x,y} if(m_obj[x][y]) BLOCK IS
// YOU, BLOCK IS (come se Baba diventa Block), VERTICALE <-> ORIZZONTALE At(x,y)
// getPos.. pos{x,y} if(m_obj[y][x])       IL MIGLIOR TENTATIVO At(x,y) getPos..
// pos{y,x} if(m_obj[y][x]) At(x,y) getPos.. pos{y,x} if(m_obj[x][y])
//

Objects &Map::At(std::size_t x, std::size_t y) { return m_objects[y][x]; }
const Objects &Map::At(std::size_t x, std::size_t y) const {
  return m_objects[y][x];
}

const std::vector<Position> Map::getPositions(Type type) const {

  std::vector<Position> positions_with_type{};
  for (std::size_t y = 0; y < MapSize::height; ++y) {
    for (std::size_t x = 0; x < MapSize::width; ++x) {
      if (type == Type::Block) { // altrimenti conta come Baba anche i Blocks
        if ((m_objects[y][x].objectHasType(type))) {
          Position pos{x, y};
          positions_with_type.emplace_back(pos);
        }
      }

      if ((m_objects[y][x].objectHasType(type)) &&
          !m_objects[y][x].objectHasType(Type::Block)) {
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

} // namespace Baba_Is_Us