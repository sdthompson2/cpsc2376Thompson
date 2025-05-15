#include <iostream>
#include <stdio.h>

#define ROWS 6
#define COLS 7

enum GameState { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };
enum Player { PLAYER_1 = 'X', PLAYER_2 = 'O' };

void makeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

void play(char board[ROWS][COLS], int column, char token) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][column] == ' ') {
            board[i][column] = token;
            break;
        }
    }
}

enum GameState gameStatus(char board[ROWS][COLS]) {
  
}

int getValidColumn(char board[ROWS][COLS]) {
    int column;
    while (1) {
        printf("Enter a column (0-6): ");
        scanf("%d", &column);
        if (column >= 0 && column < COLS && board[0][column] == ' ') {
            break;
        }
        printf("Invalid column. Try again.\n");
    }
    return column;
}

void printRules() {
    printf("Let's play CONNECT FOUR!\n");
    printf("Players take turns dropping tokens into a column.\n");
    printf("The first player to get four tokens in a row wins!\n");
}

int askToPlayAgain() {
    char response;
    printf("Want to play again? (y/n): ");
    scanf(" %c", &response);
    return (response == 'y' || response == 'Y');
}

int main() {
    char board[ROWS][COLS];
    enum GameState state;
    char currentPlayer = PLAYER_1;

    printRules();

    do {
        makeBoard(board);
        state = ONGOING;

        while (state == ONGOING) {
            printBoard(board);
            int column = getValidColumn(board);
            play(board, column, currentPlayer);
            state = gameStatus(board);

            if (state == ONGOING) {
                currentPlayer = (currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1;
            }
        }

        printBoard(board);
        if (state == PLAYER_1_WINS) {
            printf("Player 1 wins!\n");
        }
        else if (state == PLAYER_2_WINS) {
            printf("Player 2 wins!\n");
        }
        else {
            printf("Tied!\n");
        }
    } while (askToPlayAgain());

    printf("Thanks for playing!\n");
    return 0;
}