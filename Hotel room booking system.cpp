#include <iostream>
#include <string>

using namespace std;

// Structure to store room information
struct Room {
    int roomNumber;
    bool isBooked;
    string guestName;
};

int main() {
    int totalRooms;

    cout << "Enter total number of rooms: ";
    cin >> totalRooms;

    // Dynamic memory allocation for rooms (memory management + pointer)
    Room* rooms = new Room[totalRooms];

    // Initialize rooms using loop
    for (int i = 0; i < totalRooms; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = false;
        rooms[i].guestName = "";
    }

    int choice;
    string name;
    int roomChoice;

    do {
        cout << "\n--- Hotel Room Booking System ---\n";
        cout << "1. View Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nRoom Status:\n";
                for (int i = 0; i < totalRooms; i++) {
                    cout << "Room " << rooms[i].roomNumber << ": ";
                    if (rooms[i].isBooked)
                        cout << "Booked by " << rooms[i].guestName << endl;
                    else
                        cout << "Available" << endl;
                }
                break;

            case 2:
                cout << "Enter room number to book: ";
                cin >> roomChoice;

                if (roomChoice < 1 || roomChoice > totalRooms) {
                    cout << "Invalid room number.\n";
                } else if (rooms[roomChoice - 1].isBooked) {
                    cout << "Room already booked.\n";
                } else {
                    cout << "Enter guest name: ";
                    cin.ignore();
                    getline(cin, name);

                    rooms[roomChoice - 1].guestName = name;
                    rooms[roomChoice - 1].isBooked = true;

                    cout << "Room booked successfully.\n";
                }
                break;

            case 3:
                cout << "Enter room number to cancel booking: ";
                cin >> roomChoice;

                if (roomChoice < 1 || roomChoice > totalRooms) {
                    cout << "Invalid room number.\n";
                } else if (!rooms[roomChoice - 1].isBooked) {
                    cout << "Room is not booked.\n";
                } else {
                    rooms[roomChoice - 1].guestName = "";
                    rooms[roomChoice - 1].isBooked = false;

                    cout << "Booking cancelled.\n";
                }
                break;

            case 4:
                cout << "Exiting system...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    // Free dynamically allocated memory
    delete[] rooms;
    rooms = nullptr;

    return 0;
}

