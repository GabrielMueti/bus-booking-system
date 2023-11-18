#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 10
#define MAX_NAME_LENGTH 20
#define MAX_EMPLOYEES 10
#define MAX_BOOKINGS 34
#define MAX_SEATS_PER_BUS 36
#define MAX_BOOKING_HISTORY 50

struct Employee {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
};

struct Bus {
    char bus_id[MAX_NAME_LENGTH];
    char route[MAX_NAME_LENGTH];
    char departure_time[MAX_NAME_LENGTH];
    int seats[MAX_SEATS_PER_BUS];
    int num_seats;
};

struct Booking {
    char username[MAX_NAME_LENGTH];
    char bus_id[MAX_NAME_LENGTH];
    int seat_number;
};

struct BookingHistory {
    char username[MAX_NAME_LENGTH];
    char bus_id[MAX_NAME_LENGTH];
    int seat_number;
    char date[MAX_NAME_LENGTH];
};

struct Employee employees[MAX_EMPLOYEES];
int numEmployees = 0;

struct Bus buses[MAX_BUSES];
int numBuses = 0;

struct Booking bookings[MAX_BOOKINGS];
int numBookings = 0;

struct BookingHistory bookingHistory[MAX_BOOKING_HISTORY];
int numBookingHistory = 0;

// Function to add a new employee
void addEmployee(char username[], char password[]) {
    if (numEmployees < MAX_EMPLOYEES) {
        strcpy(employees[numEmployees].username, username);
        strcpy(employees[numEmployees].password, password);
        numEmployees++;
        printf("Employee added successfully!\n");
    } else {
        printf("Employee limit reached. Cannot add more employees.\n");
    }
}

// Function to validate employee login
int validateLogin(char username[], char password[]) {
    for (int i = 0; i < numEmployees; i++) {
        if (strcmp(employees[i].username, username) == 0 && strcmp(employees[i].password, password) == 0) {
            return 1; // Successful login
        }
    }
    return 0; // Login failed
}
// Function to manage bus schedules (Add, Delete, Modify, View)
void manageBusSchedules() {
    int choice;
    char username[MAX_NAME_LENGTH];
    char bus_id[MAX_NAME_LENGTH];

    do {
        printf("\nBus Schedule Management\n");
        printf("1. Add Bus Schedule\n");
        printf("2. Delete Bus Schedule\n");
        printf("3. Modify Bus Schedule\n");
        printf("4. View Bus Schedules\n");
        printf("5. Exit Bus Schedule Management\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (numBuses < MAX_BUSES) {
                    struct Bus newBus;
                    printf("Enter Bus ID: ");
                    scanf("%s", newBus.bus_id);

                    printf("Select a route:\n");
                    printf("1. Mombasa to Nairobi-3.00pm\n");
                    printf("2. Nairobi to Mombasa-4.00pm\n");
                    printf("3. Nyeri to Nairobi-2.00pm\n");
                    printf("Choose route:");
                    int route_choice;
                    scanf("%d", &route_choice);

                    // Set the route and departure time based on the user's choice
                    switch (route_choice) {
                        case 1:
                            strcpy(newBus.route, "Mombasa to Nairobi");
                            strcpy(newBus.departure_time, "3pm");
                            break;
                        case 2:
                            strcpy(newBus.route, "Nairobi to Mombasa");
                            strcpy(newBus.departure_time, "4pm");
                            break;
                        case 3:
                            strcpy(newBus.route, "Nyeri to Nairobi");
                            strcpy(newBus.departure_time, "2pm");
                            break;
                        default:
                            printf("Invalid route choice. Using a default route and departure time.\n");
                            strcpy(newBus.route, "Unknown Route");
                            strcpy(newBus.departure_time, "Unknown Time");
                    }

                    // Initialize seats as available
                    for (int i = 0; i < MAX_SEATS_PER_BUS; i++) {
                        newBus.seats[i] = 0;
                    }
                    newBus.num_seats = MAX_SEATS_PER_BUS;

                    buses[numBuses++] = newBus;
                    printf("Bus schedule added successfully!\n");
                } else {
                    printf("Bus schedule limit reached. Cannot add more schedules.\n");
                }
                break;
            case 2:
                printf("Enter Bus ID to delete: ");
                scanf("%s", bus_id);
                int found = 0;
                for (int i = 0; i < numBuses; i++) {
                    if (strcmp(buses[i].bus_id, bus_id) == 0) {
                        for (int j = i; j < numBuses - 1; j++) {
                            buses[j] = buses[j + 1];
                        }
                        numBuses--;
                        found = 1;
                        printf("Bus schedule with ID '%s' deleted successfully!\n", bus_id);
                        break;
                    }
                }
                if (!found) {
                    printf("Bus schedule with ID '%s' not found.\n");
                }
                break;
            case 3:
                printf("Enter Bus ID to modify: ");
                scanf("%s", bus_id);
                found = 0;
                for (int i = 0; i < numBuses; i++) {
                    if (strcmp(buses[i].bus_id, bus_id) == 0) {
                        printf("Select a new route:\n");
                        printf("1. Mombasa to Nairobi\n");
                        printf("2. Nairobi to Mombasa\n");
                        printf("3. Nyeri to Nairobi\n");
                        int route_choice;
                        scanf("%d", &route_choice);

                        // Set the route and departure time based on the user's choice
                        switch (route_choice) {
                            case 1:
                                strcpy(buses[i].route, "Mombasa to Nairobi");
                                strcpy(buses[i].departure_time, "3pm");
                                break;
                            case 2:
                                strcpy(buses[i].route, "Nairobi to Mombasa");
                                strcpy(buses[i].departure_time, "4pm");
                                break;
                            case 3:
                                strcpy(buses[i].route, "Nyeri to Nairobi");
                                strcpy(buses[i].departure_time, "2pm");
                                break;
                            default:
                                printf("Invalid route choice. Keeping the existing route and departure time.\n");
                        }

                        found = 1;
                        printf("Bus schedule with ID '%s' modified successfully!\n", bus_id);
                        break;
                    }
                }
                if (!found) {
                    printf("Bus schedule with ID '%s' not found.\n", bus_id);
                }
                break;
            case 4:
                if (numBuses == 0) {
                    printf("No bus schedules available.\n");
                } else {
                    printf("Bus Schedules:\n");
                    for (int i = 0; i < numBuses; i++) {
                        printf("Bus ID: %s, Route: %s, Departure Time: %s, Available Seats: %d/%d\n",
                            buses[i].bus_id, buses[i].route, buses[i].departure_time,
                            buses[i].num_seats, MAX_SEATS_PER_BUS - buses[i].num_seats);
                    }
                }
                break;
            case 5:
                return; // Exit Bus Schedule Management
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (1);
}
// Function to search for buses by route and display their IDs
void searchBusesByRoute() {
    printf("Select a Route:\n");
    printf("1. Mombasa to Nyeri\n");
    printf("2. Nairobi to Mombasa\n");
    printf("3. Nyeri to Nairobi\n");
    printf("Choose route: ");
    int route_choice;
    scanf("%d", &route_choice);

    char selected_route[MAX_NAME_LENGTH];

    switch (route_choice) {
        case 1:
            strcpy(selected_route, "Mombasa to Nyeri");
            break;
        case 2:
            strcpy(selected_route, "Nairobi to Mombasa");
            break;
        case 3:
            strcpy(selected_route, "Nyeri to Nairobi");
            break;
        default:
            printf("Invalid route choice.\n");
            return;
    }

    // Search for buses based on the selected route
    printf("Matching Bus Schedules for Route '%s':\n", selected_route);
    int found = 0;
    for (int i = 0; i < numBuses; i++) {
        if (strstr(buses[i].route, selected_route) != NULL) {
            printf("Bus ID: %s\n", buses[i].bus_id);
            found = 1;
        }
    }

    if (!found) {
        printf("No buses found for Route '%s'.\n", selected_route);
    }
}
//function to view seats
void viewAvailableSeats(char bus_id[]) {
    int found = 0;
    for (int i = 0; i < numBuses; i++) {
        if (strcmp(buses[i].bus_id, bus_id) == 0) {
            printf("Available Seats for Bus ID '%s':\n", bus_id);
            printf("Right Side \tLeft Side \n");

            for (int seat = 0; seat < 36; seat += 4) {
                for (int j = seat; j < seat + 4; j++) {
                    if (buses[i].seats[j] == 0) {
                        printf("%d\t", j + 1);
                    } else {
                        printf("X\t");
                    }
                }
                printf("\n");
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Bus ID '%s' not found.\n", bus_id);
    }
}

// Function to book a seat for a customer and issue ticket
void bookSeat(char username[], char bus_id[], int seat_number) {
    for (int i = 0; i < numBuses; i++) {
        if (strcmp(buses[i].bus_id, bus_id) == 0) {
            if (seat_number >= 1 && seat_number <= MAX_SEATS_PER_BUS) {
                if (seat_number <= 34 && buses[i].seats[seat_number - 1] == 0) {
                    buses[i].seats[seat_number - 1] = 1;
                    buses[i].num_seats--;
                    struct Booking newBooking;
                    strcpy(newBooking.username, username);
                    strcpy(newBooking.bus_id, bus_id);
                    newBooking.seat_number = seat_number;
                    bookings[numBookings++] = newBooking;

                    // Issue a ticket automatically
                    printf("Ticket Details:\n");
                    printf("Username: %s\n", username);
                    printf("Bus ID: %s\n", bus_id);
                    printf("Seat Number: %d\n", seat_number);

                    // Record the booking in the booking history
                    struct BookingHistory history;
                    strcpy(history.username, username);
                    strcpy(history.bus_id, bus_id);
                    history.seat_number = seat_number;

                    strcpy(history.date, "your_date");

                    bookingHistory[numBookingHistory++] = history;

                    printf("Seat %d on Bus ID '%s' booked successfully!\n", seat_number, bus_id);
                } else {
                    printf("Seat %d on Bus ID '%s' is either already booked or out of range (beyond 50).\n", seat_number, bus_id);
                }
            } else {
                printf("Invalid seat number. Please choose a seat number between 1 and %d.\n", MAX_SEATS_PER_BUS);
            }
            return;
        }
    }
    printf("Bus schedule with ID '%s' not found.\n", bus_id);
}
// Function to cancel a booking
void cancelBooking(char username[], char bus_id[], int seat_number) {
    for (int i = 0; i < numBookings; i++) {
        if (strcmp(bookings[i].username, username) == 0 && strcmp(bookings[i].bus_id, bus_id) == 0 && bookings[i].seat_number == seat_number) {
            for (int j = i; j < numBookings - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            numBookings--;
            for (int k = 0; k < numBuses; k++) {
                if (strcmp(buses[k].bus_id, bus_id) == 0) {
                    buses[k].seats[seat_number - 1] = 0;
                    buses[k].num_seats++;
                    printf("Booking for Seat %d on Bus ID '%s' canceled successfully!\n", seat_number, bus_id);

                    return;
                }
            }
        }
    }
    printf("No booking found for Username: %s, Bus ID: %s, Seat Number: %d\n", username, bus_id, seat_number);
}
// Function to display booking history for a specific user
void displayBookingHistory(char username[]) {
    printf("Booking History for User: %s\n", username);
    for (int i = 0; i < numBookingHistory; i++) {
        if (strcmp(bookingHistory[i].username, username) == 0) {
            printf("Bus ID: %s, Seat Number: %d\n",
                   bookingHistory[i].bus_id, bookingHistory[i].seat_number);
        }
    }
}


// Function to save data to a file
void saveDataToFile(void *data, size_t data_size, size_t num_data, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(data, data_size, num_data, file);
    fclose(file);
    printf("Data saved to file '%s'.\n", filename);
}

// Function to list available data files
void listAvailableDataFiles() {
    printf("Available data files:\n");
    printf("1. employees.txt\n");
    printf("2. buses.txt\n");
    // List other data files here
    // ...

    printf("Enter the number of the file you want to load: ");
}

// Function to load data from a file
void loadDataFromFile(void *data, size_t data_size, size_t num_data, char *filename, int viewData) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    fread(data, data_size, num_data, file);
    fclose(file);

    printf("Data loaded from file '%s'.\n", filename);

    if (viewData) {
        // Print the loaded data to the console
        for (size_t i = 0; i < num_data; i++) {
            if (data_size == sizeof(struct Employee)) {
                struct Employee *employee = ((struct Employee *)data) + i;
                printf("Username: %s, Password: %s\n", employee->username, employee->password);
            } else if (data_size == sizeof(struct Bus)) {
                struct Bus *bus = ((struct Bus *)data) + i;
                printf("Bus ID: %s, Route: %s, Departure Time: %s\n", bus->bus_id, bus->route, bus->departure_time);
            }
            // Add similar print statements for other data structures as needed
        }
    }
}


int main() {
    int choice;
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    char bus_id[MAX_NAME_LENGTH];
    char origin[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    int seat_number;

    // Sample employee records
    addEmployee("john", "amari");

    do {
        printf("\nBus Reservation and Management System\n");
        printf("1. Employee Login\n");
        printf("2. Manage Bus Schedule\n");
        printf("3. Search for Buses by Route\n");
        printf("4. View Available Seats\n");
        printf("5. Book a Seat and issue ticket\n");
        printf("6. Cancel Booking\n");
        printf("7. View Booking History\n");
        printf("8. Save data\n");
        printf("9. Load data\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                if (validateLogin(username, password)) {
                    printf("Login successful!\n");

                } else {
                    printf("Login failed. Invalid username or password.\n");
                }
                break;
            case 2:
                manageBusSchedules();
                break;
            case 3:
                searchBusesByRoute();
                break;
            case 4:
                printf("Enter Bus ID to view available seats: ");
                scanf("%s", bus_id);
                viewAvailableSeats(bus_id);
                break;
            case 5:
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Bus ID: ");
                scanf("%s", bus_id);
                printf("Enter Seat Number: ");
                scanf("%d", &seat_number);
                bookSeat(username, bus_id, seat_number);
                break;
            case 6:
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Bus ID: ");
                scanf("%s", bus_id);
                printf("Enter Seat Number: ");
                scanf("%d",&seat_number);
                cancelBooking(username,bus_id,seat_number);
                break;
            case 7:
               printf("Enter Username to view booking history: ");
               scanf("%s", username);
              displayBookingHistory(username);
               break;
                 case 8:
                // Save data to files
                saveDataToFile(employees, sizeof(struct Employee), numEmployees, "employees.txt");
                saveDataToFile(buses, sizeof(struct Bus), numBuses, "buses.txt");
                // Save bookings and booking history similarly
                break;
                case 9:
    // List available data files
    listAvailableDataFiles();
    int file_choice;
    scanf("%d", &file_choice);

    switch (file_choice) {
        case 1:
            loadDataFromFile(employees, sizeof(struct Employee), numEmployees, "employees.txt", 1);
            break;
        case 2:
            loadDataFromFile(buses, sizeof(struct Bus), numBuses, "buses.txt", 1);
            break;
        default:
            printf("Invalid file choice. Please select a valid file.\n");
    }
    break;

            case 10:
                printf("Exiting the program\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 10);

    return 0;
}




