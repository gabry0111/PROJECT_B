#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include <string_view>

#include "enum_objects.hpp"
#include "objects.hpp"

using Position = std::pair<std::size_t, std::size_t>;

namespace MapSize {
constexpr int width = 16;  // Number of tiles in the X direction = n° of columns
constexpr int height = 16; // Number of tiles in the Y direction = n° of rows
constexpr int depth = 2;
constexpr int n_tiles = width * height;

constexpr int TILE_SIZE = 32;
constexpr int FRAMES_PER_ANIMATION = 3;
constexpr int FRAME_TIME_MS = 150;
} // namespace MapSize

using MapGrid2D = std::array<std::array<int, MapSize::height>, MapSize::width>;

namespace Baba_Is_Us {

constexpr inline std::array<std::string_view, 35> tilePaths{
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
  // N.B: [0][1][2] accedi a depth = 0; x (width) = 1; y (height) = 2
  std::array<MapGrid2D, MapSize::depth> m_grid;

  // N.B: [1][2] accedi a x (width) = 1; y (height) = 2
  std::array<std::array<Objects, MapSize::height>, MapSize::width> m_objects;

 public:
  bool isOutOfBoundary(std::size_t x, std::size_t y) const;

  std::array<sf::Texture, tilePaths.size()> textures{};
  int nth_frame{};
  std::array<sf::Sprite, tilePaths.size()> tileSprites{};

  Map() = default;
  Map(std::string_view);

  void spriteOverlay();
  
  const std::array<MapGrid2D, MapSize::depth> &getm_grid() const;
  std::array<MapGrid2D, MapSize::depth> &accessm_grid();
  const std::array<std::array<Objects, MapSize::height>, MapSize::width> &
  getm_objects() const;
  std::array<std::array<Objects, MapSize::height>, MapSize::width> &
  accessm_objects();
  void setTextures();
  void setSprites();
  void redraw(sf::Clock &);
  const std::array<sf::Sprite, tilePaths.size()> &getTileSprites() const;
  sf::Sprite &accessWhichSpriteIsInPosition(Position &);

  // resetta la mappa (se PlayState::Invalid o se cambia livello)
  // N.B: ogni oggetto può avere proprietà che devono essere tolte richiamando
  // poi la funzione apposita che controlla le regole nella mappa
  void Reset(const std::array<std::array<int, MapSize::width>, MapSize::height>
                 &); 

  void addObject(Position position, Type type);

  void resetObject(Position position);

  // Quale oggetto c'è in quella posizione?
  Objects &At(std::size_t x, std::size_t y);
  const Objects &At(std::size_t x, std::size_t y) const; 
  Objects &At(Position);

  const std::vector<Position> getPositions(Type) const; 
  void pathFinder(Position, Direction, const std::array<Direction, 4>&, bool);
};

}  // namespace Baba_Is_Us
#endif