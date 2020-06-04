#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

TEST_CASE("Initial platforms")
{
    Model m;
    std::vector<Platform> expected;
    expected.push_back({{0, 530}});
    expected.push_back({{50, 460}});
    expected.push_back({{-100, 390}});
    expected.push_back({{50, 320}});
    expected.push_back({{-100, 250}});
    expected.push_back({{50, 180}});
    expected.push_back({{-100, 110}});

    std::vector<Platform> actual = m.get_platforms();

    CHECK(expected.size() == actual.size());

    for (int i = 0; i < 7; i++) {
        CHECK(actual[i].position == expected[i].position);
    }
}

struct Test_access
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


TEST_CASE("Make 2 Barrels")
{
    Model       m;
    Test_access t{m};
    Pos         p0          = {10, 94};
    Barrel      test_barrel = {p0, {5, 0}};
    t.barrels().push_back(test_barrel);
    m.update(1);
    CHECK(m.get_barrels().size() == 1);
    m.update(43);
    CHECK(m.get_barrels().size() == 2);
}

TEST_CASE("Barrel falls")
{
    Model       m;
    Test_access t{m};
    Pos         p0          = {10, 94};
    Barrel      test_barrel = {p0, {5, 3}};
    t.barrels().push_back(test_barrel);
    m.update(1);
    m.move_barrel_x(t.barrels()[0], 750);
    m.update(1);
    CHECK(m.barrel_in_hole_(t.barrels()[0], t.platforms()[7]) == 6);
}
//TEST_CASE("Special barrel climbs ladder")
//{
// checks if barrel climbs the ladder
//    Model m;
//    Test_access t{m };
//    Barrel special_barrel = {{100, 500}, true, true};
//    t.barrels().push_back(special_barrel);
//    t.ladder_.push_back({{200, 500}, false});
//    m.update();
//    special_barrel.move_to(lad.x);
//    CHECK(special_barrel.barrel_climbs_ladder());
//    m.update();
//
//    CHECK(m.get_barrels() == {{200, 600}, true, true});
//}

//TEST_CASE("Player climbs ladder")
//{
//    Model m;
//    Test_access t{m };
//    m.ladder_.clear();
//    m.ladder_.push_back({{200, 700}, false});
//    player.move_to(200);
//    CHECK(player.player_climbs_ladder())
//}
//
//TEST_CASE("Player falls")
//{
//    Model m;
//    player.move_to(500) // let x = 500 be the position of the hole
//    CHECK(player.player_falls());
//
//}

