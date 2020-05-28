#include "model.hxx"

const ge211::Position player0 {0, -200};
const ge211::Dimensions velocity0 {5, 0};
using pos = ge211::Position;

Model::Model()
    : player_(player0)
    , velocity_(velocity0)
    // initialize the private data members
{
// make the ladders and the platforms here


}

ge211::Position Model::get_player() const
{
    return player_;
}

void Model::update()
{
    player_ += velocity_; // increments the player's position

}

