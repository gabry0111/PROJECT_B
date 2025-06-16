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

        // checkRulesForProperty
        // aggiungi le proprietà giuste ad ogni oggetto
        m_players = m_map3D.getPositions(Type::You);

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

    void Game::createRule(std::vector<Type>& word1,
                        std::vector<Type>& word2, std::vector<Type>& word3) {
        std::cerr << "\n word1: "; for (Type iter : word1) {std::cerr << iter << ' ';} 
        std::cerr << "\n word2: "; for (Type iter : word2) {std::cerr << iter << ' ';}
        std::cerr << "\n word3: "; for (Type iter : word3) {std::cerr << iter << ' ';}
        
        assert(!word2.empty() && !word3.empty() && "createRule()"); // una protezione in più
            if(+word1[1] > +Type::NOUN_TYPE  // se 3 parole di fila sono NOUN_TYPE, VERB_TYPE e PROPERTY_TYPE
            && +word1[1] < +Type::ICON_NOUN_TYPE
            && +word2[1] > +Type::VERB_TYPE 
            && +word2[1] < +Type::PROPERTY_TYPE 
            && +word3[1] > +Type::PROPERTY_TYPE) {
                Rule new_rule {word1[1], word2[1], word3[1]};
                m_RM.addRule(new_rule);
        }
    }

    void Game::parseRules() {
        std::vector<Position> block_pos {m_map3D.getPositions(Type::Block)};

        // check verticale (da alto a basso)
        for (Position& pos : block_pos) {
            std::cerr << pos.second << "," << pos.first << ' ';
            // N.B: per Block: [0] = Block, [2] = ICON_NOUN_TYPE
            if(m_map3D.isOutOfBoundary(pos.second - 1, pos.first)) { // vera <=> è la prima di una colonna
                std::cerr << "Prima (verticale)   /   \n";
                std::vector<Type> word1 {m_map3D.At(pos.second    , pos.first).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.second + 1, pos.first).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.second + 2, pos.first).getTypes()};

                if (word2[0] == Type::Block && word3[0] == Type::Block) {
                    createRule(word1, word2, word3);
                    continue;
                } 
                else {continue;}
            }

            if(! m_map3D.isOutOfBoundary(pos.second + 2, pos.first)) { // soddisfatta <=> y<=14
                std::cerr << "No prima (verticale), ma esistono altre 2 celle   /   \n";
                std::vector<Type> word1 {m_map3D.At(pos.second    , pos.first).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.second + 1, pos.first).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.second + 2, pos.first).getTypes()};

                if (word2[0] == Type::Block && word3[0] == Type::Block) {
                    createRule(word1, word2, word3);
                    continue;
                } 
                else {continue;}
            }
        }

        //check orizzontale
        for (Position& pos : block_pos) {
            std::cerr << pos.first << "," << pos.second << ' ';
            if(m_map3D.isOutOfBoundary(pos.second, pos.first - 1)) { // vera <=> è la prima di una riga
                std::cerr << "Prima (orizzontale)   /   \n";
                std::vector<Type> word1 {m_map3D.At(pos.second, pos.first    ).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.second, pos.first + 1).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.second, pos.first + 2).getTypes()};

                if (word2[0] == Type::Block && word3[0] == Type::Block) {
                    createRule(word1, word2, word3);
                    continue;
                } 
                else {continue;}
            }

            if(! m_map3D.isOutOfBoundary(pos.second, pos.first + 2)) {
                std::cerr << "No prima (orizzontale), ma esistono altre 2 celle   /   \n";
                std::vector<Type> word1 {m_map3D.At(pos.second, pos.first    ).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.second, pos.first + 1).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.second, pos.first + 2).getTypes()};

                if (word2[0] == Type::Block && word3[0] == Type::Block) {
                    createRule(word1, word2, word3);
                    continue;
                } 
                else {continue;}
            }
        std::cerr << m_RM.getRules().size() <<" rules parsed\n";
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

    void Game::update(sf::RenderWindow &window, Map &map, sf::Clock &clock){

        sf::Event event;

        Direction direction;
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
                        direction = Direction::Up;
                        //call function
                        break;
                    case sf::Keyboard::A:
                        //call function
                        direction = Direction::Left;
                        //call function
                        break;
                    case sf::Keyboard::S:
                        direction = Direction::Down;
                        //call function
                        break;
                    case sf::Keyboard::D:
                        direction = Direction::Right;
                        //call function
                        break;
                    case sf::Keyboard::Space: 
                        //check se ha un oggetto in mano
                        //lancia oggetto
                        break;
                    default: 
                        break;
                }

        //      movement_check(map, player[0], Direction::Up);
        //      rotate()
        //      se vero,    
        //          movement
        //
            //move, redraw, render
            //move, redraw, render
            //move, redraw, render
        //      se falso, fanculo
        //      movement_check(map, player, Direction::Up); -> vettore di pair di playState e positions
        /*      for(auto &i : playStates){
                    if(i.first == PlayState::Playing){
                        se è l'ultimo della fila
                            movement(map, i.second)
                    }
                    }
                */      
                //checkRules 

                
                //movimento visivo
                Position shift = getShift(direction);
                std::size_t dx {shift.first};
                std::size_t dy {shift.second};
                std::cerr<<"alright here we go\n";
                std::vector<Position>& player_positions {getPlayerPositions()};
                Position old_position ={MapSize::height, MapSize::width};

                for(auto& each : player_positions){
                    //Position tail{ (*getFirstMismatchOfObjects(m_map3D.getm_grid()[1], direction, each)).first };
                    if(/*tail != each ||*/ each == old_position){
                        old_position.first = each.first + shift.first;
                        old_position.second = each.second + shift.second;
                        continue;
                    }
                    //  --O -
                    // --O
                    //      -O
                    std::cerr<<"movement check\n";
                    PlayState check {movementCheck(each, direction)};
                    old_position.first = each.first + shift.first;
                    old_position.second = each.second + shift.second;
                    std::cerr<<"complete\n";

                    //movimento visivo
                    sf::Sprite& sprite {m_map3D.tileSprites[each.second * MapSize::width + each.first]};
                    std::cerr<<"or is it?\n";
                    //first 11 pixel
                    sprite.move(static_cast<float>(dx) * 11, static_cast<float>(dy) * 11);
                    map.redraw(clock);
                    render(window, map.tileSprites);   
                    
                    if(check==PlayState::Playing){
                        //rest of the movement
                        sprite.move(static_cast<float>(dx) * 10, static_cast<float>(dy) * 10);
                        map.redraw(clock);
                        render(window, map.tileSprites);

                        sprite.move(static_cast<float>(dx) * 11, static_cast<float>(dy) * 11);
                        map.redraw(clock);
                        render(window, map.tileSprites);
                    }
                    if(check==PlayState::Invalid){
                        // GO BACK WHERE YOU BELONG
                        sf::Sprite& backwards_sprite {m_map3D.tileSprites[each.second * MapSize::width + each.first]};
                        backwards_sprite.move(static_cast<float>(dx) * -11, static_cast<float>(dy) * -11);
                        map.redraw(clock);
                        render(window, map.tileSprites);
                    }
                }
            }
        }    
    }
    
    //associamo gli enum dati in level.txt a ciascun path di tilePaths
    std::optional<std::size_t> intToBeDrawn(const std::size_t i){
        std::size_t nth{};
        switch(i) {
            case 0: nth = 0;
                break;
            case 1: nth = 7; // fisso il default di Baba a BABA_right.png
                break;
            case 3: 
            case 4:
            case 5:
            case 6: nth = i + 6;
                break;

            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21: nth = i + 4;
                break;

            case 23:

            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            default : nth = tilePaths.size();
                break;
        }
        return (nth == tilePaths.size() ? std::nullopt : std::optional<std::size_t>(nth) );
    }

    void Game::render(sf::RenderWindow &window, std::vector<sf::Sprite> sprites){
        // draw the map
        window.clear();
        int x;
        int y;
        int count{};
        for (const auto& row : m_map3D.getm_grid()[0]){
            for (const auto &i : row){
                assert (i != +Type::NOUN_TYPE && i != +Type::ICON_NOUN_TYPE 
                     && i != +Type::VERB_TYPE && i != +Type::PROPERTY_TYPE 
                     && i != +Type::Block && i != +Type::Icon_Void && "in render() not given a valid value in m_grid[0]\n");
                
                if(! intToBeDrawn(static_cast<std::size_t> (i)) ) continue;

                std::size_t nth_sprite_to_be_drawn {* intToBeDrawn(static_cast<std::size_t>(i)) };
                
                assert(nth_sprite_to_be_drawn < tilePaths.size() 
                    && "render()'s nth_sprite... is beyond tilePaths.size()");

                if (nth_sprite_to_be_drawn < tilePaths.size()){
                    //posiziona e disegna ogni sprite
                    x = ( count % MapSize::width) * MapSize::TILE_SIZE;    // = 0, 32, 64, ... 255*32 
                    y = ( count / MapSize::width) * MapSize::TILE_SIZE;

                    sprites[nth_sprite_to_be_drawn].setPosition(static_cast<float>(x), static_cast<float>(y));
                    window.draw(sprites[nth_sprite_to_be_drawn]);
                }
                ++count;
            }
        }
        window.display();
    }

    // fallisce solo se è boundary. gli passo la mappa 2D e non 3D perché se Player può "andare sopra" all'oggetto, non crea nessun problema al movimento
    std::optional<std::pair<Position, Position>> getFirstMismatchOfObjects(const MapGrid2D& grid, Direction dir, const Position& start) {
        
        std::optional<std::pair<Position, Position>> result {};
        Position shift{getShift(dir)};
        std::size_t x=start.first;
        std::size_t y=start.second;
        int value = grid[y][x];
        while(x < MapSize::width && y < MapSize::height) {
            if(grid[y][x] != value){
                result = {start, {x,y}};
                return result;
            }
                
            x += shift.first;
            y += shift.second;
        }
        return std::nullopt;
    }

    // se non si può fare (non si può muovere e gli oggetti sono già distrutti), allora vedere se movementCheck è "vuoto"
    // ASSICURATI CHE conditions() NON SIA MAI PIù CHIAMATA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // VA BENE OK DIEGO
    PlayState Game::movementCheck(const Position pos, Direction direction){
        
        if(! getFirstMismatchOfObjects(m_map3D.getm_grid()[1], direction, pos)) 
            return PlayState::Invalid;

        std::pair<Position, Position> result{*getFirstMismatchOfObjects(m_map3D.getm_grid()[1], direction, pos) };
        Position first_mismatch{ result.second.first, result.second.second };      //target
        Position first_of_line {result.first.first, result.first.second};          //farthest object relative to the target
        
        // while(conditions(getMap().At(target), getMap().At(next_target)) != PlayState::Invalid) non lo posso fare. conditions() distrugge gli objects
        return conditions(m_map3D.At(first_of_line.first, first_of_line.second), m_map3D.At(first_mismatch.first, first_mismatch.second));
    }

    void Game::rotate(Position &position, Direction direction){
        position.first = position.first;
        position.second = position.second;
        if (m_map3D.At(position.second, position.first).getTypes()[1] == Type::Baba) { //solo Baba è speciale
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

    PlayState Game::conditions(Objects& object, Objects& second) { //fanculo alle 14:30
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
