#pragma once
#include <ge211.hxx>
#include "model.hxx"

class View
{
    View();

public:
    void draw(ge211::Sprite_set& set, Model const& model);
    ge211::Position board_to_screen(ge211::Position) const;
    ge211::Position screen_to_board(ge211::Position) const;
    ge211::Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;

private:
    // sprites go here
    ge211::Circle_sprite const barrel_sprite_;
    ge211::Rectangle_sprite const platform_sprite_;
    ge211::Rectangle_sprite const ladder_sprite_;


};


