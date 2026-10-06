/*
 * Course: CS-250 Data Structures and Algorithms
 * Task: Task 3 - Train Coach Navigation System 
 * Author: Laraib Fatima
 * CMS ID: 542052
 * Class: BSDS 3A
 * Date: 06-10-2026
 */

#include <iostream>
#include <string>

using namespace std;

// Node struct
struct CoachNode {
    int coachNumber;
    string coachType;
    int capacity;
    int currentPassengers;
    CoachNode* next;
    CoachNode* prev;

    CoachNode(int num, const string& type, int cap, int pass)
        : coachNumber(num), coachType(type), capacity(cap), currentPassengers(pass), next(nullptr), prev(nullptr) {}
};

// Circular Doubly Linked List Class 
class TrainSystem {
private:
    CoachNode* current;

public:
    TrainSystem() : current(nullptr) {}

    ~TrainSystem() {
        if (!current) return;
        CoachNode* head = current;
        CoachNode* temp = head;
        do {
            CoachNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
        current = nullptr;
    }

    // Adding at end of the train
    void addCoach(int num, const string& type, int cap, int pass) {
        CoachNode* newNode = new CoachNode(num, type, cap, pass);
        if (!current) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        } else {
            CoachNode* tail = current->prev;
            newNode->next = current;
            newNode->prev = tail;
            tail->next = newNode;
            current->prev = newNode;
        }
        cout << " Added Coach " << num << " (" << type << ") to the train.\n";
    }

    // Inserting After Specific Coch
    void insertCoach(int afterNum, int num, const string& type, int cap, int pass) {
        if (!current) {
            cout << "[ERROR] Train has no coaches. Adding as first coach.\n";
            addCoach(num, type, cap, pass);
            return;
        }

        CoachNode* temp = current;
        bool found = false;
        do {
            if (temp->coachNumber == afterNum) {
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!found) {
            cout << "[ERROR] Coach number " << afterNum << " not found.\n";
            return;
        }

        CoachNode* newNode = new CoachNode(num, type, cap, pass);
        CoachNode* nextCoach = temp->next;

        newNode->next = nextCoach;
        newNode->prev = temp;
        temp->next = newNode;
        nextCoach->prev = newNode;

        cout << "Inserted Coach " << num << " after Coach " << afterNum << ".\n";
    }

    // Remove Coach by coach number
    void removeCoach(int num) {
        if (!current) {
            cout << "[ERROR] Train is empty.\n";
            return;
        }

        CoachNode* temp = current;
        bool found = false;
        do {
            if (temp->coachNumber == num) {
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!found) {
            cout << "[ERROR] Coach " << num << " not found.\n";
            return;
        }

        if (temp->next == temp) {
            current = nullptr;
        } else {
            CoachNode* prevCoach = temp->prev;
            CoachNode* nextCoach = temp->next;
            prevCoach->next = nextCoach;
            nextCoach->prev = prevCoach;
            if (current == temp) {
                current = nextCoach;
            }
        }

        cout << " Coach " << temp->coachNumber << " removed from train.\n";
        delete temp;
    }

    // Move Forward
    void moveForward() {
        if (!current) {
            cout << "[ERROR] Train is empty.\n";
            return;
        }
        current = current->next;
        cout << " Moved to next Coach: " << current->coachNumber << "\n";
    }

    // Move Backward
    void moveBackward() {
        if (!current) {
            cout << "[ERROR] Train is empty.\n";
            return;
        }
        current = current->prev;
        cout << " Moved to previous Coach: " << current->coachNumber << "\n";
    }

    // Display Current Coach
    void displayCurrentCoach() const {
        if (!current) {
            cout << "[INFO] No coach selected.\n";
            return;
        }
        cout << "\n--- CURRENT COACH DETAILS ---\n";
        cout << "Coach Number       : " << current->coachNumber << "\n";
        cout << "Coach Type         : " << current->coachType << "\n";
        cout << "Passenger Capacity : " << current->capacity << "\n";
        cout << "Current Passengers : " << current->currentPassengers << "\n";
        cout << "Available Seats    : " << (current->capacity - current->currentPassengers) << "\n";
    }

    // Display Train Clockwise
    void displayTrainClockwise() const {
        if (!current) {
            cout << "Train is empty.\n";
            return;
        }
        cout << "\n--- TRAIN COACHES (CLOCKWISE) ---\n";
        CoachNode* temp = current;
        do {
            cout << "Coach #: " << temp->coachNumber << " | Type: " << temp->coachType 
                 << " | Capacity: " << temp->capacity << " | Passengers: " << temp->currentPassengers
                 << " | Available: " << (temp->capacity - temp->currentPassengers);
            if (temp == current) cout << "  <-- [CURRENT]";
            cout << "\n";
            temp = temp->next;
        } while (temp != current);
    }

    void displayTrainAnticlockwise() const {
        if (!current) {
            cout << " Train is empty.\n";
            return;
        }
        cout << "\n--- TRAIN COACHES (ANTI-CLOCKWISE) ---\n";
        CoachNode* temp = current;
        do {
            cout << "Coach #: " << temp->coachNumber << " | Type: " << temp->coachType 
                 << " | Capacity: " << temp->capacity << " | Passengers: " << temp->currentPassengers
                 << " | Available: " << (temp->capacity - temp->currentPassengers);
            if (temp == current) cout << "  <-- [CURRENT]";
            cout << "\n";
            temp = temp->prev;
        } while (temp != current);
    }

    // Search 
    void searchCoach(int num) const {
        if (!current) {
            cout << " Train is empty.\n";
            return;
        }
        CoachNode* temp = current;
        do {
            if (temp->coachNumber == num) {
                cout << "\n Coach Details:\n";
                cout << "Coach Number       : " << temp->coachNumber << "\n";
                cout << "Coach Type         : " << temp->coachType << "\n";
                cout << "Passenger Capacity : " << temp->capacity << "\n";
                cout << "Current Passengers : " << temp->currentPassengers << "\n";
                cout << "Available Seats    : " << (temp->capacity - temp->currentPassengers) << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "[ERROR] Coach number " << num << " not found.\n";
    }

    // Find Maximum Available Capacity
    void findMaxAvailableCapacity() const {
        if (!current) {
            cout << "Train is empty.\n";
            return;
        }

        CoachNode* temp = current;
        CoachNode* maxCoach = current;
        int maxAvailable = current->capacity - current->currentPassengers;

        do {
            int available = temp->capacity - temp->currentPassengers;
            if (available > maxAvailable) {
                maxAvailable = available;
                maxCoach = temp;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "\n Coach Number: " << maxCoach->coachNumber 
             << " (" << maxCoach->coachType << ") with " << maxAvailable << " available seats.\n";
    }

    // Reverse Train Direction (Pointer Manipulation Only)
    void reverseTrainDirection() {
        if (!current || current->next == current) {
            cout << " Train direction reversed (1 or 0 coaches).\n";
            return;
        }

        CoachNode* temp = current;
        do {
            CoachNode* swapTemp = temp->next;
            temp->next = temp->prev;
            temp->prev = swapTemp;
            temp = temp->prev;
        } while (temp != current);

        cout << " Reversed complete train direction via pointer updates.\n";
    }
};

int main() {
    TrainSystem train;

    int initialCount;
    cout << "========================================\n";
    cout << "  TRAIN COACH NAVIGATION SYSTEM   \n";
    cout << "========================================\n";
    cout << "Enter initial number of coaches: ";
    cin >> initialCount;

    for (int i = 0; i < initialCount; i++) {
        int num, cap, pass;
        string type;
        cout << "\n--- Entering Coach " << (i + 1) << " Details ---\n";
        cout << "Coach Number: ";
        cin >> num;
        cin.ignore();
        cout << "Coach Type (Economy/Business/Sleeper): ";
        getline(cin, type);
        cout << "Passenger Capacity: ";
        cin >> cap;
        cout << "Current Passengers: ";
        cin >> pass;
        train.addCoach(num, type, cap, pass);
    }

    int choice;
    do {
        cout << "\n========================================\n";
        cout << "               TRAIN MENU               \n";
        cout << "========================================\n";
        cout << "1. Add Coach (At End)\n";
        cout << "2. Insert Coach After Coach Number\n";
        cout << "3. Remove Coach by Number\n";
        cout << "4. Move Forward\n";
        cout << "5. Move Backward\n";
        cout << "6. Display Current Coach\n";
        cout << "7. Display Train Clockwise\n";
        cout << "8. Display Train Anti-clockwise\n";
        cout << "9. Search Coach\n";
        cout << "10. Find Maximum Available Capacity\n";
        cout << "11. Reverse Train Direction\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int num, cap, pass;
                string type;
                cout << "Enter Coach Number: ";
                cin >> num;
                cin.ignore();
                cout << "Enter Coach Type: ";
                getline(cin, type);
                cout << "Enter Passenger Capacity: ";
                cin >> cap;
                cout << "Enter Current Passengers: ";
                cin >> pass;
                train.addCoach(num, type, cap, pass);
                break;
            }
            case 2: {
                int afterNum, num, cap, pass;
                string type;
                cout << "Enter Coach Number to insert after: ";
                cin >> afterNum;
                cout << "Enter New Coach Number: ";
                cin >> num;
                cin.ignore();
                cout << "Enter Coach Type: ";
                getline(cin, type);
                cout << "Enter Passenger Capacity: ";
                cin >> cap;
                cout << "Enter Current Passengers: ";
                cin >> pass;
                train.insertCoach(afterNum, num, type, cap, pass);
                break;
            }
            case 3: {
                int num;
                cout << "Enter Coach Number to remove: ";
                cin >> num;
                train.removeCoach(num);
                break;
            }
            case 4:
                train.moveForward();
                break;
            case 5:
                train.moveBackward();
                break;
            case 6:
                train.displayCurrentCoach();
                break;
            case 7:
                train.displayTrainClockwise();
                break;
            case 8:
                train.displayTrainAnticlockwise();
                break;
            case 9: {
                int num;
                cout << "Enter Coach Number to search: ";
                cin >> num;
                train.searchCoach(num);
                break;
            }
            case 10:
                train.findMaxAvailableCapacity();
                break;
            case 11:
                train.reverseTrainDirection();
                break;
            case 0:
                cout << "Exiting Train Navigation System...\n";
                break;
            default:
                cout << "[ERROR] Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}