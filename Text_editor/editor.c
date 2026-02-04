#include "text_editor.h"

// Tampilkan menu utama
void editor_display_menu() {
    printf("\n");
    printf("========== TEXT EDITOR MENU ==========\n");
    printf("1.  Tampilkan isi buffer\n");
    printf("2.  Tambah baris baru\n");
    printf("3.  Insert baris di posisi tertentu\n");
    printf("4.  Hapus baris\n");
    printf("5.  Edit baris\n");
    printf("6.  Buka file\n");
    printf("7.  Simpan file\n");
    printf("8.  Simpan sebagai (Save As)\n");
    printf("9.  Cari teks\n");
    printf("10. Replace teks\n");
    printf("11. Kosongkan buffer\n");
    printf("0.  Keluar\n");
    printf("======================================\n");
}

// Tampilkan status editor
void editor_display_status(TextBuffer *buffer) {
    printf("\nStatus: ");
    if (buffer->filename) {
        printf("File: %s | ", buffer->filename);
    } else {
        printf("File: [Belum diberi nama] | ");
    }
    printf("Baris: %d | ", buffer->line_count);
    printf("Modified: %s\n", buffer->modified ? "Ya" : "Tidak");
}

// Main editor loop
void editor_run(TextBuffer *buffer) {
    int choice;
    char input[MAX_LINE_LENGTH];
    char filename[256];
    char search_str[256];
    char replace_str[256];
    int line_num;
    
    while (1) {
        editor_display_status(buffer);
        editor_display_menu();
        printf("Pilihan: ");
        scanf("%d", &choice);
        getchar(); // Buang newline
        
        switch (choice) {
            case 1: // Tampilkan buffer
                buffer_display(buffer);
                break;
                
            case 2: // Tambah baris baru
                printf("Masukkan teks (enter untuk selesai):\n");
                while (1) {
                    printf("> ");
                    if (fgets(input, MAX_LINE_LENGTH, stdin) == NULL) break;
                    
                    // Hapus newline
                    size_t len = strlen(input);
                    if (len > 0 && input[len-1] == '\n') {
                        input[len-1] = '\0';
                    }
                    
                    // Jika baris kosong, selesai
                    if (strlen(input) == 0) break;
                    
                    if (!buffer_add_line(buffer, input)) {
                        printf("Error: Gagal menambah baris\n");
                    }
                }
                printf("Baris berhasil ditambahkan.\n");
                break;
                
            case 3: // Insert baris
                printf("Masukkan nomor baris (1-%d): ", buffer->line_count + 1);
                scanf("%d", &line_num);
                getchar();
                
                if (line_num < 1 || line_num > buffer->line_count + 1) {
                    printf("Nomor baris tidak valid!\n");
                    break;
                }
                
                printf("Masukkan teks: ");
                if (fgets(input, MAX_LINE_LENGTH, stdin) != NULL) {
                    size_t len = strlen(input);
                    if (len > 0 && input[len-1] == '\n') {
                        input[len-1] = '\0';
                    }
                    
                    if (buffer_insert_line(buffer, line_num - 1, input)) {
                        printf("Baris berhasil di-insert.\n");
                    } else {
                        printf("Error: Gagal insert baris\n");
                    }
                }
                break;
                
            case 4: // Hapus baris
                printf("Masukkan nomor baris yang akan dihapus (1-%d): ", buffer->line_count);
                scanf("%d", &line_num);
                getchar();
                
                if (buffer_delete_line(buffer, line_num - 1)) {
                    printf("Baris %d berhasil dihapus.\n", line_num);
                } else {
                    printf("Error: Gagal menghapus baris\n");
                }
                break;
                
            case 5: // Edit baris
                printf("Masukkan nomor baris yang akan diedit (1-%d): ", buffer->line_count);
                scanf("%d", &line_num);
                getchar();
                
                if (line_num < 1 || line_num > buffer->line_count) {
                    printf("Nomor baris tidak valid!\n");
                    break;
                }
                
                printf("Baris sekarang: %s\n", buffer->lines[line_num - 1]);
                printf("Masukkan teks baru: ");
                
                if (fgets(input, MAX_LINE_LENGTH, stdin) != NULL) {
                    size_t len = strlen(input);
                    if (len > 0 && input[len-1] == '\n') {
                        input[len-1] = '\0';
                    }
                    
                    if (buffer_modify_line(buffer, line_num - 1, input)) {
                        printf("Baris berhasil diubah.\n");
                    } else {
                        printf("Error: Gagal mengubah baris\n");
                    }
                }
                break;
                
            case 6: // Buka file
                if (buffer->modified) {
                    printf("Perhatian: Buffer sudah dimodifikasi!\n");
                    printf("Lanjutkan buka file? (y/n): ");
                    char confirm;
                    scanf("%c", &confirm);
                    getchar();
                    if (confirm != 'y' && confirm != 'Y') {
                        break;
                    }
                }
                
                printf("Masukkan nama file: ");
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    size_t len = strlen(filename);
                    if (len > 0 && filename[len-1] == '\n') {
                        filename[len-1] = '\0';
                    }
                    file_load(buffer, filename);
                }
                break;
                
            case 7: // Simpan file
                if (!buffer->filename) {
                    printf("Masukkan nama file: ");
                    if (fgets(filename, sizeof(filename), stdin) != NULL) {
                        size_t len = strlen(filename);
                        if (len > 0 && filename[len-1] == '\n') {
                            filename[len-1] = '\0';
                        }
                        file_save(buffer, filename);
                    }
                } else {
                    file_save(buffer, NULL);
                }
                break;
                
            case 8: // Save As
                printf("Masukkan nama file baru: ");
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    size_t len = strlen(filename);
                    if (len > 0 && filename[len-1] == '\n') {
                        filename[len-1] = '\0';
                    }
                    file_save_as(buffer, filename);
                }
                break;
                
            case 9: // Cari teks
                printf("Masukkan kata kunci pencarian: ");
                if (fgets(search_str, sizeof(search_str), stdin) != NULL) {
                    size_t len = strlen(search_str);
                    if (len > 0 && search_str[len-1] == '\n') {
                        search_str[len-1] = '\0';
                    }
                    search_display_results(buffer, search_str);
                }
                break;
                
            case 10: // Replace teks
                printf("Masukkan teks yang akan di-replace: ");
                if (fgets(search_str, sizeof(search_str), stdin) == NULL) break;
                size_t len = strlen(search_str);
                if (len > 0 && search_str[len-1] == '\n') {
                    search_str[len-1] = '\0';
                }
                
                printf("Masukkan teks pengganti: ");
                if (fgets(replace_str, sizeof(replace_str), stdin) == NULL) break;
                len = strlen(replace_str);
                if (len > 0 && replace_str[len-1] == '\n') {
                    replace_str[len-1] = '\0';
                }
                
                printf("Replace semua? (y/n): ");
                char replace_all_choice;
                scanf("%c", &replace_all_choice);
                getchar();
                
                int count = replace_text(buffer, search_str, replace_str, 
                                        (replace_all_choice == 'y' || replace_all_choice == 'Y'));
                printf("Berhasil meng-replace %d kemunculan.\n", count);
                break;
                
            case 11: // Kosongkan buffer
                printf("Yakin ingin mengosongkan buffer? (y/n): ");
                char confirm;
                scanf("%c", &confirm);
                getchar();
                if (confirm == 'y' || confirm == 'Y') {
                    buffer_clear(buffer);
                    printf("Buffer berhasil dikosongkan.\n");
                }
                break;
                
            case 0: // Keluar
                if (buffer->modified) {
                    printf("Buffer belum disimpan! Yakin keluar? (y/n): ");
                    char exit_confirm;
                    scanf("%c", &exit_confirm);
                    getchar();
                    if (exit_confirm != 'y' && exit_confirm != 'Y') {
                        break;
                    }
                }
                printf("Terima kasih telah menggunakan Text Editor!\n");
                return;
                
            default:
                printf("Pilihan tidak valid!\n");
        }
        
        printf("\nTekan Enter untuk melanjutkan...");
        getchar();
    }
}