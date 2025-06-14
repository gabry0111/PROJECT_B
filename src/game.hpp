#ifndef GAME_HPP
#define GAME_HPP
#include "enum_objects.hpp"
#include "objects.hpp"
#include "map.hpp"
#include "rules.hpp"

using Position = std::pair<std::size_t, std::size_t>;
namespace Baba_Is_Us{
    
    class Game {
    private : 
        Map m_map3D;
        std::vector<Position> m_players; //player's position(s)
        RuleManager m_RM;

    public :
        Game(std::string_view);
        std::vector<Position>& getPlayerPositions(); 
        RuleManager& getRuleManager();
        Map& getMap();
        // chiamata quando una parola logica è mossa, controlla la vecchia posizione della regola e 
        // vede se era attaccata a altre parole logiche e modifica m_rules.
        // N.B: le regole si creeranno solo da sx a dx e da alto a basso
        void parseRules(); //serve la mappa, quindi la sposto qui perché avrei dovuto costruire un'altra mappa in RuleManager
        void update(sf::RenderWindow &, Map &);
        void render(sf::RenderWindow &, std::vector<sf::Sprite>);
        // Objects getObject(Position); forse inutile
        // std::optional<PlayState> movementCheck(Direction, Position); inutile fare l'overload, verrà sempre scelto il vector.
        // di conseguenza anche movement per un unico oggetto sarà inutile
        std::optional<std::vector<PlayState>> movementCheck(Direction);
        void rotate(Position&, Direction);
        void movement(Map, Position, Direction);
        void movement(Direction, PlayState);
        void movement(Direction);
        PlayState conditions(Objects&, Objects&);
    };
}

#endif