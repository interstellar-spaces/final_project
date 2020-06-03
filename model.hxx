#pragma once

#include <ge211.hxx>
using Pos = ge211::Position;
using Vel = ge211::Dimensions;
using Dims = ge211::Dimensions;
using Pos_vec = std::vector<Pos>;

// Model constants

static const int barrel_radius = 8;
static int const player_radius = 10;
const ge211::Dimensions player_dims();
const ge211::Dimensions ladder_dims = {30, 70};
const ge211::Dimensions platform_dims = {850, 20};

// Model classes:
struct Barrel
{
    // hit boxes defined by the top-left corner
    Pos position;
    Vel velocity;
    // whether the barrel is a special or normal barrel
    bool special;
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

struct Player
{
    Pos position;
    Vel velocity;
    Dims dimensions;
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

    // moves the player to the right
    void move_right(bool state);

    // moves the player to the left
    void move_left(bool state);

    // moves the player up
    void jump(bool state);

    // moves the player down;
    void move_down(bool state);

    // moves the y-position of the player
    void change_y(int y);

    void move_from_platform(Platform const& platform);

    // Returns the positions of the platforms
    std::vector<Platform> get_platforms() const;

    // returns the position of all the ladders
    std::vector<Ladder> get_ladder() const;

    // View the position of the barrels
    Pos_vec get_barrels() const;
// checks if the player has won
//    bool player_wins_() const;

private:
    // Private data members
    std::vector<Barrel> barrels_;
    std::vector<Platform> platforms_;
    std::vector<Ladder> ladders_;
// The center of the player
    Pos player_;
// The velocity of the barrels
    Vel velocity_;
    // dimensions of the model
    Dims dims_;
    // random number generator
    ge211::Random&  random_;


// helper functions

// determines if player is on platform
 int player_hits_ground_(Platform const& platform);

 // checks if the player is between the platforms horizontally and vertically
 bool is_within_hole(Platform const& platform) const;

 // counts the time until barrels are released
 int barrel_counter(int start, int end) const;

 // updates the barrel velocity and position
 void barrel_update() const;
// determines whether the barrel hits the given object
//    bool barrel_hits_player_() const;
//    bool barrel_hits_end_() const;

// determines whether the barrel is on the same level as the player
//    bool barrel_encounters_player_() const;

// determines whether the barrel falls to the previous platform below
//    bool barrel_falls_() const;
//
//// determines whether the special barrel hits a ladder
//    bool barrel_on_ladder_() const;

// determines whether the player is in a ladder
    bool in_ladder_(Ladder const& ladder) const;
//
//// determines whether the player falls to the previous platform below
//    bool player_falls_() const;
//
//// returns a pointer to a destroyed barrel
//    Barrel* find_destroyed_barrel_() const;
//
//// removes destroyed barrel
//    void destroy_barrel_() const;
//
//// returns player to initial state
//    void reset_player_() const;

// Test access
    friend struct Test_access;

};
