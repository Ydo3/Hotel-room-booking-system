#include <iostream>
#include <string>
#include <fstream>
#include <limits> // For numeric_limits

using namespace std;

// Structure to store room information
struct Room {
    int roomNumber;
    bool isBooked;
    string guestName;
    long long faydaID;       // Ethiopian national ID
    string roomType;
    int days;
    double pricePerDay;       // Price in ETB
};

int main() {
    int totalRooms;

    cout << "Enter total number of rooms: ";
    cin >> totalRooms;

    // Dynamic memory allocation
    Room* rooms = new Room[totalRooms];

    // Initialize rooms
    for (int i = 0; i < totalRooms; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = false;
        rooms[i].guestName = "";
        rooms[i].faydaID = 0;
        rooms[i].days = 0;

        // Assign room types and prices
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

    int choice;

    do {
        cout << "\n--- Hotel Room Booking System ---\n";
        cout << "1. View All Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. Cancel Booking\n";
        cout << "4. View Available Rooms\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            // Case 1: View all rooms
            case 1:
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
                break;

            // Case 2: Book room
            case 2: {
                int roomChoice, days;
                string name;
                long long id;
                bool alreadyBooked = false;

                cout << "Enter Fayda ID: ";
                cin >> id;

                // Check if Fayda ID already booked
                for (int i = 0; i < totalRooms; i++) {
                    if (rooms[i].isBooked && rooms[i].faydaID == id) {
                        cout << "This Fayda ID already has a booking.\n";
                        alreadyBooked = true;
                        break;
                    }
                }

                if (alreadyBooked)
                    break;

                cout << "Enter room number to book: ";
                cin >> roomChoice;

                // Check valid room number
                if (roomChoice < 1 || roomChoice > totalRooms ||
                    rooms[roomChoice - 1].isBooked) {
                    cout << "Invalid or already booked room.\n";
                    break;
                }

                // Flush input buffer before getline
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

                // Save to file
                ofstream file("bookings.txt", ios::app);
                file << "Room " << roomChoice
                     << ", Name: " << name
                     << ", Fayda ID: " << id
                     << ", Days: " << days
                     << ", Total: " << totalCost << " ETB\n";
                file.close();

                break;
            }

            // Case 3: Cancel booking
            case 3: {
                int roomChoice;
                cout << "Enter room number to cancel booking: ";
                cin >> roomChoice;

                if (roomChoice < 1 || roomChoice > totalRooms ||
                    !rooms[roomChoice - 1].isBooked) {
                    cout << "Invalid cancellation.\n";
                    break;
                }

                rooms[roomChoice - 1].isBooked = false;
                rooms[roomChoice - 1].guestName = "";
                rooms[roomChoice - 1].faydaID = 0;
                rooms[roomChoice - 1].days = 0;

                cout << "Booking cancelled successfully.\n";
                break;
            }

            // Case 4: View available rooms
            case 4:
                cout << "\nAvailable Rooms:\n";
                for (int i = 0; i < totalRooms; i++) {
                    if (!rooms[i].isBooked) {
                        cout << "Room " << rooms[i].roomNumber
                             << " | " << rooms[i].roomType
                             << " | " << rooms[i].pricePerDay << " ETB\n";
                    }
                }
                break;

            // Case 5: Exit
            case 5:
                cout << "Exiting system...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    // Free dynamically allocated memory
    delete[] rooms;
    rooms = nullptr;

    return 0;
}



