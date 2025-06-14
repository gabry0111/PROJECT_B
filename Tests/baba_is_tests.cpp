#include "src/enum_objects.hpp" 
#include "src/objects.hpp" 
#include "src/map.hpp" 
#include "src/rules.hpp" 
#include "src/game.hpp" 
#include "doctest.h"


using namespace Baba_Is_Us;

TEST_CASE("Game - Basic")
{
    Game game("assets/levels/level1.txt");

    CHECK(game.getMap().At(1, 4).objectHasType(Type::ICON_BABA));
    CHECK(game.getMap().At(9, 4).objectHasType(Type::ICON_FLAG));
    // CHECK(game.getRuleManager().GetNumRules() == 4);
    CHECK(game.GetPlayerIcon() == Type::ICON_BABA);

    std::vector<Position> pos = game.getMap().getPositions(game.GetPlayerIcon());
    CHECK(pos.size() == 1);
    CHECK(pos[0].first == 1);
    CHECK(pos[0].second == 4);

    game.MovePlayer(Direction::UP);
    CHECK(game.getMap().At(1, 3).objectHasType(Type::ICON_BABA));
    CHECK(game.getMap().At(1, 4).objectHasType(Type::ICON_EMPTY));

    game.MovePlayer(Direction::UP);
    CHECK(game.getMap().At(1, 3).objectHasType(Type::ICON_BABA));
    CHECK(game.getMap().At(1, 2).objectHasType(Type::ICON_WALL));

    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    CHECK(game.getMap().At(4, 3).objectHasType(Type::ICON_BABA));
    CHECK(game.getMap().At(3, 3).objectHasType(Type::ICON_TILE));

    game.MovePlayer(Direction::RIGHT);
    CHECK(game.getMap().At(5, 3).objectHasType(Type::ICON_BABA));
    CHECK(game.getMap().At(6, 3).objectHasType(Type::ICON_ROCK));
    CHECK(game.getMap().At(4, 3).objectHasType(Type::ICON_TILE));

    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::DOWN);
    CHECK(game.GetPlayState() == PlayState::PLAYING);

    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    game.MovePlayer(Direction::RIGHT);
    CHECK(game.GetPlayState() == PlayState::WON);

    game.Reset();
    CHECK(game.getMap().At(1, 4).objectHasType(Type::ICON_BABA));
    CHECK(game.getMap().At(9, 4).objectHasType(Type::ICON_FLAG));
    CHECK(game.getRuleManager().GetNumRules() == 4);
    CHECK(game.GetPlayerIcon() == Type::ICON_BABA);
    CHECK(game.GetPlayState() == PlayState::PLAYING);
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

    CHECK(game.getMap().At(0, 2).objectHasType(Type::ICON_BABA));
    CHECK(game.getRuleManager().GetNumRules() == 1);
    CHECK(game.GetPlayState() == PlayState::PLAYING);

    game.MovePlayer(Direction::UP);
    CHECK(game.getRuleManager().GetNumRules() == 0);
    CHECK(game.GetPlayState() == PlayState::LOST);
}

TEST_CASE("Game - Sink")
{
    Game game(MAPS_DIR "out_of_reach.txt");

    CHECK(game.getMap().At(9, 3).objectHasType(Type::ICON_BABA));
    CHECK(game.getRuleManager().GetNumRules() == 5);
    CHECK(game.GetPlayerIcon() == Type::ICON_BABA);

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

    CHECK(game.getMap().At(10, 5).objectHasType(Type::ICON_BABA));
    CHECK(game.getMap().At(10, 6).objectHasType(Type::ICON_ROCK));

    game.MovePlayer(Direction::DOWN);

    CHECK(game.getMap().At(10, 6).objectHasType(Type::ICON_BABA));
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