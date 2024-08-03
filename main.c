#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>//For character classification and transformation operations
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char OPPONENT = 'O';

void resetBoard();
void printBoard(); // prints the board to the console
int checkFreeSpaces(); // checks the number of empty spaces on the board and returns
void playerMove(); // takes a move from the player and checks whether it is a valid move. If it is a valid move, it places it on the board
void opponentMove(); // it allows the computer to make a random move
char checkWinner(); //controls a game-winning situation. It checks horizontal, vertical and diagonal triples and returns its symbol if there is a winner
void printWinner(char); // prints the winner or draw status on the screen

int main() {
    char winner = ' ';
    char playAgain = ' ';

    do {    // This loop controls whether the player wants to play again.
        winner = ' ';
        playAgain = ' ';
        resetBoard();// function resets the board
        // continues until a winner is found or all empty fields are filled
        while (winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();// the board is printed

            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }

            opponentMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }

        printBoard();
        printWinner(winner);

        printf("\nDo you want to play again? (Y/N): ");
        scanf(" %c", &playAgain);  // Added a space before %c to ignore newline character
        playAgain = toupper(playAgain);
    } while (playAgain == 'Y');

    printf("Thanks for playing!");

    return 0;
}

void resetBoard() { // resets the board by filling it with empty spaces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() { // prints the board to the console
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreeSpaces() {  // checks the number of empty spaces on the board and returns
    int freeSpaces = 9;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }

    return freeSpaces;
}

void playerMove() { // takes a move from the player and checks whether it is a valid move. If it is a valid move, it places it on the board
    int x;
    int y;

    do {
        printf("Enter row (1-3): ");
        scanf("%d", &x);
        x--;// because, let the number I entered be 2. so it will be 1 from 2-1. we do this because there is an array
        printf("Enter column (1-3): ");
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ') {
            printf("Invalid move!\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
}

void opponentMove() { // it allows the computer to make a random move
    srand(time(0));              // It chooses random positions until it finds an empty space and places the move on the board
    int x;
    int y;

    if (checkFreeSpaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        board[x][y] = OPPONENT;
    } else {
        printWinner(' ');
    }
}

char checkWinner() {  //controls a game-winning situation. It checks horizontal, vertical and diagonal triples and returns its symbol if there is a winner
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) { // checks columns with the for loop
            return board[0][i];
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) { // checks lines with the for loop
            return board[i][0];
        }
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {  // checks crossed
        return board[0][0];
    }

    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {  // checks crossed
        return board[0][2];
    }

    return ' ';
}

void printWinner(char winner) { // prints the winner or draw status on the screen
    if (winner == PLAYER) {
        printf("You win!");
    } else if (winner == OPPONENT) {
        printf("You lose!");
    } else {
        printf("It's a tie!");
    }
}
