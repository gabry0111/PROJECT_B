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
        RuleManager m_RM;
        std::vector<Position> m_players; //player's position(s)

        PlayState m_state_of_game {PlayState::Playing};

    public :
        Game(std::string_view);
        std::vector<Position>& getPlayerPositions(); 
        RuleManager& getRuleManager();
        Map& getMap();
        PlayState accessm_state_of_game();
        // helper function una volta che si è assicurati che esistono tre blocchi di fila
        void createRule(const std::vector<Type>&, const std::vector<Type>&, const std::vector<Type>&);
        // chiamata quando una parola logica è mossa, controlla la vecchia posizione della regola e 
        // vede se era attaccata a altre parole logiche e modifica m_rules.
        // N.B: le regole si creeranno solo da sx a dx e da alto a basso
        void parseRules(); 
        // add properties to door, key, gear, pendulum (constant, don't depend by the rules)
        void constantProperties();
        // le seguenti adjust..() NON CONTROLLANO se un blocco ha creato o tolto una regola
        void adjustAddingRules(); // SOLO PER AGGIUNGERE REGOLE
        std::vector<Position> getTailMovingPosition(Direction);
        void update(sf::RenderWindow &, Map &, sf::Clock &);
        void render(sf::RenderWindow &, std::vector<sf::Sprite>);
        // Objects getObject(Position); forse inutile
        // std::optional<PlayState> movementCheck(Direction, Position); inutile fare l'overload, verrà sempre scelto il vector.
        // di conseguenza anche movement per un unico oggetto sarà inutile
        
        //void movement(Map, Position, Direction); //per ora non servono
        //void movement(Direction, PlayState);
        void movement(sf::RenderWindow &, sf::Clock &, Direction);
        PlayState handlePush(Objects&, Objects&, Direction, Position);
        PlayState conditions(Objects&, Objects&);
    };
    
}

#endif