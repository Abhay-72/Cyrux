#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayChoice(int choice) {
    if (choice == 1)
        printf("Rock");
    else if (choice == 2)
        printf("Paper");
    else if (choice == 3)
        printf("Scissors");
}

int main() {
    int userChoice, computerChoice;
    char playAgain;

    srand(time(NULL));

    do {
        printf("\nEnter 1 (Rock), 2 (Paper), or 3 (Scissors): ");
        if (scanf("%d", &userChoice) != 1 || userChoice < 1 || userChoice > 3) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            
            while (getchar() != '\n');
            continue;
        }

        if (userChoice == 1) {
            computerChoice = 3;
        } else if (userChoice == 2) {
            computerChoice = 1;
        } else if (userChoice == 3) {
            computerChoice = 2;
        }

        printf("You chose ");
        displayChoice(userChoice);
        printf(", Computer chose ");
        displayChoice(computerChoice);
        printf(".\n");

        if (userChoice == computerChoice) {
            printf("It's a tie!\n");
        } else {
            printf("You win!\n");
        }

        printf("Do you want to continue? (y/n): ");
        while (getchar() != '\n');
        playAgain = getchar();

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Game over. Thanks for playing!\n");
    return 0;
}
