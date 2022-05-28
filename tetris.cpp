#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define ROWS 25
#define COLS 25


short Table[ROWS][COLS] = {0};

typedef struct Shape
{
    int (*arr)[3][3];
    short x, y;
};
Shape current;
Shape old_shape;

void print_shape(short row, short col);
void clear_shape(short row, short col);
void print_at_pos(char symbol, short x, short y);
bool check_x_colision(int direction);
bool check_y_colision();
void write_to_table();

// L - Shape
int L_shape[3][3] = {
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 1},
};

int Fliped_L_shape[3][3] = {
    {0, 0, 1},
    {1, 1, 1},
    {0, 0, 0},
};

// S - Shape
int S_shape[3][3] = {
    {0, 1, 1},
    {1, 1, 0},
    {0, 0, 0},
};

int Fliped_S_shape[3][3] = {
    {1, 0, 0},
    {1, 1, 0},
    {0, 1, 0},
};

// T - Shape
int T_shape[3][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 0, 0},
};

int Fliped_T_shape[3][3] = {
    {0, 1, 0},
    {1, 1, 0},
    {0, 1, 0},
};

// I - Shape
int I_shape[3][3] = {
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
};

int Fliped_I_shape[3][3] = {
    {0, 0, 0},
    {1, 1, 1},
    {0, 0, 0},
};

// Z - Shape
int Z_shape[3][3] = {
    {1, 1, 0},
    {0, 1, 1},
    {0, 0, 0},
};

int Fliped_Z_shape[3][3] = {
    {0, 1, 0},
    {1, 1, 0},
    {1, 0, 0},
};

// Square - Shape
int Square_shape[3][3] = {
    {0, 1, 1},
    {0, 1, 1},
    {0, 0, 0},
};


int main() {
    current.arr = &L_shape;
    srand(time(NULL));

    for (short row = 0; row < ROWS; row++) {
        for (short col = 0; col < COLS; col++) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD {col, row});
            switch (Table[row][col]) {
                case 0:
                    printf(".");
                    break;

                case 1:
                    printf("#");
                    break;
            }
        }
    }

    current.x = 5;
    current.y = 1;

    while (true) {
        if (check_y_colision()) {
            old_shape = current;
            current.y++;
            for (short row = 0; row < 3; row++) {
                for (short col = 0; col < 3; col++){
                    if ((*current.arr)[row][col] == 1) clear_shape(row, col);
                }
            }
            for (short row = 0; row < 3; row++) {
                for (short col = 0; col < 3; col++){
                    if ((*current.arr)[row][col] == 1) print_shape(row, col);
                }
            }
            for (int i = 0; i < 50; i++) {
                Sleep(10);
                fflush(stdin);
                if (kbhit()) {
                    char key = getch();

                    switch (key) {
                        case 'a':
                            if (check_x_colision(-1)) {
                                old_shape = current;
                                current.x--;
                                for (short row = 0; row < 3; row++) {
                                    for (short col = 0; col < 3; col++){
                                        if ((*current.arr)[row][col] == 1) clear_shape(row, col);
                                    }
                                }
                                for (short row = 0; row < 3; row++) {
                                    for (short col = 0; col < 3; col++){
                                        if ((*current.arr)[row][col] == 1) print_shape(row, col);
                                    }
                                }
                            }
                            break;
                        
                        case 'd':
                            if (check_x_colision(1)) {
                                old_shape = current;
                                current.x++;
                                for (short row = 0; row < 3; row++) {
                                    for (short col = 0; col < 3; col++){
                                        if ((*current.arr)[row][col] == 1) clear_shape(row, col);
                                    }
                                }
                                for (short row = 0; row < 3; row++) {
                                    for (short col = 0; col < 3; col++){
                                        if ((*current.arr)[row][col] == 1) print_shape(row, col);
                                    }
                                }
                            }
                            break;
                    }
                }
            }
        }
        else {
            write_to_table();
            break;
        }
    }
    main();
}


void print_shape(short row, short col) {
    if ((row == 0) && (col == 0)) {
        short x = current.x - 1;
        short y = current.y - 1;
        print_at_pos('#', x, y);
    }

    else if ((row == 0) && (col == 1)) {
        short x = current.x;
        short y = current.y - 1;
        print_at_pos('#', x, y);
    }

    else if ((row == 0) && (col == 2)) {
        short x = current.x + 1;
        short y = current.y - 1;
        print_at_pos('#', x, y);
    }

    else if ((row == 1) && (col == 0)) {
        short x = current.x - 1;
        short y = current.y;
        print_at_pos('#', x, y);
    }

    else if ((row == 1) && (col == 1)) {
        short x = current.x;
        short y = current.y;
        print_at_pos('#', x, y);
    }

    else if ((row == 1) && (col == 2)) {
        short x = current.x + 1;
        short y = current.y;
        print_at_pos('#', x, y);
    }

    else if ((row == 2) && (col == 0)) {
        short x = current.x - 1;
        short y = current.y + 1;
        print_at_pos('#', x, y);
    }

    else if ((row == 2) && (col == 1)) {
        short x = current.x;
        short y = current.y + 1;
        print_at_pos('#', x, y);
    }

    else if ((row == 2) && (col == 2)) {
        short x = current.x + 1;
        short y = current.y + 1;
        print_at_pos('#', x, y);
    }
}


void clear_shape(short row, short col) {
    if ((row == 0) && (col == 0)) {
        short x = old_shape.x - 1;
        short y = old_shape.y - 1;
        print_at_pos('.', x, y);
    }

    else if ((row == 0) && (col == 1)) {
        short x = old_shape.x;
        short y = old_shape.y - 1;
        print_at_pos('.', x, y);
    }

    else if ((row == 0) && (col == 2)) {
        short x = old_shape.x + 1;
        short y = old_shape.y - 1;
        print_at_pos('.', x, y);
    }

    else if ((row == 1) && (col == 0)) {
        short x = old_shape.x - 1;
        short y = old_shape.y;
        print_at_pos('.', x, y);
    }

    else if ((row == 1) && (col == 1)) {
        short x = old_shape.x;
        short y = old_shape.y;
        print_at_pos('.', x, y);
    }

    else if ((row == 1) && (col == 2)) {
        short x = old_shape.x + 1;
        short y = old_shape.y;
        print_at_pos('.', x, y);
    }

    else if ((row == 2) && (col == 0)) {
        short x = old_shape.x - 1;
        short y = old_shape.y + 1;
        print_at_pos('.', x, y);
    }

    else if ((row == 2) && (col == 1)) {
        short x = old_shape.x;
        short y = old_shape.y + 1;
        print_at_pos('.', x, y);
    }

    else if ((row == 2) && (col == 2)) {
        short x = old_shape.x + 1;
        short y = old_shape.y + 1;
        print_at_pos('.', x, y);
    }
}


void print_at_pos(char symbol, short x, short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", symbol);
}


bool check_x_colision(int direction) {
    for (short row = 0; row < 3; row++) {
        for (short col = 0; col < 3; col++) {
            if ((*current.arr)[row][col] == 1) {
                if ((row == 0) && (col == 0)) {
                    if ((((current.x - 1) + direction) < 0) || (((current.x - 1) + direction) >= COLS)) return false;
                }

                else if ((row == 0) && (col == 1)) {
                    if ((((current.x) + direction) < 0) || (((current.x) + direction) >= COLS)) return false;
                }

                else if ((row == 0) && (col == 2)) {
                    if ((((current.x + 1) + direction) < 0) || (((current.x + 1) + direction) >= COLS)) return false;
                }

                else if ((row == 1) && (col == 0)) {
                    if ((((current.x - 1) + direction) < 0) || (((current.x - 1) + direction) >= COLS)) return false;
                }

                else if ((row == 1) && (col == 1)) {
                    if ((((current.x) + direction) < 0) || (((current.x) + direction) >= COLS)) return false;
                }

                else if ((row == 1) && (col == 2)) {
                    if ((((current.x + 1) + direction) < 0) || (((current.x + 1) + direction) >= COLS)) return false;
                }

                else if ((row == 2) && (col == 0)) {
                    if ((((current.x - 1) + direction) < 0) || (((current.x - 1) + direction) >= COLS)) return false;
                }

                else if ((row == 2) && (col == 1)) {
                    if ((((current.x) + direction) < 0) || (((current.x) + direction) >= COLS)) return false;
                }

                else if ((row == 2) && (col == 2)) {
                    if ((((current.x + 1) + direction) < 0) || (((current.x + 1) + direction) >= COLS)) return false;
                }
            }
        }
    }
    return true;
}


bool check_y_colision() {
    for (short row = 0; row < 3; row++) {
        for (short col = 0; col < 3; col++) {
            if ((*current.arr)[row][col] == 1) {
                if ((row == 0) && (col == 0)) {
                    if (((current.y - 1) + 1) == ROWS) return false;
                }

                else if ((row == 0) && (col == 1)) {
                    if (((current.y - 1) + 1) == ROWS) return false;
                }

                else if ((row == 0) && (col == 2)) {
                    if (((current.y - 1) + 1) == ROWS) return false;
                }

                else if ((row == 1) && (col == 0)) {
                    if (((current.y) + 1) == ROWS) return false;
                }

                else if ((row == 1) && (col == 1)) {
                    if (((current.y) + 1) == ROWS) return false;
                }

                else if ((row == 1) && (col == 2)) {
                    if (((current.y) + 1) == ROWS) return false;
                }

                else if ((row == 2) && (col == 0)) {
                    if (((current.y + 1) + 1) == ROWS) return false;
                }

                else if ((row == 2) && (col == 1)) {
                    if (((current.y + 1) + 1) == ROWS) return false;
                }

                else if ((row == 2) && (col == 2)) {
                    if (((current.y + 1) + 1) == ROWS) return false;
                }
            }
        }
    }
    return true;
}


void write_to_table() {
    for (short row = 0; row < 3; row++) {
        for (short col = 0; col < 3; col++) {
            if ((*current.arr)[row][col] == 1) {
                if ((row == 0) && (col == 0)) {
                    Table[current.y - 1][current.x - 1] = 1;
                }

                else if ((row == 0) && (col == 1)) {
                    Table[current.y - 1][current.x] = 1;
                }

                else if ((row == 0) && (col == 2)) {
                    Table[current.y - 1][current.x + 1] = 1;
                }

                else if ((row == 1) && (col == 0)) {
                    Table[current.y][current.x - 1] = 1;
                }

                else if ((row == 1) && (col == 1)) {
                    Table[current.y][current.x] = 1;
                }

                else if ((row == 1) && (col == 2)) {
                    Table[current.y][current.x + 1] = 1;
                }

                else if ((row == 2) && (col == 0)) {
                    Table[current.y + 1][current.x - 1] = 1;
                }

                else if ((row == 2) && (col == 1)) {
                    Table[current.y + 1][current.x] = 1;
                }

                else if ((row == 2) && (col == 2)) {
                    Table[current.y + 1][current.x + 1] = 1;
                }
            }
        }
    }
}
