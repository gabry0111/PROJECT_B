#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#include <SFML/Graphics.hpp>
#include "enum_objects.hpp"
#include "objects.hpp"

namespace MapSize {
    constexpr int width = 16;  // Number of tiles in the X direction = n° of columns
    constexpr int height = 16; // Number of tiles in the Y direction = n° of rows
    constexpr int n_tiles = width*height; // Total number of tiles
}

namespace Baba_Is_Us {
using Position = std::pair<std::size_t, std::size_t>;

class Map{
private :

    std::vector<Objects> m_objects {};

    bool IsBoundary(std::size_t x, std::size_t y) const;

public:
    // alloca lo spazio di m_objects per (MapSize::width * MapSize::height) elementi
    Map();

    // inizializza ogni Objects di m_objects al tipo della corrispondente cella di new_map_grida
    // da chiamare appena creata un'istanza di Map
    constexpr void load(const std::vector<std::vector<int>>& new_map_grid);
    // resetta la mappa (se PlayState::Invalid o se cambia livello)
    // N.B: ogni oggetto può avere proprietà che devono essere tolte richiamando poi la funzione apposita che controlla le regole nella mappa
    constexpr void Reset(const std::vector<std::vector<int>>& new_map_grid);
    

    // aggiungi un oggetto
    constexpr void AddObject(Position position, Type type);

    // rimuovi un oggetto
    constexpr void RemoveObject(Position position, Type type);

    //Quale oggetto c'è in quella posizione?
    //N.B: NON IN MINUSCOLO, è una funzione di vector
    Objects& At(Position position);
    const Objects& At(Position position) const;

    //restituisce le posizioni di uno specifico tipo
    std::vector<std::reference_wrapper<Position>> getPositions(Type) const;

};


}
#endif