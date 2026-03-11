#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[9];
char current_player = 'X';
int mode = 1; 

void resetboard() {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
    current_player = 'X';
}

void asciiart() {
    printf("================================================================================\n");
    printf ("████████╗██╗ ██████╗    ████████╗ █████╗  ██████╗    ████████╗ ██████╗ ███████╗\n");
    printf ("╚══██╔══╝██║██╔════╝    ╚══██╔══╝██╔══██╗██╔════╝    ╚══██╔══╝██╔═══██╗██╔════╝\n");
    printf ("   ██║   ██║██║            ██║   ███████║██║            ██║   ██║   ██║█████╗  \n");
    printf ("   ██║   ██║██║            ██║   ██╔══██║██║            ██║   ██║   ██║██╔══╝  \n");
    printf ("   ██║   ██║╚██████╗       ██║   ██║  ██║╚██████╗       ██║   ╚██████╔╝███████╗\n");
    printf ("   ╚═╝   ╚═╝ ╚═════╝       ╚═╝   ╚═╝  ╚═╝ ╚═════╝       ╚═╝    ╚═════╝ ╚══════╝\n");                                                                           
    printf("                               TIC TAC TOE GAME                                 \n");
    printf("================================================================================\n\n");
}

void displayboard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
    printf("\n");
}

void switchplayer() {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

int checkwin() {
    int win[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (int i = 0; i < 8; i++) {
        if (board[win[i][0]] == current_player &&
            board[win[i][1]] == current_player &&
            board[win[i][2]] == current_player)
            return 1;
    }
    return 0;
}

int checkdraw() {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O')
            return 0;
    }
    return 1;
}

void bot_easy_move() {
    int choice;
    while (1) {
        choice = rand() % 9;
        if (board[choice] != 'X' && board[choice] != 'O') {
            board[choice] = 'O';
            break;
        }
    }
}

int main() {
    int choice;
    char playagain;

    srand(time(NULL));
    resetboard();

    system("clear");
    asciiart();

    printf("Pilih Mode:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs Bot (Easy)\n");
    printf("Pilihan: ");
    scanf("%d", &mode);

    do {
        resetboard();

        while (1) {
            system("clear");
            asciiart();
            displayboard();

            if (mode == 2 && current_player == 'O') {
                printf("Bot sedang berpikir...\n");
                bot_easy_move();
            } else {
                printf("Player %c, pilih angka (1-9): ", current_player);
                scanf("%d", &choice);

                if (choice < 1 || choice > 9 ||
                    board[choice - 1] == 'X' || board[choice - 1] == 'O') {
                    printf("Pilihan tidak valid!\n");
                    getchar(); getchar();
                    continue;
                }

                board[choice - 1] = current_player;
            }

            if (checkwin()) {
                system("clear");
                asciiart();
                displayboard();
                printf("Player %c MENANG! 🎉\n", current_player);
                break;
            }

            if (checkdraw()) {
                system("clear");
                asciiart();
                displayboard();
                printf("Permainan SERI 🤝\n");
                break;
            }

            switchplayer();
        }

        printf("\nMain lagi? (y/n): ");
        scanf(" %c", &playagain);

    } while (playagain == 'y' || playagain == 'Y');

    printf("\nTerima kasih sudah bermain 💙\n");
    return 0;
}
