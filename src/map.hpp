#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#include "enum_objects.hpp"
#include "objects.hpp"
#include <SFML/Graphics.hpp>
#include <array>

using Position = std::pair<std::size_t, std::size_t>;

namespace MapSize {
    constexpr int width = 16;  // Number of tiles in the X direction = n° of columns
    constexpr int height = 16; // Number of tiles in the Y direction = n° of rows
    constexpr int n_tiles = width*height; // Total number of tiles

    constexpr int TILE_SIZE = 32;
    constexpr int FRAME_TIME_MS = 150;
    
}

namespace Baba_Is_Us {
// va implementato un modo per cui il compilatore prenda il file dalla BUILD
    // così da semplificare l'azione che prende il percorso (di tipo std::string)
    inline std::array<std::string, 12> tilePaths { //20
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/BABA_move_up_right_spritesheet.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/BABA_move_down_left_spritesheet.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/BABA_move_left_spritesheet.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/BABA_move_right_spritesheet.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/BABA_spritesheet_up.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/BABA_spritesheet_down.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/BABA_spritesheet_right.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/BABA_spritesheet_left.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/FLAG_spritesheet.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/LAVA_spritesheet.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/ROCK_spritesheet.png",
        "/Users/lele/progetto/PROJECT_B/png_PROGETTO/WALL_spritesheet.png" 
    };

class Map{
private :

    std::vector<std::vector<Objects>> m_objects {} ; 
    bool IsBoundary(std::size_t x, std::size_t y) const;

    std::vector<sf::Texture> textures{};
    std::vector<int> frameCounts{};
    std::vector<int> current_frame_per_tile_ID{};
    std::vector<sf::Sprite> tileSprites{};

public:
    // alloca lo spazio di m_objects per (MapSize::width * MapSize::height) elementi
    Map(const std::array<std::array<std::array<int, MapSize::width>, MapSize::height>, 2> &);
    // inizializza ogni Objects di m_objects al tipo della corrispondente cella di new_map_grid
    // da chiamare appena creata un'istanza di Map

    std::array<std::array<std::array<int, MapSize::width>, MapSize::height>, 2> grid;

    void setTextures();
    void setSprites();
    void redraw(sf::Clock &);
    std::vector<sf::Sprite> getTileSprites();

    // resetta la mappa (se PlayState::Invalid o se cambia livello)
    // N.B: ogni oggetto può avere proprietà che devono essere tolte richiamando poi la funzione apposita che controlla le regole nella mappa
    void Reset(const std::array<std::array<int,16>,16> ); // può diventare constexpr
    

    // aggiungi un oggetto
    // constexpr void addObject(Position position, Type type);

    // rimuovi un oggetto
    // constexpr void resetObject(Position position);

    // Quale oggetto c'è in quella posizione?
    // N.B: NON IN MINUSCOLO, è una funzione di vector
    const Objects& At(Position);
    const Objects& At(std::size_t y, std::size_t x) const; // NON può diventare constexpr (m_objects è vector)

    // restituisce le posizioni di uno specifico tipo
    std::vector<Position> getPositions(Type) const; // non conviene diventare constexpr (dovrebbe essere template di array)

};

}
#endif