#pragma once

#include <ge211.hxx>
using Pos = ge211::Position;
using Vel = ge211::Dimensions;

// Model constants


const int barrel_radius;
const ge211::Dimensions player_dims;
const ge211::Dimensions platform_dims;
const ge211::Dimensions ladder_dims;
const ge211::Dimensions hole_dims;

// Model classes:
// Barrel
struct Barrel
{
    // hit boxes defined by the top-left corner
    Pos position;
    Vel velocity;

    // whether the barrel still exists
    bool live;
    // whether the barrel is a special or normal barrel
    bool special;
};

struct Ladder
{
    //position of the ladders
    Pos position;
    // whether the ladder is activated
    bool within;
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
};

class Model
{
// Private data members
private:

    std::vector<Barrel> barrels_;
    std::vector<Platform> platforms_;

// The center of the player
    Pos player_;

// The velocity of the barrels
    Vel velocity_;

// public functions
public:
    Model();
    // View the states of all the barrels
    std::vector<Pos> get_barrels() const;
// updates the model state for one time step
    void update();
// Returns the player’s position
    Pos get_player() const;

    // Returns the positions of the platforms
    std::vector<Platform> const& get_platforms() const;
// moves the object to the given x
    void move_to(int x);
// checks if the player has won
    bool player_wins_() const;
private:
// helper functions

// determines whether the barrel hits the given object
    bool barrel_hits_player_() const;
    bool barrel_hits_side_() const;

// determines whether the barrel is on the same level as the player
    bool barrel_encounters_player_() const;

// determines whether the barrel falls to the previous platform below
    bool barrel_falls_() const;

// determines whether the special barrel hits a ladder
    bool barrel_climbs_ladder_() const;

// determines whether the player hits a ladder
    bool player_climbs_ladder_() const;

// determines whether the player falls to the previous platform below
    bool player_falls_() const;

// returns a pointer to a destroyed barrel
    Barrel* find_destroyed_barrel_() const;

// removes destroyed barrel
    void destroy_barrel_() const;

// returns player to initial state
    void reset_player_() const;

// Test access
    friend struct Test_access;

};
