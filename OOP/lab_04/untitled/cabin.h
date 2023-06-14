#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include "door.h"

class Cabin: public QObject
{
    Q_OBJECT

    enum CabinState
    {
        WAIT,
        FREE,
        MOVE
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() = default;

signals:
    void door_open_signal();
    void pass_floor_signal(bool, int = 1);

public slots:
    void cabin_move();
    void cabin_stop();

private slots:
    void _cabin_passed_target_floor();

private:

    Door _door;
    CabinState _current_state;
    QTimer _cabin_move_timer;

};

#endif // CABIN_H
