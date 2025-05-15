

namespace Baba {

enum class Type {  // DA AGGIUNGERE overload per convertirli in int (learncpp.com)
  NOUN_TYPE,
  Baba, //aspetto del Player di default
  Door,  // apribile automaticamente azionando ingranaggio/leva
  Flag, // avrà come standard l'attributo "win"
  Gear,  // fisso
  Lava,
  Lever,  //?trasportabile?
  Rock,  // lanciabile se ha aggettivo launchable, Player deve "calpestarla" per 
         //poterla lanciare(con tasto space premuto e direzione)
  Wall,  
/*
  ICON_NOUN_TYPE, //da rispettare l'ordine con NOUN_TYPE
  Icon_Baba, 
  Icon_Door, 
  Icon_Flag,
  Icon_Gear, 
  Icon_Lava,
  Icon_Lever,
  Icon_Rock, 
  Icon_Wall, 
*/
  VERB_TYPE, //Anche per i power-up
  And,
  Is,
  On,

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

/* sarà inizializzato l'oggetto con tipo Type: voglio sapere se

funzioni per: capire frase logica; convertire Type in numero, font e viceversa
*/

//Funzione che ritorna quale NOUN ha
//Funzione che ritorna quale VERB ha
//Funzione che ritorna quale PROPERTY ha

inline Type getNoun() {

}

}