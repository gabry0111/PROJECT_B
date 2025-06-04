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
    Map();

    // resetta la mappa (se PlayState::Invalid)
    constexpr void loadAndReset(std::vector<std::vector<int>>& );

    // aggiungi un oggetto
    void addObject(Position, Type);

    // rimuovi un oggetto
    void removeObject(Position, Type);

    //Quale oggetto c'è in quella posizione?
    Objects& At(Position);
    const Objects& At(Position) const;

    //restituisce le posizioni di uno specifico tipo
    std::vector<Position> getPositions(Type) const;

};


}
#endif