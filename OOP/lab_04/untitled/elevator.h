#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "cabin.h"
#include "controller.h"
#include <memory>
#include <QVBoxLayout>

class Elevator: public QObject
{
    Q_OBJECT

public:
    explicit Elevator(QObject *parent = nullptr);
    ~Elevator() = default;

    QWidget *widget();

private:
    Cabin _cabin;
    Controller _controller;
};

#endif // ELEVATOR_H
