#include "text_editor.h"

TextBuffer* buffer_create() {
    TextBuffer *buffer = (TextBuffer*)malloc(sizeof(TextBuffer));
    if (!buffer) return NULL;
    
    buffer->capacity = 100;
    buffer->lines = (char**)malloc(buffer->capacity * sizeof(char*));
    if (!buffer->lines) {
        free(buffer);
        return NULL;
    }
    
    buffer->line_count = 0;
    buffer->current_line = 0;
    buffer->filename = NULL;
    buffer->modified = 0;
    
    return buffer;
}

void buffer_destroy(TextBuffer *buffer) {
    if (!buffer) return;
    
    for (int i = 0; i < buffer->line_count; i++) {
        free(buffer->lines[i]);
    }
    free(buffer->lines);
    
    if (buffer->filename) {
        free(buffer->filename);
    }
    
    free(buffer);
}

int buffer_add_line(TextBuffer *buffer, const char *line) {
    if (!buffer || !line) return 0;
    
    if (buffer->line_count >= buffer->capacity) {
        buffer->capacity *= 2;
        char **new_lines = (char**)realloc(buffer->lines, buffer->capacity * sizeof(char*));
        if (!new_lines) return 0;
        buffer->lines = new_lines;
    }
    
    buffer->lines[buffer->line_count] = (char*)malloc((strlen(line) + 1) * sizeof(char));
    if (!buffer->lines[buffer->line_count]) return 0;
    
    strcpy(buffer->lines[buffer->line_count], line);
    buffer->line_count++;
    buffer->modified = 1;
    
    return 1;
}

int buffer_insert_line(TextBuffer *buffer, int line_num, const char *line) {
    if (!buffer || !line || line_num < 0 || line_num > buffer->line_count) return 0;
    
    if (buffer->line_count >= buffer->capacity) {
        buffer->capacity *= 2;
        char **new_lines = (char**)realloc(buffer->lines, buffer->capacity * sizeof(char*));
        if (!new_lines) return 0;
        buffer->lines = new_lines;
    }
    
    for (int i = buffer->line_count; i > line_num; i--) {
        buffer->lines[i] = buffer->lines[i-1];
    }
    
    buffer->lines[line_num] = (char*)malloc((strlen(line) + 1) * sizeof(char));
    if (!buffer->lines[line_num]) return 0;
    
    strcpy(buffer->lines[line_num], line);
    buffer->line_count++;
    buffer->modified = 1;
    
    return 1;
}

int buffer_delete_line(TextBuffer *buffer, int line_num) {
    if (!buffer || line_num < 0 || line_num >= buffer->line_count) return 0;
    
    free(buffer->lines[line_num]);
    
    for (int i = line_num; i < buffer->line_count - 1; i++) {
        buffer->lines[i] = buffer->lines[i+1];
    }
    
    buffer->line_count--;
    buffer->modified = 1;
    
    return 1;
}

int buffer_modify_line(TextBuffer *buffer, int line_num, const char *new_line) {
    if (!buffer || !new_line || line_num < 0 || line_num >= buffer->line_count) return 0;
    
    free(buffer->lines[line_num]);
    
    buffer->lines[line_num] = (char*)malloc((strlen(new_line) + 1) * sizeof(char));
    if (!buffer->lines[line_num]) return 0;
    
    strcpy(buffer->lines[line_num], new_line);
    buffer->modified = 1;
    
    return 1;
}

void buffer_display(TextBuffer *buffer) {
    if (!buffer) return;
    
    if (buffer->line_count == 0) {
        printf("\n[Buffer kosong]\n");
        return;
    }
    
    printf("\n");
    printf("====================================\n");
    for (int i = 0; i < buffer->line_count; i++) {
        printf("%4d | %s\n", i + 1, buffer->lines[i]);
    }
    printf("====================================\n");
    printf("Total: %d baris\n", buffer->line_count);
}

void buffer_clear(TextBuffer *buffer) {
    if (!buffer) return;
    
    for (int i = 0; i < buffer->line_count; i++) {
        free(buffer->lines[i]);
    }
    
    buffer->line_count = 0;
    buffer->modified = 1;
}