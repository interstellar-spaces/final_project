#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

TEST_CASE("Initial platforms")
{
    Model m;
    std::vector<Platform> expected;
    expected.push_back({winning_platform_pos});
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
    std::vector<Ladder>& ladders()
    { return model.ladders_ ; }
    std::vector<Platform> platforms()
    { return model.platforms_ ; }
    Dimensions& velocity()
    { return model.velocity_ ; }
    Position& player()
    { return model.player_;}
    bool in_ladder(Ladder const ladder)
    { return model.in_ladder_(ladder); }

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
    m.update(99);
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
    m.move_barrel_x(t.barrels()[0], 750+ 2*barrel_radius);
    m.update(1);
    int check = m.barrel_in_hole_(t.barrels()[0], t.platforms()[7]);
    CHECK(check == 6);
}

TEST_CASE("Player in ladder")
{
    Model m;
    Test_access t{m };
    t.ladders().clear();
    t.ladders().push_back({{200, 700}});
    m.change_x(202);
    bool check;
    check = t.in_ladder(t.ladders()[0]);
    CHECK(check);
}

