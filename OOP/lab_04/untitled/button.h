#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT;

    enum ButtonState
    {
        ACTIVE,
        NOTACTIVE
    };

public:
    Button(QWidget *parent = nullptr);
    ~Button() = default;

    void set_floor(const int &floor);

signals:
    void press_signal(bool, int floor);
    void unpress_signal();

public slots:
    void press();
    void unpress();

private:
    ButtonState _current_state;
    int _current_floor;
};

#endif // BUTTON_H
