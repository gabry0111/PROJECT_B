#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.hpp"
#include "game.hpp"
#include "objects.hpp"
#include "rules.hpp"

/* Avuta la mappa del livello corrente, verifica quali azioni sono possibili:
- verifica le proprietà di ciascun oggetto (sarà fatto nel Main Loop)
- resetta il livello se PlayState è Invalid
- gestisce il movimento del Player
- gestisce il movimento degli oggetti 
- 
*/ 

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
    void Game::adjustRules() {
        std::vector<Rule> rules {m_RM.getm_rules()};
        assert (rules.size() > 0);
        for (const Rule& each_rule : m_RM.getm_rules()) { // per ogni singola regola
            for (auto rule_type : each_rule.getm_rule()) {std::cerr <<"rule_type: " << rule_type << ' ';}

            Type noun_type {each_rule.getm_rule()[0]}; // cerca il NOUN_TYPE a cui fa riferimento
            assert(noun_type != Type::Block);
            Type prop_or_noun_type {each_rule.getm_rule()[2]}; // salva la NOUN o PROPERTY_TYPE della regola
            std::vector<Position> pos_of_types_with_rule {m_map3D.getPositions(noun_type)}; 

            for (const Position& each_pos : pos_of_types_with_rule) { // per ogni istanza dell'oggetto
                std::cerr << noun_type << prop_or_noun_type << each_pos.first << each_pos.second << '\n';

                Objects obj {m_map3D.At(each_pos.first, each_pos.second)};
                if(! obj.objectHasType(prop_or_noun_type)){ // controlla che non abbia già il tipo delle regole
                    obj.addType(prop_or_noun_type);
                    // gli Objects sono tutti salvati qui, non in m_grid
                    m_map3D.accessm_objects()[each_pos.second][each_pos.first] = obj;
                    for (auto types : obj.getTypes()) 
                        std::cerr <<"Types: " << types << '\n';
                } else {}
            }
        }
    }

    void Game::createRule(std::vector<Type>& word1,
                        std::vector<Type>& word2, std::vector<Type>& word3) {
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
        std::cerr << "In parseRules()\n";
        std::vector<Position> block_pos {m_map3D.getPositions(Type::Block)};

        // check verticale (da alto a basso)
        for (Position& pos : block_pos) {
            std::cerr << '(' << pos.first << "," << pos.second << ')';
            
            // N.B: per Block: [0] = Block, [2] = ICON_NOUN_TYPE
            if(m_map3D.isOutOfBoundary(pos.first, pos.second - 1)) { // vera <=> è la prima di una colonna
                std::cerr << " Prima (verticale)   /   \n";
                std::cerr << "Rule orientation: vertical" << " | From (x=" << pos.first << ", y=" << pos.second 
                << " to " << pos.first << pos.second + 1 <<  ")\n";

                std::vector<Type> word1 {m_map3D.At(pos.first, pos.second    ).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.first, pos.second + 1).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.first, pos.second + 2).getTypes()};

                if (word2[0] == Type::Block && word3[0] == Type::Block) {

                    createRule(word1, word2, word3);
                    continue;
                } 
                else {continue;}
            }

            if(! m_map3D.isOutOfBoundary(pos.first, pos.second + 2)) { // soddisfatta <=> y<=14
                std::cerr << " No prima (verticale), ma esistono altre 2 celle   /   \n";
                std::cerr << "Rule orientation: vertical" << " | From (x=" << pos.first << ", y=" << pos.second 
                << " to " << pos.first << pos.second + 1 <<  ")\n";
                std::vector<Type> word1 {m_map3D.At(pos.first, pos.second    ).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.first, pos.second + 1).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.first, pos.second + 2).getTypes()};

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
            if(m_map3D.isOutOfBoundary(pos.first - 1, pos.second)) { // vera <=> è la prima di una riga
                std::cerr << " Prima (orizzontale)   /   \n";
                std::cerr << "Rule orientation: horizontal" << " | From (x=" << pos.first << ", y=" << pos.second 
                << " to " << pos.first + 1 << pos.second <<  ")\n";
                std::vector<Type> word1 {m_map3D.At(pos.first    , pos.second).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.first + 1, pos.second).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.first + 2, pos.second).getTypes()};

                if (word2[0] == Type::Block && word3[0] == Type::Block) {
                    createRule(word1, word2, word3);
                    continue;
                } 
                else {continue;}
            }

            if(! m_map3D.isOutOfBoundary(pos.first + 2, pos.second)) {
                std::cerr << " No prima (orizzontale), ma esistono altre 2 celle   /   \n";
                std::cerr << "Rule orientation: horizontal" << " | From (x=" << pos.first << ", y=" << pos.second 
                << " to " << pos.first + 1 << pos.second <<  ")\n";
                std::vector<Type> word1 {m_map3D.At(pos.first    , pos.second).getTypes()};
                std::vector<Type> word2 {m_map3D.At(pos.first + 1, pos.second).getTypes()};
                std::vector<Type> word3 {m_map3D.At(pos.first + 2, pos.second).getTypes()};

                if (word2[0] == Type::Block && word3[0] == Type::Block) {
                    createRule(word1, word2, word3);
                    continue;
                } 
                else {continue;}
            }
        }
        std::cerr << m_RM.getm_rules().size() <<" rules parsed\n";
        adjustRules();
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

    // controlla se l'oggetto è all'inizio della riga (vert o orizz)
    //AGGIUNGERE LO SHIFT PER FARLO PIù BELLINO


    Position getShift(Direction dir) {
        switch (dir) {                                                      
            case Direction::Up:    return {0, -1};                          
            case Direction::Down:  return {0, 1 };
            case Direction::Left:  return {-1, 0};
            case Direction::Right: return {1, 0 };
            default:               return {0, 0 };
        }
    }
    bool isBeginningOfLine(Position pos, Map &map, Direction dir) { //prima (circa) funzione ricorsiva!!!! yay :3 yippee :DDDD
        Position shift {getShift(dir)};
        Type type {map.At(pos.first, pos.second).getTypes()[0]};
        std::size_t dx = shift.first;
        std::size_t dy = shift.second;
        std::cerr<<"no, here! -";
        if (map.isOutOfBoundary(pos.first+dx, pos.second+dy)){
            std::cerr<<"seems here -";
            return true;
        }

        else if (map.getm_objects()[pos.second-dy][pos.first-dx].getTypes()[0] != type)
            return true;

        return false;
        /*
        //isBeginningOfLine non deve controllare questo (), deve controllare che sia il primo della FILA di oggetti, non della riga lunga 16
        switch(dir){ // è la prima della riga <=> ...
            case Direction::Up: 
                return (y == MapSize::height || map.At(x, y - 1).getTypes()[0] != type);
                break;
            case Direction::Down:
                return (y == 0 || map.At(x, y + 1).getTypes()[0] != type);
                break;
            case Direction::Left:
                return (x == MapSize::width || map.At(x - 1, y).getTypes()[0] != type);
                break;
            case Direction::Right:
                return (x == MapSize::width || map.At(x + 1, y).getTypes()[0] != type);
                break;
            default: throw(std::runtime_error("isBeginningOfLine(): not given a valid direction"));
        }
            */
    }

    std::vector<Position> Game::getFirstMovingPositions(Direction direction) {
        std::vector<Position> pos_to_be_moved {};
        std::cerr<<"in here - ";
        assert (m_players.size() > 0);
        for (auto& pos : m_players){
            if (isBeginningOfLine(pos, m_map3D, direction)) {
                std::cerr<<"i guess here\n";
                pos_to_be_moved.emplace_back(pos);
            }
        }
        return pos_to_be_moved;
    }
    
    //N.B: la sprite di Baba sarà quella ferma, non "...move_up"
    void Game::rotate(Position &position, Direction direction, std::size_t& index_to_modify){
        if (m_map3D.At(position.first, position.second).getTypes()[0] == Type::Baba) { //solo Baba è speciale
            // purché teniamo sempre l'ordine di: enum Direction e gifs di Baba in tilePaths possiamo fare:
            index_to_modify = static_cast<std::size_t> (+direction + 5);
            sf::Sprite& sprite {m_map3D.tileSprites[index_to_modify]};
            std::cerr<<m_map3D.getm_grid()[0][position.second][position.first]<<" in grid in direction "<< +direction<<"\n";
            
            sprite.setTexture(m_map3D.textures[ static_cast<std::size_t> (+direction + 1) ]);
        }
    }

    //overload
    void Game::movement(sf::RenderWindow& window, sf::Clock& clock, Direction direction){ 

        Position shift = getShift(direction);
        std::size_t dx {shift.first};
        std::size_t dy {shift.second};
        std::cerr<<"alright here we go\n";
        std::vector<Position> moving_pos {getFirstMovingPositions(direction)};

        assert(moving_pos.size() > 0 && "movement(): moving_pos.size() == 0");
            std::cerr << "moving_pos.size() == "<< moving_pos.size() << " positions: ";

        for (const auto& pos : moving_pos)
            std::cerr<<pos.first<<" "<<pos.second<<"\n";
        
        for (auto& each : moving_pos){ // solo i primi oggetti per fila che si spostano in quella direzione
            //movimento visivo
            
            std::size_t index_to_be_drawn {indexToBeDrawn(static_cast<std::size_t>(+m_map3D.getm_grid()[0][each.second][each.first]))};
            sf::Sprite& player_sprite {m_map3D.tileSprites[index_to_be_drawn]}; // & because all players should change
            std::cerr<<"it's visual time!\n";
         
            //ROTATE BANANA ROTATE
            rotate(each, direction, index_to_be_drawn);
            m_map3D.redraw(clock);
            render(window, m_map3D.tileSprites);
            std::cerr<<" - rotated - ";
            if(m_map3D.isOutOfBoundary(each.first + dx, each.second + dy)) {
                continue;
            }
            //first 11 pixels
            //baba (the special one) goes to moving sprite
            if(m_map3D.At(each.first, each.second).getTypes()[0] == Type::Baba) {
                player_sprite=m_map3D.tileSprites[index_to_be_drawn -4];
                std::cerr<<index_to_be_drawn<<" "<<index_to_be_drawn -4 <<" "<<index_to_be_drawn +4 <<"\n";
            }
            player_sprite.move(static_cast<float>(dx) * 11, static_cast<float>(dy) * 11);
            m_map3D.redraw(clock);
            render(window, m_map3D.tileSprites); 
            

            PlayState check {movementCheck(each, direction)};
            // se l'azione è valida (=> l'oggetto movente non è distrutto)
            if (check == PlayState::Playing) { 
                std::cerr << "PlayState = Playing - ";
                player_sprite.move(static_cast<float>(dx) * 10, static_cast<float>(dy) * 10);
                m_map3D.redraw(clock);
                render(window, m_map3D.tileSprites);

                player_sprite.move(static_cast<float>(dx) * 11, static_cast<float>(dy) * 11);
                m_map3D.redraw(clock);
                render(window, m_map3D.tileSprites);
            
                if(m_map3D.isOutOfBoundary(each.first + dx, each.second + dy)) continue;

                m_map3D.accessm_grid()[0][each.second + dy][each.first + dx] = m_map3D.accessm_grid()[0][each.second][each.first];

                m_map3D.accessm_grid()[1][each.second + dy][each.first + dx] = m_map3D.accessm_grid()[1][each.second][each.first];

                m_map3D.accessm_objects()[each.second + dy][each.first + dx] =m_map3D.At(each.first, each.second).getTypes();
                m_map3D.resetObject({each.first, each.second}); // with addObj e resetObj, m_objects è a posto -> FALSO
                
                if(m_map3D.getm_objects()[each.second][each.first].getTypes()[0] == Type::Void) { // se l'oggetto che si muove si è distrutto

                    m_map3D.accessm_grid()[0][each.second][each.first] = +Type::Void;

                    if (m_map3D.getm_objects()[each.second + dy][each.first + dx].getTypes()[0] == Type::Void) {//se anche il target si è distrutto
                        m_map3D.accessm_grid()[1][each.second + dy][each.first + dx] = +Type::Void;
                        std::cerr<< "uh oh - ";
                    }
                } 

            } else if(check == PlayState::Invalid) {
                std::cerr << "PlayState = Invalid \n";
                player_sprite.move(static_cast<float>(dx) * -11, static_cast<float>(dy) * -11);
                m_map3D.redraw(clock);
                render(window, m_map3D.tileSprites);
            }

            //baba goes to idle sprite
            player_sprite=m_map3D.tileSprites[index_to_be_drawn];
            player_sprite.setTexture(m_map3D.textures[index_to_be_drawn]);

            m_map3D.redraw(clock);
            render(window, m_map3D.tileSprites);

        }
        std::cerr<<" visual movement complete\n";
        
        std::vector<Position>& player_positions {getPlayerPositions()};
        assert(player_positions.size() > 0 && "movement(): player_positions.size() == 0");
        
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

    // fallisce solo se è boundary. gli passo la mappa 2D e non 3D perché se Player può "andare sopra" all'oggetto, non crea nessun problema al movimento
    std::optional<std::pair<Position, Position>> getFirstAndMismatch(const MapGrid2D& grid, Direction dir, Position start) {
        std::optional<std::pair<Position, Position>> result {};
        Position shift{getShift(dir)};
        std::size_t x {start.first};
        std::size_t y {start.second};
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
        if(! getFirstAndMismatch(m_map3D.getm_grid()[1], direction, pos)) // se la linea continua fino a fine mappa
            return PlayState::Invalid;

        std::pair<Position, Position> result{*getFirstAndMismatch(m_map3D.getm_grid()[1], direction, pos) };
        Position first_mismatch{ result.second.first, result.second.second };      //target
        Position first_of_line {result.first.first, result.first.second};          //farthest object relative to the target
        
        // ATTENZIONE: while(conditions(getMap().At(target), getMap().At(next_target)) != PlayState::Invalid) non lo posso fare. conditions() distrugge gli objects
        return conditions(m_map3D.At(first_of_line.first, first_of_line.second)
                        , m_map3D.At(first_mismatch.first, first_mismatch.second));
    }

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
            // beh, in teoria vale

            switch (type) {
            case Type::Block:  return PlayState::Playing; break; // i blocchi si possono sempre muovere, LASCIAMOLO PER PRIMO

            case Type::Void: action = PlayState::Playing; break;
            case Type::Defeat: action = handleDefeat(object, second, m_state_of_game); break;
            case Type::Hot:    action = handleHot(object, second); break;
            case Type::Launch: action = PlayState::Playing; break;
            case Type::Melt:   action = PlayState::Playing; break;
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
