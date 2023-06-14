#ifndef DOOR_H
#define DOOR_H

#include <QTimer>
#include "defines.h"

class Door : public QObject
{
    Q_OBJECT
    enum DoorState
    {
        OPENED,
        OPENNING,
        CLOSING,
        CLOSED
    };

public:
    Door();
    ~Door() = default;

signals:
    void closed_door_signal();

public slots:
    void openning();
    void closing();


private slots:
    void _open();
    void _close();

private:
    DoorState _current_state;

    QTimer _open_timer;
    QTimer _close_timer;
    QTimer _wait_timer;
};

#endif // DOOR_H
