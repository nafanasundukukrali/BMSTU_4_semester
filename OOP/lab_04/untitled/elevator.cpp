#include "elevator.h"

Elevator::Elevator(QObject *parent): QObject{parent}
{
    QObject::connect(&_cabin, SIGNAL(pass_floor_signal(bool,int)),
                     &_controller, SLOT(new_target_slot(bool,int)));

    QObject::connect(&_controller, SIGNAL(move_signal()),
                     &_cabin, SLOT(cabin_move()));

    QObject::connect(&_controller, SIGNAL(stop_signal()),
                     &_cabin, SLOT(cabin_stop()));
}

QWidget *Elevator::widget()
{
    return &this->_controller;
}
