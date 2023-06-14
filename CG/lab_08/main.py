import sys
from PySide6.QtWidgets import QApplication
from PySide6.QtCore import Qt
from MainWindow import MainWindow

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setStyle('fusion')
    app.setStyleSheet('''
    QListWidget::item:selected:!active {
        background: lightBlue;
        color: black;
    }''')

    window = MainWindow()
    window.setWindowTitle("ЛР №7, Конкина Алина, ИУ7-43Б")
    window.setStyleSheet("* {font-size: 14pt}")

    window.setWindowState(Qt.WindowMaximized)
    # window.setWindowFlags(window.windowFlags() | Qt.CustomizeWindowHint)
    # window.setWindowFlags(window.windowFlags() & ~Qt.WindowMinimizeFlag)
    # window.setWindowFlags(Qt.WindowMinimizeButtonHint)
    app.exec()
