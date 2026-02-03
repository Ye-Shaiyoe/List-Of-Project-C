#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_LINES 10000


typedef struct {
    char **lines;  
    int line_count;       
    int capacity;           
    int current_line;       
    char *filename;         
    int modified;           
} TextBuffer;

TextBuffer* buffer_create();
void buffer_destroy(TextBuffer *buffer);
int buffer_add_line(TextBuffer *buffer, const char *line);
int buffer_insert_line(TextBuffer *buffer, int line_num, const char *line);
int buffer_delete_line(TextBuffer *buffer, int line_num);
int buffer_modify_line(TextBuffer *buffer, int line_num, const char *new_line);
void buffer_display(TextBuffer *buffer);
void buffer_clear(TextBuffer *buffer);

int file_load(TextBuffer *buffer, const char *filename);
int file_save(TextBuffer *buffer, const char *filename);
int file_save_as(TextBuffer *buffer, const char *filename);

int search_text(TextBuffer *buffer, const char *search_str, int start_line);
int replace_text(TextBuffer *buffer, const char *search_str, const char *replace_str, int replace_all);
void search_display_results(TextBuffer *buffer, const char *search_str);

void editor_run(TextBuffer *buffer);
void editor_display_menu();
void editor_display_status(TextBuffer *buffer);

#endif