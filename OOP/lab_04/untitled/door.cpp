#include "door.h"
#include <iostream>


Door::Door(): _current_state(CLOSED)
{
    QObject::connect(&_open_timer, SIGNAL(timeout()),
                     this, SLOT(_open()));

    QObject::connect(&_wait_timer, SIGNAL(timeout()),
                     this, SLOT(closing()));

    QObject::connect(&_close_timer, SIGNAL(timeout()),
                     this, SLOT(_close()));
}

void Door::openning()
{
    if (this->_current_state == CLOSED || this->_current_state == CLOSING)
    {
        std::cout << "Двери открываются\n";

        if (this->_current_state == CLOSED)
        {
            this->_current_state = OPENNING;
            this->_open_timer.start(DOOR_TIME);
        }
        else
        {
            this->_current_state = OPENNING;
            auto timer = this->_close_timer.remainingTime();

            _close_timer.stop();
            this->_open_timer.start(DOOR_TIME - timer);
        }
    }
}

void Door::_open()
{
    if (this->_current_state != OPENNING)
        return;

    this->_current_state = OPENED;

    std::cout << "Двери открыты\n";

    this->_wait_timer.start(DOOR_TIME);
}

void Door::closing()
{
    if (this->_current_state != OPENED)
        return;

    this->_current_state = CLOSING;

    std::cout << "Двери закрываются\n";

    this->_close_timer.start(DOOR_TIME);
}

void Door::_close()
{
    if (this->_current_state != CLOSING)
        return;

    this->_current_state = CLOSED;

    std::cout << "Двери закрыты\n";

    emit closed_door_signal();
}
