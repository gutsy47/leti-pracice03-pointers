#include <iostream>
#include <cstdlib>
#include <Windows.h>

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
    if (x == 0) return 1;
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

void zeroFill(int *arr, int N) {
    for (int i = 0; i < N*N; ++i) *(arr++) = 0;
}

void snakeFill(int *arr, int N) {
    // Init
    int startCursorPosY = getCursorPositionY();
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

    // Return cursor to the end of the matrix
    for (int i = 0; i < N; ++i) putchar('\n');
}

void spiralFill(int *arr, int N) {
    // Init
    int startCursorPosY = getCursorPositionY();
    printMatrix(arr, N);

    // Main loop
    int *pArr = arr;
    int size = N;
    for (int square = 0; square < N/2; ++square) {
        int change = 1;
        for (int direction = 0; direction < 4; ++direction) {
            for (int i = 0; i < size-1; ++i) {
                *pArr = getRandInt(1, N*N);
                updateMatrix((pArr - arr) % N, startCursorPosY + (pArr - arr) / N, *pArr);
                pArr += change;
            }
            change = abs(change) == 1 ? N : 1;
            change = direction < 1 ? +change : -change;
        }
        size -= 2;
        pArr += N + 1;
    }

    // Return cursor to the end of the matrix
    for (int i = 0; i < N/2; ++i) putchar('\n');
}

int *getQuadPointer(int *arr, int N, int quadNum) {
    switch (quadNum) {
        case 1: return (arr);
        case 2: return (arr + N/2);
        case 3: return (arr + N*N/2);
        case 4: return (arr + N*N/2 + N/2);
    }
}

void swapQuadrants(int *arr, int N, int q1, int q2) {
    // Get first elements pointers of the quadrants
    int *pQuad1 = getQuadPointer(arr, N, q1);
    int *pQuad2 = getQuadPointer(arr, N, q2);

    // Swap
    for (int i = 0; i < N/2; ++i) {
        for (int j = 0; j < N/2; ++j)
            std::swap(*(pQuad1++), *(pQuad2++));
        pQuad1 += N - N/2;
        pQuad2 += N - N/2;
    }
}

void insertionSort(int *arr, int N) {
    for (int *p1 = arr+1; p1 < arr + N; ++p1)
        for (int *p2 = p1; p2 > arr && *(p2-1) > *p2; --p2)
            std::swap(*(p2-1), *p2);
}

int main() {
    // Init matrix
    const int N = 6;
    int matrix[N][N];
    int *ptrMatrix = &matrix[0][0];
    zeroFill(ptrMatrix, N);

    return 0;
}
