#include "text_editor.h"

// Load file ke buffer
int file_load(TextBuffer *buffer, const char *filename) {
    if (!buffer || !filename) return 0;
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Tidak dapat membuka file '%s'\n", filename);
        return 0;
    }
    
    // Kosongkan buffer dulu
    buffer_clear(buffer);
    
    char line[MAX_LINE_LENGTH];
    int line_loaded = 0;
    
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // Hapus newline di akhir jika ada
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        if (!buffer_add_line(buffer, line)) {
            printf("Error: Gagal menambahkan baris ke buffer\n");
            fclose(file);
            return 0;
        }
        line_loaded++;
    }
    
    fclose(file);
    
    // Set filename
    if (buffer->filename) {
        free(buffer->filename);
    }
    buffer->filename = (char*)malloc((strlen(filename) + 1) * sizeof(char));
    strcpy(buffer->filename, filename);
    
    buffer->modified = 0;
    
    printf("Berhasil memuat %d baris dari '%s'\n", line_loaded, filename);
    return 1;
}

// Simpan buffer ke file
int file_save(TextBuffer *buffer, const char *filename) {
    if (!buffer) return 0;
    
    // Jika filename tidak diberikan, gunakan filename dari buffer
    const char *target_file = filename ? filename : buffer->filename;
    
    if (!target_file) {
        printf("Error: Nama file tidak ditentukan\n");
        return 0;
    }
    
    FILE *file = fopen(target_file, "w");
    if (!file) {
        printf("Error: Tidak dapat membuka file '%s' untuk ditulis\n", target_file);
        return 0;
    }
    
    // Tulis semua baris ke file
    for (int i = 0; i < buffer->line_count; i++) {
        fprintf(file, "%s\n", buffer->lines[i]);
    }
    
    fclose(file);
    
    // Update filename jika berbeda
    if (filename && (!buffer->filename || strcmp(buffer->filename, filename) != 0)) {
        if (buffer->filename) {
            free(buffer->filename);
        }
        buffer->filename = (char*)malloc((strlen(filename) + 1) * sizeof(char));
        strcpy(buffer->filename, filename);
    }
    
    buffer->modified = 0;
    
    printf("Berhasil menyimpan %d baris ke '%s'\n", buffer->line_count, target_file);
    return 1;
}

// Simpan buffer ke file baru (Save As)
int file_save_as(TextBuffer *buffer, const char *filename) {
    if (!buffer || !filename) return 0;
    
    return file_save(buffer, filename);
}