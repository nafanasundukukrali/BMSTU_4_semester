#include "button.h"
#include <iostream>

Button::Button(QWidget *parent) : QPushButton(parent)
{
    QObject::connect(this, SIGNAL(clicked()),
                     this, SLOT(press()));
    QObject::connect(this, SIGNAL(unpress_signal()),
                     this, SLOT(unpress()));

    this->setStyleSheet("background-color:white;");
    this->_current_state = NOTACTIVE;
    this->_current_floor = 1;
}

void Button::set_floor(const int &floor)
{
    this->_current_floor = floor;
}

void Button::press()
{
    if (this->_current_state != NOTACTIVE)
        return;

    this->setStyleSheet("background-color:gray;");
    this->update();
    this->_current_state = ACTIVE;
    this->setDisabled(true);

    emit this->press_signal(true, this->_current_floor);
}

void Button::unpress()
{
    if (this->_current_state != ACTIVE)
        return;

    this->setStyleSheet("background-color:white;");
    this->update();
    this->_current_state = NOTACTIVE;
    this->setDisabled(false);
}
