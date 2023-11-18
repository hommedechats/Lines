#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

typedef struct Coordinates{
    int x;
    int y;
}Coordinates;
typedef struct Ball_list{
    int color;
    Coordinates coordinates;
    struct Ball_list *next;
}Ball_list;

void draw_grid(int x, int y, int width, int height, int rows, int row_ascii, int column_ascii);
void delete_ball (Ball_list **list, Coordinates ball_location);
void insert_element (Ball_list **list, int is_random, int color_number, int x, int y);
Ball_list *create_list ();
int search_ball (Ball_list *list, Coordinates location);
Coordinates ball_ascii_location (Ball_list *list);
void display_balls (Ball_list *list);
void destroy_list (Ball_list **list);
void display_menu ();
void game_loop (Ball_list *ball);
void quit (Ball_list *list, int is_ingame);
void display_score ();
int search_color (Coordinates coords, Ball_list *list, int color);
int update_score (Ball_list *list);
int select_square (Ball_list *list, int is_ball);
void menu_loop (Ball_list *ball);
void move_ball (Ball_list *ball, Coordinates move_location, Coordinates ball_location);
void skip_turn (Ball_list *temp);
void program_duration (void);
void delete_used_balls(int used_count, Ball_list *list);
void display_controls ();
void save_highscore ();
void quicksort(int *scores, int left, int right);
int *load_highscore ();
void display_highscore ();
void load_state (Ball_list **list, int score);
void save_state (Ball_list *list, int score);

