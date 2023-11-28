#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define MAX_NAME_LENGTH 50

typedef struct {
    int row;
    int col;
    int reserved;
    char customerName[MAX_NAME_LENGTH];
    int age;
    char gender;
} Seat;

void initializeSeatingChart(Seat seatingChart[MAX_ROWS][MAX_COLS]);
void displaySeatingChart(Seat seatingChart[MAX_ROWS][MAX_COLS]);
void gatherCustomerInformation(Seat seatingChart[MAX_ROWS][MAX_COLS], char name[], int *age, char *gender);
void updateSeatingChart(Seat seatingChart[MAX_ROWS][MAX_COLS], int newRow, int newCol, int oldRow, int oldCol, char name[], int age, char gender);
void confirmReservation(Seat seatingChart[MAX_ROWS][MAX_COLS], int row, int col);

int main() {
    Seat seatingChart[MAX_ROWS][MAX_COLS];
    initializeSeatingChart(seatingChart);

    int option;

    do {
        printf("\n1. Display Seating Chart\n");
        printf("2. Make Reservation\n");
        printf("3. Update Reservation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                displaySeatingChart(seatingChart);
                break;
            case 2:
                {
                    char name[MAX_NAME_LENGTH];
                    int age;
                    char gender;
                    gatherCustomerInformation(seatingChart, name, &age, &gender);
                }
                break;
            case 3:
                {
                    int newRow, newCol, oldRow, oldCol;
                    printf("Enter the current row and number for the reservation to update: ");
                    scanf("%d %d", &oldRow, &oldCol);
                    
                    if (oldRow >= 1 && oldRow <= MAX_ROWS && oldCol >= 1 && oldCol <= MAX_COLS && seatingChart[oldRow - 1][oldCol - 1].reserved) {
                        char name[MAX_NAME_LENGTH];
                        int age;
                        char gender;
                        
                        printf("Enter the new row and number for the updated reservation: ");
                        scanf("%d %d", &newRow, &newCol);
                        if (newRow >= 1 && newRow <= MAX_ROWS && newCol >= 1 && newCol <= MAX_COLS && !seatingChart[newRow - 1][newCol - 1].reserved) {
                            updateSeatingChart(seatingChart, newRow - 1, newCol - 1, oldRow - 1, oldCol - 1, name, age, gender);
                            displaySeatingChart(seatingChart);
                        } else {
                            printf("Invalid new seat selection or seat already reserved. Reservation update failed.\n");
                        }
                    } else {
                        printf("Invalid seat selection or seat not reserved. Please try again.\n");
                    }
                }
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }

    } while (option != 4);

    return 0;
}

void initializeSeatingChart(Seat seatingChart[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            seatingChart[i][j].row = i + 1;
            seatingChart[i][j].col = j + 1;
            seatingChart[i][j].reserved = 0;
            strcpy(seatingChart[i][j].customerName, "");
            seatingChart[i][j].age = 0;
            seatingChart[i][j].gender = '\0';
        }
    }
}

void displaySeatingChart(Seat seatingChart[MAX_ROWS][MAX_COLS]) {
    printf("Seating Chart:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%c ", seatingChart[i][j].reserved ? 'X' : 'O');
        }
        printf("\n");
    }
}

void gatherCustomerInformation(Seat seatingChart[MAX_ROWS][MAX_COLS], char name[], int *age, char *gender) {
    int row, col;

    printf("Enter the row and number for your reservation: ");
    scanf("%d %d", &row, &col);

    if (row >= 1 && row <= MAX_ROWS && col >= 1 && col <= MAX_COLS && !seatingChart[row - 1][col - 1].reserved) {
        printf("Enter your name: ");
        scanf("%s", name);
        printf("Enter your age: ");
        scanf("%d", age);
        printf("Enter your gender (M/F): ");
        scanf(" %c", gender);

        updateSeatingChart(seatingChart, row - 1, col - 1, -1, -1, name, *age, *gender);

        confirmReservation(seatingChart, row - 1, col - 1);
    } else {
        printf("Invalid seat selection or seat already reserved. Please try again.\n");
    }
}

void updateSeatingChart(Seat seatingChart[MAX_ROWS][MAX_COLS], int newRow, int newCol, int oldRow, int oldCol, char name[], int age, char gender) {
    if (oldRow != -1 && oldCol != -1) {
        seatingChart[oldRow][oldCol].reserved = 0;
        strcpy(seatingChart[oldRow][oldCol].customerName, "");
        seatingChart[oldRow][oldCol].age = 0;
        seatingChart[oldRow][oldCol].gender = '\0';
    }

    seatingChart[newRow][newCol].reserved = 1;
    strcpy(seatingChart[newRow][newCol].customerName, name);
    seatingChart[newRow][newCol].age = age;
    seatingChart[newRow][newCol].gender = gender;
}

void confirmReservation(Seat seatingChart[MAX_ROWS][MAX_COLS], int row, int col) {
    printf("Reservation confirmed for %s! You have reserved seat %d-%d.\n",
           seatingChart[row][col].customerName, seatingChart[row][col].row, seatingChart[row][col].col);
}

