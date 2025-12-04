#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define FILE_NAME "expenses.txt"

typedef struct {
    char description[50];
    float amount;
} Expense;

Expense expenses[MAX_EXPENSES];
int count = 0;

// Function prototypes
void addExpense();
void viewExpenses();
void saveExpenses();
void loadExpenses();
void totalExpenses();

int main() {
    int choice;
    loadExpenses(); // Load stored data on start

    do {
        printf("\n=== Expense Tracking System ===\n");
        printf("1. Add Expense\n");
        printf("2. View All Expenses\n");
        printf("3. Total Expenses\n");
        printf("4. Save Expenses\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: totalExpenses(); break;
            case 4: saveExpenses(); break;
            case 5: saveExpenses(); printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while(choice != 5);

    return 0;
}

void addExpense() {
    if (count >= MAX_EXPENSES) {
        printf("Expense list full!\n");
        return;
    }

    printf("Enter description: ");
    getchar();  // Clear newline
    fgets(expenses[count].description, 50, stdin);
    expenses[count].description[strcspn(expenses[count].description, "\n")] = 0;

    printf("Enter amount: ");
    scanf("%f", &expenses[count].amount);

    count++;
    printf("Expense added successfully!\n");
}

void viewExpenses() {
    if (count == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\n--- All Expenses ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - $%.2f\n", i + 1, expenses[i].description, expenses[i].amount);
    }
}

void totalExpenses() {
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }
    printf("Total Expenses: $%.2f\n", total);
}

void saveExpenses() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error saving file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%f\n", expenses[i].description, expenses[i].amount);
    }

    fclose(file);
    printf("Expenses saved successfully!\n");
}

void loadExpenses() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) return;  // No saved data yet

    while (!feof(file) && count < MAX_EXPENSES) {
        fscanf(file, "%49[^,],%f\n", expenses[count].description, &expenses[count].amount);
        count++;
    }

    fclose(file);
}
