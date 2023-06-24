#include<stdio.h>
#include"project_lib.h"
#include"splash.h"
#include"login.h"

void recursiveLoading();
void splash();
int main() {



    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    recursiveLoading(0);
    splash();
    system("cls");

    system("E:\\nafiz1.jpg");



    struct Pharmacy pharmacy;
    pharmacy.count = 0;

    struct UserDatabase userDB;
    userDB.count = 0;

    int choice;

    loadMedicinesFromFile(&pharmacy);
    loadUsersFromFile(&userDB);

    while (1) {
        printf("Pharmacy Management System\n");
        printf("---------------------------\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Registration
                if (userDB.count >= MAX_USERS) {
                    printf("Cannot register more users. Maximum limit reached.\n");
                    break;
                }

                printf("Enter username: ");
                scanf("%s", userDB.users[userDB.count].username);

                printf("Enter password: ");
                scanf("%s", userDB.users[userDB.count].password);

                userDB.count++;
                saveUsersToFile(&userDB);

                printf("Registration successful.\n");
                break;
            case 2:
                // Login
                printf("Enter username: ");
                char username[50];
                scanf("%s", username);

                printf("Enter password: ");
                char password[50];
                scanf("%s", password);

                int loggedIn = 0;
                for (int i = 0; i < userDB.count; i++) {
                    if (strcmp(userDB.users[i].username, username) == 0 &&
                        strcmp(userDB.users[i].password, password) == 0) {
                        printf("Login successful.\n");
                        loggedIn = 1;
                        break;
                    }
                }

                if (!loggedIn) {
                    printf("Invalid username or password.\n");
                    break;
                }

                while (1) {
                    printf("\nPharmacy Management System\n");
                    printf("---------------------------\n");
                    printf("1. Add Medicine\n");
                    printf("2. Sell Medicine\n");
                    printf("3. Display Medicines\n");
                    printf("4. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addMedicine(&pharmacy);
                            break;
                        case 2:
                            sellMedicine(&pharmacy);
                            break;
                        case 3:
                            displayMedicines(&pharmacy);
                            break;
                        case 4:
                            printf("Logging out...\n");
                            loggedIn = 0;
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                            break;
                    }

                    if (!loggedIn) {
                        break;
                    }
                }

                break;
            case 3:
                printf("Exiting...\n");
                saveMedicinesToFile(&pharmacy);
                saveUsersToFile(&userDB);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\n");
    }

    return 0;
}

