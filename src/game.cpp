#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.hpp"
#include "game.hpp"
#include "objects.hpp"

/* Avuta la mappa del livello corrente, verifica quali azioni sono possibili:
- verifica le proprietà di ciascun oggetto (sarà fatto nel Main Loop)
- resetta il livello se PlayState è Invalid
- gestisce il movimento del Player
- gestisce il movimento degli oggetti 
- 
*/


namespace Baba_Is_Us{

    Position target;        //tile that the player wants to move into
    Position next_target;   //tile after the target, in case something gets pushed

    std::vector<Position> targets;
    std::vector<Position> next_targets;

<<<<<<< HEAD
    Game::Game(std::string_view filename) :
        m_map3D{},
        m_players{},
        m_RM{}
=======
    Game::Game(std::string_view filename) : m_map3D{filename}, m_RM{}, m_players{}
>>>>>>> 6ec62ae7a5f4756cba36d03e1f4e137aadc42637
    {
        std::cout<<"aaaaaaaaa\n";
        parseRules();
        std::cout<<"parsed rules\n";

        // checkRulesForProperty
        // aggiungi le proprietà giuste ad ogni oggetto
        m_players = m_map3D.getPositions(Type::You);
        std::cout<<"QUA\n";
        m_RM.clearRules();
    }

    std::vector<Position>& Game::getPlayerPositions() {
        return m_players;
    } 
    RuleManager& Game::getRuleManager() {
        return m_RM;
    }
    Map& Game::getMap() {
        return m_map3D;
    }

    void Game::parseRules() {
        for (auto pos : m_map3D.getPositions(Type::Block)) {
            // N.B: per Block: [0] = Block, [1] = NOUN_TYPE, [2] = ICON_NOUN_TYPE
            // check verticale
            if (m_map3D.At(pos.second - 1, pos.first).getTypes()[0] == Type::Block) {continue; // se non sei la prima parola logica
            } else {
                std::vector<Type> word1 {m_map3D.At(pos.second, pos.first).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.second + 1, pos.first).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.second + 2, pos.first).getTypes()};
                if (word2[0] == Type::Block && word3[0] == Type::Block) { // se ci sono altre 2 parole logiche in fila
                    if(+word1[1] > +Type::ICON_NOUN_TYPE  // se 3 parole di fila sono NOUN_TYPE, VERB_TYPE e PROPERTY_TYPE
                    && +word1[1] < +Type::VERB_TYPE
                    && +word2[1] > +Type::VERB_TYPE 
                    && +word2[1] < +Type::PROPERTY_TYPE 
                    && +word3[1] > +Type::PROPERTY_TYPE) {
                        Rule new_rule {word1[1], word2[1], word3[1]};
                        m_RM.addRule(new_rule);
                    }
                }
            }
            //check orizzontale
            if (m_map3D.At(pos.second, pos.first - 1).getTypes()[0] == Type::Block) {continue; // se non sei la prima parola logica, non fare nulla
            } else {
                std::vector<Type> word1 {m_map3D.At(pos.second, pos.first).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.second, pos.first + 1).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.second, pos.first + 2).getTypes()};
                if (word2[0] == Type::Block && word3[0] == Type::Block) { // se ci sono altre 2 parole logiche in fila
                    if(+word1[1] > +Type::ICON_NOUN_TYPE  // se 3 parole di fila sono NOUN_TYPE, VERB_TYPE e PROPERTY_TYPE
                    && +word1[1] < +Type::VERB_TYPE
                    && +word2[1] > +Type::VERB_TYPE 
                    && +word2[1] < +Type::PROPERTY_TYPE 
                    && +word3[1] > +Type::PROPERTY_TYPE) {
                        Rule new_rule {word1[1], word2[1], word3[1]};
                        m_RM.addRule(new_rule);
                    }
                }
            }
        }
    }

    Position getShift(Direction dir) {
        switch (dir) {
            case Direction::Up:    return {-1, 0};
            case Direction::Down:  return {1, 0};
            case Direction::Left:  return {0, -1};
            case Direction::Right: return {0, 1};
            default:               return {0, 0};
        }
    }

    void Game::update(sf::RenderWindow &window, Map &map){

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed){
                m_players = map.getPositions(Type::You);

                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::W:
                        //controllo di player
                        // 1) un solo oggetto in Position Player
                        //      movement_check(map, player[0], Direction::Up);
                        //      se vero, rotate e movement
                        //      se falso, rotate
                        // 2) più di uno
                        //      movement_check(map, player, Direction::Up); -> vettore di pair di playState e positions
                        /*      for(auto &i : playStates){
                                    if(i.first == PlayState::Playing){
                                        se è l'ultimo della fila
                                            movement(map, i.second)
                                    }
                                }
                        */      
                        
                        //checkRules 

                        break;
                    case sf::Keyboard::A:
                        break;
                    case sf::Keyboard::S:
                        break;
                    case sf::Keyboard::D:
                        break;
                    case sf::Keyboard::Space: 
                        //check se ha un oggetto in mano
                        //lancia oggetto
                        break;
                    default: break;
                }
            }
        }    
    }

    void Game::render(sf::RenderWindow &window, std::vector<sf::Sprite> sprites){
        // draw the map
        window.clear();
        for (const auto& sprite : sprites)
            window.draw(sprite);
        window.display();
    }


    // fallisce solo se è boundary. gli passo la mappa 2D e non 3D perché se Player può "andare sopra" all'oggetto, non crea nessun problema al movimento
    std::optional<Position> getFirstMismatchOfObjects(const MapGrid2D& grid, Direction dir, const Position& start) {
        Position shift{getShift(dir)};
        std::size_t x=start.first;
        std::size_t y=start.second;
        int value = grid[y][x];
        while(x < MapSize::width && y < MapSize::height) {
            if(grid[y][x] != value)
                return Position {x,y};
            x += shift.first;
            y += shift.second;
        }
        return std::nullopt;
    }

    // se non si può fare (non si può muovere e gli oggetti sono già distrutti), allora vedere se movementCheck è "vuoto"
    // ASSICURATI CHE conditions() NON SIA MAI PIù CHIAMATA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // VA BENE OK DIEGO
    std::optional<std::vector<PlayState>> Game::movementCheck(Direction direction){
        Position shift{getShift(direction)};
        std::vector<PlayState> results {};
        
        for(const auto& pos : getPlayerPositions()){
            if(! getFirstMismatchOfObjects(m_map3D.getm_grid()[0], direction, pos)) 
                return std::optional<std::vector<PlayState>>{ {PlayState::Invalid, } };

            Position first_mismatch {* getFirstMismatchOfObjects(m_map3D.getm_grid()[0], direction, pos)};
            Position last_before_mismatch {first_mismatch.first - shift.first, first_mismatch.second - shift.second};

            // while(conditions(getMap().At(target), getMap().At(next_target)) != PlayState::Invalid) non lo posso fare. conditions() distrugge gli objects
            results.emplace_back(conditions(m_map3D.At(last_before_mismatch.first, last_before_mismatch.second), m_map3D.At(first_mismatch.first, first_mismatch.second)));
        }
        return results.empty() ? std::nullopt : std::optional<std::vector<PlayState>>(results);
    }


    void Game::rotate(Position &player_position, Direction direction){
        player_position.first = player_position.first;
        player_position.second = player_position.second;
        switch(direction){
            case Baba_Is_Us::Direction::Up:
                break;
            case Baba_Is_Us::Direction::Down:
                break;
            case Baba_Is_Us::Direction::Left:
                break;
            case Baba_Is_Us::Direction::Right:
                break;
            default: break;
        }
    }


    void Game::movement(Direction direction, PlayState playstate){
        if(direction!=Direction::Up)        //
            direction=Direction::Up;        //TEMPORANEI, per far compilare
        if (playstate!=PlayState::Playing)  //
            playstate=PlayState::Playing;   //

        /*  
        divide movement in 3rds, for each frame of the animation:
            - change the player's sprite position by 1/3 towards the target's position
            - if target is pushable, game::update chiamerà anche movement(target, direction)
        SI PUò FARE ANCHE PER OGGETTI CHE DEVONO ESSERE DISTRUTTI?
        COME FARE A VEDERE DOVE STA GUARDANDO PLAYER? (PER ROCK) (togliamo launch e mettiamoci gradino?)
        */ 
        
        // 1/3
        
        // 2/3 

        // 3/3 
        //position.first = target.first;
        //position.second = target.second;
    
        //return true;
    }

    //overload
    void Game::movement(Direction direction){ 
        std::vector<Position>& player_positions {getPlayerPositions()};
        for (auto& each : player_positions) {
            rotate(each, direction);

        }
        /*  
        divide movement in 3rds, for each frame of the animation:
            - determine which sprite is in that position
            - shift the player's sprite position by 1/3 towards the target's position (32 px per sprite, 16 cells in total => shift by 32/3)
            - if target is pushable, game::update chiamerà anche movement(target, direction)
        SI PUò FARE ANCHE PER OGGETTI CHE DEVONO ESSERE DISTRUTTI?
        COME FARE A VEDERE DOVE STA GUARDANDO PLAYER? (PER ROCK) (togliamo launch e mettiamoci gradino?)
        */ 
        
        // 1/3
        
        // 2/3 

        // 3/3 
        for (size_t i={0}; i<player_positions.size(); ++i){
            player_positions[i].first = targets[i].first;
            player_positions[i].second = targets[i].second;
            if(direction!=Direction::Up)
                direction=Direction::Up; //TEMPORANEO, per far compilare
        }
        
        //return true;
    }

    PlayState handleHot(Objects& object, Objects& second) {
        if (!second.objectHasType(Type::Push)) {
            object.resetObject();
        }
        return PlayState::Playing;
    }

    PlayState handleShut(Objects& object, Objects& second) {
        if (object.objectHasType(Type::Open)) {
            second.resetObject();
            object.resetObject();
            return PlayState::Playing;
        }
        return PlayState::Invalid;
    }

    PlayState handleSink(Objects& object, Objects& second) {
        if (object.objectHasType(Type::Float)) {
            second.resetObject();
            object.resetObject();
        } else {
            object.resetObject();
        }
        return PlayState::Playing;
    }

    PlayState handleStop(Objects&, Objects& second) {
        if (second.objectHasType(Type::Push)) return PlayState::Playing;
        return PlayState::Invalid;
    }

    PlayState Game::conditions(Objects& object, Objects& second) {
        std::vector<Type> second_types {second.getTypes()};
        PlayState action {PlayState::Invalid};
        
        for(const auto type : second_types){ // per ogni Type di Objects second
            /*
            // deve essere valido Baba is you, Baba is wall, Baba is lava, ma non Baba is block
            if(+Type::NOUN_TYPE < +type && +type < +Type::ICON_NOUN_TYPE && type != Type::Block) { 
                assert(!object.objectHasType(type)); // controlla non abbia già quel tipo in m_object
                if(!object.objectHasType(type)) { // per la grafica (nel caso Baba is wall and rock) verrà applicata solo la skin del primo tipo
                    object.addType(type);
                    action = PlayState::Playing;
                }
                else{} //{std::iter_swap(std::find(object.getTypes().begin(), object.getTypes().end(), type), object.getTypes().end() - 1);}
            }
            */
            // non ci interessa degli ICON_NOUN_TYPE
            // non ci interessa dei verb type che creeranno una regola. Ci penserà un'altra funzione

            //
            // controllare che object[0] NON sia Type::Block -----------------------
            //
            switch (type) {
            case Type::Hot:    action = handleHot(object, second); break;
            case Type::Launch: action = PlayState::Playing; break;
            case Type::Move:   action = PlayState::Playing; break;
            case Type::Open:   action = PlayState::Playing; break;
            case Type::Push:   action = PlayState::Playing; break;
            case Type::Shut:   action = handleShut(object, second); break;
            case Type::Sink:   action = handleSink(object, second); break;
            case Type::Stop:   action = handleStop(object, second); break;
            case Type::Win:    action = PlayState::Won; break;
            case Type::You:    action = PlayState::Playing; break;
            default:           break;
            }
            if (action == PlayState::Invalid) return PlayState::Invalid;
        }
        return action;
    }

    // check se intorno a target delle rules sono state cambiate, in tal caso reverse the effects of that rule
}
