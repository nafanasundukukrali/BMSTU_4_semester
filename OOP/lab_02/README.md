# Напишите контейнерный класс по c++20 по вариантам (в моём случае матрица)
* По известным причинам, должны быть конструкторы переноса, копирования (последний с explisit, если нет спрашивает почему должен). Ещё должны быть конструкторы с использованием инциализируещего списка, 
любого другого контейнера (который поддерживает наши методы получения размера объекта), списка. 
* ВСЕ КОСТУРКТОРЫ, ОПЕРАТОРЫ, МЕТОДЫ ДОЛЖНЫ БЫТЬ РАСЧИТАНЫ НА ТО, ЧТО ПРИДЁТ МАТРИЦА С ДРУГИМ ТИПОМ И ВСЁ БУДЕТ РАБОТАТЬ. Типа, операция int * float должно работать.
* У меня лично ни разу не смотрел тесты, но у первых сдающих смотрел.
* Аллиасы должны быть.
* ИТЕРАТОР с random_access. Это значит, что должны быть написаны все операторы, с которыми данный тип итертаора работает. 
* Класс const_iterator - это не моя фантазия. Не ищите как это можно убрать, да, способы есть, но вас всё равно заставят переделать. Просто смиритесь, такова жизнь.