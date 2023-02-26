#include "error.h"

void displayErrorMessage(const int error_type)
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);

    switch (error_type)
    {
        case ERROR_READ_DATA:
            msg.setText("Возникла ошибка при чтении кординаты из файла.");
            break;
        case ERROR_OPEN_FILE:
            msg.setText("Возникла ошибка при попытке открытия файла.");
            break;
        case ERROR_NO_DATA:
            msg.setText("Не удалось корректно прочитать данные из файла.");
            break;
        default:
            msg.setText("Возникла непредвиденная ошибка.");
            break;
    }

    msg.exec();
}
