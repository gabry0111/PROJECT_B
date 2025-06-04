#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#include <SFML/Graphics.hpp>
#include "enum_objects.hpp"
#include "objects.hpp"

namespace MapSize {
    constexpr std::size_t width = 16;  // Number of tiles in the X direction = n° of columns
    constexpr std::size_t height = 16; // Number of tiles in the Y direction = n° of rows
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
    constexpr void loadAndReset(std::vector<std::vector<int>>& map_grid);

    // aggiungi un oggetto
    void AddObject(Position position, Type type);

    // rimuovi un oggetto
    void RemoveObject(Position position, Type type);

    //Quale oggetto c'è in quella posizione?
    Objects& At(Position position);
    const Objects& At(Position position) const;

    //restituisce le posizioni di uno specifico tipo
    std::vector<Position> GetPositions(Type type) const;
};


}
#endif