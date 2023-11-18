#include "lines.h"
const char *save_file = "save.bin";

void save_state (Ball_list *list, int score){
    FILE *file = fopen(save_file, "wb");
    if(file == NULL){
        exit(1);
    }
    fwrite(&score, sizeof(score), 1, file);
    while(list != NULL){
        fwrite(&list->coordinates.x, sizeof(list->coordinates.x), 1, file);
        fwrite(&list->coordinates.y, sizeof(list->coordinates.y), 1, file);
        fwrite(&list->color, sizeof(list->color), 1, file);
        list = list->next;
    }
    fclose(file);
}
void load_state (Ball_list **list, int score){

    FILE *file = fopen(save_file, "rb");
    if(file == NULL){
      exit(3);
    }
    Ball_list temp;
    temp.next = NULL;   
    fread(&score, sizeof(score), 1, file);
    while(fread(&temp.coordinates.x, sizeof(temp.coordinates.x), 1, file) && fread(&temp.coordinates.y, sizeof(temp.coordinates.y), 1, file) && fread(&temp.color, sizeof(temp.color), 1, file)){ 
      insert_element(list, 0, temp.color, temp.coordinates.x, temp.coordinates.y);
    }
    fclose(file);
}
