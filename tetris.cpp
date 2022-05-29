#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define ROWS 25
#define COLS 25


short Table[ROWS][COLS] = {0};
int score = 0;

typedef struct Shape
{
    int (*arr)[3][3];
    short x, y;
    char type;
    bool fliped = false;
};
Shape current;
Shape old_shape;

void print_shape(Shape shape);
void clear_shape(Shape shape);
void print_at_pos(char symbol, short x, short y);
bool check_x_colision(int direction);
bool check_y_colision();
void write_to_table();
void reset_row(int r);
void print_score();

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
    switch (rand() % 6) {
        case 0:
            current.arr = &L_shape;
            current.type = 'L';
            break;

        case 1:
            current.arr = &S_shape;
            current.type = 'S';
            break;
        
        case 2:
            current.arr = &T_shape;
            current.type = 'T';
            break;

        case 3:
            current.arr = &I_shape;
            current.type = 'I';
            break;
        
        case 4:
            current.arr = &Z_shape;
            current.type = 'Z';
            break;
        
        case 5:
            current.arr = &Square_shape;
            current.type = 'Q';
            break;
    }

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

    current.x = rand() % 15 + 5;
    current.y = 1;

    while (true) {
        if (check_y_colision()) {
            old_shape = current;
            current.y++;
            clear_shape(old_shape);
            print_shape(current);
            for (int i = 0; i < 20; i++) {
                Sleep(1);
                fflush(stdin);
                if (kbhit()) {
                    char key = getch();

                    switch (key) {
                        case 'a':
                            if (check_x_colision(-1)) {
                                old_shape = current;
                                current.x--;
                                clear_shape(old_shape);
                                print_shape(current);
                            }
                            break;
                        
                        case 'd':
                            if (check_x_colision(1)) {
                                old_shape = current;
                                current.x++;
                                clear_shape(old_shape);
                                print_shape(current);
                            }
                            break;
                        
                        case 'w':
                            switch (current.type) {
                                case 'L':
                                    clear_shape(current);
                                    if (current.fliped) {
                                        current.arr = &L_shape;
                                        current.fliped = false;
                                        break;
                                    }
                                    current.arr = &Fliped_L_shape;
                                    current.fliped = true;
                                    print_shape(current);
                                    break;
                                
                                case 'S':
                                    clear_shape(current);
                                    if (current.fliped) {
                                        current.arr = &S_shape;
                                        current.fliped = false;
                                        break;
                                    }
                                    current.arr = &Fliped_S_shape;
                                    current.fliped = true;
                                    print_shape(current);
                                    break;
                                
                                case 'T':
                                    clear_shape(current);
                                    if (current.fliped) {
                                        current.arr = &T_shape;
                                        current.fliped = false;
                                        break;
                                    }
                                    current.arr = &Fliped_T_shape;
                                    current.fliped = true;
                                    print_shape(current);
                                    break;
                                
                                case 'I':
                                    clear_shape(current);
                                    if (current.fliped) {
                                        current.arr = &I_shape;
                                        current.fliped = false;
                                        break;
                                    }
                                    current.arr = &Fliped_I_shape;
                                    current.fliped = true;
                                    print_shape(current);
                                    break;
                                
                                case 'Z':
                                    clear_shape(current);
                                    if (current.fliped) {
                                        current.arr = &Z_shape;
                                        current.fliped = false;
                                        break;
                                    }
                                    current.arr = &Fliped_Z_shape;
                                    current.fliped = true;
                                    print_shape(current);
                                    break;
                            }
                        case 's':
                            i = 50;
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


void print_shape(Shape shape) {
    for (short row = 0; row < 3; row++) {
        for (short col = 0; col < 3; col++){
            if ((*shape.arr)[row][col] == 1) {
                if ((row == 0) && (col == 0)) {
                    short x = shape.x - 1;
                    short y = shape.y - 1;
                    print_at_pos('#', x, y);
                }

                else if ((row == 0) && (col == 1)) {
                    short x = shape.x;
                    short y = shape.y - 1;
                    print_at_pos('#', x, y);
                }

                else if ((row == 0) && (col == 2)) {
                    short x = shape.x + 1;
                    short y = shape.y - 1;
                    print_at_pos('#', x, y);
                }

                else if ((row == 1) && (col == 0)) {
                    short x = shape.x - 1;
                    short y = shape.y;
                    print_at_pos('#', x, y);
                }

                else if ((row == 1) && (col == 1)) {
                    short x = shape.x;
                    short y = shape.y;
                    print_at_pos('#', x, y);
                }

                else if ((row == 1) && (col == 2)) {
                    short x = shape.x + 1;
                    short y = shape.y;
                    print_at_pos('#', x, y);
                }

                else if ((row == 2) && (col == 0)) {
                    short x = shape.x - 1;
                    short y = shape.y + 1;
                    print_at_pos('#', x, y);
                }

                else if ((row == 2) && (col == 1)) {
                    short x = shape.x;
                    short y = shape.y + 1;
                    print_at_pos('#', x, y);
                }

                else if ((row == 2) && (col == 2)) {
                    short x = shape.x + 1;
                    short y = shape.y + 1;
                    print_at_pos('#', x, y);
                }
            }
        }
    }
}


void clear_shape(Shape shape) {
    for (short row = 0; row < 3; row++) {
        for (short col = 0; col < 3; col++){
            if ((*shape.arr)[row][col] == 1) {
                if ((row == 0) && (col == 0)) {
                    short x = shape.x - 1;
                    short y = shape.y - 1;
                    print_at_pos('.', x, y);
                }

                else if ((row == 0) && (col == 1)) {
                    short x = shape.x;
                    short y = shape.y - 1;
                    print_at_pos('.', x, y);
                }

                else if ((row == 0) && (col == 2)) {
                    short x = shape.x + 1;
                    short y = shape.y - 1;
                    print_at_pos('.', x, y);
                }

                else if ((row == 1) && (col == 0)) {
                    short x = shape.x - 1;
                    short y = shape.y;
                    print_at_pos('.', x, y);
                }

                else if ((row == 1) && (col == 1)) {
                    short x = shape.x;
                    short y = shape.y;
                    print_at_pos('.', x, y);
                }

                else if ((row == 1) && (col == 2)) {
                    short x = shape.x + 1;
                    short y = shape.y;
                    print_at_pos('.', x, y);
                }

                else if ((row == 2) && (col == 0)) {
                    short x = shape.x - 1;
                    short y = shape.y + 1;
                    print_at_pos('.', x, y);
                }

                else if ((row == 2) && (col == 1)) {
                    short x = shape.x;
                    short y = shape.y + 1;
                    print_at_pos('.', x, y);
                }

                else if ((row == 2) && (col == 2)) {
                    short x = shape.x + 1;
                    short y = shape.y + 1;
                    print_at_pos('.', x, y);
                }
            }
        } 
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
                    if (Table[current.y - 1][(current.x - 1) + direction] == 1) return false;
                }

                else if ((row == 0) && (col == 1)) {
                    if ((((current.x) + direction) < 0) || (((current.x) + direction) >= COLS)) return false;
                    if (Table[current.y - 1][(current.x) + direction] == 1) return false;
                }

                else if ((row == 0) && (col == 2)) {
                    if ((((current.x + 1) + direction) < 0) || (((current.x + 1) + direction) >= COLS)) return false;
                    if (Table[current.y - 1][(current.x + 1) + direction] == 1) return false;
                }

                else if ((row == 1) && (col == 0)) {
                    if ((((current.x - 1) + direction) < 0) || (((current.x - 1) + direction) >= COLS)) return false;
                    if (Table[current.y][(current.x - 1) + direction] == 1) return false;
                }

                else if ((row == 1) && (col == 1)) {
                    if ((((current.x) + direction) < 0) || (((current.x) + direction) >= COLS)) return false;
                    if (Table[current.y][(current.x) + direction] == 1) return false;
                }

                else if ((row == 1) && (col == 2)) {
                    if ((((current.x + 1) + direction) < 0) || (((current.x + 1) + direction) >= COLS)) return false;
                    if (Table[current.y][(current.x + 1) + direction] == 1) return false;
                }

                else if ((row == 2) && (col == 0)) {
                    if ((((current.x - 1) + direction) < 0) || (((current.x - 1) + direction) >= COLS)) return false;
                    if (Table[current.y + 1][(current.x - 1) + direction] == 1) return false;
                }

                else if ((row == 2) && (col == 1)) {
                    if ((((current.x) + direction) < 0) || (((current.x) + direction) >= COLS)) return false;
                    if (Table[current.y + 1][(current.x) + direction] == 1) return false;
                }

                else if ((row == 2) && (col == 2)) {
                    if ((((current.x + 1) + direction) < 0) || (((current.x + 1) + direction) >= COLS)) return false;
                    if (Table[current.y + 1][(current.x + 1) + direction] == 1) return false;
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
                    if (Table[(current.y - 1) + 1][current.x - 1] == 1) return false;
                }

                else if ((row == 0) && (col == 1)) {
                    if (((current.y - 1) + 1) == ROWS) return false;
                    if (Table[(current.y - 1) + 1][current.x] == 1) return false;
                }

                else if ((row == 0) && (col == 2)) {
                    if (((current.y - 1) + 1) == ROWS) return false;
                    if (Table[(current.y - 1) + 1][current.x + 1] == 1) return false;
                }

                else if ((row == 1) && (col == 0)) {
                    if (((current.y) + 1) == ROWS) return false;
                    if (Table[(current.y) + 1][current.x - 1] == 1) return false;
                }

                else if ((row == 1) && (col == 1)) {
                    if (((current.y) + 1) == ROWS) return false;
                    if (Table[(current.y) + 1][current.x] == 1) return false;
                }

                else if ((row == 1) && (col == 2)) {
                    if (((current.y) + 1) == ROWS) return false;
                    if (Table[(current.y) + 1][current.x + 1] == 1) return false;
                }

                else if ((row == 2) && (col == 0)) {
                    if (((current.y + 1) + 1) == ROWS) return false;
                    if (Table[(current.y + 1) + 1][current.x - 1] == 1) return false;
                }

                else if ((row == 2) && (col == 1)) {
                    if (((current.y + 1) + 1) == ROWS) return false;
                    if (Table[(current.y + 1) + 1][current.x] == 1) return false;
                }

                else if ((row == 2) && (col == 2)) {
                    if (((current.y + 1) + 1) == ROWS) return false;
                    if (Table[(current.y + 1) + 1][current.x + 1] == 1) return false;
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
                if ((current.y - 1) <= 0) exit(0);
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


void reset_row(int r) {
    for (int row = r; row != 0; row--) {
        for (int col = 0; col < COLS; col++) {
            int value = Table[row - 1][col];
            Table[row][col] = value;
        }
    }
}


void print_score() {
    
}
