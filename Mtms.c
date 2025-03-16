#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SEATS 100
#define MAX_NAME_LENGTH 50
#define MAX_MOVIES 100 


typedef struct Movie {
    char name[MAX_NAME_LENGTH];
    int totalSeats;
    int availableSeats;
    float ticketPrice;
    int seats[MAX_SEATS];
    struct Movie* next; 
} Movie;

Movie* createMovie(char* name, int totalSeats, float ticketPrice);
void addMovie(Movie** head, char* name, int totalSeats, float ticketPrice);
void displayMovies(Movie* head);
void bookTickets(Movie* head);
void cancelTickets(Movie* head);
void saveMoviesToFile(Movie* head);
void loadMoviesFromFile(Movie** head);
void freeMovies(Movie* head);
void displaySeatLayout(Movie* movie);

int main() {
    Movie* head = NULL; 
    int choice;

    loadMoviesFromFile(&head); 

    while (1) {
        printf("\nMovie Ticket Management System\n");
        printf("1. Add Movie\n");
        printf("2. Display Movies\n");
        printf("3. Book Ticket\n");
        printf("4. Cancel Ticket\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1: {
                char name[MAX_NAME_LENGTH];
                int totalSeats;
                float ticketPrice;

                printf("Enter movie name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0; 

                printf("Enter total seats (max %d): ", MAX_SEATS);
                scanf("%d", &totalSeats);
                if (totalSeats > MAX_SEATS) {
                    printf("Total seats cannot exceed %d.\n", MAX_SEATS);
                    break;
                }

                printf("Enter ticket price: ");
                scanf("%f", &ticketPrice);
                if (ticketPrice < 0) {
                    printf("Ticket price cannot be negative.\n");
                    break;
                }

                addMovie(&head, name, totalSeats, ticketPrice);
                break;
            }
            case 2:
                displayMovies(head);
                break;
            case 3:
                bookTickets(head);
                break;
            case 4:
                cancelTickets(head);
                break;
            case 5:
                saveMoviesToFile(head);
                freeMovies(head);
                printf("Exiting the system.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

Movie* createMovie(char* name, int totalSeats, float ticketPrice) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (!newMovie) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newMovie->name, name);
    newMovie->totalSeats = totalSeats;
    newMovie->availableSeats = totalSeats;
    newMovie->ticketPrice = ticketPrice;
    for (int i = 0; i < totalSeats; i++) {
        newMovie->seats[i] = 0; 
    }
    newMovie->next = NULL;
    return newMovie;
}

void addMovie(Movie** head, char* name, int totalSeats, float ticketPrice) {
    Movie* newMovie = createMovie(name, totalSeats, ticketPrice);
    newMovie->next = *head;
    *head = newMovie;
    printf("Movie '%s' added successfully!\n", name);
}

void displayMovies(Movie* head) {
    if (head == NULL) {
        printf("No movies available.\n");
        return;
    }
    printf("\nAvailable Movies:\n");
    Movie* current = head;
    while (current) {
        printf("Name: %s, Total Seats: %d, Available Seats: %d, Price: $%.2f\n",
               current->name, current->totalSeats, current->availableSeats, current->ticketPrice);
        displaySeatLayout(current);
        current = current->next;
    }
}

void displaySeatLayout(Movie* movie) {
    printf("Seat Layout for '%s':\n", movie->name);
    for (int i = 0; i < movie->totalSeats; i++) {
        printf("%c ", movie->seats[i] ? 'B' : 'A'); 
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void bookTickets(Movie* head) {
    char name[MAX_NAME_LENGTH];
    printf("Enter movie name to book tickets: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; 

    Movie* current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            int numSeats;
            printf("Enter number of seats to book: ");
            scanf("%d", &numSeats);

            if (numSeats > current->availableSeats) {
                printf("Not enough available seats!\n");
                return;
            }

            printf("Available seats:\n");
            displaySeatLayout(current);

            for (int i = 0; i < numSeats; i++) {
                int seatNumber;
                printf("Enter seat number to book (0 to %d): ", current->totalSeats - 1);
                scanf("%d", &seatNumber);

                if (seatNumber < 0 || seatNumber >= current->totalSeats || current->seats[seatNumber] == 1) {
                    printf("Invalid seat number or seat already booked. Please try again.\n");
                    i--; 
                    continue;
                }

                current->seats[seatNumber] = 1;
                printf("Successfully booked seat number %d.\n", seatNumber);
            }

            current->availableSeats -= numSeats;
            printf("Successfully booked %d seats for '%s'.\n", numSeats, current->name);
            return;
        }
        current = current->next;
    }
    printf("Movie '%s' not found.\n", name);
}

void cancelTickets(Movie* head) {
    char name[MAX_NAME_LENGTH];
    printf("Enter movie name to cancel tickets: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; 

    Movie* current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            int seatNumber;
            printf("Enter seat number to cancel (0 to %d): ", current->totalSeats - 1);
            scanf("%d", &seatNumber);

            if (seatNumber < 0 || seatNumber >= current->totalSeats || current->seats[seatNumber] == 0) {
                printf("Invalid seat number or seat already available!\n");
                return;
            }

            current->seats[seatNumber] = 0;
            current->availableSeats++;
            printf("Successfully canceled ticket for seat number %d in '%s'.\n", seatNumber, current->name);
            return;
        }
        current = current->next;
    }
    printf("Movie '%s' not found.\n", name);
}

void saveMoviesToFile(Movie* head) {
    FILE* file = fopen("movies.txt", "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }
    
    Movie* current = head;
    while (current) {
        fprintf(file, "%s,%d,%d,%.2f\n", current->name, current->totalSeats, current->availableSeats, current->ticketPrice);
        for (int i = 0; i < current->totalSeats; i++) {
            fprintf(file, "%d ", current->seats[i]); 
        }
        fprintf(file, "\n");
        current = current->next;
    }
    
    fclose(file);
    printf("Movies saved to file successfully.\n");
}

void loadMoviesFromFile(Movie** head) {
    FILE* file = fopen("movies.txt", "r");
    if (!file) {
        printf("No saved data found. Starting fresh.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char name[MAX_NAME_LENGTH];
        int totalSeats, availableSeats;
        float ticketPrice;

        sscanf(line, "%[^,],%d,%d,%f", name, &totalSeats, &availableSeats, &ticketPrice);

        Movie* newMovie = createMovie(name, totalSeats, ticketPrice);
        newMovie->availableSeats = availableSeats;
        for (int i = 0; i < totalSeats; i++) {
            fscanf(file, "%d", &newMovie->seats[i]); 
        }
        newMovie->next = *head; 
        *head = newMovie;
    }

    fclose(file);
    printf("Movies loaded from file successfully.\n");
}

void freeMovies(Movie* head) {
    while (head) {
        Movie* temp = head;
        head = head->next;
        free(temp);
    }
}

