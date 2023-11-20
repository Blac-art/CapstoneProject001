#include <stdio.h>
#include <string.h>

#define MAX_SEATS 10
#define MAX_BUSES 3

struct Reservation {
    char name[50];
    int seat_number;
};

struct Bus {
    char name[50];
    char route[100];
    char schedule[50];
    int available_seats;
    int price;
    int seats[MAX_SEATS];
    struct Reservation reservations[MAX_SEATS];
};

int authenticateUser() {
    char username[] = "David";
    char password[] = "1250012093";

    char inputUsername[50];
    char inputPassword[50];

    printf("Username: ");
    scanf("%s", inputUsername);
    printf("Password: ");
    scanf("%s", inputPassword);

    if (strcmp(username, inputUsername) == 0 && strcmp(password, inputPassword) == 0) {
        return 1; // Authentication successful
    } else {
        printf("Authentication failed. Exiting...\n");
        return 0; // Authentication failed
    }
}

int writeReservationsToFile(const struct Bus *bus, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return 0; // Unable to open the file
    }

    for (int i = 0; i < MAX_SEATS; ++i) {
        if (bus->seats[i] == 1) {
            fprintf(file, "%d %s\n", i + 1, bus->reservations[i].name);
        }
    }

    fclose(file);
    return 1; // Successful write
}

int readReservationsFromFile(struct Bus *bus, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // Unable to open the file
    }

    int seat;
    while (fscanf(file, "%d", &seat) == 1) {
        bus->seats[seat - 1] = 1;
        bus->available_seats--;
        fscanf(file, "%s", bus->reservations[seat - 1].name);
    }

    fclose(file);
    return 1; // Successful read
}

void displayBuses(const struct Bus *buses, int numBuses) {
    for (int i = 0; i < numBuses; ++i) {
        printf("Bus %d: %s - Route: %s, Schedule: %s, Available Seats: %d, Price: $%d\n",
               i + 1, buses[i].name, buses[i].route, buses[i].schedule, buses[i].available_seats, buses[i].price);
    }
}

void displaySeats(const struct Bus bus) {
    printf("Available seats for Bus %s:\n", bus.name);
    for (int i = 0; i < MAX_SEATS; ++i) {
        if (bus.seats[i] == 0) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

int bookSeat(struct Bus *bus, int seat_number, const char *name) {
    if (seat_number < 1 || seat_number > MAX_SEATS) {
        printf("Invalid seat number.\n");
        return 0;
    }

    if (bus->seats[seat_number - 1] == 0) {
        bus->seats[seat_number - 1] = 1;
        bus->available_seats--;
        strcpy(bus->reservations[seat_number - 1].name, name);
        bus->reservations[seat_number - 1].seat_number = seat_number;
        printf("Seat %d booked for %s on Bus %s.\n", seat_number, name, bus->name);
        return 1;
    } else {
        printf("Seat %d is already booked.\n", seat_number);
        return 0;
    }
}

void generateTicket(const struct Bus bus, int seat_number) {
    printf("Ticket for %s - Bus: %s, Route: %s, Schedule: %s, Seat: %d, Price: $%d\n",
           bus.reservations[seat_number - 1].name, bus.name, bus.route, bus.schedule, seat_number, bus.price);
}

int main() {
    struct Bus buses[MAX_BUSES] = {
        {"Bus A", "Route 1", "10:00 AM", MAX_SEATS, 50, {0}},
        {"Bus B", "Route 2", "11:30 AM", MAX_SEATS, 40, {0}},
        {"Bus C", "Route 3", "2:00 PM", MAX_SEATS, 60, {0}}
    };

    int numBuses = MAX_BUSES;

    if (!authenticateUser()) {
        return 1; // Authentication failed, exit program
    }

    int choice;
    while (1) {
        printf("\nOptions:\n");
        printf("1. Display available buses\n");
        printf("2. Display available seats for a bus\n");
        printf("3. Book a seat\n");
        printf("4. Generate ticket\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBuses(buses, numBuses);
                break;
            case 2:
                if (numBuses > 0) {
                    int busChoice;
                    printf("Select a bus (1 to %d): ", numBuses);
                    scanf("%d", &busChoice);
                    if (busChoice >= 1 && busChoice <= numBuses) {
                        displaySeats(buses[busChoice - 1]);
                    } else {
                        printf("Invalid bus selection.\n");
                    }
                } else {
                    printf("No buses available.\n");
                }
                break;
            case 3:
                if (numBuses > 0) {
                    int busChoice;
                    printf("Select a bus (1 to %d): ", numBuses);
                    scanf("%d", &busChoice);
                    if (busChoice >= 1 && busChoice <= numBuses) {
                        struct Bus *bus = &buses[busChoice - 1];
                        if (bus->available_seats > 0) {
                            int seat_number;
                            char name[50];
                            printf("Enter seat number: ");
                            scanf("%d", &seat_number);
                            printf("Enter passenger name: ");
                            scanf("%s", name);
                            bookSeat(bus, seat_number, name);
                            writeReservationsToFile(bus, "reservations.txt");
                        } else {
                            printf("All seats for Bus %s are booked. No more bookings allowed.\n", bus->name);
                        }
                    } else {
                        printf("Invalid bus selection.\n");
                    }
                } else {
                    printf("No buses available.\n");
                }
                break;
            case 4:
                if (numBuses > 0) {
                    int busChoice;
                    printf("Select a bus (1 to %d): ", numBuses);
                    scanf("%d", &busChoice);
                    if (busChoice >= 1 && busChoice <= numBuses) {
                        int seat_number;
                        printf("Enter seat number: ");
                        scanf("%d", &seat_number);
                        generateTicket(buses[busChoice - 1], seat_number);
                    } else {
                        printf("Invalid bus selection.\n");
                    }
                } else {
                    printf("No buses available.\n");
                }
                break;
            case 5:
                printf("Thank you for using the bus reservation system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
