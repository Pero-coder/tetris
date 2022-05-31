#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define ROWS 25
#define COLS 25

#define LEFT 'a'
#define RIGHT 'd'
#define ROTATE 'w'
#define FALL 's'


short Table[ROWS][COLS] = {0};
int score = 0;

typedef struct Shape
{
    int arr[3][3];
    short x, y;
};
Shape current;
Shape old_shape;

int old_arr[3][3] = {0};

void print_shape(Shape shape, char symbol);
bool check_x_colision(int direction);
bool check_y_colision();
void write_to_table();
void reset_row(int r);
void print_score();
void copy_arr(int from[3][3], int to[3][3]);
void rotate();


int shapes[6][3][3] = {
    // 0 - L_Shape
    {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 1},
    },
    // 1 - S_Shape
    {
        {0, 1, 1},
        {1, 1, 0},
        {0, 0, 0},
    },
    // 2 - Z_Shape
    {
        {1, 1, 0},
        {0, 1, 1},
        {0, 0, 0},
    },
    // 3 - T_Shape
    {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0},
    },
    // 4 - I_Shape
    {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
    },
    // 5 - Squre_Shape
    {
        {0, 1, 1},
        {0, 1, 1},
        {0, 0, 0},
    },
};


int main() {
    for (short row = 0; row < ROWS; row++) {
        int zeros = 0;
        for (short col = 0; col < COLS; col++) {
            if (Table[row][col] == 0) zeros++;
        }
        if (zeros == 0) {
            reset_row(row);
        }
    }

    srand(time(NULL));
    copy_arr(shapes[rand() % 6], current.arr);

    for (short row = 0; row < ROWS; row++) {
        for (short col = 0; col < COLS; col++) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD {col, row});
            if (Table[row][col] == 0) printf(".");
            else printf("#");
        }
    }

    print_score();

    current.x = rand() % 15 + 5;
    current.y = 1;

    while (true) {
        if (check_y_colision()) {
            old_shape = current;
            current.y++;
            print_shape(old_shape, '.');
            print_shape(current, '#');
            for (int i = 0; i < 20; i++) {
                Sleep(1);
                fflush(stdin);
                if (kbhit()) {
                    char key = tolower(getch());

                    if (key == LEFT) {
                        if (check_x_colision(-1)) {
                            old_shape = current;
                            current.x--;
                            print_shape(old_shape, '.');
                            print_shape(current, '#');
                        }
                    }

                    if (key == RIGHT) {
                        if (check_x_colision(1)) {
                            old_shape = current;
                            current.x++;
                            print_shape(old_shape, '.');
                            print_shape(current, '#');
                        }
                    }

                    if (key == ROTATE) {
                        print_shape(current, '.');
                        rotate();
                        print_shape(current, '#');
                    }

                    if (key == FALL) {
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


void print_shape(Shape shape, char symbol) {
    for (short row = -1; row <= 1; row++) {
        for (short col = -1; col <= 1; col++){
            if ((shape.arr)[row + 1][col + 1] == 1) {
                SetConsoleCursorPosition(
                        GetStdHandle(STD_OUTPUT_HANDLE), 
                        COORD {short (shape.x + col), short (shape.y + row)});
                printf("%c", symbol);
            }
        }
    }
}


bool check_x_colision(int direction) {
    for (short row = -1; row <= 1; row++) {
        for (short col = -1; col <= 1; col++) {
            if ((current.arr)[row + 1][col + 1] == 1) {
                if ((((current.x + col) + direction) < 0) || (((current.x + col) + direction) >= COLS)) return false;
                if (Table[current.y + row][(current.x + col) + direction] == 1) return false;
            }
        }
    }
    return true;
}


bool check_y_colision() {
    for (short row = -1; row <= 1; row++) {
        for (short col = -1; col <= 1; col++) {
            if ((current.arr)[row + 1][col + 1] == 1) {
                if (((current.y + row) + 1) == ROWS) return false;
                if (Table[(current.y + row) + 1][current.x + col] == 1) return false;
            }
        }
    }
    return true;
}


void write_to_table() {
    if ((current.y - 1) <= 0) exit(0);
    for (short row = -1; row <= 1; row++) {
        for (short col = -1; col <= 1; col++) {
            if ((current.arr)[row + 1][col + 1] == 1) {
                Table[current.y + row][current.x + col] = 1;
            }
        }
    }
}


void reset_row(int r) {
    score += 100;
    for (int row = r; row != 0; row--) {
        for (int col = 0; col < COLS; col++) {
            int value = Table[row - 1][col];
            Table[row][col] = value;
        }
    }
}


void print_score() {
    short x = COLS + 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD {x, 1});
    printf("Score: %d", score);
}


void rotate() {
    copy_arr(current.arr, old_arr);
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            current.arr[row][col] = old_arr[2 - col][row];
        }
    }
}


void copy_arr(int from[3][3], int to[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            to[row][col] = from[row][col];
        }
    }
}
