#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

struct Room {
    int roomNumber;
    bool isBooked;
    string guestName;
    long long faydaID;
    string roomType;
    int days;
    double pricePerDay;
};


int safeInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (!cin.fail())
            return value;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
    }
}

long long safeLongLong(const string& prompt) {
    long long value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (!cin.fail())
            return value;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid ID.\n";
    }
}

/*  FUNCTION DEFINITIONS */

void showMenu() {
    cout << "\n--- Hotel Room Booking System ---\n";
    cout << "1. View All Rooms\n";
    cout << "2. Book Room\n";
    cout << "3. Cancel Booking\n";
    cout << "4. View Available Rooms\n";
    cout << "5. Exit\n";
}

void initializeRooms(Room* rooms, int totalRooms) {
    for (int i = 0; i < totalRooms; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = false;
        rooms[i].guestName = "";
        rooms[i].faydaID = 0;
        rooms[i].days = 0;

        if (i % 3 == 0) {
            rooms[i].roomType = "Single";
            rooms[i].pricePerDay = 1000;
        } else if (i % 3 == 1) {
            rooms[i].roomType = "Double";
            rooms[i].pricePerDay = 1800;
        } else {
            rooms[i].roomType = "Suite";
            rooms[i].pricePerDay = 3000;
        }
    }
}

void viewAllRooms(Room* rooms, int totalRooms) {
    cout << "\nAll Rooms:\n";
    for (int i = 0; i < totalRooms; i++) {
        cout << "Room " << rooms[i].roomNumber << " | "
             << rooms[i].roomType << " | "
             << rooms[i].pricePerDay << " ETB | ";

        if (rooms[i].isBooked)
            cout << "Booked by " << rooms[i].guestName << endl;
        else
            cout << "Available\n";
    }
}

void viewAvailableRooms(Room* rooms, int totalRooms) {
    cout << "\nAvailable Rooms:\n";
    bool found = false;

    for (int i = 0; i < totalRooms; i++) {
        if (!rooms[i].isBooked) {
            found = true;
            cout << "Room " << rooms[i].roomNumber << " | "
                 << rooms[i].roomType << " | "
                 << rooms[i].pricePerDay << " ETB\n";
        }
    }

    if (!found)
        cout << "No rooms available.\n";
}

void bookRoom(Room* rooms, int totalRooms) {
    long long id = safeLongLong("Enter Fayda ID: ");

    for (int i = 0; i < totalRooms; i++) {
        if (rooms[i].isBooked && rooms[i].faydaID == id) {
            cout << "This Fayda ID already has a booking.\n";
            return;
        }
    }

    int roomChoice = safeInt("Enter room number to book: ");

    if (roomChoice < 1 || roomChoice > totalRooms ||
        rooms[roomChoice - 1].isBooked) {
        cout << "Invalid or already booked room.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name;
    cout << "Enter guest name: ";
    getline(cin, name);

    int days = safeInt("Enter number of days: ");
    if (days <= 0) {
        cout << "Days must be greater than zero.\n";
        return;
    }

    Room& r = rooms[roomChoice - 1];
    r.isBooked = true;
    r.guestName = name;
    r.faydaID = id;
    r.days = days;

    double totalCost = r.pricePerDay * days;

    cout << "Room booked successfully!\n";
    cout << "Total cost: " << totalCost << " ETB\n";

    ofstream file("bookings.txt", ios::app);
    if (file) {
        file << "Room " << r.roomNumber
             << ", Name: " << name
             << ", Fayda ID: " << id
             << ", Days: " << days
             << ", Total: " << totalCost << " ETB\n";
        file.close();
    } else {
        cout << "Warning: Booking could not be saved to file.\n";
    }
}

void cancelBooking(Room* rooms, int totalRooms) {
    int roomChoice = safeInt("Enter room number to cancel booking: ");

    if (roomChoice < 1 || roomChoice > totalRooms ||
        !rooms[roomChoice - 1].isBooked) {
        cout << "Invalid cancellation.\n";
        return;
    }

    rooms[roomChoice - 1].isBooked = false;
    rooms[roomChoice - 1].guestName = "";
    rooms[roomChoice - 1].faydaID = 0;
    rooms[roomChoice - 1].days = 0;

    cout << "Booking cancelled successfully.\n";
}

/* ---------- MAIN ---------- */

int main() {
    int totalRooms;

    while (true) {
        totalRooms = safeInt("Enter total number of rooms: ");
        if (totalRooms > 0)
            break;
        cout << "Number of rooms must be greater than zero.\n";
    }

    Room* rooms = nullptr;

    try {
        rooms = new Room[totalRooms];
    } catch (...) {
        cout << "Memory allocation failed. Exiting.\n";
        return 1;
    }

    initializeRooms(rooms, totalRooms);

    int choice;
    do {
        showMenu();
        choice = safeInt("Enter your choice: ");

        switch (choice) {
            case 1: viewAllRooms(rooms, totalRooms); break;
            case 2: bookRoom(rooms, totalRooms); break;
            case 3: cancelBooking(rooms, totalRooms); break;
            case 4: viewAvailableRooms(rooms, totalRooms); break;
            case 5: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    delete[] rooms;
    rooms = nullptr;

    return 0;
}
