#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <tchar.h>

char Table[20][15];


int main() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < sizeof(Table[i]); j++) {
            printf("%", Table[i][j]);
        }
        printf("\n");
    }
}
