#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void initializeSeats(bool* seats, int totalSeats) {
    for (int i = 0; i < totalSeats; ++i) {
        seats[i] = true;
    }
}

void displayAvailableSeats(bool* seats, int totalSeats) {
    printf("Available Seats:\n");
    for (int i = 0; i < totalSeats; ++i) {
        if (seats[i]) {
            printf("Seat %d is available.\n", i + 1);
        } else {
            printf("Seat %d is booked.\n", i + 1);
        }
    }
}

void reserveSeat(bool* seats, int seatNumber, int totalSeats) {
    if (seatNumber >= 1 && seatNumber <= totalSeats) {
        if (seats[seatNumber - 1]) {
            seats[seatNumber - 1] = false;
            printf("Seat %d reserved successfully.\n", seatNumber);
        } else {
            printf("Seat %d is already booked.\n", seatNumber);
        }
    } else {
        printf("Invalid seat number.\n");
    }
}

int main() {
    const int TOTAL_SEATS = 10;
    bool* seats = (bool*)malloc(TOTAL_SEATS * sizeof(bool));
    initializeSeats(seats, TOTAL_SEATS);

    while (true) {
        printf("\n1. View Available Seats\n2. Reserve a Seat\n3. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAvailableSeats(seats, TOTAL_SEATS);
                break;
            case 2:
                {
                    int seatNumber;
                    printf("Enter the seat number you want to reserve: ");
                    scanf("%d", &seatNumber);
                    reserveSeat(seats, seatNumber, TOTAL_SEATS);
                }
                break;
            case 3:
                free(seats);
                printf("Thank you for using the bus reservation system. Have a nice day!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}