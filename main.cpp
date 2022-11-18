#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

// 1) �ᯮ���� ��䬥⨪� 㪠��⥫��, �������� ��������� 楫��᫥���� ������ ���浪� N (6,8,10)
//    ��砩�묨 �᫠�� �� 1 �� N*N ᮣ��᭮ �奬��, �ਢ������ �� ��㭪�� (ᯨࠫ� � ������).
//    ���짮��⥫� ������ ������ ����� ���������� ������筮� ������.
// 2) ����砥� ����� ������, �� ������ �. 1, ����⠢��� �� ����� � ᮮ⢥��⢨� � �奬���:
// 3) �ᯮ���� ��䬥⨪� 㪠��⥫��, ������ ������ �� ���஢���.
// 4) �����蠥�, 㢥��稢���, 㬭����� ��� ����� �� ������ ������ �� ��������� ���짮��⥫�� �᫮.

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
