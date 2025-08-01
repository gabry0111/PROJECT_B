#ifndef ENUM_OBJECTS_HPP
#define ENUM_OBJECTS_HPP

#include <stdexcept>
#include <type_traits>

namespace Baba_Is_Us {

enum class Type {
  NOUN_TYPE = -1,
  Void,
  Baba,  // Player di default
  Block, // per scriverci le parole (Baba, Is, Hot...) sopra. Sarà l'unica
         // eccezione al tipico m_object vector<Type> perché sarà del tipo
         // [0] = Block, [1] = ICON_NOUN_TYPE
  Door,
  Flag,
  Gear,
  Key,
  Lava,
  Lever,
  Rock,
  Wall,

  ICON_NOUN_TYPE, // da rispettare l'ordine con NOUN_TYPE
                  // abbinerà ciascun oggetto Objects alla sua sprite
  Icon_Void,
  Icon_Baba,
  Icon_Defeat,
  Icon_Door,
  Icon_Flag,
  Icon_Gear,
  Icon_Hot,
  Icon_Is,
  Icon_Key,
  Icon_Lava,
  Icon_Lever,
  Icon_Melt,
  Icon_Push,
  Icon_Rock,
  Icon_Shut,
  Icon_Stop,
  Icon_Wall,
  Icon_Win,
  Icon_You,

  VERB_TYPE,
  Is,

  PROPERTY_TYPE,
  Defeat,
  Hot,
  Melt,
  Open,
  Push,
  Shut,
  Spin,
  Stop,
  Switch,
  Win,
  You,
};

// da learncpp.com
template <typename T> constexpr int operator+(T a) noexcept {
  static_assert(std::is_enum_v<T> &&
                "Unary plus operator only works on enum types");
  return static_cast<std::underlying_type_t<T>>(a);
}

// associamo gli int sottostanti da enum Type, dati in level.txt, a un indice di
// tilePath.
constexpr std::size_t indexToBeDrawn(const int i) {
  switch (i) { // clang-format off
  case 0:   return 0;
  case 1:   return 6; // fisso il default sprite di Baba a BABA_right.png
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:  return static_cast<std::size_t>(i + 6);

  case 13:
  case 14:
  case 15:
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
  case 22:
  case 23:
  case 24:
  case 25:
  case 26:
  case 27:
  case 28:
  case 29:
  case 30:  return static_cast<std::size_t>(i + 4);
  default:  throw(std::runtime_error("indexToBeDrawn(): not given a valid int from map_grid"));
  } // clang-format on
}

constexpr Type intToType(int value) { return static_cast<Type>(value); }

enum class PlayState {
  Invalid,
  Playing,
  Won,
  Lose,
};

enum class Direction {
  Up,
  Right,
  Down,
  Left,
};

} // namespace Baba_Is_Us

#endif