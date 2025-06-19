#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "map.hpp"
#include "game.hpp"
#include "objects.hpp"
#include "rules.hpp"

namespace Baba_Is_Us{

    

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
    PlayState Game::accessm_state_of_game() {
        return m_state_of_game;
    }

    ///////////////////////////////////     Chapter: HandlingRules     ///////////////////////////////////

    // Per ogni regola di m_rules, aggiunge il PROPERTY_TYPE della regola a tutti gli oggetti indicati dalla regola
    void Game::adjustAddingRules() {
        std::vector<Rule> rules {m_RM.getm_rules()};
        assert (rules.size() > 0);
        for (const Rule& each_rule : m_RM.getm_rules()) { // per ogni singola regola
            //for (auto rule_type : each_rule.getm_rule()) {std::cerr <<"rule_type: " << rule_type << ' ';}

            Type noun_type {each_rule.getm_rule()[0]}; // cerca il NOUN_TYPE a cui fa riferimento
            assert(noun_type != Type::Block && "adjustAddingRules(): noun_type == Type::Block");
            Type prop_or_noun_type {each_rule.getm_rule()[2]}; // salva la NOUN o PROPERTY_TYPE della regola
            std::vector<Position> pos_of_types_with_rule {m_map3D.getPositions(noun_type)}; 

            assert(((+prop_or_noun_type > +Type::NOUN_TYPE && +prop_or_noun_type < +Type::ICON_NOUN_TYPE) 
                || (+prop_or_noun_type > +Type::PROPERTY_TYPE)) && "adjustAddingRules(): prop_or_noun_type not one of the two Types");
            for (const Position& each_pos : pos_of_types_with_rule) { // per ogni istanza dell'oggetto NOUN_TYPE
                Objects& obj {m_map3D.At(each_pos.first, each_pos.second)};
                //std::cerr << noun_type << prop_or_noun_type << each_pos.first << each_pos.second << '\n';
                std::cerr << "Property or noun type is: " << prop_or_noun_type;
                if (+prop_or_noun_type > +Type::PROPERTY_TYPE) { // se è una PROPERTY_TYPE, aggiungila o toglila semplicemente
                    if(! obj.objectHasType(prop_or_noun_type)){ // controlla che non abbia già il tipo delle regole
                        obj.addType(prop_or_noun_type); //N.B: obj è reference
                        //for (auto types : obj.getTypes()) 
                        //    std::cerr <<"Types: " << types << '\n';
                    } 
                } else { // se è una NOUN_TYPE, aggiungi tutte le property di quel NOUN_TYPE
                    for (const Rule iter_rules : m_RM.getm_rules()) {
                        if(std::find(iter_rules.getm_rule().begin(), iter_rules.getm_rule().end()
                                      , prop_or_noun_type) != iter_rules.getm_rule().end()) {
                            obj.addType(iter_rules.getm_rule()[2]); //aggiungi la PROPERTY_TYPE della regola
                        }
                    }
                }
            }
        }
    }

    void Game::createRule(const std::vector<Type>& word1,
                        const std::vector<Type>& word2, const std::vector<Type>& word3) {
        std::cerr << "\n word1: "; for (Type iter : word1) {std::cerr << iter << ' ';} 
        std::cerr << "\n word2: "; for (Type iter : word2) {std::cerr << iter << ' ';}
        std::cerr << "\n word3: "; for (Type iter : word3) {std::cerr << iter << ' ';}
        std::cerr << '\n'; 
        
        assert(!word2.empty() && !word3.empty() && "createRule()"); // una protezione in più
        if(+word1[1] > +Type::NOUN_TYPE  // se 3 parole di fila sono NOUN_TYPE, VERB_TYPE e PROPERTY_TYPE
        && +word1[1] < +Type::ICON_NOUN_TYPE
        && +word2[1] > +Type::VERB_TYPE 
        && +word2[1] < +Type::PROPERTY_TYPE 
        && +word3[1] > +Type::PROPERTY_TYPE) {
            bool already_exists = std::any_of(m_RM.getm_rules().begin(), m_RM.getm_rules().end(),[&](const Rule& rule) {
                return rule.getm_rule()[0] == word1[1] &&
                    rule.getm_rule()[1] == word2[1] &&
                    rule.getm_rule()[2] == word3[1]; });
            if (!already_exists) {
                Rule new_rule {word1[1], word2[1], word3[1]};
                m_RM.addRule(new_rule);
                std::cerr << "Rule added: " << word1[1] << " " << word2[1] << " " << word3[1] << '\n';


            }
        }
    }

    void Game::parseRules() {
        m_RM.clearRules();
        std::cerr << "In parseRules()\n";
        std::vector<Position> block_pos {m_map3D.getPositions(Type::Block)};

        for (const Position& pos : block_pos) {
            std::cerr << '(' << pos.first << "," << pos.second << ") ";

            // check verticale
            if (!m_map3D.isOutOfBoundary(pos.first, pos.second + 2)) {
                std::cerr << "Rule orientation: vertical"
                        << " | From (x=" << pos.first << ", y=" << pos.second
                        << ") to (" << pos.first << "," << pos.second + 2 << ")\n";

                const auto& word1 = m_map3D.At(pos.first, pos.second    ).getTypes();
                const auto& word2 = m_map3D.At(pos.first, pos.second + 1).getTypes();
                const auto& word3 = m_map3D.At(pos.first, pos.second + 2).getTypes();

                if (word2[0] == Type::Block && word3[0] == Type::Block)
                    createRule(word1, word2, word3);
            }

            // check orizzontale
            if (!m_map3D.isOutOfBoundary(pos.first + 2, pos.second)) {
                std::cerr << "Rule orientation: horizontal"
                        << " | From (x=" << pos.first << ", y=" << pos.second
                        << ") to (" << pos.first + 2 << "," << pos.second << ")\n";

                const auto& word1 = m_map3D.At(pos.first    , pos.second).getTypes();
                const auto& word2 = m_map3D.At(pos.first + 1, pos.second).getTypes();
                const auto& word3 = m_map3D.At(pos.first + 2, pos.second).getTypes();

                if (word2[0] == Type::Block && word3[0] == Type::Block)
                    createRule(word1, word2, word3);
            }
        }

        std::cerr << m_RM.getm_rules().size() <<" rules parsed\n";
        adjustAddingRules();
        std::cerr << "Exiting parseRules()\n";
        for(Type type : m_map3D.At(0,1).getTypes()) {
            std::cerr << "Types of object at position (0,1) from .At(): " << m_map3D.At(0,1).getTypes()[0] << type << '\n';}
        for(Type type : m_map3D.At(1,0).getTypes()) {
            std::cerr << "Types of object at position (1,0) from .At(): " << m_map3D.At(1,0).getTypes()[0] << type << '\n';}
        for(Type type : m_map3D.getm_objects()[0][1].getTypes() ) {
            std::cerr << "Types of object at position (1,0) from m_objects: " << m_map3D.getm_objects()[0][1].getTypes()[0] << type << '\n';}
        for(Type type : m_map3D.getm_objects()[1][0].getTypes() ) {
            std::cerr << "Types of object at position (0,1) from m_objects: " << m_map3D.getm_objects()[1][0].getTypes()[0] << type << '\n';}
        std::cerr << '\n';
    }


    /////////////////////////////////// Chapter: Handling Movement and KeyPressing ///////////////////////////////////
    
    // servirà per un altro controllo che nessun oggetto abbia tre NOUN_TYPE
    std::optional<std::size_t> findSecondNoun(const std::vector<Type>& types) {
        int count {};
        for (std::size_t i = 0; i < types.size(); ++i) {
            if (types[i] > Type::Void && types[i] < Type::ICON_NOUN_TYPE) { 
                ++count;
                if (count == 2) {
                    return i;
                }
            }
        }
        assert (count > 0 && count < 3  &&"findSecondNoun() non funziona"); // N.B: t==0 sarebbe il primo NOUN_TYPE
        return std::nullopt; 
    }

    Position getShift(Direction dir) {
        switch (dir) {                                                      
            case Direction::Up:    return {0, -1};                          
            case Direction::Down:  return {0, 1 };
            case Direction::Left:  return {-1, 0};
            case Direction::Right: return {1, 0 };
            default:               return {0, 0 };
        }
    }

    // N.B: data una fila verticale di oggetti attaccati e la direzione Up, l'oggetto Tail è quello più in basso
    bool isTailOfLine(Position pos, Map &map, Direction dir) { //prima (circa) funzione ricorsiva!!!! yay :3 yippee :DDDD
        Type type {map.At(pos.first, pos.second).getTypes()[0]};
        std::size_t dx = getShift(dir).first;
        std::size_t dy = getShift(dir).second;
        if (map.isOutOfBoundary(pos.first-dx, pos.second-dy)){
            return true;
        }
        return (type != map.At(pos.first - dx, pos.second - dy).getTypes()[0]);
    }

    std::vector<Position> Game::getTailMovingPosition(Direction direction) {
        std::vector<Position> pos_to_be_moved {};
        assert (m_players.size() > 0);
        for (const Position& pos : m_players){
            if (isTailOfLine(pos, m_map3D, direction)) {
                pos_to_be_moved.emplace_back(pos);
            }
        }
        return pos_to_be_moved;
    }


    // fallisce solo se è boundary. gli passo la mappa 2D e non 3D perché se Player può "andare sopra" all'oggetto, non crea nessun problema al movimentoMore actions
    // N.B: TAIL SARà GIA PASSATO COME START PERCHé è CHIAMATA PRIMA getTailMovingPosition()
    std::optional<Position> getMismatch(const MapGrid2D& grid, Direction dir, Position start) {
        std::optional<Position> result {};
        Position shift{getShift(dir)};
        std::size_t x {start.first};
        std::size_t y {start.second};
        int value = grid[y][x];
        std::cerr << "Position start: " << start.first << start.second << " And type: " << intToType(value) << '\n';
        while(x < MapSize::width && y < MapSize::height) {
            if(grid[y][x] != value){
                result = {x,y};
                std::cerr << "Mismatch is in position: " << x << y << '\n';
                return result;
            }

            x += shift.first;
            y += shift.second;
        }
        return std::nullopt;
    }

    //overload
    void Game::movement(sf::RenderWindow& window, sf::Clock& clock, Direction direction){ 

        
        Position shift = getShift(direction);
        std::size_t dx {shift.first};
        std::size_t dy {shift.second};

        
        std::cerr<<"alright here we go\n";
        std::vector<Position> tail_pos {getTailMovingPosition(direction)};

        assert(tail_pos.size() > 0 && "movement(): tail_pos.size() == 0");
            std::cerr << "tail_pos.size() == "<< tail_pos.size() << " positions: ";

        const std::size_t baba_move_index{static_cast<std::size_t> (+direction + 1)};
        const std::size_t baba_idle_index{static_cast<std::size_t> (+direction + 5)};

        for (const auto& pos : tail_pos)
            std::cerr<<pos.first<<" "<<pos.second<<"\n";
        
        for (auto& each : tail_pos){ // solo gli oggetti tail, per ciascuna fila, si spostano in quella direzione, non tutti

            // CASO POSSIBILE: nel caso Baba is Wall, m_grid[0] sarà Baba, m_grid[1] sarà Baba, m_objects sarà Baba con NOUN_TYPE Wall, e sarà disegnato Wall
            
            // ???????????????????????????????????????????????????????????????? 
            // CASO POSSIBILE: nel caso Wall is Move (scavalcabile), m_grid[0] sarà Baba, m_grid[1] sarà ???, m_objects ???
            // Perché m_objects se ha un altro NOUN_TYPE dentro un oggetto, visualizzerà il secondo
            
            // quale sprite devi muovere e/o ruotare, tenendo conto del caso descritto?
            std::vector<Type> types {m_map3D.getm_objects()[each.second][each.first].getTypes()};
            std::size_t index_to_modify {};
            findSecondNoun(types).has_value() ? index_to_modify = +(*findSecondNoun(types))
                                              : index_to_modify = indexToBeDrawn(static_cast<size_t>(m_map3D.getm_grid()[0][each.second][each.first]));
            
            sf::Sprite& player_sprite = m_map3D.tileSprites[index_to_modify];
            
            // solo Baba (in tilePaths con indice da 1 a 8) ha varianti nelle texture.
            // Per prima cosa, giriamo la sprite.
            if (index_to_modify >= 1 && index_to_modify <= 8){  
                player_sprite = m_map3D.tileSprites[baba_idle_index];
                player_sprite.setTexture(m_map3D.textures[baba_idle_index]);
            }
            m_map3D.redraw(clock);
            render(window, m_map3D.tileSprites);

            std::optional<Position> mismatch_opt {getMismatch(m_map3D.getm_grid()[1], direction, each)};
            if (!mismatch_opt) continue;
            Position pos_mismatch = *mismatch_opt;
            // N.B: non serve il valore assoluto, ma il loro segno dipende dalla direzione mandata in getMismatch()
            size_t delta_x = pos_mismatch.first - each.first;
            size_t delta_y = pos_mismatch.second - each.second;

            // Verifichiamo che il movimento eventuale non sia fuori dalla mappa
            if(m_map3D.isOutOfBoundary(each.first + delta_x, each.second + delta_y)) {continue;}


            // Ora siamo pronti

            //////////// movimento visivo

            // se la sprite è a bordo mappa, muoverla oltre la mappa crea casini (N.B: deve essere m_grid[1])
            if(! getMismatch(m_map3D.getm_grid()[1], direction, each).has_value()) {continue;
            } else {
            player_sprite = m_map3D.tileSprites[baba_move_index];
            player_sprite.setTexture(m_map3D.textures[baba_move_index]);
            player_sprite.move(static_cast<float>(dx * 11), static_cast<float>(dy * 11));
            m_map3D.redraw(clock);
            render(window, m_map3D.tileSprites);
            sf::sleep(sf::milliseconds(30));
            }

            Objects& obj_tail = m_map3D.At(each.first, each.second);
            Objects& obj_mismatch = m_map3D.At(pos_mismatch.first, pos_mismatch.second);
            PlayState state = conditions(obj_tail, obj_mismatch);

            if (state == PlayState::Playing) {
                player_sprite.move(static_cast<float>(dx * 11), static_cast<float>(dy * 11));
                m_map3D.redraw(clock);
                render(window, m_map3D.tileSprites);
                sf::sleep(sf::milliseconds(30));

                player_sprite.move(static_cast<float>(dx * 11), static_cast<float>(dy * 11));
                m_map3D.redraw(clock);
                render(window, m_map3D.tileSprites);
                sf::sleep(sf::milliseconds(30));

                //movimento visivo ////////////
                //////////// movimento effettivo

                m_map3D.accessm_grid()[0][each.second + delta_y][each.first + delta_x] = m_map3D.accessm_grid()[0][each.second][each.first];
                m_map3D.accessm_grid()[0][each.second][each.first] = +Type::Void;

                m_map3D.accessm_grid()[1][each.second + delta_y][each.first + delta_x] = m_map3D.accessm_grid()[1][each.second][each.first];
                m_map3D.accessm_grid()[1][each.second][each.first] = +Type::Void;    

                m_map3D.accessm_objects()[each.second + delta_y][each.first + delta_x] = m_map3D.At(each.first, each.second).getTypes();
                m_map3D.resetObject({each.first, each.second}); 

                    //movimento effettivo ////////////
                    //////////// movimento visivo

                } else if(state == PlayState::Invalid) {
                    player_sprite.move(static_cast<float>(dx) * -11, static_cast<float>(dy) * -11);
                    m_map3D.redraw(clock);
                    render(window, m_map3D.tileSprites);
                }

                player_sprite = m_map3D.tileSprites[baba_idle_index];
                player_sprite.setTexture(m_map3D.textures[baba_idle_index]);
                m_map3D.redraw(clock);
                render(window, m_map3D.tileSprites);
                
                //movimento visivo ////////////
        }
        std::cerr<<" movement complete\n";
        
        std::vector<Position>& player_positions {getPlayerPositions()};
        assert(player_positions.size() > 0 && "movement(): player_positions.size() == 0");
        for (std::size_t i {}; i<16; ++i){
            for (std::size_t j{}; j<16; ++j){
                std::cerr<<m_map3D.getm_grid()[0][i][j]<<" ";
            }                
            std::cerr<<"\n";
        }
        std::cerr<<"akfnjdsaknjaofbjabd\n";
        for (std::size_t i {}; i<16; ++i){
            for (std::size_t j{}; j<16; ++j){
                std::cerr<<m_map3D.getm_grid()[1][i][j]<<" ";
            }                
            std::cerr<<"\n";
        }
        std::cerr<<"OBEJKFCSDJTKJSADAS------------\n";
        for (std::size_t i {}; i<16; ++i){
            for (std::size_t j{}; j<16; ++j){
                std::cerr<<m_map3D.getm_objects()[i][j].getTypes()[0]<<" ";
            }
            std::cerr<<"\n";
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
                        movement(window, clock, direction);
                        break;
                    case sf::Keyboard::A:
                        //call function
                        direction = Direction::Left;
                        movement(window, clock, direction);
                        break;
                    case sf::Keyboard::S:
                        direction = Direction::Down;
                        movement(window, clock, direction);
                        break;
                    case sf::Keyboard::D:
                        direction = Direction::Right;
                        movement(window, clock, direction);

                        break;
                    case sf::Keyboard::Space: 
                        //check se ha un oggetto in mano
                        //lancia oggetto
                        break;
                    default: 
                        break;
                }
            }
        }
    }    
    
    /////////////////////////////////// Chapter: Handling Displaying ///////////////////////////////////

    

    void Game::render(sf::RenderWindow &window, std::vector<sf::Sprite> sprites){
        // draw the map
        window.clear();
        int x;
        int y;
        int count{};
        for (const auto& rows : m_map3D.getm_grid()[0]){
            for (const auto &i : rows){
                assert (i != +Type::NOUN_TYPE && i != +Type::ICON_NOUN_TYPE 
                     && i != +Type::VERB_TYPE && i != +Type::PROPERTY_TYPE 
                     && i != +Type::Block && i != +Type::Icon_Void && "in render() not given a valid value in m_grid[0]\n");
                if(indexToBeDrawn(static_cast<std::size_t> (i)) > tilePaths.size()) continue;

                std::size_t nth_sprite_to_be_drawn {indexToBeDrawn(static_cast<std::size_t>(i)) };
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

    /////////////////////////////////// Chapter: Handling Interactions ///////////////////////////////////

    PlayState handleDefeat(Objects& object, Objects&, PlayState& state_of_game) {
        if (object.objectHasType(Type::You)) {
            state_of_game = PlayState::Lose;
            return PlayState::Playing;
        }
        return PlayState::Invalid;
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

    PlayState handleStop(Objects& object, Objects&) {
        if (object.objectHasType(Type::Push)) return PlayState::Playing;
        return PlayState::Invalid;
    }

    PlayState Game::conditions(Objects& tail, Objects& mismatch) { //fanculo alle 14:30
        
        std::vector<Type> mismatch_types {mismatch.getTypes()};
        PlayState action {PlayState::Playing};
        for(const auto type : mismatch_types){ // per ogni Type di Objects second
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
            // controllare che object[0] NON sia Type::Block -----------------------
            // beh, in teoria vale

            switch (type) {
            case Type::Block:  return PlayState::Playing; break; // i blocchi si possono sempre muovere, LASCIAMOLO PER PRIMO

            case Type::Void:   action = PlayState::Playing; break;
            case Type::Defeat: action = handleDefeat(tail, mismatch, m_state_of_game); break;
            case Type::Hot:    action = handleHot(tail, mismatch); break;
            case Type::Launch: action = PlayState::Playing; break;
            case Type::Melt:   action = PlayState::Playing; break;
            case Type::Move:   action = PlayState::Playing; break;
            case Type::Open:   action = PlayState::Playing; break;
            case Type::Push:   action = PlayState::Playing; break;
            case Type::Shut:   action = handleShut(tail, mismatch); break;
            case Type::Stop:   action = handleStop(tail, mismatch); break;
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
