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
}

using MapGrid2D = std::array<std::array<int, MapSize::height>, MapSize::width>;

namespace Baba_Is_Us {

inline std::array<std::string, 31> tilePaths{
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
    "assets/png_PROGETTO/text/FLAG_text_spritesheet.png",       // 19
    "assets/png_PROGETTO/text/HOT_text_spritesheet.png",        // 20
    "assets/png_PROGETTO/text/IS_text_spritesheet.png",         // 21
    "assets/png_PROGETTO/text/LAVA_text_spritesheet.png",       // 22
    "assets/png_PROGETTO/text/MELT_text_spritesheet.png",       // 23
    "assets/png_PROGETTO/text/PUSH_text_spritesheet.png",       // 24
    "assets/png_PROGETTO/text/ROCK_text_spritesheet.png",       // 25
    "assets/png_PROGETTO/text/SHUT_text_spritesheet.png",       // 26
    "assets/png_PROGETTO/text/STOP_text_spritesheet.png",       // 27
    "assets/png_PROGETTO/text/WALL_text_spritesheet.png",       // 28
    "assets/png_PROGETTO/text/WIN_text_spritesheet.png",        // 29
    "assets/png_PROGETTO/text/YOU_text_spritesheet.png"         // 30
};

// associamo gli int sottostanti da enum Type, dati in level.txt, a un indice di tilePath
inline std::size_t indexToBeDrawn(const int i) {
  std::size_t nth{};
  std::string substring;
  std::size_t tilePaths_size{tilePaths.size()};
  auto searchIndex = [tilePaths_size](const std::string &sub) -> std::size_t {
    for (std::size_t iter = 0; iter < tilePaths_size; ++iter) {
      if (tilePaths[iter].find(sub) != std::string::npos) return iter;
    }
    return tilePaths_size;
  };
  // clang-format off
  switch (i) {
    case 0: substring = "gifs/VOID";                    break;
    case 1: substring = "gifs/BABA_spritesheet_right";  break; // fisso il default di Baba a BABA_right.png
    case 3: substring = "gifs/DOOR";                    break;
    case 4: substring = "gifs/FLAG";                    break;
    case 5: substring = "gifs/GEAR";                    break;
    case 6: substring = "gifs/KEY";                     break;
    case 7: substring = "gifs/LAVA";                    break;
    case 8: substring = "gifs/LEVER_LEFT";              break;
    case 9: substring = "gifs/ROCK";                   break;
    case 10: substring = "gifs/WALL";                   break;

  case 13:
    substring = "text/BABA";
    break;
  case 14:
    substring = "text/DEFEAT";
    break;
  case 15:
    substring = "text/FLAG";
    break;
  case 16:
    substring = "text/HOT";
    break;
  case 17:
    substring = "text/IS";
    break;
  case 18:
    substring = "text/LAVA";
    break;
  case 19:
    substring = "text/MELT";
    break;
  case 20:
    substring = "text/PUSH";
    break;
  case 21:
    substring = "text/ROCK";
    break;
  case 22:
    substring = "text/STOP";
    break;
  case 23:
    substring = "text/WALL";
    break;
  case 24:
    substring = "text/WIN";
    break;
  case 25:
    substring = "text/YOU";
    break;
  default : break;
  } //clang-format on
  if (substring.size() == 0) throw (std::runtime_error("intToBeDrawn(): index in level.txt too high"));
  else {return (nth = searchIndex(substring));}
}

inline std::size_t findLastNoun(const std::vector<Type>& types) {
  std::size_t last {};
  for (std::size_t i{}; i < types.size(); ++i) {
      if (+types[i] > +Type::Void && +types[i] < +Type::ICON_NOUN_TYPE) { 
          last = i;
      }
  }
  return static_cast<std::size_t>(+(types[last])); 
}

//clang-format off
inline Type iconToAll(Type type) {
  switch (type) {
    case Type::Icon_Void:   return Type::Void;
    case Type::Icon_Baba:   return Type::Baba;
    case Type::Icon_Defeat: return Type::Defeat;
    case Type::Icon_Flag:   return Type::Flag;
    case Type::Icon_Hot:    return Type::Hot;
    case Type::Icon_Is:     return Type::Is;
    case Type::Icon_Lava:   return Type::Lava;
    case Type::Icon_Melt:   return Type::Melt;
    case Type::Icon_Push:   return Type::Push;
    case Type::Icon_Rock:   return Type::Rock;
    case Type::Icon_Stop:   return Type::Stop;
    case Type::Icon_Wall:   return Type::Wall;
    case Type::Icon_Win:    return Type::Win;
    case Type::Icon_You:    return Type::You;
    default:  throw(std::runtime_error("iconToAll(): not given an ICON_TYPE"));
  } //clang-format on
}

class Map {
 private:
  // N.B: [0][1][2] accedi a depth = 0; x (width) = 1; y (height) = 2
  std::array<MapGrid2D, MapSize::depth> m_grid;

  // N.B: [1][2] accedi a x (width) = 1; y (height) = 2
  std::array<std::array<Objects, MapSize::height>, MapSize::width> m_objects;

 public:
  bool isOutOfBoundary(std::size_t x, std::size_t y) const;

  std::vector<sf::Texture> textures{};
  std::vector<int> frameCounts{};
  int nth_frame{};
  std::vector<sf::Sprite> tileSprites{};

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
  const std::vector<sf::Sprite> &getTileSprites() const;
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
  void pathFinder(Position, Direction, std::vector<Position>&, std::vector<Direction>&);
};
std::size_t indexToBeDrawn(const std::size_t i);

}  // namespace Baba_Is_Us
#endif