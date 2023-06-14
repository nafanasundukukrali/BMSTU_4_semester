#include "controller.h"
#include <QObject>
#include "defines.h"
#include <iostream>

Controller::Controller(QWidget *parent): QWidget(parent)
{
    this->_layout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->setLayout(this->_layout.get());
    this->_control_direction = UP;
    this->_current_floor = 1;
    this->_create_buttons();
    QObject::connect(this, SIGNAL(reach_floor_signal()), this, SLOT(reach_floor()));
}

Controller &Controller::_create_buttons()
{
    for (int i = FLOORS_COUNT; i > 0; i--)
    {
        std::shared_ptr<Button> buffer_button(new Button);
        buffer_button->set_floor(i);
        buffer_button->setText(QString::number(i));
        this->_layout->addWidget(dynamic_cast<QPushButton*>(buffer_button.get()));
        this->_buttons.insert(this->_buttons.begin(), buffer_button);
        this->_visited_floors.push_back(true);
        auto real_button = buffer_button.get();
        QObject::connect(real_button, SIGNAL(press_signal(bool,int)),
                         this, SLOT(new_target_slot(bool,int)));
    }

    return *this;
}

Controller::Direction Controller::_update_direction()
{
    Direction dir;

    if (this->_need_floor < this->_current_floor)
        dir = UP;
    else if (this->_need_floor > this->_current_floor)
        dir = DOWN;
    else
        dir = STOP;

    return dir;
}


void Controller::_update_floor()
{
    this->_current_floor += this->_control_direction;
    Direction dir = this->_update_direction();

    if (dir != STOP)
        std::cout << "Лифт в пути, сейчас на этаже № " << this->_current_floor << "\n";
}

void Controller::new_target_slot(bool got_new, int floor)
{
    this->_current_state = BUSY;
    Direction dir;

    if (got_new)
    {
        this->_visited_floors[floor - 1] = false;
        this->_is_target(this->_need_floor);
        dir = this->_update_direction();

        if (dir == STOP)
            emit this->reach_floor_signal();
        else
            emit this->move_signal();
    }
    else if (this->_is_target(this->_need_floor))
    {
        dir = this->_update_direction();

        if (dir != STOP)
        {
            emit this->move_signal();
            this->_update_floor();
        }
        else
        {
            emit this->reach_floor_signal();
        }
    }
}

bool Controller::_is_target(int &new_floor_target)
{
    int dir = DOWN;

    if (this->_control_direction != STOP)
        dir = _control_direction;

    for (int i = this->_current_floor - 1; i >= 0 && i < FLOORS_COUNT; i += dir)
        if (!this->_visited_floors[i])
        {
            this->_control_direction = ((dir == UP) ? UP : DOWN);
            new_floor_target = i + 1;
            return true;
        }

    for (int i = this->_current_floor - 1; i >= 0 && i < FLOORS_COUNT; i -= dir)
        if (!this->_visited_floors[i])
        {
            this->_control_direction = ((dir == UP) ? DOWN : UP);
            new_floor_target = i + 1;
            return true;
        }

    this->_control_direction = STOP;

    return false;
}

void Controller::reach_floor()
{
    if (this->_current_state != BUSY) return;

    this->_current_state = FREE;

    std::cout << "Лифт приехал на этаж № " << this->_current_floor << "\n";

    this->_visited_floors[this->_need_floor - 1] = true;
    emit this->_buttons[this->_current_floor - 1]->unpress_signal();
    this->_is_target(this->_need_floor);

    emit stop_signal();
}
