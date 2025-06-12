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



int main() {

    //spostato tilePaths in map.hpp

    std::vector<sf::Texture> textures{};    // tutte le textures da caricare nel livello 
    std::vector<int> frameCounts{};         // grandezze /16 delle textures = numero di frame per ogni gif
    std::vector<int> current_frame_per_tile_ID{}; // tengo traccia di un unico frame per ogni object, quindi ogni istanza di ciascun oggetto si aggiornerà insieme

    // load textures e tieni conto, per ogni indice, della quantità di frame
    

    //map_grid ha i valori (enum type) di ogni oggetto caricato nella rispettiva cella
    std::vector<std::vector<int>> map_grid = { // può diventare constexpr
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
    Map map{map_grid};



    std::cout<<"Initializing game engine... (please please work)\n";
    // game engine: handles window and game state every frame
    Game game;
    sf::RenderWindow window(sf::VideoMode({512, 512}), "Oui");

    //setting the sprites
    std::cout<<"Loading textures...\n";
    map.setTextures();
    std::cout<<"Converting into sprites...\n";
    map.setSprites();

    // Animation loop
    sf::Clock clock;
    std::cout<<"~ ~ ~ dancin ~ ~ ~\n";

    while (window.isOpen()) {
        game.update(window, map);

        map.redraw(clock);

        game.render(window, map.getTileSprites());
    }

    return 0;
}
