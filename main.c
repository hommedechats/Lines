#include "lines.h"
#include "con_lib.h"

const int ROW_MULTIPLIER = 8;
const int ROW_START_LOCATION = 4;
const int COLUMN_START_LOCATION = 2;
const int COLUMN_MULTIPLIER = 4;
const int GRID_X = 73;
const int GRID_Y = 37;
const int ROW_COUNT = 9;
const int ASCII1 = 196;
const int ASCII2 = 124;
const char *LOG_FILE = "lines.log";
const char *USED_BALLS = "delete_balls.txt";
const char *HIGHSCORES = "highscores.txt";
clock_t start;
int ball_count = 0;
int score = 0;

int main (){
    start = clock();
    atexit(program_duration);
    srand(time(NULL));
    Ball_list *ball = NULL;
    ball = create_list();
    Coordinates b;
    b.x = 0;
    b.y = 0;
    delete_ball(&ball, b);
    menu_loop(ball);

    return 0;
}
Ball_list *create_list (){

    Ball_list *new_list = malloc(sizeof(Ball_list));
    if(new_list == NULL){
        return NULL;
    }
    new_list->coordinates.x = 0;
    new_list->coordinates.y = 0;
    new_list->color = 1;
    new_list->next = NULL;

    return new_list;
}
void draw_grid (int x, int y, int width, int height, int rows, int row_ascii, int column_ascii){
    int x_start = x + 1;
    int y_start = y + height/rows; 
    for(int i = 0; i <= rows; ++i){
        for(int j = 0; j < width - 2; ++j){
            con_set_pos(x_start + j, y_start * i);
            printf("%c", row_ascii);
        }
    }
    x_start = x + width/rows;
    y_start = y + 1;
    for(int i = 0; i <= rows; ++i){
        for(int j = 0; j < height - 2; ++j){
            con_set_pos(x_start * i, y_start + j);
            printf("%c", column_ascii);
        }
    }
}
void insert_element (Ball_list **list, int is_random, int color_number, int x, int y){
    Coordinates temp_location;
    Ball_list *element = malloc(sizeof(Ball_list));
    if(ball_count + 1 > ROW_COUNT * ROW_COUNT){
        return;
    }
    if(is_random){
        temp_location.x = rand() % ROW_COUNT;
        temp_location.y= rand() % ROW_COUNT;
        while(search_ball(*list, temp_location) == 1){
            temp_location.x = rand() % ROW_COUNT;
            temp_location.y= rand() % ROW_COUNT;
        }
        element->coordinates.x = temp_location.x;
        element->coordinates.y = temp_location.y;
        element->color = (rand() % (6 - 1) + 1);
        element->next = *(list);
        *(list) = element;
    }
    else{
        element->coordinates.x = x;
        element->coordinates.y = y;
        element->color = color_number;
        element->next = *(list);
        *(list) = element;
    }
    ++ball_count;
}
int search_ball (Ball_list *list, Coordinates location){
    Ball_list *temp = list;
    while(temp != NULL){
        if(temp->coordinates.x == location.x && temp->coordinates.y == location.y){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
void display_balls (Ball_list *list){
    Ball_list *temp = list;
    Coordinates location;
    while(temp != NULL){
        location = ball_ascii_location(temp);
        con_set_pos(location.x, location.y);
        con_set_color(0, temp->color);
        printf("O");
        temp = temp->next;
    }
}
Coordinates ball_ascii_location (Ball_list *list){
    Coordinates ascii_location;
    ascii_location.x = list->coordinates.x * ROW_MULTIPLIER + ROW_START_LOCATION;
    ascii_location.y = list->coordinates.y * COLUMN_MULTIPLIER + COLUMN_START_LOCATION;

    return ascii_location;
}
void destroy_list (Ball_list **list){
    Ball_list *copy = *(list);
    while(copy != NULL){
        copy = copy->next;
        free(*(list));
        *(list) = copy;
    }
}
void display_menu (){
    con_clear();
    printf("\n1. Continue previous game\n");
    printf("2. New game\n");
    printf("3. Exit\n");
    printf("4. Controls\n");
    printf("5. Highscores");
}
void game_loop (Ball_list *ball){
    Coordinates *balls_to_delete;
    int is_ball = 0;
    int result;
    while(1){
        display_score(score);
        if(select_square(ball, is_ball) == 0){
            is_ball = 1;
        }
        if(select_square(ball, is_ball) == 1){
            is_ball = 0;
        }
        result = update_score(ball);
        if(!result){
            for(int i = 0; i < 3; ++i){
                insert_element(&ball, 1, 0, 0, 0);
            }            
        }
        else if(result >= 5){
            delete_used_balls(result, ball);
        }
        score += result;
        draw_grid(0, 0, GRID_X, GRID_Y, ROW_COUNT, ASCII1, ASCII2);
        display_balls(ball);
    }
}
void move_ball (Ball_list *ball, Coordinates move_location, Coordinates ball_location){
    Ball_list *temp = ball;
    while(temp != NULL){
        if(temp->coordinates.x == ball_location.x && temp->coordinates.y == ball_location.y){
            temp->coordinates = move_location;
        }
        temp = temp->next;
    }
    con_clear();
}
int select_square (Ball_list *list, int is_ball){
    Ball_list *temp = list;
    int is_ingame = 1;
    int x = 0;
    int y = 0;
   //int is_ball = 1;
    Coordinates ascii_location;
    Coordinates previous;
    Coordinates location;
    previous.x = x;
    previous.y = y;
    char selection;
    Coordinates pos_temp;
    ascii_location.x = ROW_START_LOCATION;
    ascii_location.y = COLUMN_START_LOCATION + 1;
    while(1){
        selection = getch();
        if(selection == 'a' && x > 0){
            --x;
        }
        else if(selection == 'd' && x < 8){
            ++x;
        }
        else if(selection == 'w' && y > 0){
            --y;
        }
        else if(selection == 's' && y < 8){
            ++y;
        }
        else if(selection == 'q'){
            quit(list, is_ingame);
        }
        previous.x = ascii_location.x;
        previous.y = ascii_location.y;
        ascii_location.x = x * ROW_MULTIPLIER + ROW_START_LOCATION;
        ascii_location.y = y * COLUMN_MULTIPLIER + COLUMN_START_LOCATION + 1;
        con_set_pos(ascii_location.x, ascii_location.y);
        con_set_color(0, 5);
        printf("_");
        location.x = x;
        location.y = y;
        con_set_pos(previous.x, previous.y);
        con_set_color(0, 0);
        printf(" ");
        if(selection == ' ' && is_ball == 0 && search_ball(temp, location)){
            is_ball = 1;
            con_set_color(1, 1);
            printf("^");
            con_set_color(0, 7);
            pos_temp = location;
            return 0;
        }
        else if(selection == ' ' && is_ball == 1 && !search_ball(temp, location)){//TODO: end loop
            is_ball = 0;
            move_ball(temp, location, pos_temp);
            return 1;
        }
    }
}
void delete_ball (Ball_list **ball, Coordinates ball_location){
    Ball_list *temp = *ball;
    Ball_list *previous;
    if(temp != NULL && temp->coordinates.x == ball_location.x && temp->coordinates.y == ball_location.y){
        *ball = temp->next;   
        free(temp);               
        return;
    }
    while (temp != NULL && (temp->coordinates.x != ball_location.x || temp->coordinates.y != ball_location.y)){
        previous = temp;
        temp = temp->next;
    }
    if(temp == NULL){
        return;
    }
    previous->next = temp->next;
    free(temp);
    --ball_count;
}
void display_score (){
    con_set_pos(75, 15);
    con_set_color(0,7);
    printf("SCORE: %d", score);
}
int update_score (Ball_list *list){
    Coordinates location;
    int counter = 0;
    int temp_color = 0;
    Ball_list *temp = list;
    Ball_list *temp2 = NULL;
    FILE *file = fopen(USED_BALLS, "w");
    if(file == NULL){
        exit(6);
    }
    while(temp != NULL){
        location.x = temp->coordinates.x;
        location.y = temp->coordinates.y;
        temp_color = temp->color;
        temp2 = list;
        if(location.y + 5 <= ROW_COUNT){
            while(search_color(location, temp2, temp_color) == 1){
                fprintf(file, "%d %d\n", location.x, location.y);
                ++location.y;
                ++counter;
            }
        }
        temp2 = list;        
        if(counter >= 5){
            fclose(file);
            return counter;
        }
        else{
            fclose(file);
            fopen(USED_BALLS, "w");
        }
        counter = 0;
        location.x = temp->coordinates.x;
        location.y = temp->coordinates.y;
        if(location.x + 5 <= ROW_COUNT){
            while(search_color(location, temp2, temp_color) == 1){
                fprintf(file, "%d %d\n", location.x, location.y);
                ++location.x;
                ++counter;
            }
        }
        if(counter >= 5){
            fclose(file);
            return counter;
        }
        else{
            fclose(file);
            fopen(USED_BALLS, "w");
        }
        temp2 = list;
        counter = 0;
        location.x = temp->coordinates.x;
        location.y = temp->coordinates.y;
        if(location.x + 5 <= ROW_COUNT && location.y + 5 <= ROW_COUNT){
            while(search_color(location, temp2, temp_color) == 1){
                fprintf(file, "%d %d\n", location.x, location.y);
                ++location.x;
                ++location.y;
                ++counter;
            }
        }
        if(counter >= 5){
            fclose(file);
            return counter;
        }
        else{
            fclose(file);
            fopen(USED_BALLS, "w");
        }
        temp2 = list;
        counter = 0;
        location.x = temp->coordinates.x;
        location.y = temp->coordinates.y;
        if(location.x - 4 >= 0 && location.y + 5 <= ROW_COUNT){
            while(search_color(location, temp2, temp_color) == 1){
                fprintf(file, "%d %d\n", location.x, location.y);
                --location.x;
                ++location.y;
                ++counter;
            }

        }
        if(counter >= 5){
            fclose(file);
            return counter;
        }
        else{
            fclose(file);
            fopen(USED_BALLS, "w");
        }
        temp = temp->next;
        counter = 0;     
    }
    fclose(file);
    return 0;
}
int search_color (Coordinates coords, Ball_list *list, int color){
    Ball_list *temp = list;
    while(temp != NULL){
        if(temp->coordinates.x == coords.x && temp->coordinates.y == coords.y && temp->color == color){
          return 1;
        }
        temp = temp->next;
    }
    return 0;
}
void menu_loop (Ball_list *ball){
    display_menu();
    con_set_pos(0, 30);
    printf("\nChoose: ");
    int is_ingame = 0;
    while(1){
        char selection;
        selection = getch();
        if(selection == '1'){
            load_state(&ball, score);
            con_clear();
            con_show_cursor(0);
            draw_grid(0, 0, GRID_X, GRID_Y, ROW_COUNT, ASCII1, ASCII2);
            display_balls(ball);
            con_set_color(0, 0);
            game_loop(ball);
        }
        else if(selection == '2'){
            con_clear();
            con_show_cursor(0);
            skip_turn(ball);
            for(int i = 0; i < 3; ++i){
                insert_element(&ball, 1, 0, 0, 0);
            }
            draw_grid(0, 0, GRID_X, GRID_Y, ROW_COUNT, ASCII1, ASCII2);
            display_balls(ball);
            con_set_color(0, 0);
            game_loop(ball);
        }
        if(selection == '3'){
            quit(ball, is_ingame);
        }
        else if(selection == '4'){
            display_controls();
        }
        else if(selection == '5'){
            display_highscore();
        }
    }
}
void quit (Ball_list *list, int is_ingame){
    con_clear();
    con_show_cursor(1);
    save_state(list, score);
    destroy_list(&list);
    if(is_ingame){
        menu_loop(list);
    }
    else{
        save_highscore();
        exit(0);
    }
}
void skip_turn (Ball_list *temp){
    for(int i = 0; i < 3; ++i){
        insert_element(&temp, 1, 0, 0, 0);
    }
}
void program_duration (void){
    clock_t end = clock();
    double duration = ((double)(end - start)/1000);
    FILE *file = fopen(LOG_FILE, "a");
    if(file == NULL){
        exit(5);
    }
    fprintf(file, "%.2lf\n", duration);
    printf("The game ran for: %.2lfs", duration);
    fclose(file);
}
void delete_used_balls (int used_count, Ball_list *list){
    Coordinates location;
    printf("opa2");
    if(used_count == 0){
        return;
    }
    FILE *file = fopen(USED_BALLS, "r");
    if(file == NULL){
        exit(7);
    }
    int i = 0;
    while(i != used_count){
        fscanf(file, "%d %d", &location.x, &location.y);
        delete_ball(&list, location);
        ++i;
    }
    fclose(file);
    fopen(USED_BALLS, "w");
    fclose(file);
}
void display_controls (){
    con_set_pos(0, 17);
    printf("\nMove up: W\n");
    printf("Move down: S\n");
    printf("Move right: D\n");
    printf("Move left: A\n");
    printf("Select square/ball: Spacebar\n");
    printf("Quit to menu: q");
}
void save_highscore (){
    if(score >= 5){
        FILE *score_file = fopen(HIGHSCORES, "a");
        if(score_file == NULL){
            return;
        }
        fprintf(score_file, "%d ", score);
        fclose(score_file);
    }
}
int *load_highscore (){
    FILE *score_file = fopen(HIGHSCORES, "r");
    if(score_file == NULL){
        return NULL;
    }
    fseek(score_file, 0, SEEK_END);
    long file_size = ftell(score_file);
    if(file_size == 0){
        fclose(score_file);
        return NULL;
    }
    rewind(score_file);
    int *scores;
    int i = 0;
    int temp;
    scores = malloc(sizeof(int));
    while (fscanf(score_file, "%d", &temp) != EOF) {
        scores[i] = temp;
        i++;
        scores = realloc(scores, sizeof(int)*(i+1));
    }
    fclose(score_file);
    return scores;
}
void display_highscore (){
    char selection;
    int *scores = load_highscore();
    con_clear();
    if(scores == NULL){
        printf("There are no scores registered\n");
    }
    else{
        int size = sizeof(scores)/sizeof(scores[0]);
        quicksort(scores, 0, size - 1); 
        for(int i = 0; i < size; ++i){
            printf("%d. %d\n", i+1, scores[i]);
        }
    }
    free(scores);
    printf("\n\nPress q to return to menu");
    while(selection != 'q'){
        selection = getch();
    }
    quit(NULL, 1);
}
void quicksort (int *scores, int left, int right){
    int i = left, j = right;
    int pivot = scores[(left + right) / 2];
    int temp;

    while (i <= j) {
        while (scores[i] > pivot) {
            i++;
        }
        while (scores[j] < pivot) {
            j--;
        }
        if (i <= j) {
            temp = scores[i];
            scores[i] = scores[j];
            scores[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j) {
        quicksort(scores, left, j);
    }
    if (i < right) {
        quicksort(scores, i, right);
    }
}