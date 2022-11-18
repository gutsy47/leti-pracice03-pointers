#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

// 1) Используя арифметику указателей, заполняет квадратичную целочисленную матрицу порядка N (6,8,10)
//    случайными числами от 1 до N*N согласно схемам, приведенным на рисунках (спираль и змейка).
//    Пользователь должен видеть процесс заполнения квадратичной матрицы.
// 2) Получает новую матрицу, из матрицы п. 1, переставляя ее блоки в соответствии со схемами:
// 3) Используя арифметику указателей, сортирует элементы любой сортировкой.
// 4) Уменьшает, увеличивает, умножает или делит все элементы матрицы на введенное пользователем число.

void printMatrix(int *arr, int N) {
    for (int i = 0; i < N*N; i+=N) {
        for (int j = i; j < i+N; j++) {
            std::cout << arr[j] << '\t';
        }
        putchar('\n');
    }
}

int getRandInt(int from, int to) {
    return -from + std::rand() % (from + to + 1);
}

void snakeFill(int *arr, int N) {
    int *pArr = arr;
    int change = N;
    for (int i = 0; i < N; i++) {
        int *pRowEnd = (change > 0) ? pArr + N*N - N : pArr - N*N + N;
        while (pArr - change != pRowEnd) {
            *pArr = getRandInt(1, 100);

            system("cls");
            printMatrix(arr, N);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            pArr += change;
        }
        pArr -= change - 1;
        change = -change;
    }
}

int main() {
    const int N = 6;
    int array[N*N];

    for (int i = 0; i < N*N; i++) {
        array[i] = 0;
    }

    snakeFill(array, N);

    return 0;
}
