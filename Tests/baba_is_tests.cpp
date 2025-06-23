#include "src/enum_objects.hpp" 
#include "src/objects.hpp" 
#include "src/map.hpp" 
#include "src/rules.hpp" 
#include "src/game.hpp" 
#include "doctest.h"


using namespace Baba_Is_Us;

TEST_CASE("Basic functions") {
    Game game("assets/levels/level_test1.txt");

    CHECK(game.getMap().At(0, 0).objectHasType(Type::Block));
    CHECK(game.getMap().At(8, 8).objectHasType(Type::Void));
    CHECK(game.getMap().At(8, 7).objectHasType(Type::Baba));
    CHECK(game.getMap().At(9, 3).objectHasType(Type::Flag));

    std::vector<Type> types {game.getMap().At(0,0).getTypes()};
    CHECK(types.size() == 3);
    CHECK(types[0] == Type::Block);
    CHECK(types[1] == Type::Baba);
    CHECK(types[2] == Type::Push);

    std::vector<Type> types {game.getMap().At(8,8).getTypes()};
    CHECK(types.size() == 1);
    CHECK(types[0] == Type::Void);

    std::vector<Type> types {game.getMap().At(8,7).getTypes()};
    CHECK(types.size() == 2);
    CHECK(types[0] == Type::Baba);
    CHECK(types[1] == Type::You);

    std::vector<Type> types {game.getMap().At(9,3).getTypes()};
    CHECK(types.size() == 2);
    CHECK(types[0] == Type::Flag);
    CHECK(types[1] == Type::Win);

    
    CHECK() objectHasType(const Type type)  // può forse diventare constexpr (solo al runtime a meno di controllare, prima di chiamare la funzione, che il tipo sia valido) 
    void addType(const Type word); // può diventare constexpr (solo al runtime)
    void removeType(Type type); // come objectHasType()
    void resetObject()
}

TEST_CASE("Game - Basic movement and transformation between map_layers")
{
    Game game("assets/levels/level_test1.txt");


    // il livello si è caricato bene, per le posizioni?
    CHECK(game.getMap().At(8, 7).objectHasType(Type::Baba));
    CHECK(game.getMap().At(9, 3).objectHasType(Type::Flag));
    CHECK(game.getRuleManager().getm_rules().size() == 5);
    bool all_rules_present {true};
    for(const Rule& rule : game.getRuleManager().getm_rules()) {
        CHECK (+rule.getm_rule()[0] > +Type::NOUN_TYPE 
            && +rule.getm_rule()[0] < +Type::ICON_NOUN_TYPE
            && +rule.getm_rule()[1] > +Type::VERB_TYPE 
            && +rule.getm_rule()[1] < +Type::PROPERTY_TYPE 
            && +rule.getm_rule()[2] > +Type::PROPERTY_TYPE 
            || (+rule.getm_rule()[2] > +Type::NOUN_TYPE 
            && +rule.getm_rule()[2] < +Type::ICON_NOUN_TYPE) 
        );
    }
    for(const Position pos : game.getPlayerPositions()) {
        CHECK(game.getMap().At(pos.first, pos.second).getTypes()[0] == Type::Baba);
        CHECK(game.getMap().getm_grid()[0][pos.second][pos.first] == +Type::Baba);
    }

    std::vector<Position> you_positions = game.getMap().getPositions(Type::You);
    CHECK(you_positions.size() == 1);
    CHECK(you_positions[0].first == 8);
    CHECK(you_positions[0].second == 7);

    //////// iniziamo il movimento:
    sf::RenderWindow window(sf::VideoMode({512, 512}), "Oui");
    game.accessMap().setTextures();
    game.accessMap().setSprites();
    sf::Clock clock;


    // gli oggetti non si spostano in alto se baba non li tocca
    game.movement(window, clock, Direction::Up);
    CHECK(game.getMap().At(8, 6).objectHasType(Type::Baba));
    CHECK(game.getMap().At(8, 7).objectHasType(Type::Void));
    CHECK(game.getMap().At(8, 4).objectHasType(Type::Lava));
    CHECK(game.getMap().At(8, 6).objectHasType(intToType(+Type::Baba)));
    CHECK(game.getMap().At(8, 7).objectHasType(intToType(+Type::Void)));
    CHECK(game.getMap().At(8, 4).objectHasType(intToType(+Type::Lava)));

    CHECK(game.getMap().getm_grid()[0][6][8] == +Type::Baba);
    CHECK(game.getMap().getm_grid()[0][7][8] == +Type::Void);
    CHECK(game.getMap().getm_grid()[0][4][8] == +Type::Lava);

    CHECK(game.getMap().getm_grid()[1][6][8] == +Type::Baba);
    CHECK(game.getMap().getm_grid()[1][7][8] == +Type::Void);
    CHECK(game.getMap().getm_grid()[1][4][8] == +Type::Lava);


    // gli oggetti non si spostano in alto se baba non li tocca
    game.movement(window, clock, Direction::Up);
    CHECK(game.getMap().At(8, 5).objectHasType(Type::Baba));
    CHECK(game.getMap().At(8, 6).objectHasType(Type::Void));
    CHECK(game.getMap().At(8, 4).objectHasType(Type::Lava));
    CHECK(game.getMap().At(8, 5).objectHasType(intToType(+Type::Baba)));
    CHECK(game.getMap().At(8, 6).objectHasType(intToType(+Type::Void)));
    CHECK(game.getMap().At(8, 4).objectHasType(intToType(+Type::Lava)));

    CHECK(game.getMap().getm_grid()[0][6][8] == +Type::Baba);
    CHECK(game.getMap().getm_grid()[0][7][8] == +Type::Void);
    CHECK(game.getMap().getm_grid()[0][4][8] == +Type::Lava);

    CHECK(game.getMap().getm_grid()[1][6][8] == +Type::Baba);
    CHECK(game.getMap().getm_grid()[1][7][8] == +Type::Void);
    CHECK(game.getMap().getm_grid()[1][4][8] == +Type::Lava);


    // gli oggetti non si spostano in basso se baba non li tocca
    game.movement(window, clock, Direction::Down);
    CHECK(game.getMap().At(8, 6).objectHasType(Type::Baba));
    CHECK(game.getMap().At(8, 5).objectHasType(Type::Void));
    CHECK(game.getMap().At(8, 4).objectHasType(Type::Lava));
    CHECK(game.getMap().At(8, 6).objectHasType(intToType(+Type::Baba)));
    CHECK(game.getMap().At(8, 5).objectHasType(intToType(+Type::Void)));
    CHECK(game.getMap().At(8, 4).objectHasType(intToType(+Type::Lava)));

    CHECK(game.getMap().getm_grid()[0][6][8] == +Type::Baba);
    CHECK(game.getMap().getm_grid()[0][7][8] == +Type::Void);
    CHECK(game.getMap().getm_grid()[0][4][8] == +Type::Lava);

    CHECK(game.getMap().getm_grid()[1][6][8] == +Type::Baba);
    CHECK(game.getMap().getm_grid()[1][7][8] == +Type::Void);
    CHECK(game.getMap().getm_grid()[1][4][8] == +Type::Lava);


    // i !!! BLOCCHI !!! non si spostano a dx se baba non li tocca
    game.movement(window, clock, Direction::Right);
    game.movement(window, clock, Direction::Right);
    game.movement(window, clock, Direction::Right);
    CHECK(game.getMap().At(11, 6).objectHasType(Type::Baba));
    CHECK(game.getMap().At(11, 6).objectHasType(Type::You));
    CHECK(game.getMap().At(2, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(2, 6).getTypes()[1] == (Type::Lava));
    CHECK(game.getMap().At(2, 6).getTypes()[2] == (Type::Push));
    CHECK(game.getMap().At(3, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(3, 6).getTypes()[1] == (Type::Is));
    CHECK(game.getMap().At(3, 6).getTypes()[2] == (Type::Push));
    CHECK(game.getMap().At(4, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(4, 6).getTypes()[1] == (Type::Hot));
    CHECK(game.getMap().At(4, 6).getTypes()[2] == (Type::Push));

    CHECK(game.getMap().getm_grid()[0][6][2] == +Type::Icon_Lava);
    CHECK(game.getMap().getm_grid()[0][6][3] == +Type::Icon_Is);
    CHECK(game.getMap().getm_grid()[0][6][4] == +Type::Icon_Hot);

    CHECK(game.getMap().getm_grid()[1][6][2] == +Type::Block);
    CHECK(game.getMap().getm_grid()[1][6][2] == +game.getMap().getm_objects()[6][2].getTypes()[0]);
    CHECK(game.getMap().getm_grid()[1][6][3] == +Type::Block);
    CHECK(game.getMap().getm_grid()[1][6][3] == +game.getMap().getm_objects()[6][3].getTypes()[0]);
    CHECK(game.getMap().getm_grid()[1][6][4] == +Type::Block);
    CHECK(game.getMap().getm_grid()[1][6][4] == +game.getMap().getm_objects()[6][4].getTypes()[0]);


    // i !!! BLOCCHI !!! non si spostano a dx se baba non li tocca
    game.movement(window, clock, Direction::Left);
    game.movement(window, clock, Direction::Left);
    CHECK(game.getMap().At(9, 6).objectHasType(Type::Baba));
    CHECK(game.getMap().At(9, 6).objectHasType(Type::You));
    CHECK(game.getMap().At(2, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(2, 6).getTypes()[1] == (Type::Lava));
    CHECK(game.getMap().At(2, 6).getTypes()[2] == (Type::Push));
    CHECK(game.getMap().At(3, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(3, 6).getTypes()[1] == (Type::Is));
    CHECK(game.getMap().At(3, 6).getTypes()[2] == (Type::Push));
    CHECK(game.getMap().At(4, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(4, 6).getTypes()[1] == (Type::Hot));
    CHECK(game.getMap().At(4, 6).getTypes()[2] == (Type::Push));

    CHECK(game.getMap().getm_grid()[0][6][2] == +Type::Icon_Lava);
    CHECK(game.getMap().getm_grid()[0][6][3] == +Type::Icon_Is);
    CHECK(game.getMap().getm_grid()[0][6][4] == +Type::Icon_Hot);

    CHECK(game.getMap().getm_grid()[1][6][2] == +Type::Block);
    CHECK(game.getMap().getm_grid()[1][6][2] == +game.getMap().getm_objects()[6][2].getTypes()[0]);
    CHECK(game.getMap().getm_grid()[1][6][3] == +Type::Block);
    CHECK(game.getMap().getm_grid()[1][6][3] == +game.getMap().getm_objects()[6][3].getTypes()[0]);
    CHECK(game.getMap().getm_grid()[1][6][4] == +Type::Block);
    CHECK(game.getMap().getm_grid()[1][6][4] == +game.getMap().getm_objects()[6][4].getTypes()[0]);
}

TEST_CASE("Game - Rules changing") {
    Game game("assets/levels/level_test1.txt");

    // il livello si è caricato bene, per le posizioni?
    CHECK(game.getMap().At(8, 7).objectHasType(Type::Baba));
    CHECK(game.getMap().At(9, 3).objectHasType(Type::Flag));

    // il livello si è caricato bene, per le regole?
    CHECK(game.getRuleManager().getm_rules().size() == 5);
    bool all_rules_present {true};
    for(const Rule& rule : game.getRuleManager().getm_rules()) {
        CHECK (+rule.getm_rule()[0] > +Type::NOUN_TYPE 
            && +rule.getm_rule()[0] < +Type::ICON_NOUN_TYPE
            && +rule.getm_rule()[1] > +Type::VERB_TYPE 
            && +rule.getm_rule()[1] < +Type::PROPERTY_TYPE 
            && +rule.getm_rule()[2] > +Type::PROPERTY_TYPE 
            || (+rule.getm_rule()[2] > +Type::NOUN_TYPE 
            && +rule.getm_rule()[2] < +Type::ICON_NOUN_TYPE) 
        );
    }

    const std::vector<Position> player_positions {game.getPlayerPositions()};
    const std::vector<Position> you_positions {game.getMap().getPositions(Type::You)};
    CHECK(player_positions.size() == you_positions.size());
    for(std::size_t iii{}; iii < player_positions.size(); ++iii) {
        CHECK(player_positions[iii].first == you_positions[iii].first 
           && player_positions[iii].second == you_positions[iii].second);
    }
    

    sf::RenderWindow window(sf::VideoMode({512, 512}), "Oui");
    game.accessMap().setTextures();
    game.accessMap().setSprites();
    sf::Clock clock;

    // gli oggetti non si spostano in alto se baba non li tocca
    game.movement(window, clock, Direction::Up);
    game.get

    // gli oggetti non si spostano in alto se baba non li tocca
    game.movement(window, clock, Direction::Up);
    CHECK(game.getMap().At(8, 5).objectHasType(Type::Baba));
    CHECK(game.getMap().At(8, 6).objectHasType(Type::Void));
    CHECK(game.getMap().At(8, 4).objectHasType(Type::Lava));

    // gli oggetti non si spostano in basso se baba non li tocca
    game.movement(window, clock, Direction::Down);
    CHECK(game.getMap().At(8, 6).objectHasType(Type::Baba));
    CHECK(game.getMap().At(8, 5).objectHasType(Type::Void));
    CHECK(game.getMap().At(8, 4).objectHasType(Type::Lava));

    // i blocchi non si spostano a dx se baba non li tocca
    game.movement(window, clock, Direction::Right);
    game.movement(window, clock, Direction::Right);
    game.movement(window, clock, Direction::Right);
    CHECK(game.getMap().At(11, 6).objectHasType(Type::Icon_Baba));
    CHECK(game.getMap().At(2, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(2, 6).getTypes()[1] == (Type::Lava));
    CHECK(game.getMap().At(2, 6).getTypes()[2] == (Type::Push));
    CHECK(game.getMap().At(3, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(3, 6).getTypes()[1] == (Type::Is));
    CHECK(game.getMap().At(3, 6).getTypes()[2] == (Type::Push));
    CHECK(game.getMap().At(4, 6).getTypes()[0] == (Type::Block));
    CHECK(game.getMap().At(4, 6).getTypes()[1] == (Type::Hot));
    CHECK(game.getMap().At(4, 6).getTypes()[2] == (Type::Push));
}
    

TEST_CASE("Game - Won")
{
    Game game(MAPS_DIR "off_limits_bug.txt");

    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::DOWN);
    CHECK(game.GetPlayState() == PlayState::WON);
}

TEST_CASE("Game - Lost")
{
    Game game(MAPS_DIR "simple_map.txt");

    CHECK(game.getMap().At(0, 2).objectHasType(Type::Icon_Baba));
    CHECK(game.getRuleManager().GetNumRules() == 1);
    CHECK(game.GetPlayState() == PlayState::PLAYING);

    game.MovePlayer(Direction::UP);
    CHECK(game.getRuleManager().GetNumRules() == 0);
    CHECK(game.GetPlayState() == PlayState::LOST);
}

TEST_CASE("Game - Sink")
{
    Game game(MAPS_DIR "out_of_reach.txt");

    CHECK(game.getMap().At(9, 3).objectHasType(Type::Icon_Baba));
    CHECK(game.getRuleManager().GetNumRules() == 5);
    CHECK(game.GetPlayerIcon() == Type::Icon_Baba);

    game.MovePlayer(Direction::UP);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::DOWN);
    game.MovePlayer(Direction::LEFT);
    game.MovePlayer(Direction::LEFT);
    game.MovePlayer(Direction::UP);
    game.MovePlayer(Direction::LEFT);
    game.MovePlayer(Direction::DOWN);
    game.MovePlayer(Direction::DOWN);
    game.MovePlayer(Direction::DOWN);

    CHECK(game.getMap().At(10, 5).objectHasType(Type::Icon_Baba));
    CHECK(game.getMap().At(10, 6).objectHasType(Type::ICON_ROCK));

    game.MovePlayer(Direction::DOWN);

    CHECK(game.getMap().At(10, 6).objectHasType(Type::Icon_Baba));
    CHECK_FALSE(game.getMap().At(10, 7).objectHasType(Type::ICON_ROCK));

    game.MovePlayer(Direction::DOWN);
    CHECK(game.GetPlayState() == PlayState::LOST);
}

TEST_CASE("Game - Defeat")
{
    Game game(MAPS_DIR "off_limits_bug.txt");

    CHECK(game.getMap().At(12, 1).objectHasType(Type::ICON_SKULL));

    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);

    CHECK(game.getMap().At(12, 1).objectHasType(Type::ICON_SKULL));
}

TEST_CASE("Map - Basic")
{
    Map map(5, 5);

    map.AddObject(4, 3, Type::BABA);
    CHECK(map.At(3, 3).objectHasType(Type::ICON_EMPTY));
    CHECK(map.At(4, 3).objectHasType(Type::BABA));
}

TEST_CASE("RuleManager - Basic")
{
    RuleManager ruleManager;

    const Rule rule1{ Object(std::vector<Type>{ Type::BABA }),
                      Object(std::vector<Type>{ Type::IS }),
                      Object(std::vector<Type>{ Type::YOU }) };
    const Rule rule2{ Object(std::vector<Type>{ Type::KEKE }),
                      Object(std::vector<Type>{ Type::IS }),
                      Object(std::vector<Type>{ Type::STOP }) };

    ruleManager.AddRule(rule1);
    CHECK(ruleManager.GetNumRules() == 1);

    ruleManager.AddRule(rule2);
    CHECK(ruleManager.GetNumRules() == 2);

    ruleManager.RemoveRule(rule2);
    CHECK(ruleManager.GetNumRules() == 1);
}

TEST_CASE("Map - Icon Vanishing")
{
    Game game(MAPS_DIR "off_limits_bug.txt");

    CHECK(game.getMap().At(14, 1).objectHasType(Type::ICON_WALL));

    game.MovePlayer(Direction::RIGHT);

    CHECK(game.getMap().At(14, 1).objectHasType(Type::ICON_WALL));
}

TEST_CASE("Map - Icon Spread")
{
    Game game(MAPS_DIR "off_limits_bug.txt");

    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::LEFT);
    game.MovePlayer(Direction::LEFT);

    CHECK(game.getMap().At(21, 3).objectHasType(Type::ICON_WALL));
    CHECK(game.getMap().At(21, 4).objectHasType(Type::ICON_WALL));
    CHECK(game.getMap().At(21, 5).objectHasType(Type::ICON_WALL));
    CHECK(game.getMap().At(22, 3).objectHasType(Type::ICON_EMPTY));
    CHECK(game.getMap().At(22, 4).objectHasType(Type::ICON_EMPTY));
    CHECK(game.getMap().At(22, 5).objectHasType(Type::ICON_FLOWER));
    CHECK(game.getMap().At(23, 3).objectHasType(Type::ICON_EMPTY));
    CHECK(game.getMap().At(23, 4).objectHasType(Type::ICON_EMPTY));
    CHECK(game.getMap().At(23, 5).objectHasType(Type::ICON_EMPTY));
}

TEST_CASE("Preprocess - Basic")
{
    Game game(MAPS_DIR "baba_is_you.txt");

    const std::vector<float> tensor = Preprocess::StateToTensor(game);
    CHECK_EQ(tensor.size(), Preprocess::TENSOR_DIM * game.getMap().GetWidth() *
                                game.getMap().GetHeight());

    const auto ToIndex = [](std::size_t x, std::size_t y, std::size_t c) {
        return (c * 11 * 9) + (y * 11) + x;
    };

    CHECK_EQ(tensor[ToIndex(0, 0, 0)], 1.0f);
    CHECK_EQ(tensor[ToIndex(1, 0, 1)], 1.0f);
    CHECK_EQ(tensor[ToIndex(2, 0, 2)], 1.0f);

    CHECK_EQ(tensor[ToIndex(0, 0, 14)], 1.0f);
    CHECK_EQ(tensor[ToIndex(1, 0, 14)], 1.0f);
    CHECK_EQ(tensor[ToIndex(2, 0, 14)], 1.0f);
    CHECK_EQ(tensor[ToIndex(3, 0, 14)], 0.0f);

    CHECK_EQ(tensor[ToIndex(0, 0, 15)], 1.0f);
    CHECK_EQ(tensor[ToIndex(1, 0, 15)], 1.0f);
    CHECK_EQ(tensor[ToIndex(2, 0, 15)], 1.0f);
    CHECK_EQ(tensor[ToIndex(3, 0, 15)], 0.0f);
}

TEST_CASE("RandomAgent - Basic")
{
    const Game game(MAPS_DIR "baba_is_you.txt");

    RandomAgent agent;

    std::vector<Direction> actions = { Direction::UP, Direction::DOWN,
                                       Direction::LEFT, Direction::RIGHT,
                                       Direction::NONE };
    const Direction action = agent.GetAction(game);

    CHECK_NE(std::find(begin(actions), end(actions), action), end(actions));
}