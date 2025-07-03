#include <SFML/Graphics.hpp>
#include <array>
#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "game.hpp"
#include "map.hpp"
using namespace Baba_Is_Us;

int main() {
  std::cout << "There are different levels available, enter which level you "
               "want to play: 1, 2, 3 or 4\n";
  std::size_t nth_level{};
  std::cin >> nth_level;
  assert(nth_level > 0 && nth_level < 5);
  constexpr std::array<std::string_view, 4> level_paths{
      "assets/levels/level1.txt", "assets/levels/level2.txt",
      "assets/levels/level3.txt", "assets/levels/level4.txt"};

  sf::RenderWindow window(sf::VideoMode({512, 512}), "Baba Is Us");

  Game game(level_paths[nth_level - 1]);

  // setting the sprites
  game.accessMap().setTextures();
  game.accessMap().setSprites();

  // Animation loop
  sf::Clock clock;
  while (window.isOpen()) {
    game.update(window, clock);

    game.accessMap().redraw(clock);

    game.render(window, game.getMap().tileSprites);
  }
  std::cerr << "Program successfully terminated\n";
  return 0;
}