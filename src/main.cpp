#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "map.hpp"
using namespace Baba_Is_Us;
//ciao
//suca

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({512, 256}), "Tilemap");

    // define the level with an array of tile indices
    std::array level = {
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("/ToBeMoved/Images/Levels/baba-babisyou-v0.png", {32, 32}, level.data(), 16, 16))
        return -1;

    sf::Texture texture;
    if (!texture.load)

    // run the main loop
    while (window.isOpen())
    {
        window.clear();
        window.draw(map)
        // handle events
        game.update(window);
        game.render(window, map);

    }
    return 0;
}
