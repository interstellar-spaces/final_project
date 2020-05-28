//
// Created by dnguy on 5/26/2020.
//

#include "controller.hxx"

void Controller::on_key_down(ge211::Key key)
{
    Abstract_game::on_key_down(key);
}

void Controller::draw(ge211::Sprite_set &set)
{
    view_.draw(set, model_);
}

void Controller::on_frame(double last_frame_seconds)
{
    Abstract_game::on_frame(last_frame_seconds);
    model_.update();
}

Controller::~Controller()
{

}
