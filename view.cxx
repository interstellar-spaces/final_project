//
// Created by dnguy on 5/26/2020.
//

#include "view.hxx"
using ge211::Color;
using Dimensions = ge211::Dimensions;
using Position   = ge211::Position;
using Color      = ge211::Color;
using Sprite_set = ge211::Sprite_set;


View::View()
    : barrel_sprite_(barrel_radius, Color::medium_red())
    , platform_sprite_(platform_dims, Color::medium_blue())
    , ladder_sprite_(ladder_dims, Color::medium_yellow())
{

}
void View::draw(ge211::Sprite_set &set, const Model &model)
{
    set.add_sprite(barrel_sprite_, model.get_barrels());
    set.add_sprite(platform_sprite_, model.get_platforms());
    set.add_sprite(ladder_sprite_, );

};

Position View::board_to_screen(Position pos) const {

}

Position View::screen_to_board(ge211::Position) const {

}

Dimensions View::initial_window_dimensions() const {
    return grid_size *
}