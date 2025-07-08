#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string_view>

#include "enum_objects.hpp"
#include "objects.hpp"
#include "rules.hpp"

namespace MapSize {
constexpr int width{16};
constexpr int height{16};
constexpr int n_tiles{width * height};

constexpr int TILE_SIZE{32};
constexpr int FRAMES_PER_ANIMATION{3};
constexpr int FRAME_TIME_MS{150};
} // namespace MapSize

using Position = std::pair<std::size_t, std::size_t>;
using MapGrid2D = std::array<std::array<int, MapSize::height>, MapSize::width>;
using ObjectMap = std::array<std::array<Baba_Is_Us::Objects, MapSize::height>,
                             MapSize::width>;

namespace Baba_Is_Us {

constexpr const std::array<std::string_view, 35> tilePaths{
    "assets/png_PROGETTO/gifs/VOID_spritesheet.png",            // 0
    "assets/png_PROGETTO/gifs/BABA_move_up_spritesheet.png",    // 1
    "assets/png_PROGETTO/gifs/BABA_move_right_spritesheet.png", // 2
    "assets/png_PROGETTO/gifs/BABA_move_down_spritesheet.png",  // 3
    "assets/png_PROGETTO/gifs/BABA_move_left_spritesheet.png",  // 4
    "assets/png_PROGETTO/gifs/BABA_spritesheet_up.png",         // 5
    "assets/png_PROGETTO/gifs/BABA_spritesheet_right.png",      // 6
    "assets/png_PROGETTO/gifs/BABA_spritesheet_down.png",       // 7
    "assets/png_PROGETTO/gifs/BABA_spritesheet_left.png",       // 8
    "assets/png_PROGETTO/gifs/DOOR_spritesheet.png",            // 9
    "assets/png_PROGETTO/gifs/FLAG_spritesheet.png",            // 10
    "assets/png_PROGETTO/gifs/GEAR_spritesheet.png",            // 11
    "assets/png_PROGETTO/gifs/KEY_spritesheet.png",             // 12
    "assets/png_PROGETTO/gifs/LAVA_spritesheet.png",            // 13
    "assets/png_PROGETTO/gifs/LEVER_spritesheet.png",           // 14
    "assets/png_PROGETTO/gifs/ROCK_spritesheet.png",            // 15
    "assets/png_PROGETTO/gifs/WALL_spritesheet.png",            // 16
    "assets/png_PROGETTO/text/BABA_text_spritesheet.png",       // 17
    "assets/png_PROGETTO/text/DEFEAT_text_spritesheet.png",     // 18
    "assets/png_PROGETTO/text/DOOR_text_spritesheet.png",       // 19
    "assets/png_PROGETTO/text/FLAG_text_spritesheet.png",       // 20
    "assets/png_PROGETTO/text/GEAR_text_spritesheet.png",       // 21
    "assets/png_PROGETTO/text/HOT_text_spritesheet.png",        // 22
    "assets/png_PROGETTO/text/IS_text_spritesheet.png",         // 23
    "assets/png_PROGETTO/text/KEY_text_spritesheet.png",        // 24
    "assets/png_PROGETTO/text/LAVA_text_spritesheet.png",       // 25
    "assets/png_PROGETTO/text/LEVER_text_spritesheet.png",      // 26
    "assets/png_PROGETTO/text/MELT_text_spritesheet.png",       // 27
    "assets/png_PROGETTO/text/PUSH_text_spritesheet.png",       // 28
    "assets/png_PROGETTO/text/ROCK_text_spritesheet.png",       // 29
    "assets/png_PROGETTO/text/SHUT_text_spritesheet.png",       // 30
    "assets/png_PROGETTO/text/STOP_text_spritesheet.png",       // 31
    "assets/png_PROGETTO/text/WALL_text_spritesheet.png",       // 32
    "assets/png_PROGETTO/text/WIN_text_spritesheet.png",        // 33
    "assets/png_PROGETTO/text/YOU_text_spritesheet.png"         // 34
};

class Map {
private:
  MapGrid2D m_grid;
  ObjectMap m_objects;

public:
  std::array<sf::Texture, tilePaths.size()> textures{};
  int nth_frame{};
  std::array<sf::Sprite, tilePaths.size()> tileSprites{};

  Map() = delete;
  Map(std::string_view);

  constexpr bool isOutOfBoundary(const std::size_t x,
                                 const std::size_t y) const;
  void spriteOverlay();
  constexpr const MapGrid2D &getm_grid() const { return m_grid; }
  constexpr MapGrid2D &accessm_grid() { return m_grid; }
  constexpr const ObjectMap &getm_objects() const { return m_objects; }
  constexpr ObjectMap &accessm_objects() { return m_objects; }
  void placeTextures();
  void placeSprites();
  void redraw(sf::Clock &);
  constexpr const std::array<sf::Sprite, tilePaths.size()> &
  getTileSprites() const;
  void addObject(const Position position, const Type type);
  void resetObject(const Position position);
  constexpr Objects &At(const std::size_t x, const std::size_t y);
  constexpr const Objects &At(const std::size_t x, const std::size_t y) const;
  constexpr Objects &At(const Position position);
  constexpr const Objects &At(const Position position) const;
  const std::vector<Position> getPositions(const Type) const;
  // gestisce le interazioni tra You, Lever, Gear e Shut con Game::interact()
  void pathFinder(const Position, const Direction,
                  const std::array<Direction, 4> &, const bool);
};

constexpr bool Map::isOutOfBoundary(const std::size_t x,
                                    const std::size_t y) const {
  return ((x > MapSize::width - 1) || (y > MapSize::height - 1));
}

constexpr const std::array<sf::Sprite, tilePaths.size()> &
Map::getTileSprites() const {
  return tileSprites;
}
constexpr Objects &Map::At(const std::size_t x, const std::size_t y) {
  return m_objects[y][x];
}
constexpr const Objects &Map::At(const std::size_t x,
                                 const std::size_t y) const {
  return m_objects[y][x];
}
constexpr Objects &Map::At(const Position position) {
  return m_objects[position.second][position.first];
}
constexpr const Objects &Map::At(const Position position) const {
  return m_objects[position.second][position.first];
}

} // namespace Baba_Is_Us
#endif