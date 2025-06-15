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

    Game::Game(std::string_view filename) : m_map3D{filename}, m_RM{}, m_players{}
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
            std::cerr << pos.first << ' ' << pos.second << '\n';
            // N.B: per Block: [0] = Block, [1] = NOUN_TYPE, [2] = ICON_NOUN_TYPE
            // check verticale
            if(m_map3D.isBoundary(pos.second, pos.first)) continue;
            if (m_map3D.At(pos.second - 1, pos.first).getTypes()[0] == Type::Block) {
                std::cerr << "no prima\n";
                continue; // se non sei la prima parola logica
            } else {
                std::cerr << "Prima";
                std::vector<Type> word1 {m_map3D.At(pos.second, pos.first).getTypes()};
                std::vector<Type> word2 {};
                std::vector<Type> word3 {};
                if(m_map3D.isBoundary(pos.second, pos.first)) word2 = m_map3D.At(pos.second + 1, pos.first).getTypes();
                if(m_map3D.isBoundary(pos.second + 1, pos.first)) word3 = m_map3D.At(pos.second + 2, pos.first).getTypes();
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
            if(m_map3D.isBoundary(pos.second, pos.first)) continue;
            if (m_map3D.At(pos.second, pos.first - 1).getTypes()[0] == Type::Block) {
                std::cerr << "no prima\n";
                continue; // se non sei la prima parola logica
            } else {
                std::cerr << "Prima";
                std::vector<Type> word1 {m_map3D.At(pos.second, pos.first).getTypes()};
                std::vector<Type> word2 {};
                std::vector<Type> word3 {};
                if(m_map3D.isBoundary(pos.second, pos.first)) word2 = m_map3D.At(pos.second, pos.first + 1).getTypes();
                if(m_map3D.isBoundary(pos.second, pos.first + 1)) word3 = m_map3D.At(pos.second, pos.first + 2).getTypes();
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
        std::cerr << "ParseRules()";
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
        std::cerr<<"update\n";

        sf::Event event;

        Direction temp;
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
                        //      rotate()
                        //      se vero,    
                        //          poi movement, sprite.move, redraw e render 3 volte  
                        //
            //move, redraw, render
            //move, redraw, render
            //move, redraw, render
                        //      se falso, fanculo
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
                        temp = Direction::Up;
                        goto pippo;
                    case sf::Keyboard::A:
                        temp = Direction::Left;
                        goto pippo; 
                    case sf::Keyboard::S:
                        temp = Direction::Down;
                        goto pippo;
                    case sf::Keyboard::D:
                        temp = Direction::Right;
                        goto pippo;
                        pippo:
                        Position shift = getShift(temp);
                        std::size_t dx {shift.first};
                        std::size_t dy {shift.second};

                        std::vector<Position>& player_positions {getPlayerPositions()};

                        for(auto& each : player_positions){
                            if(movementCheck(each, temp)==PlayState::Playing){
                                sf::Sprite& sprite {m_map3D.tileSprites[each.second * MapSize::width + each.first]};
                                sprite.move(static_cast<float>(dx) * 11, static_cast<float>(dy) * 11);
                                sprite.move(static_cast<float>(dx) * 10, static_cast<float>(dy) * 10);
                                sprite.move(static_cast<float>(dx) * 11, static_cast<float>(dy) * 11);
                            }
                            
                        }
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

    void Game::render(sf::RenderWindow &window, const std::vector<sf::Sprite> sprites){
        std::cerr<<"render\n";

        // draw the map
        window.clear();
        for (const auto& row : m_map3D.getm_grid()[0]){
            std::cerr << "dammi da disegnare\n";
            for (const auto& i : row){
                std::cerr << "dentro le righe\n" << sprites.size();
                switch (i){
                case 1:
                    window.draw(sprites[6]);    //baba
                    break;
                case 3:
                    window.draw(sprites[8]);    //flag
                    break;
                case 4:
                    window.draw(sprites[9]);    //lava
                    break;
                case 5:
                    window.draw(sprites[10]);   //rock
                    break;
                case 6 :
                    window.draw(sprites[11]);   //wall
                    break;     
                case 1+ +Type::Icon_Void:       //word baba
                case 2+ +Type::Icon_Void:       //word defeat
                case 3+ +Type::Icon_Void:       //word flag
                case 4+ +Type::Icon_Void:       //word hot
                case 5+ +Type::Icon_Void:       //word is
                case 6+ +Type::Icon_Void:       //word lava
                case 7+ +Type::Icon_Void:       //word melt
                case 8+ +Type::Icon_Void:       //word push
                case 9+ +Type::Icon_Void:       //word rock
                case 10+ +Type::Icon_Void:      //word stop
                case 11+ +Type::Icon_Void:      //word wall
                case 12+ +Type::Icon_Void:      //word win
                case 13+ +Type::Icon_Void:      //word you
                    window.draw(sprites[static_cast<std::size_t>(i+3)]);
                    break;
                default: break;
                }
            }

        }
        std::cerr << "welp, almost end of render()";
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
    PlayState Game::movementCheck(Position pos, Direction direction){
        Position shift{getShift(direction)};
        
        if(! getFirstMismatchOfObjects(m_map3D.getm_grid()[0], direction, pos)) 
            return PlayState::Invalid;

        Position first_mismatch {* getFirstMismatchOfObjects(m_map3D.getm_grid()[0], direction, pos)};
        Position last_before_mismatch {first_mismatch.first - shift.first, first_mismatch.second - shift.second};

        // while(conditions(getMap().At(target), getMap().At(next_target)) != PlayState::Invalid) non lo posso fare. conditions() distrugge gli objects
        return conditions(m_map3D.At(last_before_mismatch.first, last_before_mismatch.second), m_map3D.At(first_mismatch.first, first_mismatch.second));
    }

    void Game::rotate(Position &position, Direction direction){
        position.first = position.first;
        position.second = position.second;
        if (m_map3D.At(position.second, position.first).getTypes()[0] == Type::Baba) { //solo Baba è speciale
            sf::Sprite sprite {m_map3D.tileSprites[position.second * MapSize::width + position.first]};
            switch(direction){
                case Baba_Is_Us::Direction::Up:
                    sprite.setTexture(m_map3D.textures[4]);
                    break;
                case Baba_Is_Us::Direction::Down:
                    sprite.setTexture(m_map3D.textures[5]);
                    break;
                case Baba_Is_Us::Direction::Left:
                    sprite.setTexture(m_map3D.textures[7]);
                    break;
                case Baba_Is_Us::Direction::Right:
                    sprite.setTexture(m_map3D.textures[6]);
                    break;
                default: break;
            }
        }
    }


   /*void Game::movement(Direction direction, PlayState playstate){
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
         
        
        // 1/3
        
        // 2/3 

        // 3/3 
        //position.first = target.first;
        //position.second = target.second;
    
        //return true;
    }*/

    //overload
    void Game::movement(Direction direction){ 
        Position shift{getShift(direction)};
        std::size_t dx {shift.first};
        std::size_t dy {shift.second};
        std::vector<Position>& player_positions {getPlayerPositions()};

        for (auto& each : player_positions) {
            rotate(each, direction);
            //sf::Sprite& sprite {m_map3D.tileSprites[each.second * MapSize::width + each.first]};
            /*
            sprite.move(static_cast<float>(dx) * 11, static_cast<float>(dy) * 11); //muovi in direzione direction di 11 pixels
                sprite.move(MapSize::TILE_SIZE - static_cast<float>(dx) * 11, MapSize::TILE_SIZE - static_cast<float>(dy) * 11);
                    sprite.move(- static_cast<float>(dx) * 11, - static_cast<float>(dy) * 11);
            
            */
            m_map3D.accessm_grid()[0][each.second + dy][each.first + dx] = m_map3D.accessm_grid()[0][each.second][each.first];

            m_map3D.accessm_grid()[1][each.second + dy][each.first + dx] = m_map3D.accessm_grid()[1][each.second][each.first];

            m_map3D.addObject({dx, dy}, m_map3D.At(each.second, each.first).getTypes()[0]); 
            m_map3D.resetObject({dx, dy}); // with addObj e resetObj, m_objects è a posto
            
            if(m_map3D.getm_objects()[each.second][each.first].getTypes()[0] == Type::Void) { // se l'oggetto che si muove si è distrutto
                m_map3D.accessm_grid()[0][each.second][each.first] = +Type::Void;
                if (m_map3D.getm_objects()[each.second + dx][each.first + dy].getTypes()[0] == Type::Void) {//se anche il target si è distrutto
                    m_map3D.accessm_grid()[1][each.second + dy][each.first + dx] = +Type::Void;
                }
            } 
            
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

    PlayState handleStop(Objects&, Objects& second) {
        if (second.objectHasType(Type::Push)) return PlayState::Playing;
        return PlayState::Invalid;
    }

    PlayState Game::conditions(Objects& object, Objects& second) { //fanculo
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
