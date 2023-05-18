import time
from PySide6.QtCore import QPoint, QLine


def analyzer(function):
    def _wrapper(self, has_delay=False):
        start = time.time_ns()

        result = function(self, has_delay)

        end = time.time_ns()

        return (end - start) // 1000000, result

    return _wrapper
