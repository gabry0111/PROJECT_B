#include <SFML/Graphics.hpp>
#include <array>
#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "enum_objects.hpp"
#include "game.hpp"
#include "map.hpp"
#include "objects.hpp"
using namespace Baba_Is_Us;

int main() {
  // tutte le textures da caricare nel livello
  std::vector<sf::Texture> textures{};
  // grandezze /16 delle textures = numero di frame per ogni gif
  std::vector<int> frameCounts{};
  // tengo traccia di un unico frame per ogni object, quindi ogni istanza di
  // ciascun oggetto si aggiornerà insieme
  std::vector<int> current_frame_per_tile_ID{};

  std::cout << "Current working directory: " << std::filesystem::current_path()
            << "\n";

  std::cout << "Initializing game engine... (please please work)\n";

  std::cout << "There are different levels available, enter which level you "
               "want to play: 1, 2, 3 or 4\n";
  int nth_level{};
  std::cin >> nth_level;
  assert(nth_level > 0 && nth_level < 5);
  constexpr std::array<std::string_view, 4> level_paths{
      "assets/levels/level1.txt", "assets/levels/level2.txt",
      "assets/levels/level3.txt", "assets/levels/level4.txt"};

  Game game(level_paths[nth_level - 1]);

  std::cout << "Current working directory: " << std::filesystem::current_path()
            << "\n";
  std::cout << "Oui\n";

  sf::RenderWindow window(sf::VideoMode({512, 512}), "Baba Is Us");

  // setting the sprites
  game.accessMap().setTextures();
  game.accessMap().setSprites();

  // Animation loop
  sf::Clock clock;
  std::cerr << "balls";
  while (window.isOpen()) {
    game.update(window, clock);

    game.accessMap().redraw(clock);

    game.render(window, game.getMap().tileSprites);
  }
  std::cerr << "Program successfully terminated\n";
  return 0;
}