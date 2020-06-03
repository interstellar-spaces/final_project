//
// Created by dnguy on 5/26/2020.
//

#include "view.hxx"

using Dimensions = ge211::Dimensions;
using Position   = ge211::Position;
using Color      = ge211::Color;
using Sprite_set = ge211::Sprite_set;

static int const grid_size = 42;
static Color player_color = ge211::Color::medium_red();
static Color platform_color = ge211::Color::medium_green();
static Color ladder_color = ge211::Color::medium_yellow();
static Color barrel_color = ge211::Color::medium_magenta();


View::View()
    : player_sprite_(player_radius, player_color)
    , barrel_sprite_(barrel_radius, barrel_color)
    , platform_sprite_({platform_dims.width, platform_dims.height}, platform_color)
    , ladder_sprite_({ladder_dims.width, ladder_dims.height}, ladder_color)
{
}

void View::draw(ge211::Sprite_set& set, const Model& model)
{
 //   auto top_left = model.get_player() - player_radius / 2;

    for (int row = 0; row < 7; row++) {
        int y = 600 - (70 * (row + 1));
        if (row == 0) {
            set.add_sprite(platform_sprite_, {0, y}, 0);
        }
        else if (row % 2 != 0) {
            set.add_sprite(platform_sprite_, {50, y}, 0);
            set.add_sprite(ladder_sprite_, {160, y}, 1);
            set.add_sprite(ladder_sprite_, {210, y}, 1);
        }
        else if (row % 2 == 0) {
            set.add_sprite(ladder_sprite_, {650, y}, 1);
            set.add_sprite(ladder_sprite_, {700, y}, 1);
            set.add_sprite(platform_sprite_, {-100, y}, 0);
        }
    }

    for (Pos pi : model.get_barrels()) {
        set.add_sprite(barrel_sprite_, pi);
    }

    set.add_sprite(player_sprite_, model.get_player(), 2);
}

//
//Position View::board_to_screen(Position pos) const
//{
//    int x = pos.x * grid_size;
//    int y = pos.y * grid_size;
//    return {x, y};
//}
//
//Position View::screen_to_board(Position screen_pos) const
//{
//    int col = screen_pos.x / grid_size;
//    int row = screen_pos.y / grid_size;
//    return {col, row};
//}
//
//Dimensions View::initial_window_dimensions() const
//{
//    return grid_size * model_.board().dimension();
//}

std::string View::initial_window_title() const
{
    return "Donkey Kong";
}