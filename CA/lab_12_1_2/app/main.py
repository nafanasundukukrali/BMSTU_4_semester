from IntArray import *
import tkinter as tk
from tkinter import *
from tkinter import ttk
import tkinter.messagebox as message

class MainWindow:
    def __init__(self):
        self.tk = tk
        self.window = tk.Tk()
        self.window.title('Сдвиг в лево и поиск квадратов')
        self.__array = IntArray()

        self.input_number = tk.StringVar()
        self.input_k_number = tk.StringVar()

        self.array_string = tk.StringVar()
    
    @staticmethod
    def free_number(number_field):
        number_field.set("")

    @staticmethod
    def print_array_type_error_message(code):
        if code == ERROR_TYPE:
            message.showerror('Ошибка', 'В качестве нового элемента введено не целое число.') 
        elif code == ERROR_BIG_NUMBER:
            message.showerror('Ошибка', 'В качестве нового элемента введено слишком большое число по модулю.') 
        elif code == ERROR_ARRAY_OVERFLOW:
            message.showerror('Ошибка', f'Массив переполнен: в нём уже {MAX_ARRAY_SIZE}.')
        elif code == ERROR_EMPTY_DATA:
            message.showerror('Ошибка', f'Массив пуст.')
        elif code == ERROR_LESS_ZERO:
            message.showerror('Ошибка', 'Введено число меньше 0.')
        else:
            message.showerror('Ошибка', 'Произошла непредвиденная ошибка')


    def add_number(self):
        if not self.data_checking(self.input_number.get()):
            return_code = ERROR_TYPE
        else:
            return_code = self.__array.add(int(self.input_number.get()))

        if return_code:
            self.print_array_type_error_message(return_code)
        else:
            self.array_string.set(self.__array.get_array_string())

        self.free_number(self.input_number)

    def remove_number(self):
        return_code = self.__array.pop()

        if return_code:
            self.print_array_type_error_message(return_code)
        else:
            self.array_string.set(self.__array.get_array_string())

    def move_for_k(self):
        if not self.data_checking(self.input_k_number.get()):
            return_code = ERROR_TYPE
        else:
            return_code = self.__array.array_left_move(int(self.input_k_number.get()))

        if return_code:
            self.print_array_type_error_message(return_code)
        else:
            self.array_string.set(self.__array.get_array_string())

        self.free_number(self.input_k_number)

    def get_squares(self):
        result = self.__array.array_get_squares()
        message.showinfo('Массив квадратов', result)

    def set_standard_geometry(self, w=800, h=400):
        self.window.geometry(f'{w}x{h}+{self.window.winfo_screenwidth() // 2 - w // 2}'
                f'+{self.window.winfo_screenheight() // 2 - h // 2 - 50}')

    def prepare_window(self):
        self.set_standard_geometry()

        buttons_frame = tk.Frame(self.window)
        buttons_frame.pack(expand=True)

        for _ in range(4):
            buttons_frame.rowconfigure(_, weight=1)

        for _ in range(5):
            buttons_frame.columnconfigure(_, weight=1)

        paddings = {'padx': 10, 'pady': 10}

        input_number_label = tk.Label(buttons_frame, text="Новое целое число:")
        input_number_label.grid(row=0, column=0, columnspan=2, **paddings)

    def set_standard_geometry(self, w=800, h=400):
        self.window.geometry(f'{w}x{h}+{self.window.winfo_screenwidth() // 2 - w // 2}'
                f'+{self.window.winfo_screenheight() // 2 - h // 2 - 50}')

    def prepare_window(self):
        self.set_standard_geometry()

        buttons_frame = tk.Frame(self.window)
        buttons_frame.pack(expand=True)

        for _ in range(5):
            buttons_frame.rowconfigure(_, weight=1)

        for _ in range(5):
            buttons_frame.columnconfigure(_, weight=1)

        paddings = {'padx': 10, 'pady': 10}

        input_number_label = tk.Label(buttons_frame, text="Новое число:")
        input_number_label.grid(row=0, column=0, columnspan=2, **paddings)
        input_number_field = tk.Entry(buttons_frame, textvariable=self.input_number)
        input_number_field.grid(row=1, column=0, columnspan=2, **paddings)

        add_number_button = tk.Button(buttons_frame, command=self.add_number, 
                text='Добавить число', width=30, background='palevioletred', 
                fg='pink', activebackground='palevioletred')
        add_number_button.grid(row=1, column=2, **paddings)

        remove_number_button = tk.Button(buttons_frame, command=self.remove_number, 
                text='Удалить последнее число', width=30, background='palevioletred', 
                fg='pink', activebackground='palevioletred')
        remove_number_button.grid(row=1, column=3, **paddings)

        k_label = tk.Label(buttons_frame, text="k:")
        k_label.grid(row=2, column=0, columnspan=2, **paddings)
        k_field = tk.Entry(buttons_frame, textvariable=self.input_k_number)
        k_field.grid(row=3, column=0, columnspan=2, **paddings)

        move_number_button = tk.Button(buttons_frame, command=self.move_for_k, 
                text='Сдвигуть массив влево на k', width=30, background='palevioletred', 
                fg='pink', activebackground='palevioletred')
        move_number_button.grid(row=3, column=2, **paddings)

        squares_number_button = tk.Button(buttons_frame, command=self.get_squares, 
                text='Получить все квадраты из массива', width=30, 
                background='palevioletred', fg='pink', activebackground='palevioletred')
        squares_number_button.grid(row=3, column=3, **paddings)

        k_label = tk.Label(buttons_frame, text="Массив")
        k_label.grid(row=4, column=0, columnspan=5, **paddings)
        scroll_x = tk.Scrollbar(self.window, orient=tk.HORIZONTAL)
        array_string = tk.Entry(buttons_frame, state='disabled', width=500, 
                textvariable=self.array_string, xscrollcommand=scroll_x.set)
        array_string.grid(row=5, column=0, columnspan=4, **paddings)

    def start_window(self):
        self.prepare_window();
        self.window.mainloop()

    @staticmethod
    def data_checking(number):
        try:
            buffer = int(number)
        except Exception:
            return False
        
        return True

if __name__ == '__main__':
    MainWindow().start_window()
