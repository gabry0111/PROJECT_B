#ifndef ENUM_OBJECTS_HPP
#define ENUM_OBJECTS_HPP

#include <iostream>
#include <type_traits> 

namespace Baba_Is_Us {

enum class Type { 
  NOUN_TYPE = -1,
  Void, 
  Baba,  // aspetto del Player di default
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

  ICON_NOUN_TYPE, // da rispettare l'ordine con NOUN_TYPE (l'int sottostante
                  // sarà calcolabile facilmente) abbinerà ciascun oggetto
                  // Objects alla sua sprite
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
  Open,   // key
  Push,
  Shut,   // door
  Spin,   // gear
  Stop,
  Switch, // lever
  Win,
  You,
};

// Overload the unary + operator to convert an enum class to the underlying type
template <typename T> constexpr int operator+(T a) noexcept {
  static_assert(std::is_enum_v<T> &&
                "Unary plus operator only works on enum types");
  return static_cast<std::underlying_type_t<T>>(a);
}

constexpr inline std::string_view getTypeName(Type type) {
  //clang-format off
  switch (type) { 
  case Type::NOUN_TYPE:       return "NOUN_TYPE";
  case Type::Void:            return "Void";
  case Type::Baba:            return "Baba";
  case Type::Block:           return "Block";
  case Type::Door:            return "Door";
  case Type::Flag:            return "Flag";
  case Type::Gear:            return "Gear";
  case Type::Key:             return "Key";
  case Type::Lava:            return "Lava";
  case Type::Lever:           return "Lever";
  case Type::Rock:            return "Rock";
  case Type::Wall:            return "Wall";

  case Type::ICON_NOUN_TYPE:  return "ICON_NOUN_TYPE";
  case Type::Icon_Void:       return "Icon_Void";
  case Type::Icon_Baba:       return "Icon_Baba";
  case Type::Icon_Defeat:     return "Icon_Defeat";
  case Type::Icon_Door:       return "Icon_Door";
  case Type::Icon_Flag:       return "Icon_Flag";
  case Type::Icon_Gear:       return "Icon_Gear";
  case Type::Icon_Hot:        return "Icon_Hot";
  case Type::Icon_Is:         return "Icon_Is";
  case Type::Icon_Key:        return "Icon_Key";
  case Type::Icon_Lava:       return "Icon_Lava";
  case Type::Icon_Lever:      return "Icon_Lever";
  case Type::Icon_Melt:       return "Icon_Melt";
  case Type::Icon_Push:       return "Icon_Push";
  case Type::Icon_Rock:       return "Icon_Rock";
  case Type::Icon_Shut:       return "Icon_Shut";
  case Type::Icon_Stop:       return "Icon_Stop";
  case Type::Icon_Wall:       return "Icon_Wall";
  case Type::Icon_Win:        return "Icon_Win";
  case Type::Icon_You:        return "Icon_You";

  case Type::VERB_TYPE:       return "VERB_TYPE";
  case Type::Is:              return "Is";

  case Type::PROPERTY_TYPE:   return "PROPERTY_TYPE";
  case Type::Defeat:          return "Defeat";
  case Type::Hot:             return "Hot";
  case Type::Melt:            return "Melt";
  case Type::Open:            return "Open";
  case Type::Push:            return "Push";
  case Type::Shut:            return "Shut";
  case Type::Spin:            return "Spin";
  case Type::Stop:            return "Stop";
  case Type::Switch:          return "Switch";
  case Type::Win:             return "Win";
  case Type::You:             return "You";
  default:                    return "No type";
  } // clang-format on
}
  
inline std::ostream &operator<<(std::ostream &out, Type type) {
  return out << getTypeName(type);
}

// associamo gli int sottostanti da enum Type, dati in level.txt, a un indice di tilePath.
inline std::size_t indexToBeDrawn(const int i) {
  switch (i) {
    case 0:  return 0;
    case 1:  return 6; // fisso il default sprite di Baba a BABA_right.png
    case 3:  
    case 4:  
    case 5:  
    case 6:  
    case 7:  
    case 8:  
    case 9:  
    case 10: return static_cast<std::size_t> (i + 6);

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
    case 30: return static_cast<std::size_t> (i + 4);
    default: throw(std::runtime_error("indexToBeDrawn(): not given a valid int from map_grid"));
  } //clang-format on
}

constexpr Type intToType(int value) { return static_cast<Type>(value); }

enum class PlayState {
  Invalid, // se un'azione non è andata a buon fine
  Playing, // azione andata a buon fine, stato di default
  Won,     // 'You' ha toccato 'Win'
  Lose,    // se niente è 'You' (=il gioco è fermo per sempre) o 'You' ha toccato 'Defeat'
};

enum class Direction {
  Up,
  Right,
  Down,
  Left,
};

} // namespace Baba_Is_Us

#endif