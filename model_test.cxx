#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

TEST_CASE("Initial platforms")
{
    Model m;
    std::vector<Platform> expected {
            {{300, 100}},
            {{0, 200}},
            {{100, 300}},
            {{0, 400}},
            {{100, 500}},
            {{0, 600}},
            {{0, 700}}
    };
    CHECK(m.get_platforms() == expected);
}

struct Test_access // 4
{
    Model& model;
    std::vector<Barrel>& barrels()
    { return model.barrels_ ; }
    std::vector<Platform> platforms()
    { return model.platforms_ ; }
    Dimensions& velocity()
    { return model.velocity_ ; }
    Position& player()
    { return model.player_;}

};

TEST_CASE("Barrels fall through")
{
    Model m;
    Test_access t{m };
    Barrel test_barrel = {{0, 200}, true, false};
    t.barrels().push_back(test_barrel);
    test_barrel.move_to(500); // let {500, 200} be the location of the hole
    m.update();
    CHECK(test_barrel.barrel_falls());
}

TEST_CASE("Special barrel climbs ladder")
{
// checks if barrel climbs the ladder
    Model m;
    Test_access t{m };
    Barrel special_barrel = {{100, 500}, true, true};
    t.barrels().push_back(special_barrel);
    t.ladder_.push_back({{200, 500}, false});
    m.update();
    special_barrel.move_to(lad.x);
    CHECK(special_barrel.barrel_climbs_ladder());
    m.update();

    CHECK(m.get_barrels() == {{200, 600}, true, true});
}

TEST_CASE("Player climbs ladder")
{
    Model m;
    Test_access t{m };
    m.ladder_.clear();
    m.ladder_.push_back({{200, 700}, false});
    player.move_to(200);
    CHECK(player.player_climbs_ladder())
}

TEST_CASE("Player falls")
{
    Model m;
    player.move_to(500) // let x = 500 be the position of the hole
    CHECK(player.player_falls());

}

