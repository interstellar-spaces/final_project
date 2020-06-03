#pragma once
#include <ge211.hxx>
#include "model.hxx"
#include <string>
using ge211::Color;


class View
{

public:
    View();
    void draw(ge211::Sprite_set& set, Model const& model);
//    ge211::Position board_to_screen(ge211::Position) const;
//    ge211::Position screen_to_board(ge211::Position) const;
//    ge211::Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;


private:
 //   Model const& model_;

    // sprites go here
    ge211::Circle_sprite const barrel_sprite_;
    ge211::Rectangle_sprite const platform_sprite_;
    ge211::Rectangle_sprite const ladder_sprite_;
    ge211::Circle_sprite const player_sprite_;
//   ge211::Image_sprite const player_sprite_;
//    ge211::Image_sprite player_sprite_{"mario.png"};



};


