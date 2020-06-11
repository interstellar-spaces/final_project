#include "model.hxx"


Model::Model(Pos pos0, Dims dims, ge211::Random& random)
        : player_(player0)
        , dims_(dims)
        , velocity_(velocity0)
        , random_(random)
{
    for (int row = 0; row < 7; row++) {
        int y = platform_init_x - (platform_spacing * (row + 1));
        if (row == 0) {
            Pos p0{0, y};
            platforms_.push_back(Platform{p0});
        }
        else if (row % 2 != 0) {
            Pos p0{50, y};
            platforms_.push_back(Platform{p0});
            ladders_.push_back(Ladder{{left_ladder_first, y}});
            ladders_.push_back(Ladder{{left_ladder_second, y}});
        }
        else if (row % 2 == 0) {
            Pos p0{-100, y};
            platforms_.push_back(Platform{p0});
            ladders_.push_back(Ladder{{right_ladder_first, y}});
            ladders_.push_back(Ladder{{right_ladder_second, y}});
        }
    }
    platforms_.push_back(Platform{winning_platform_pos});
    ladders_.push_back(Ladder{winning_ladder_pos});
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
    if (player_wins()){
        velocity_ = {0,0};
    }
    player_.x += velocity_.width;
    player_.y += velocity_.height;

    // doesn't allow player to pass the limit of the screen
    if (player_.x < 0) {
        change_x(0);
        velocity_.width = 0;
    }
    if ((player_.x + 2*player_radius) > dims_.width) {
        change_x(dims_.width - 2*player_radius);
        velocity_.width = 0;
    }

    // keeps player on the ground
    velocity_.height = gravity_ + player_momentum_;

    // concludes jump
    if (!onladder_) {
        if (current_platform() == 1) {
            if (player_.y < get_platforms()[1].position.y + platform_dims
                    .height) {
                player_momentum_ = 0;
            }
        }
        if (current_platform() == 2) {
            if (player_.y < get_platforms()[2].position.y + platform_dims
                    .height) {
                player_momentum_ = 0;
            }
        }
        if (current_platform() == 3) {
            if (player_.y < get_platforms()[3].position.y + platform_dims
                    .height) {
                player_momentum_ = 0;
            }
        }
        if (current_platform() == 4) {
            if (player_.y < get_platforms()[4].position.y + platform_dims
                    .height) {
                player_momentum_ = 0;
            }
        }
        if (current_platform() == 5) {
            if (player_.y < get_platforms()[5].position.y + platform_dims
                    .height) {
                player_momentum_ = 0;
            }
        }
        if (current_platform() == 6) {
            if (player_.y < get_platforms()[6].position.y + platform_dims
                    .height) {
                player_momentum_ = 0;
            }
        }
        if (current_platform() == 7) {
            if (player_.y < get_platforms()[7].position.y + platform_dims
                    .height) {
                player_momentum_ = 0;
            }
        }
        if (current_platform() == 8) {
            if (player_.y < 0) {
                player_momentum_ = 0;
            }
        }
    }

    //checks to see if player is in any ladder
    for (Ladder lad : ladders_) {
        if (in_ladder_(lad)) {
            current_lad_ = lad;
        }
    }

    onladder_ = in_ladder_(current_lad_);

    for (Platform plat : platforms_) {
        if (player_hits_ground_(plat) != 5) { // hits doesn't go through
            move_from_platform(plat); // checks if it's 3 or 4
        }
    }

    if (dt % 299 == 0) {
        barrels_.push_back({barrel_p0, barrel_v0});
    }

    barrel_update();

}

bool Model::player_lose_() const
{
    return lives == 0;
}

bool Model::player_wins() const
{
    return (player_.y < winning_platform_pos.y + player_radius) &&
           (player_.x > winning_platform_pos.x &&
            player_.x < winning_platform_pos.x + winning_platform_dims.width);
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
    if (state) {
        velocity_.width = -4;
    } else {
        velocity_.width = 0;
    }
}

void Model::jump()
{
    if (!onair_)
        player_momentum_ = -6;
    onair_ = true;
}

void Model::change_y(int y)
{
    player_.y = y;
}

void Model::change_x(int x)
{
    player_.x = x;
}

void Model::move_barrel_x(Barrel& bar, int x)
{
    bar.position.x = x;
}

void Model::move_barrel_y(Barrel& bar, int y)
{
    bar.position.y = y;
}

void Model::move_from_platform(Platform const platform)
{
    if (player_hits_ground_(platform) == 3 && !onladder_) {
        change_y(platform.position.y + platform_dims.height);
        velocity_.height = 0;
    }

    if (player_hits_ground_(platform) == 4 && !onladder_) {
        change_y(platform.position.y - 2*player_radius);
        velocity_.height = 0;
        onair_ = false;
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
    int left = player_.x + 1;
    int right = player_.x + 2*player_radius - 1;
    int bottom = player_.y + 2*player_radius;
    int center = player_.y + player_radius;

    bool side = right < ladder.position.x + ladder_dims.width && left > ladder
            .position.x;

    bool tops = (center > ladder.position.y && bottom <= ladder.position.y +
                                                         ladder_dims.height);
    return (side && tops);
}

void Model::barrel_update() {
    for (int i = 0; i < barrels_.size(); i++) {
        if (player_wins()) {
            barrels_[i].velocity = {0,0};
        }
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
            reset_player_();
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

void Model::reset_player_()
{
    player_ = player0;
    lives--;
}

int Model::current_platform() const {
    if( (player_.y < get_platforms()[0].position.y) && (player_.y >
                                                        get_platforms()[1].position.y - player_radius + platform_dims.height) ) {
        return 1;
    } else if ((player_.y < get_platforms()[1].position.y) && (player_.y >
                                                               get_platforms()[2].position.y - player_radius + platform_dims.height)) {
        return 2;
    } else if ((player_.y < get_platforms()[2].position.y) && (player_.y >
                                                               get_platforms()[3].position.y - player_radius + platform_dims.height)){
        return 3;
    } else if ( (player_.y < get_platforms()[3].position.y) && (player_.y >
                                                                get_platforms()[4].position.y - player_radius + platform_dims.height) ){
        return 4;
    } else if ( (player_.y < get_platforms()[4].position.y) && (player_.y >
                                                                get_platforms()[5].position.y - player_radius + platform_dims.height) ){
        return 5;
    } else if ( (player_.y < get_platforms()[5].position.y) && (player_.y >
                                                                get_platforms()[6].position.y - player_radius + platform_dims.height) ){
        return 6;
    } else if ( (player_.y < get_platforms()[6].position.y) && (player_.y >
                                                                get_platforms()[7].position.y - player_radius + platform_dims.height) ){
        return 7;
    } else {
        return 0;
    }
}
