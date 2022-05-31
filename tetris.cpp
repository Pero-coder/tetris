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
#define SPACE 32
#define ESC 27


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
COORD sizeCache;

void print_shape(Shape shape, char symbol);
bool check_x_colision(int direction);
bool check_y_colision();
void write_to_table();
void reset_row(int r);
void print_score();
void copy_arr(int from[3][3], int to[3][3]);
void rotate();
void menu();
void print_at_mid(char text[], int y);
void set_console_size(short x, short y);
void goto_XY_end();
void gotoXY(short x, short y);
bool resized();
COORD get_size();
COORD get_cursor();
void play();
void game_over();
void print_game_over();


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
    menu();
}


void play() {
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
            goto_XY_end();
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
                            goto_XY_end();
                        }
                    }

                    if (key == RIGHT) {
                        if (check_x_colision(1)) {
                            old_shape = current;
                            current.x++;
                            print_shape(old_shape, '.');
                            print_shape(current, '#');
                            goto_XY_end();
                        }
                    }

                    if (key == ROTATE) {
                        print_shape(current, '.');
                        rotate();
                        print_shape(current, '#');
                        goto_XY_end();
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
    play();
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
    if ((current.y - 1) <= 0) game_over();
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


COORD get_cursor() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord = {0, 0};

	int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	if(ret) coord = csbi.dwCursorPosition;
	return coord;
}


COORD get_size() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord = {0, 0};

	int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	if(ret) coord = {(short)(csbi.srWindow.Right-csbi.srWindow.Left+1), (short)(csbi.srWindow.Bottom-csbi.srWindow.Top+1)};
	return coord;
}


bool resized() {
	COORD size = get_size();
	if(size.X != sizeCache.X || size.Y != sizeCache.Y) {
		sizeCache = size;
		return true;
	}
	return false;
}


void gotoXY(short x, short y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {x, y});
}


void goto_XY_end() {
	COORD coord = get_size();
	gotoXY(coord.X-1, coord.Y-1);
}


void set_console_size(short x, short y) {
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD mWindowSize = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

	if(mWindowSize.X < x || x < 1) x = mWindowSize.X;
	if(mWindowSize.Y < y || y < 1) y = mWindowSize.Y;

	SMALL_RECT windowSize = {0, 0 , (short)(x-1), (short)(y-1)};

	fflush(stdout);
	SetConsoleScreenBufferSize(hConOut, {x, y});
    SetConsoleWindowInfo(hConOut, TRUE, &windowSize);
}

void print_at_mid(char text[], int y = 0) {
	int size;
	for(size = 0; text[size] != '\0'; size++);

	y += get_cursor().Y;
	
	gotoXY((get_size().X-size)/2, y);
	printf("%s", text);
	gotoXY(0, y+1);
}


void menu() {
    while (true) {
        if (resized()) {
            system("cls");
            print_at_mid("  _______ ______ _______ _____  _____  _____ ", 10);
            print_at_mid(" |__   __|  ____|__   __|  __ \\|_   _|/ ____|");
            print_at_mid("    | |  | |__     | |  | |__) | | | | (___  ");
            print_at_mid("    | |  |  __|    | |  |  _  /  | |  \\___ \\ ");
            print_at_mid("    | |  | |____   | |  | | \\ \\ _| |_ ____) |");
            print_at_mid("    |_|  |______|  |_|  |_|  \\_\\_____|_____/ ");
            print_at_mid("Press SPACE to start the game or press ESC to close the program...", 3);
            goto_XY_end();
        }

        if (kbhit()) {
            char key = getch();
            
            if (key == ESC) {
                exit(0);
            }

            if (key == SPACE){
                system("cls");
                play();
                break;
            }
        }
    }
}


void print_game_over() {
    system("cls");
    print_at_mid("  _____          __  __ ______    ______      ________ _____ ", 5);
    print_at_mid("  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ");
    print_at_mid("| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
    print_at_mid("| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ");
    print_at_mid("| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ");
    print_at_mid(" \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");
    print_at_mid("  _____", 3);
    print_at_mid(" /     \\");
    print_at_mid(" | () () |");
    print_at_mid(" \\  ^  /");
    print_at_mid("  |||||");
    print_at_mid("  |||||");
    print_at_mid("Press SPACE to start the game or press ESC to close the program...", 3);
}


void game_over() {
    print_game_over();
    goto_XY_end();
    while (true) {
        if (resized()) {
            print_game_over();
            goto_XY_end();
        }

        if (kbhit()) {
            char key = getch();
            
            if (key == ESC) {
                exit(0);
            }

            if (key == SPACE){
                system("cls");
                play();
                break;
            }
        }
    }
}
