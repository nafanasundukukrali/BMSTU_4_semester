#include "cabin.h"
#include "defines.h"
#include <iostream>

Cabin::Cabin(QObject *parent): QObject{parent}
{
    this->_current_state = FREE;

    QObject::connect(this, SIGNAL(door_open_signal()),
                     &_door, SLOT(openning()));

    QObject::connect(&this->_cabin_move_timer, SIGNAL(timeout()),
                     this, SLOT(_cabin_passed_target_floor()));

    QObject::connect(&_door, SIGNAL(closed_door_signal()),
                     this, SLOT(_cabin_passed_target_floor()));
}

void Cabin::cabin_move()
{
    if (this->_current_state != FREE)
        return;

    this->_current_state = MOVE;
    this->_cabin_move_timer.start(CHANGE_ONE_FLOOR_TIME);
}

void Cabin::cabin_stop()
{
    this->_current_state = WAIT;
    this->_cabin_move_timer.stop();

    emit this->door_open_signal();
}

void Cabin::_cabin_passed_target_floor()
{
    if (this->_current_state != FREE)
    {
        this->_current_state = FREE;

        emit this->pass_floor_signal(false);
    }
}
