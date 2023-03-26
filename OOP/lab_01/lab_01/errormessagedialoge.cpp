#include "errormessagedialoge.h"

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
        case ERROR_NO_PATH:
            msg.setText("Вы не указали путь до файла со входными данными.");
            break;
        case ERROR_CLOSE_FILE:
            msg.setText("Возникла ошибка при закрытии файла.");
            break;
        case ERROR_ALLOCATE_MEMORY:
            msg.setText("Возникла ошибка при выделении памяти из кучи.");
            break;
        case ERROR_INCORRECT_EDGE_INFO:
            msg.setText("Входные данные содержат некорректную информацию о концах рёбер.");
            break;
        case ERROR_NO_LOADED_FIGURE:
            msg.setText("Входные данные не были предоставлены.");
            break;
        default:
            msg.setText("Возникла непредвиденная ошибка.");
            break;
    }

    msg.exec();
}
