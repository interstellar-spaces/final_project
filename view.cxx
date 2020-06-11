//
// Created by dnguy on 5/26/2020.
//

#include "view.hxx"

using Dimensions = ge211::Dimensions;
using Position   = ge211::Position;
using Color      = ge211::Color;
using Sprite_set = ge211::Sprite_set;

static Color player_color = ge211::Color::medium_red();
static Color platform_color = ge211::Color::medium_green();
static Color ladder_color = ge211::Color::medium_yellow();
static Color barrel_color = ge211::Color::medium_magenta();

View::View(Model& model)
        : model_(model)
        , player_sprite_(player_radius, player_color)
        , barrel_sprite_(barrel_radius, barrel_color)
        , platform_sprite_({platform_dims.width, platform_dims.height}, platform_color)
        , ladder_sprite_({ladder_dims.width, ladder_dims.height}, ladder_color)
        , winning_platform_sprite({winning_platform_dims.width,
                                   winning_platform_dims.height}, platform_color)
{}

void View::draw(ge211::Sprite_set& set, const Model& model)
{
    set.add_sprite(winning_platform_sprite, winning_platform_pos, 0);
    set.add_sprite(ladder_sprite_, winning_ladder_pos, 1);
    set.add_sprite(player_sprite_, model.get_player(), 4);

    for (int row = 0; row < 7; row++) {
        int y = platform_init_x - (platform_spacing * (row + 1));
        if (row == 0) {
            set.add_sprite(platform_sprite_, {0, y}, 0);
        }
        else if (row % 2 != 0) {
            set.add_sprite(platform_sprite_, {50, y}, 0);
            set.add_sprite(ladder_sprite_, {left_ladder_first, y}, 1);
            set.add_sprite(ladder_sprite_, {left_ladder_second, y}, 1);
        }
        else if (row % 2 == 0) {
            set.add_sprite(ladder_sprite_, {right_ladder_first, y}, 1);
            set.add_sprite(ladder_sprite_, {right_ladder_second, y}, 1);
            set.add_sprite(platform_sprite_, {-100, y}, 0);
        }
    }

    for (Pos pi : model.get_barrels()) {
        set.add_sprite(barrel_sprite_, pi, 2);
    }
}


std::string View::initial_window_title() const
{
    return "Donkey Kong";
}