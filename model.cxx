#include "model.hxx"

const Pos player0 {780, 510};
const Vel velocity0 {0, 0};

Model::Model()
    : Model(player0, ge211::Abstract_game::default_window_dimensions, random_)
{}

Model::Model(Pos pos0, Dims dims, ge211::Random& random)
    : player_(player0)
    , dims_(dims)
    , velocity_(velocity0)
    , random_(random)
{
    for (int row = 0; row < 7; row++) {
        int y = 600 - (platform_spacing * (row + 1));
        if (row == 0) {
            Pos p0{0, y};
            platforms_.push_back(Platform{p0});
        }
        else if (row % 2 != 0) {
            Pos p0{50, y};
            platforms_.push_back(Platform{p0});
            ladders_.push_back(Ladder{{160, y}});
            ladders_.push_back(Ladder{{210, y}});
        }
        else if (row % 2 == 0) {
            Pos p0{-100, y};
            platforms_.push_back(Platform{p0});
            ladders_.push_back(Ladder{{650, y}});
            ladders_.push_back(Ladder{{700, y}});
        }
    }
}

ge211::Position Model::get_player() const
{
    return player_;
}

std::vector<Platform> Model::get_platforms() const
{
    return platforms_;
}

std::vector<Ladder> Model::get_ladder() const
{
    return ladders_;
}

Pos_vec Model::get_barrels() const
{
    Pos_vec positions;
    for (int i = 0; i < barrels_.size(); i++) {
        positions.push_back(barrels_[i].position);
    }
    return positions;
}

void Model::update(int dt)
{
     // increments the player's position
    player_ += velocity_;

    for (Platform plat : platforms_) {
        if (player_hits_ground_(plat) != 5) { // hits doesn't go through
            for (Ladder lad : ladders_) {
                if (in_ladder_(lad))
                    break;
                else {
                    move_from_platform(plat); // checks if it's 3 or 4
                }
            }
        }
    }

    if (dt % 99 == 0) {
        Pos p0 = {10, 90};
        Vel v0 = {2, 0};
        barrels_.push_back({p0, v0});
    }
    barrel_update();

}

Dims Model::dims() const
{
    return dims_;
}

void Model::move_right(bool state)
{
    if (state)
        velocity_.width = 4;
    else velocity_.width = 0;

}

void Model::move_left(bool state)
{
    if (state)
        velocity_.width = -4;
    else velocity_.width = 0;
}

void Model::jump(bool state)
{
    if (state)
        velocity_.height = -4;
    else {
        velocity_.height = 4;
    }
}

void Model::move_down(bool state)
{
    if (state)
        velocity_.height = 4;
    else velocity_.height = 0;
}

void Model::change_y(int y)
{
    player_.y = y;
}

Barrel Model::move_barrel_x(Barrel& bar, int x)
{
    bar.position.x = x;
    return bar;
}

void Model::move_barrel_y(Barrel& bar, int y)
{
    bar.position.y = y;
}

void Model::move_from_platform(Platform const platform)
{
    if (player_hits_ground_(platform) == 3) {
        change_y(platform.position.y + platform_dims.height);
        velocity_.height = 0;
    }

    if (player_hits_ground_(platform) == 4) {
        change_y(platform.position.y - 2*player_radius);
        velocity_.height = 0;
    }
}
int Model::player_hits_ground_(Platform const platform)
{
    int bottom = player_.y + 2*player_radius;
    int top = player_.y;

    if (top < platform.position.y + platform_dims.height && top > platform
    .position.y) {
        if (is_within_hole(platform))
            return 5; // not on the platform
        return 3; // within the top platform
    }

    if (bottom < platform.position.y + platform_dims.height && bottom >
    platform.position.y) {
        if (is_within_hole(platform))
            return 5; // not on the platform
        return 4; // within the bottom platform
    }
    return 5;
}
bool Model::is_within_hole(Platform const platform) const
{
    int left = player_.x;
    int right = player_.x + 2*player_radius;

    // checks in player is in a hole
    bool hole = (right < platform.position.x  && left < platform.position.x
            || left > platform.position.x + platform_dims.width && right > platform.position.x + platform_dims.width);

    return hole;
}

bool Model::in_ladder_(Ladder const ladder) const
{
    int left = player_.x;
    int right = player_.x + 2*player_radius;
    int bottom = player_.y + 2*player_radius;
    int top = player_.y;

    bool side = right < ladder.position.x + ladder_dims.width && left > ladder
            .position.x;

    bool tops = (top > ladder.position.y && bottom <= ladder.position.y +
            ladder_dims.height);
    return (side && tops);
}

void Model::barrel_update()
{
    for (int i = 0; i < barrels_.size(); i++) {
        barrels_[i].position.x += barrels_[i].velocity.width;
        barrels_[i].position.y += barrels_[i].velocity.height;

        if (barrels_[i].position.x > player0.x && barrels_[i].position.y >
        player0.y) {
            std::swap(barrels_[i], barrels_.back());
            barrels_.pop_back();
        }
        for (Platform platform : platforms_) {
            barrel_hits_platform(barrels_[i], platform);
        }
        if (barrel_hits_player_(barrels_[i]))


    }
}

int Model::barrel_in_hole_(Barrel& barrel, Platform const platform)
{
    int left = barrel.position.x;
    int right = barrel.position.x + 2*barrel_radius;
    int bottom = barrel.position.y + 2 * barrel_radius;
    int top = barrel.position.y;

    int top_right = platform.position.x + platform_dims.width + 2*barrel_radius;
    int top_left = platform.position.x - 2*barrel_radius;
    bool left_hole  = (right < top_left || left < top_left)
            && (bottom < platform.position.y && top > platform.position.y - platform_spacing);
    bool right_hole = (left > top_right && right > top_right)
                && (bottom < platform.position.y && top > platform.position.y
                - platform_spacing);
    if (left_hole)
        return 5;
    if (right_hole) {
        barrel.velocity.height = 3;
        return 6;
    }
    return 7;
}

void Model::barrel_hits_platform(Barrel& barrel, Platform const& platform)
{
    int bottom = barrel.position.y + 2 * barrel_radius;

    if (bottom < platform.position.y + platform_dims.height || bottom >
            platform.position.y) {
        if (barrel_in_hole_(barrel, platform) == 5) {
            move_barrel_y(barrel, platform.position.y - platform_dims.height +
            platform_spacing);
            barrel.velocity.width = 3;
        }
        else if (barrel_in_hole_(barrel, platform) == 6) {
            move_barrel_y(barrel, platform.position.y - platform_dims.height +
                                  platform_spacing);
            barrel.velocity.width = -3;
        }
        else
            barrel.velocity.height = 0;
    }
}

bool Model::barrel_hits_player_(Barrel barrel) const
{
    int b_left   = barrel.position.x;
    int b_right  = barrel.position.x + 2 * barrel_radius;
    int b_bottom = barrel.position.y + 2 * barrel_radius;
    int b_top    = barrel.position.y;

    int p_left   = player_.x;
    int p_right  = player_.x + 2 * player_radius;
    int p_bottom = player_.y + 2 * player_radius;
    int p_top    = player_.y;

    bool cond = (b_right < p_left || b_left > p_right) ||
            (b_bottom < p_top || b_top > p_bottom);

    return !cond;

}
