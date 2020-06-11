#pragma once

#include <ge211.hxx>
using Pos = ge211::Position;
using Vel = ge211::Dimensions;
using Dims = ge211::Dimensions;
using Pos_vec = std::vector<Pos>;

// Model constants

static const int barrel_radius = 8;
static const Pos barrel_p0 = {10, 93};
static const Dims barrel_v0 = {2, 0};
static int const player_radius = 10;
static int const platform_spacing = 70;
static int lives = 3; // can change this to change the amount of lives
int const gravity_ = 3;
const Dims ladder_dims = {30, 70};
const Dims platform_dims = {850, 20};
const Dims winning_platform_dims = {150, 20};
const Pos winning_platform_pos = {300, 40};
const Pos winning_ladder_pos = {360, 40};
static int const platform_init_x = 600;
static int const left_ladder_first = 160;
static int const left_ladder_second = 210;
static int const right_ladder_first = 650;
static int const right_ladder_second = 700;


// Model classes:
struct Barrel
{
    // hit boxes defined by the top-left corner
    Pos position;
    Vel velocity;
};

struct Ladder
{
    //position of the ladders
    Pos position;
};

struct Platform
{
    // position of the platforms
    Pos position;
};

class Model
{
public:
    Model();
    Model(Pos player0, Dims dims, ge211::Random& random);

    // updates the model with time
    void update(int dt);

    // returns the position of the player
    Pos get_player() const;

    // returns the dimensions of the model
    Dims dims() const;

    // states whether or not the player wins
    bool player_wins() const;

    // checks if the player has run out of lives
    bool player_lose_() const;

    // moves the player to the right
    void move_right(bool state);

    // moves the player to the left
    void move_left(bool state);

    // moves the player up
    void jump();

    // moves the y-position of the player
    void change_y(int y);

    // moves the x-position of the player
    void change_x(int x);

    // moves the barrels to the given x
    void move_barrel_x(Barrel& barrel, int x);

    // moves the barrels to the given y
    void move_barrel_y(Barrel& barrel, int y);

    //current platform player is in
    int current_platform() const;

    // Returns the positions of the platforms
    std::vector<Platform> get_platforms() const;

    // returns the position of all the ladders
    std::vector<Ladder> get_ladder() const;

    // View the position of the barrels
    Pos_vec get_barrels() const;

    // determines whether the barrel falls through a left hole or right hole
    int barrel_in_hole_(Barrel& barrel, Platform const platform);

    // returns player to initial state
    void reset_player_();


private:
    // Private data members
    std::vector<Barrel> barrels_;
    std::vector<Platform> platforms_;
    std::vector<Ladder> ladders_;
// The center of the player
    Pos player_;
// The velocity of the player
    Vel velocity_;
    // dimensions of the model
    Dims dims_;
    // random number generator
    ge211::Random&  random_;
    // whether the player is jumping or not
    bool onair_;
    // stores ladder player is currently on
    Ladder current_lad_ = {{0,0}};

    // player momentum_
    int player_momentum_;

// helper functions

// whether the player is still on the last ladder it was on
    bool onladder_;
// determines if player is on platform
    int player_hits_ground_(Platform const platform);

    // checks if the player is between the platforms horizontally and vertically
    bool is_within_hole(Platform const platform) const;

    // updates the barrel velocity and position
    void barrel_update();

    // determines whether the player is in a ladder
    bool in_ladder_(Ladder const ladder) const;

    // moves the player based on whether it has hit a platform
    void move_from_platform(Platform const platform);

    // determines whether the barrel hits a platform
    void barrel_hits_platform(Barrel& barrel, Platform const& platform);

// determines whether the barrel hits the player
    bool barrel_hits_player_(Barrel barrel) const;

// Test access
    friend struct Test_access;

};
