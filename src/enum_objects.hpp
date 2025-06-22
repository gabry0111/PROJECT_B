#ifndef ENUM_OBJECTS_HPP
#define ENUM_OBJECTS_HPP

#include <type_traits> //per underlying_type
#include <iostream>


namespace Baba_Is_Us {

enum class Type {  // DA AGGIUNGERE overload per convertirli in int (learncpp.com)
  NOUN_TYPE=-1,
  Void, // possiamo creare un vector o array così: std::array<std::array<int,colonne>,righe> e inizializzare tutto a void; poi aggiungere ciascun elemento
        // oppure serve per vettore di alcune informazioni (findPlayer() fallisce => PlayState::Invalid) (N.B: void negli if = false)
  Baba, // aspetto del Player di default
  Block, // per scriverci le parole (Baba, Is, Hot...) sopra. Sarà l'unica eccezione al tipico m_object vector<Type> perché sarà del tipo
         // [0] = Block, [1] (da vedere se sarà così) = ICON_NOUN_TYPE
  Door,
  Flag,
  Gear,
  Key, 
  Lava,
  Lever,
  Pendulum,
  Rock,  // lanciabile se ha aggettivo launchable, Player deve "calpestarla" per 
         // poterla lanciare(con tasto space premuto e direzione)
  Wall,  
  
  //Door,  // apribile automaticamente azionando ingranaggio/leva
  //Gear,  // fisso
  //Lever,  // ?trasportabile?
  

  ICON_NOUN_TYPE, // da rispettare l'ordine con NOUN_TYPE (l'int sottostante sarà calcolabile facilmente)
                  // abbinerà ciascun oggetto Objects alla sua sprite
  Icon_Void,  
  Icon_Baba, 
  Icon_Defeat,
  Icon_Flag,
  Icon_Hot,
  Icon_Is,
  Icon_Lava,
  Icon_Melt,
  Icon_Push,
  Icon_Rock, 
  Icon_Stop,
  Icon_Wall,
  Icon_Win,
  Icon_You, 
  
  VERB_TYPE, //Anche per i power-up
  Is,

  PROPERTY_TYPE,
  Defeat,
  Hot,
  Launch, // launchable
  Melt,
  Move, // = Player può camminare sopra quel tipo
  Open, //door
  Push,
  Shut, //door
  Spin,
  Swing,
  Stop,
  Win,
  You,
  
};

// Overload the unary + operator to convert an enum class to the underlying type
template <typename T>
constexpr int operator+(T a) noexcept
{
  static_assert(std::is_enum_v<T> && "Unary plus operator only works on enum types");
  return static_cast<std::underlying_type_t<T>>(a);
}
/*
template <typename T>
constexpr auto operator-(T a) noexcept
{
  static_assert(std::is_integral_v<T> && "Unary minus operator only works on integral types");
  return static_cast<Type>(a);
}
*/

constexpr std::string_view getTypeName(Type type)
{
    switch (type)
    {
    case Type::NOUN_TYPE:       return "NOUN_TYPE";
    case Type::Void:            return "Void";
    case Type::Baba:            return "Baba";
    case Type::Block:           return "Block";
    case Type::Flag:            return "Flag";
    case Type::Lava:            return "Lava";
    case Type::Rock:            return "Rock";
    case Type::Wall:            return "Wall";
    case Type::ICON_NOUN_TYPE:  return "ICON_NOUN_TYPE";
    case Type::Icon_Void:       return "Icon_Void";
    case Type::Icon_Baba:       return "Icon_Baba";
    case Type::Icon_Defeat:     return "Icon_Defeat";
    case Type::Icon_Flag:       return "Icon_Flag";
    case Type::Icon_Hot:        return "Icon_Hot";
    case Type::Icon_Is:         return "Icon_Is";
    case Type::Icon_Lava:       return "Icon_Lava";
    case Type::Icon_Melt:       return "Icon_Melt";
    case Type::Icon_Push:       return "Icon_Push";
    case Type::Icon_Rock:       return "Icon_Rock";
    case Type::Icon_Stop:       return "Icon_Stop";
    case Type::Icon_Wall:       return "Icon_Wall";
    case Type::Icon_Win:        return "Icon_Win";
    case Type::Icon_You:        return "Icon_You";
    case Type::VERB_TYPE:       return "VERB_TYPE";
    case Type::Is:              return "Is";
    case Type::PROPERTY_TYPE:   return "PROPERTY_TYPE";
    case Type::Defeat:          return "Defeat";
    case Type::Hot:             return "Hot";
    case Type::Launch:          return "Launch";
    case Type::Melt:            return "Melt";
    case Type::Move:            return "Move";
    case Type::Open:            return "Open";
    case Type::Push:            return "Push";
    case Type::Shut:            return "Shut";
    case Type::Stop:            return "Stop";
    case Type::Win:             return "Win";
    case Type::You:             return "You";
    default:                    return "No type";
    }
}

inline std::ostream& operator<<(std::ostream& out, Type type)
{
    return out << getTypeName(type);
}

constexpr Type intToType(int value) {
  return static_cast<Type>(value);
}

enum class PlayState {
  Invalid, // se un'azione non è andata a buon fine
  Playing, // per una volta lo posso dire: è ovvio
  Won, // 'You' ha toccato 'Win'
  Lose, // se niente è 'You' (=il gioco è fermo per sempre) o 'You' è morto 
};

enum class Direction {
  Up,  
  Down, 
  Right,
  Left, 
};

}

#endif