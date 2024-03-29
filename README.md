# s21_matrix+

Реализация библиотеки s21_matrix_oop.h


## Contents

1. [Chapter I](#chapter-i) \
    1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
    2.1. [Information](#information)
3. [Chapter III](#chapter-iii) \
    3.1. [Part 1](#part-1-реализация-функции-библиотеки-s21_matrix_ooph)


## Chapter I

## Introduction

В данном проекте реализована библиотеку для работы с матрицами используя объектно-ориентированный подход.

## Chapter 2

### Операции над матрицами

Ниже представлено краткое описание операций над матрицами, которые реализованы в разрабатываемой библиотеке.  

| Операция    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const S21Matrix& other)` | Проверяет матрицы на равенство между собой |  |
| `void SumMatrix(const S21Matrix& other)` | Прибавляет вторую матрицы к текущей | различная размерность матриц |
| `void SubMatrix(const S21Matrix& other)` | Вычитает из текущей матрицы другую | различная размерность матриц |
| `void MulNumber(const double num)` | Умножает текущую матрицу на число |  |
| `void MulMatrix(const S21Matrix& other)` | Умножает текущую матрицу на вторую | число столбцов первой матрицы не равно числу строк второй матрицы |
| `S21Matrix Transpose()` | Создает новую транспонированную матрицу из текущей и возвращает ее |  |
| `S21Matrix CalcComplements()` | Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее | матрица не является квадратной |
| `double Determinant()` | Вычисляет и возвращает определитель текущей матрицы | матрица не является квадратной |
| `S21Matrix InverseMatrix()` | Вычисляет и возвращает обратную матрицу | определитель матрицы равен 0 |

Помимо реализации данных операций, необходимо также реализовать конструкторы и деструкторы:

| Метод    | Описание   |
| ----------- | ----------- |
| `S21Matrix()` | Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью |  
| `S21Matrix(int rows, int cols)` | Параметризированный конструктор с количеством строк и столбцов | 
| `S21Matrix(const S21Matrix& other)` | Конструктор копирования |
| `S21Matrix(S21Matrix&& other)` | Конструктор переноса |
| `~S21Matrix()` | Деструктор |

А также нужно перегрузить следующие операторы, частично соответствующие операциям выше:

| Оператор    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `+`      | Сложение двух матриц  | различная размерность матриц |
| `-`   | Вычитание одной матрицы из другой | различная размерность матриц |
| `*`  | Умножение матриц и умножение матрицы на число | число столбцов первой матрицы не равно числу строк второй матрицы |
| `==`  | Проверка на равенство матриц (`EqMatrix`) | |
| `=`  | Присвоение матрице значений другой матрицы | |
| `+=`  | Присвоение сложения (`SumMatrix`)   | различная размерность матриц |
| `-=`  | Присвоение разности (`SubMatrix`) | различная размерность матриц |
| `*=`  | Присвоение умножения (`MulMatrix`/`MulNumber`) | число столбцов первой матрицы не равно числу строк второй матрицы |
| `(int i, int j)`  | Индексация по элементам матрицы (строка, колонка) | индекс за пределами матрицы |


## Chapter III

## Part 1. Реализация функции библиотеки s21_matrix_oop.h

- Программа разработана на языке C++ стандарта C++17 с использованием компилятора gcc
- Код программы находится в папке src
- При написании кода соблюдён Google Style
- Матрицу реализована в виде класса `S21Matrix`
- Хранятся только приватные поля `matrix_`, `rows_` и `cols_`
- Реализован доступ к приватным полям `rows_` и `cols_` через accessor и mutator. При увеличении размера - матрица дополняется нулевыми элементами, при уменьшении - лишнее просто отбрасывается
- Решение оформлено как статическая библиотека (с заголовочным файлом s21_matrix_oop.h)
- Реализованы операции, описанные [выше](#операции-над-матрицами)
- Перегружены операторы в соответствии с таблицой в разделе [выше](#операции-над-матрицами).
- Выполнено полное покрытие unit-тестами функций библиотеки c помощью библиотеки GTest
- Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix_oop.a)

