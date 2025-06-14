#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#include "enum_objects.hpp"
#include "objects.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <string_view>
#include <fstream>

using Position = std::pair<std::size_t, std::size_t>;

namespace MapSize {
    constexpr int width = 16;  // Number of tiles in the X direction = n° of columns
    constexpr int height = 16; // Number of tiles in the Y direction = n° of rows
    constexpr int depth = 2;   // Number of layers in the map
    constexpr int n_tiles = width * height; // Total number of tiles

    constexpr int TILE_SIZE = 32;
    constexpr int FRAME_TIME_MS = 150;
    
}
using MapGrid2D = std::array<std::array<int, MapSize::width>, MapSize::height>;

namespace Baba_Is_Us {

// va implementato un modo per cui il compilatore prenda il file dalla BUILD
    // così da semplificare l'azione che prende il percorso (di tipo std::string)
    inline std::array<std::string, 25> tilePaths { //20
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/BABA_move_up_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/BABA_move_down_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/BABA_move_left_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/BABA_move_right_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/BABA_spritesheet_up.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/BABA_spritesheet_down.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/BABA_spritesheet_right.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/BABA_spritesheet_left.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/FLAG_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/LAVA_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/ROCK_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/gifs/WALL_spritesheet.png",

        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/BABA_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/DEFEAT_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/FLAG_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/HOT_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/IS_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/LAVA_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/MELT_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/PUSH_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/ROCK_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/STOP_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/WALL_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/WIN_text_spritesheet.png",
        "/home/diegoarcari/labs/progetto/PROJECT_B/build/assets/png_PROGETTO/text/YOU_text_spritesheet.png",
    };

class Map{
private :

    std::array<MapGrid2D, MapSize::depth> m_grid;
    std::array<std::array<Objects, MapSize::height>, MapSize::width> m_objects;

public:
    bool isBoundary(std::size_t x, std::size_t y) const;

    std::vector<sf::Texture> textures{};
    std::vector<int> frameCounts{};
    std::vector<int> current_frame_per_tile_ID{};
    std::vector<sf::Sprite> tileSprites{};

    Map() = default;
    // alloca lo spazio di m_objects per (MapSize::width * MapSize::height) elementi
    Map(std::string_view);

    // inizializza ogni Objects di m_objects al tipo della corrispondente cella di new_map_grid
    // da chiamare appena creata un'istanza di Map

    const std::array<MapGrid2D, MapSize::depth>& getm_grid();
    void setTextures();
    void setSprites();
    void redraw(sf::Clock &);
    std::vector<sf::Sprite> getTileSprites();
    sf::Sprite getWhichSpriteIsInPosition(Position&);
    // resetta la mappa (se PlayState::Invalid o se cambia livello)
    // N.B: ogni oggetto può avere proprietà che devono essere tolte richiamando poi la funzione apposita che controlla le regole nella mappa
    void Reset(const std::array<std::array<int,MapSize::width>,MapSize::height>& ); // può diventare constexpr
    

    // aggiungi un oggetto
    // constexpr void addObject(Position position, Type type);

    // rimuovi un oggetto
    // constexpr void resetObject(Position position);

    // Quale oggetto c'è in quella posizione?
    // N.B: NON IN MINUSCOLO, è una funzione di vector

    Objects& At(std::size_t y, std::size_t x);
    const Objects& At(std::size_t y, std::size_t x) const; // NON può diventare constexpr (m_objects è vector)

    // restituisce le posizioni di uno specifico tipo
    std::vector<Position> getPositions(Type) const; // non conviene diventare constexpr (dovrebbe essere template di array)

};

}
#endif