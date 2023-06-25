#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEDICINES 100

struct Medicine {
    char name[50];
    int quantity;
    float price;
};

struct Pharmacy {
    struct Medicine medicines[MAX_MEDICINES];
    int count;
};



void saveMedicinesToFile(struct Pharmacy* pharmacy) {
    FILE* file = fopen("medicines.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < pharmacy->count; i++) {
        fprintf(file, "%s %d %.2f\n",
                pharmacy->medicines[i].name,
                pharmacy->medicines[i].quantity,
                pharmacy->medicines[i].price);
    }

    fclose(file);
}

void loadMedicinesFromFile(struct Pharmacy* pharmacy) {
    FILE* file = fopen("medicines.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    pharmacy->count = 0;

    while (!feof(file) && pharmacy->count < MAX_MEDICINES) {
        fscanf(file, "%s %d %f\n",
               pharmacy->medicines[pharmacy->count].name,
               &pharmacy->medicines[pharmacy->count].quantity,
               &pharmacy->medicines[pharmacy->count].price);
        pharmacy->count++;
    }

    fclose(file);
}


void addMedicine(struct Pharmacy* pharmacy) {
    if (pharmacy->count >= MAX_MEDICINES) {
        printf("Cannot add more medicines. Maximum limit reached.\n");
        return;
    }

    struct Medicine newMedicine;

    printf("Enter medicine name: ");
    scanf("%s", newMedicine.name);
    printf("Enter quantity: ");
    scanf("%d", &newMedicine.quantity);
    printf("Enter price: ");
    scanf("%f", &newMedicine.price);

    pharmacy->medicines[pharmacy->count] = newMedicine;
    pharmacy->count++;

    printf("Medicine added successfully.\n");
    saveMedicinesToFile(pharmacy);
}

void sellMedicine(struct Pharmacy* pharmacy) {
    char medicineName[50];

    printf("Enter medicine name to sell: ");
    scanf("%s", medicineName);

    for (int i = 0; i < pharmacy->count; i++) {
        if (strcmp(pharmacy->medicines[i].name, medicineName) == 0) {
            int quantityToSell;
            printf("Enter quantity to sell: ");
            scanf("%d", &quantityToSell);

            if (quantityToSell > pharmacy->medicines[i].quantity) {
                printf("Insufficient quantity in stock.\n");
                return;
            }

            float totalAmount = quantityToSell * pharmacy->medicines[i].price;
            printf("Total amount to be paid: $%.2f\n", totalAmount);

            pharmacy->medicines[i].quantity -= quantityToSell;
            printf("Medicine sold successfully.\n");
            saveMedicinesToFile(pharmacy);

            return;
        }
    }

    printf("Medicine not found.\n");
}

void displayMedicines(struct Pharmacy* pharmacy) {
    printf("Medicine Name\t\tQuantity\t\tPrice\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < pharmacy->count; i++) {
        printf("%-20s\t%-10d\t\t$%.2f\n",
               pharmacy->medicines[i].name,
               pharmacy->medicines[i].quantity,
               pharmacy->medicines[i].price);
    }

    printf("---------------------------------------------------\n");
}

