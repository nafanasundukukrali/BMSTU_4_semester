#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <memory>
#include <vector>
#include <utility>

#include "button.h"

class Controller : public QWidget
{
    Q_OBJECT

    enum ControllerState
    {
        BUSY,
        FREE
    };

    enum Direction
    {
        UP = 1,
        DOWN = -1,
        STOP = 0
    };

public:
    explicit Controller(QWidget *parent = nullptr);
    ~Controller() = default;

signals:
    void reach_floor_signal();
    void stop_signal();
    void move_signal();

public slots:
    void reach_floor();
    void new_target_slot(bool got_new, int floor);

private:
    int _current_floor;
    int _need_floor;
    ControllerState _current_state;
    Direction _control_direction;
    std::vector<std::shared_ptr<Button>> _buttons;
    std::vector<bool> _visited_floors;
    std::unique_ptr<QVBoxLayout> _layout;

    Direction _update_direction();
    void _update_floor();
    Controller &_create_buttons();
    bool _is_target(int &floor);
};

#endif // CONTROLLER_H
