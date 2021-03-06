//
// Created by dnguy on 5/26/2020.
//

#include "controller.hxx"

Controller::Controller()
    : view_(model_)
{
}
void Controller::draw(ge211::Sprite_set &set)
{
    view_.draw(set, model_);
}

void Controller::on_frame(double last_frame_seconds)
{
    int random = get_random().between(1, 300);

    model_.update(random);

    if (model_.player_lose_()) {
        quit();
    }

}

void Controller::on_key_down(ge211::Key key)
{
    if (key == ge211::Key::right())
        model_.move_right(true);
    if (key == ge211::Key::left())
        model_.move_left(true);
    if (key == ge211::Key::up())
        model_.jump();

}

void Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::right())
        model_.move_right(false);
    if (key == ge211::Key::left())
        model_.move_left(false);
}

