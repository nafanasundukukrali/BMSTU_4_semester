import ctypes
import sys

lib = ctypes.CDLL('../lib/libarray.so')

_array_left_move = lib.array_left_move
_array_left_move.restype = ctypes.c_short
_array_left_move.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.c_size_t)

_array_get_square = lib.array_get_squares
_array_get_square.restype = ctypes.c_short 
_array_get_square.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_size_t))

ERROR_TYPE = 11
ERROR_BIG_NUMBER = 12
ERROR_ARRAY_OVERFLOW = 13
ERROR_EMPTY_DATA = 14
ERROR_LESS_ZERO = 15
EXIT_SUCCESS = 0

MAX_ARRAY_SIZE = 100

class IntArray():
    def __init__(self):
        self.__array = [];

    def len(self):
        return len(self.__array)

    def get_array_string(self):
        if self.len() == 0:
            return ""
        
        string = ""

        for _ in self.__array:
            string += str(_) + ' '

        return string

    def add(self, value):
        if type(value) != int:
            return ERROR_TYPE
        elif abs(value) > ctypes.c_uint(-1).value:
            return ERROR_BIG_NUMBER
        elif self.len() >= MAX_ARRAY_SIZE:
            return ERROR_ARRAY_OVERFLOW

        self.__array.append(value)

        return EXIT_SUCCESS 

    def pop(self):
        if self.len() == 0:
            return ERROR_EMPTY_DATA 
        
        self.__array.pop()

        return EXIT_SUCCESS

    def array_left_move(self, k):
        if type(k) != int:
            return ERROR_TYPE
        elif abs(k) > ctypes.c_size_t(-1).value:
            return ERROR_BIG_NUMBER
        elif self.len() == 0:
            return ERROR_EMPTY_DATA
        elif k < 0:
            return ERROR_LESS_ZERO

        src = (ctypes.c_int * self.len())(*self.__array)
        return_code = _array_left_move(src, self.len(), k)

        if return_code:
            return return_code
        
        self.__array = list(src)

        return EXIT_SUCCESS 

    def array_get_squares(self):
        if self.len() == 0:
            return ""

        src = (ctypes.c_int * self.len())(*self.__array)
        result = (ctypes.c_int * self.len())(*self.__array)
        size_t = ctypes.c_size_t(self.len())
        point = ctypes.pointer(size_t)
        _array_get_square(src, self.len(), result, point)

        if size_t == 0:
            return ""

        string = ""

        for i in range(size_t.value):
            string += str(result[i]) + ' '

        return string
