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

// ---------------- FUNCTION DEFINITIONS ----------------

void showMenu() {
    cout << "\n--- Hotel Room Booking System ---\n";
    cout << "1. View All Rooms\n";
    cout << "2. Book Room\n";
    cout << "3. Cancel Booking\n";
    cout << "4. View Available Rooms\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
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
    cout << "\nAll Room Status:\n";
    for (int i = 0; i < totalRooms; i++) {
        cout << "Room " << rooms[i].roomNumber
             << " | " << rooms[i].roomType
             << " | " << rooms[i].pricePerDay << " ETB | ";

        if (rooms[i].isBooked)
            cout << "Booked by " << rooms[i].guestName << endl;
        else
            cout << "Available\n";
    }
}

void bookRoom(Room* rooms, int totalRooms) {
    int roomChoice, days;
    string name;
    long long id;

    cout << "Enter Fayda ID: ";
    cin >> id;

    for (int i = 0; i < totalRooms; i++) {
        if (rooms[i].isBooked && rooms[i].faydaID == id) {
            cout << "This Fayda ID already has a booking.\n";
            return;
        }
    }

    cout << "Enter room number to book: ";
    cin >> roomChoice;

    if (roomChoice < 1 || roomChoice > totalRooms ||
        rooms[roomChoice - 1].isBooked) {
        cout << "Invalid or already booked room.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter guest name: ";
    getline(cin, name);

    cout << "Enter number of days: ";
    cin >> days;

    rooms[roomChoice - 1].guestName = name;
    rooms[roomChoice - 1].faydaID = id;
    rooms[roomChoice - 1].days = days;
    rooms[roomChoice - 1].isBooked = true;

    double totalCost = rooms[roomChoice - 1].pricePerDay * days;

    cout << "Room booked successfully!\n";
    cout << "Total cost: " << totalCost << " ETB\n";

    ofstream file("bookings.txt", ios::app);
    file << "Room " << roomChoice
         << ", Name: " << name
         << ", Fayda ID: " << id
         << ", Days: " << days
         << ", Total: " << totalCost << " ETB\n";
    file.close();
}

void cancelBooking(Room* rooms, int totalRooms) {
    int roomChoice;

    cout << "Enter room number to cancel booking: ";
    cin >> roomChoice;

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

void viewAvailableRooms(Room* rooms, int totalRooms) {
    cout << "\nAvailable Rooms:\n";
    for (int i = 0; i < totalRooms; i++) {
        if (!rooms[i].isBooked) {
            cout << "Room " << rooms[i].roomNumber
                 << " | " << rooms[i].roomType
                 << " | " << rooms[i].pricePerDay << " ETB\n";
        }
    }
}



int main() {
    int totalRooms;

    cout << "Enter total number of rooms: ";
    cin >> totalRooms;

    Room* rooms = new Room[totalRooms];

    initializeRooms(rooms, totalRooms);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                viewAllRooms(rooms, totalRooms);
                break;
            case 2:
                bookRoom(rooms, totalRooms);
                break;
            case 3:
                cancelBooking(rooms, totalRooms);
                break;
            case 4:
                viewAvailableRooms(rooms, totalRooms);
                break;
            case 5:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    delete[] rooms;
    rooms = nullptr;

    return 0;
}
