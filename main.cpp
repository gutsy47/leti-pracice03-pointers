#include <iostream>
#include <cstdlib>
#include <chrono>
#include <Windows.h>

// 1) �ᯮ���� ��䬥⨪� 㪠��⥫��, �������� ��������� 楫��᫥���� ������ ���浪� N (6,8,10)
//    ��砩�묨 �᫠�� �� 1 �� N*N ᮣ��᭮ �奬��, �ਢ������ �� ��㭪�� (ᯨࠫ� � ������).
//    ���짮��⥫� ������ ������ ����� ���������� ������筮� ������.
// 2) ����砥� ����� ������, �� ������ �. 1, ����⠢��� �� ����� � ᮮ⢥��⢨� � �奬���:
// 3) �ᯮ���� ��䬥⨪� 㪠��⥫��, ������ ������ �� ���஢���.
// 4) �����蠥�, 㢥��稢���, 㬭����� ��� ����� �� ������ ������ �� ��������� ���짮��⥫�� �᫮.

int getRandInt(int from, int to) {
    return from + std::rand() % to;
}

void printMatrix(int *arr, int N, int width = 6) {
    for (int i = 0; i < N*N; i+=N) {
        for (int j = i; j < i+N; j++) {
            std::cout.width(width);
            std::cout << arr[j];
        }
        putchar('\n');
    }
}

int getIntLength(int x) {
    int amount = 0;
    while (x) {
        x /= 10;
        amount++;
    }
    return amount;
}

int getCursorPositionY() {
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo = {};
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBufferInfo);
    return screenBufferInfo.dwCursorPosition.Y;
}

void updateMatrix(int x, int y, int value, int width = 6) {
    COORD destCoord;
    destCoord.X = (x+1)*width - getIntLength(value);
    destCoord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), destCoord);

    std::cout << value << '\r';
    std::cout.flush();

    Sleep(100);
}

void snakeFill(int *arr, int N) {
    // Init
    int startCursorPosY = getCursorPositionY() == 0 ? 0 : getCursorPositionY() + 1;
    printMatrix(arr, N);

    // Main loop
    int *pArr = arr;
    int change = N;
    for (int i = 0; i < N; ++i) {
        int *pRowEnd = (change > 0) ? pArr + N*N - N : pArr - N*N + N;
        while (pArr - change != pRowEnd) {
            *pArr = getRandInt(1, N*N);
            updateMatrix((pArr - arr) % N, startCursorPosY + (pArr - arr) / N, *pArr);
            pArr += change;
        }
        pArr -= change - 1;
        change = -change;
    }
}

int main() {
    // Init matrix
    const int N = 6;
    int matrix[N][N];
    int *ptrMatrix = &matrix[0][0];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            *((ptrMatrix + (N * i)) + j) = 0;
        }
    }

    snakeFill(ptrMatrix, N);

    int exit;
    std::cin >> exit;
    return 0;
}
