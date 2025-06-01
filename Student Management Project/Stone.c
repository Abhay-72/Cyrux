#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int userChoice, computerChoice;
    srand(time(NULL));

    printf("Enter 1 (Rock), 2 (Paper), or 3 (Scissors): ");
    scanf("%d", &userChoice);

    computerChoice = rand() % 3 + 1;

    if (userChoice == computerChoice) {
        printf("Tie!");
    } else if ((userChoice == 1 && computerChoice == 3) ||
               (userChoice == 2 && computerChoice == 1) ||
               (userChoice == 3 && computerChoice == 2)) {
        printf("You win!");
    } else {
        printf("Computer wins!");
    }

    return 0;
}