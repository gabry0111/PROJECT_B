#include "enum_objects.hpp"
#include "objects.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include "game.hpp"
#include "map.hpp"
using namespace Baba_Is_Us;

                        ///////////////////////
                        // ----- METODO SPRITES ----- //
namespace Baba_Is_Us{
    std::vector<std::vector<int>> map_grid{};
};
int main() {
    constexpr int TILE_SIZE = 32;
    constexpr int FRAME_TIME_MS = 150;

    // va implementato un modo per cui il compilatore prenda il file dalla BUILD
    // così da semplificare l'azione che prende il percorso (di tipo std::string)
    std::vector<std::string> tilePaths { //20
        "PROJECT_B/png_PROGETTO/BABA_move_down_spritesheet.png",
        // "/Users/lele/progetto/PROJECT_B/png_PROGETTO/FLAG_spritesheet.png",
        // "/Users/lele/progetto/PROJECT_B/png_PROGETTO/LAVA_spritesheet.png",
        // "/Users/lele/progetto/PROJECT_B/png_PROGETTO/ROCK_spritesheet.png",
        // "/Users/lele/progetto/PROJECT_B/png_PROGETTO/WALL_spritesheet.png" 
    };

    std::vector<sf::Texture> textures{};    // tutte le textures da caricare nel livello 
    std::vector<int> frameCounts{};         // grandezze /16 delle textures = numero di frame per ogni gif
    std::vector<int> current_frame_per_tile_ID{}; // tengo traccia di un unico frame per ogni object, quindi ogni istanza di ciascun oggetto si aggiornerà insieme

    // load textures e tieni conto, per ogni indice, della quantità di frame
    std::cout<<"Loading textures...\n";
    for (std::size_t i{}; i < tilePaths.size(); ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile(tilePaths[i])) {
            std::cerr << "Failed to load " << tilePaths[i] << "\n";
            continue;
        }

        int width = static_cast<int>(texture.getSize().x); // 72
        int frames = std::max(1, width / TILE_SIZE);       // 3
        textures.emplace_back(texture);
        frameCounts.emplace_back(frames);
        current_frame_per_tile_ID.push_back(0); // ogni tile ID partirà dal frame n° 0
    }
    
    //map_grid ha i valori (enum type) di ogni oggetto caricato nella rispettiva cella
    map_grid = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    // converti le tileID in sprites
    std::vector<sf::Sprite> tileSprites{};

    for (std::size_t i = 0; i < MapSize::n_tiles; ++i) {
        int tileID {map_grid[i/MapSize::height][i%MapSize::width]}; // typing convenience
        if (tileID < 0 || tileID >= static_cast<int>(textures.size())) continue;
        sf::Sprite sprite;
        //metto la texture sullo sprite
        sprite.setTexture(textures[static_cast<std::size_t>(tileID)]);

        sprite.setTextureRect({0, 0, TILE_SIZE, TILE_SIZE}); //snip snip 32x32

        int x = (static_cast<int> (i) % MapSize::width) * TILE_SIZE;    // = 0, 32, 64, ... 255*32 
        int y = (static_cast<int> (i) / MapSize::height) * TILE_SIZE;
        sprite.setPosition(static_cast<float>(x), static_cast<float>(y));

        //non riesco a capire counter -> 4
        tileSprites.emplace_back(sprite); // alla fine avrà level.size() elementi, ognuno con una sprite (<- quella che si beve?)

    }


    std::cout<<"Initializing game engine... (please please work)\n";
    // game engine: handles window and game state every frame
    Game game;
    sf::RenderWindow window(sf::VideoMode({512, 512}), "Oui");

    // Animation loop
    sf::Clock clock;
    std::cout<<"~ ~ ~ dancin ~ ~ ~\n";

    while (window.isOpen()) {

        if (clock.getElapsedTime().asMilliseconds() >= FRAME_TIME_MS) {

            //change the current frame of every individual texture
            //it could be different across textures if we add more detailed spritesheets or more frames per animation
            for (std::size_t i{}; i < frameCounts.size(); ++i) {
                if (frameCounts[i] > 1) { // se in i c'è un'animazione
                    current_frame_per_tile_ID[i] = (current_frame_per_tile_ID[i] + 1) % frameCounts[i]; //frameCounts[i] sarà sempre 3 se è animazione, quindi prova a calcolare
                
                }
            }
            clock.restart();
        }
        //resize and draw
        for (std::size_t i{}; i < tileSprites.size(); ++i) {
            int tileID {map_grid[i/MapSize::height][i%MapSize::width]};
            int frame = current_frame_per_tile_ID[static_cast<size_t> (tileID)];
            tileSprites[i].setTextureRect({frame * TILE_SIZE, 0,TILE_SIZE, TILE_SIZE});
            // se vogliamo ruotare l'oggetto, aggiungere funzioni qui. (con switch per comandi WASD?)
        }
        
        game.update(window);
        game.render(window, tileSprites);
    }

    return 0;
}
