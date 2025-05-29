#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct User {
    char username[50];
    char password[50];
};

struct Bus {
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
};

void speak(const char *text) {
    char command[200];
    #ifdef _WIN32
        sprintf(command, "espeak \"%s\"", text);
    #else
        sprintf(command, "espeak '%s'", text);
    #endif

    system(command);
}

int loadUsers(struct User users[], int *numUsers, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("User file not found. Creating a new file...\n");
        file = fopen(filename, "w");
        if (!file) {
            printf("Error creating file!\n");
            exit(1);
        }
        fclose(file);
        return 0;
    }

    *numUsers = 0;
    while (fscanf(file, "%s %s", users[*numUsers].username, users[*numUsers].password) == 2) {
        (*numUsers)++;
    }
    fclose(file);
    return 1;
}

void saveUsers(struct User users[], int numUsers, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error saving user data!\n");
        speak("Error saving user data");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "Username: %s, Password: %s\n", users[i].username, users[i].password);
    }
    fclose(file);
}

void displayMainMenu() {
    printf("\n========== Main Menu ==========\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Delete User\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    speak("This is main menu. Enter your choice");
}

void displayUserMenu() {
    printf("\n========== User Menu ==========\n");
    printf("1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Status\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");
    speak("this is user menu. Enter your choice.");
}

void getPassword(char *password) {
    int i = 0;
    char ch;
    printf("Enter Password: ");
    speak("Enter your password");
    while (1) {
        ch = getch();
        if (ch == '\r') {
            break;
        } else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}


int loginUser(struct User users[], int numUsers, char username[], char password[]) {
    printf("\nEnter Username: ");
    speak("Enter your username");
    scanf("%s", username);

    getPassword(password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

int registerUser(struct User users[], int *numUsers, const char *filename) {
    char username[50], password[50];

    printf("\nEnter New Username: ");
    speak("Enter your new username");
    scanf("%s", username);

    for (int i = 0; i < *numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Error: Username already exists. Try a different Username.\n");
            speak("username is already exists. try a different username");
            return 0;
        }
    }

    getPassword(password);

    strcpy(users[*numUsers].username, username);
    strcpy(users[*numUsers].password, password);
    (*numUsers)++;

    saveUsers(users, *numUsers, filename);
    printf("Registration successful! You can now log in with your new account.\n");
    speak("Registration successful you can now log in with your new account");
    return 1;
}

void deleteUser(struct User users[], int *numUsers, const char *filename) {
    char username[50];
    printf("\nEnter Username to Delete: ");
    speak("Enter username to delete");
    scanf("%s", username);

    int userIndex = -1;
    for (int i = 0; i < *numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Error: Username not found.\n");
        speak("username not found");
    } else {
        for (int i = userIndex; i < *numUsers - 1; i++) {
            users[i] = users[i + 1];
        }
        (*numUsers)--;

        saveUsers(users, *numUsers, filename);
        printf("User '%s' deleted successfully.\n", username);
        speak("User deleted successfully");
    }
}

void bookTicket(struct Bus buses[], int numBuses) {
    printf("\nEnter Bus Number: ");
    speak("Enter bus number");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus with Bus Number %d not found.\n", busNumber);
        speak("Bus not found");
    } else {
        printf("Enter Number of Seats: ");
        speak("enter numbers of seat you want to book");
        int seatsToBook;
        scanf("%d", &seatsToBook);

        if (buses[busIndex].availableSeats < seatsToBook) {
            printf("Sorry, only %d seats are available.\n", buses[busIndex].availableSeats);
            speak("Sorry, we don't have enough seat");
        } else {
            buses[busIndex].availableSeats -= seatsToBook;
            printf("Booking successful! %d seats booked on Bus Number %d.\n", seatsToBook, busNumber);
            speak("Your booking is confirmed. Have a nice journey.");

        }
    }
}

void cancelTicket(struct Bus buses[], int numBuses) {
    printf("\nEnter Bus Number: ");
    speak("Enter bus number");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus with Bus Number %d not found.\n", busNumber);
        speak("Bus not found");
    } else {
        printf("Enter Number of Seats to Cancel: ");
        speak("Enter number of seat you want to cancel");
        int seatsToCancel;
        scanf("%d", &seatsToCancel);

        if (seatsToCancel > (buses[busIndex].totalSeats - buses[busIndex].availableSeats)) {
            printf("Error: You can't cancel more seats than were booked.\n");
            speak("You can't cancel more seats than were booked");
        } else {
            buses[busIndex].availableSeats += seatsToCancel;
            printf("Cancellation successful! %d seats canceled on Bus Number %d.\n", seatsToCancel, busNumber);
            speak("Your cancellation is confirmed");
        }
    }
}

void checkBusStatus(struct Bus buses[], int numBuses) {
    printf("\nEnter Bus Number: ");
    speak("Enter bus number");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex != -1) {
        printf("\nBus Number: %d\n", buses[busIndex].busNumber);
        printf("Source: %s\n", buses[busIndex].source);
        printf("Destination: %s\n", buses[busIndex].destination);
        printf("Total Seats: %d\n", buses[busIndex].totalSeats);
        printf("Available Seats: %d\n", buses[busIndex].availableSeats);
        printf("Fare: %.2f\n", buses[busIndex].fare);
        speak("Status of your bus");
    } else {
        printf("Bus with Bus Number %d not found.\n", busNumber);
        speak("Bus not found");
    }
}

int main() {
    struct User users[100];
    int numUsers = 0;

    const char *filename = "users.txt";

    loadUsers(users, &numUsers, filename);
    struct Bus buses[3] = {
        {101, "City A", "City B", 50, 50, 500.0},
        {102, "City C", "City D", 40, 40, 400.0},
        {103, "City E", "City F", 30, 30, 300.0},
    };
    int numBuses = 3;

    int loggedInUserId = -1;

    while (1) {
        if (loggedInUserId == -1) {
            displayMainMenu();
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                char username[50];
                char password[50];

                loggedInUserId = loginUser(users, numUsers, username, password);
                if (loggedInUserId == -1) {
                    printf("Login failed. Please check your username and password.\n");
                    speak("Login failed. Please try again.");
                } else {
                    printf("Login successful. Welcome, %s!\n", username);
                    speak("Login successful. Welcome.");
                }

            } else if (choice == 2) {
                registerUser(users, &numUsers, filename);
            } else if (choice == 3) {
                deleteUser(users, &numUsers, filename);
            } else if (choice == 4) {
                printf("Exiting the program.\n");
                speak("Thank you Now we are exiting.");
                break;
            } else {
                printf("Invalid choice. Please try again.\n");
                speak("Invalid choice. Please try again.");
            }
        } else {
            displayUserMenu();
            int userChoice;
            scanf("%d", &userChoice);

            switch (userChoice) {
            case 1:
                bookTicket(buses, numBuses);
                break;
            case 2:
                cancelTicket(buses, numBuses);
                break;
            case 3:
                checkBusStatus(buses, numBuses);
                break;
            case 4:
                printf("Logging out.\n");
                speak("Logging out.");
                loggedInUserId = -1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                speak("Invalid choice. Please try again.");
            }
        }
    }
    return 0;
}