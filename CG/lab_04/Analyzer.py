import time
from PySide6.QtCore import QPoint, QLine


def analyzer(function):
    def _wrapper(center, a, b=None, time_analyzer=False):
        if time_analyzer:
            start = time.time_ns()

        if b:
            array = function(center, a, b)
        else:
            array = function(center, a)

        if time_analyzer:
            end = time.time_ns()

            return end - start
        else:
            return array

    return _wrapper
