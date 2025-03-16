
# Movie Ticket Management System

This is a simple console-based Movie Ticket Management System developed in C. It allows administrators to add movies, view available movies, book and cancel tickets, and save or load movie data from a file.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [How It Works](#how-it-works)
- [How to Run](#how-to-run)
- [Possible Improvements](#possible-improvements)
- [Author](#author)

---

## Overview

This application is a simple implementation of a movie ticket management system using the C programming language. It demonstrates the use of file handling, structures, dynamic memory allocation, and linked lists.

It provides functionality to:
- Add new movies.
- Display all movies along with their available seats.
- Book tickets for specific movies and seats.
- Cancel previously booked tickets.
- Save and load movie data using file operations.

---

## Features

- **Add Movie**: Add new movies with details such as name, total seats, and ticket price.
- **Display Movies**: View all available movies, including seat layouts showing which seats are available (A) and which are booked (B).
- **Book Tickets**: Book seats for a specific movie by selecting seat numbers.
- **Cancel Tickets**: Cancel a previously booked ticket by selecting the seat number.
- **File Handling**: Save movies and their seat bookings to a text file (`movies.txt`) and reload them when the application starts.

---

## Technologies Used

- C Programming Language
- File Handling (`fopen`, `fclose`, `fprintf`, `fscanf`, etc.)
- Linked Lists (to manage multiple movies dynamically)
- Arrays (to handle seat allocations)

---

## How It Works

### Data Structure
The core data structure is a `Movie` struct that stores:
- Movie name
- Total seats and available seats
- Ticket price
- Seat booking status using an array (`seats[]`)
- A pointer to the next movie (`next`), forming a linked list of movies

### Main Functions
- `addMovie`: Adds a new movie to the list.
- `displayMovies`: Shows all movies and their seat layouts.
- `bookTickets`: Books seats for a movie.
- `cancelTickets`: Cancels booked seats.
- `saveMoviesToFile`: Saves the movie list and seat data to a file (`movies.txt`).
- `loadMoviesFromFile`: Loads the movie list and seat data from `movies.txt` on startup.
- `freeMovies`: Frees dynamically allocated memory.

### Seat Layout Representation
- Available seat: `A`
- Booked seat: `B`

---

## How to Run

### Prerequisites
- A C compiler (GCC recommended)

### Compilation

```bash
gcc movie_ticket_system.c -o movie_ticket_system
```

### Run the Program

```bash
./movie_ticket_system
```

### On Windows

```bash
movie_ticket_system.exe
```

The program will create or load the `movies.txt` file to manage movie records.

---

## FutureImprovements

Here are some ways you could enhance the system in the future:
- Add user authentication (Admin/User login)
- Implement different seat categories (Regular, Premium, VIP)
- Improve the UI using a graphical interface (GUI)
- Include transaction history for bookings and cancellations
- Apply concurrency controls to manage simultaneous bookings (for multi-user systems)
- Export reports of bookings and movie statistics

---

## Author

**Developed By:** Pravalika Batchu
**Language:** C Programming  
**Purpose:** Academic project for learning file handling, structures, and dynamic data structures.
