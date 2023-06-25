#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_USERS 100



struct User {
    char username[50];
    char password[50];
};

struct UserDatabase {
    struct User users[MAX_USERS];
    int count;
};


void saveUsersToFile(struct UserDatabase* userDB) {
    FILE* file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < userDB->count; i++) {
        fprintf(file, "%s %s\n", userDB->users[i].username, userDB->users[i].password);
    }

    fclose(file);
}

void loadUsersFromFile(struct UserDatabase* userDB) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    userDB->count = 0;

    while (!feof(file) && userDB->count < MAX_USERS) {
        fscanf(file, "%s %s\n",
               userDB->users[userDB->count].username,
               userDB->users[userDB->count].password);
        userDB->count++;
    }

    fclose(file);
}
