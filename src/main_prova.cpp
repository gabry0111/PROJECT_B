#include "enum_objects.hpp"
#include "objects.hpp"
#include "game.hpp"
#include "map.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <array>
#include <filesystem>
using namespace Baba_Is_Us;

int main() {
    std::vector<sf::Texture> textures{};    // tutte le textures da caricare nel livello 
    std::vector<int> frameCounts{};         // grandezze /16 delle textures = numero di frame per ogni gif
    std::vector<int> current_frame_per_tile_ID{}; // tengo traccia di un unico frame per ogni object, quindi ogni istanza di ciascun oggetto si aggiornerà insieme
    
    std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

    std::cout<<"Initializing game engine... (please please work)\n";
    // game engine: handles window and game state every frame
    Game game("../../assets/levels/level1.txt"); // ??? non so se funziona
    std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";
    std::cout<<"Oui\n";

    sf::RenderWindow window(sf::VideoMode({512, 512}), "Oui");
   
    //setting the sprites
    std::cout<<"Loading textures...\n";
    game.getMap().setTextures();
    std::cout<<"Converting into sprites...\n";
    game.getMap().setSprites();

    // Animation loop
    sf::Clock clock;
    std::cout<<"~ ~ ~ dancin ~ ~ ~\n";

    while (window.isOpen()) {
        
        game.update(window, game.getMap(), clock);
        
        game.getMap().redraw(clock);

        game.render(window, game.getMap().tileSprites);
    }
    std::cerr << "adieu\n";
    return 0;
}
