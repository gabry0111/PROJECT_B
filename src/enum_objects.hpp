#ifndef ENUM_OBJECTS_HPP
#define ENUM_OBJECTS_HPP

#include <type_traits> //per underlying_type


namespace Baba_Is_Us {

enum class Type {  // DA AGGIUNGERE overload per convertirli in int (learncpp.com)
  NOUN_TYPE=-1,
  Void, // possiamo creare un vector o array così: std::array<std::array<int,colonne>,righe> e inizializzare tutto a void; poi aggiungere ciascun elemento
        // oppure serve per vettore di alcune informazioni (findPlayer() fallisce => PlayState::Invalid) (N.B: void negli if = false)
  Baba, // aspetto del Player di default
  Flag, 
  Lava,
  Rock,  // lanciabile se ha aggettivo launchable, Player deve "calpestarla" per 
         // poterla lanciare(con tasto space premuto e direzione)
  Wall,  
  Block, // per scriverci le parole (Baba, Is, Hot...) sopra
  Door,  // apribile automaticamente azionando ingranaggio/leva
  Gear,  // fisso
  Lever,  // ?trasportabile?
  

  ICON_NOUN_TYPE, // da rispettare l'ordine con NOUN_TYPE (l'int sottostante sarà calcolabile facilmente)
                  // abbinerà ciascun oggetto Objects alla sua sprite
  Icon_Void,
  Icon_Baba, 
  Icon_Door, 
  Icon_Flag,
  Icon_Gear, 
  Icon_Lava,
  Icon_Lever,
  Icon_Rock, 
  Icon_Wall, 
  
  VERB_TYPE, //Anche per i power-up
  And,
  Is,
  On, //vedi Rock

  PROPERTY_TYPE,
  Hot,
  Launch, //launchable
  Move,
  Open, //door
  Push,
  Quantum, //se Player passa attraverso una porta, Player si sdoppia
  Shut, //door
  Stop,
  Win,
  You,
  
};

// Overload the unary + operator to convert an enum class to the underlying type
template <typename T>
constexpr auto operator+(T a) noexcept
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

constexpr Type intToType(int value) {
  return static_cast<Type>(value);
}

enum class PlayState {
  Invalid, // se niente è 'You' (=il gioco è fermo per sempre) 
  Playing, // per una volta lo posso dire: è ovvio
  Won, // 'You' ha toccato 'Win'
  Reset, // se si vuole resettare il livello (da togliere?)
};

enum class Direction {
  Up,  
  Down, 
  Right,
  Left, 
};

}

#endif