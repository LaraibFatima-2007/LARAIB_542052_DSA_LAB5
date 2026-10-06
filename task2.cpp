/*
 * Course: CS-250 Data Structures and Algorithms
 * Task: Task 2 - Circular Photo Album 
 * Author: Laraib Fatima
 * CMS ID: 542052
 * Class: BSDS 3A
 * Date: 06-10-2026
 */

#include <iostream>
#include <string>

using namespace std;

// Node struct
struct PhotoNode {
    int photoID;
    string photoName;
    string dateTaken;
    string location;
    PhotoNode* next;
    PhotoNode* prev;

    PhotoNode(int id, const string& name, const string& date, const string& loc)
        : photoID(id), photoName(name), dateTaken(date), location(loc), next(nullptr), prev(nullptr) {}
};

// Circular Doubly Linked List Class 
class PhotoAlbum {
private:
    PhotoNode* current;

public:
    PhotoAlbum() : current(nullptr) {}

    ~PhotoAlbum() {
        if (!current) return;
        PhotoNode* head = current;
        PhotoNode* temp = head;
        do {
            PhotoNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
        current = nullptr;
    }

    // Adding at end  before current
    void addPhoto(int id, const string& name, const string& date, const string& loc) {
        PhotoNode* newNode = new PhotoNode(id, name, date, loc);
        if (!current) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        } else {
            PhotoNode* tail = current->prev;
            newNode->next = current;
            newNode->prev = tail;
            tail->next = newNode;
            current->prev = newNode;
        }
        cout << " Added Photo '" << name << "' (ID: " << id << ") to album.\n";
    }

    // Inserting Photo After Current
    void insertPhotoAfterCurrent(int id, const string& name, const string& date, const string& loc) {
        if (!current) {
            addPhoto(id, name, date, loc);
            return;
        }
        PhotoNode* newNode = new PhotoNode(id, name, date, loc);
        PhotoNode* nextPhoto = current->next;

        newNode->next = nextPhoto;
        newNode->prev = current;
        current->next = newNode;
        nextPhoto->prev = newNode;

        cout << "Inserted Photo '" << name << "' after current photo.\n";
    }

    // Removing Photo by ID
    void removePhoto(int id) {
        if (!current) {
            cout << "[ERROR] Album is empty.\n";
            return;
        }

        PhotoNode* temp = current;
        bool found = false;

        do {
            if (temp->photoID == id) {
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!found) {
            cout << "[ERROR] Photo with ID " << id << " not found.\n";
            return;
        }

        if (temp->next == temp) {
            current = nullptr;
        } else {
            PhotoNode* prevPhoto = temp->prev;
            PhotoNode* nextPhoto = temp->next;
            prevPhoto->next = nextPhoto;
            nextPhoto->prev = prevPhoto;
            if (current == temp) {
                current = nextPhoto;
            }
        }

        cout << "Photo '" << temp->photoName << "' (ID: " << id << ") deleted.\n";
        delete temp;
    }

    // Removing Current Photo
    void removeCurrentPhoto() {
        if (!current) {
            cout << "[ERROR] Album is empty.\n";
            return;
        }
        removePhoto(current->photoID);
    }

    void moveNext() {
        if (!current) {
            cout << "[ERROR] Album is empty.\n";
            return;
        }
        current = current->next;
        cout << " Switched to Next Photo: " << current->photoName << "\n";
    }

    // Move Previous
    void movePrevious() {
        if (!current) {
            cout << "[ERROR] Album is empty.\n";
            return;
        }
        current = current->prev;
        cout << " Switched to Previous Photo: " << current->photoName << "\n";
    }

    // Display Album Forward
    void displayAlbumForward() const {
        if (!current) {
            cout << " Album is empty.\n";
            return;
        }
        cout << "\n--- PHOTO ALBUM (FORWARD) ---\n";
        PhotoNode* temp = current;
        do {
            cout << "ID: " << temp->photoID << " | Name: " << temp->photoName 
                 << " | Date: " << temp->dateTaken << " | Location: " << temp->location;
            if (temp == current) cout << "  <-- [SELECTED]";
            cout << "\n";
            temp = temp->next;
        } while (temp != current);
    }

    // Display Album Backward
    void displayAlbumBackward() const {
        if (!current) {
            cout << " Album is empty.\n";
            return;
        }
        cout << "\n--- PHOTO ALBUM (BACKWARD) ---\n";
        PhotoNode* temp = current;
        do {
            cout << "ID: " << temp->photoID << " | Name: " << temp->photoName 
                 << " | Date: " << temp->dateTaken << " | Location: " << temp->location;
            if (temp == current) cout << "  <-- [SELECTED]";
            cout << "\n";
            temp = temp->prev;
        } while (temp != current);
    }

    // Search Photo by ID
    void searchPhoto(int id) const {
        if (!current) {
            cout << " Album is empty.\n";
            return;
        }
        PhotoNode* temp = current;
        do {
            if (temp->photoID == id) {
                cout << "\n[FOUND] Photo Details:\n";
                cout << "ID      : " << temp->photoID << "\n";
                cout << "Name    : " << temp->photoName << "\n";
                cout << "Date    : " << temp->dateTaken << "\n";
                cout << "Location: " << temp->location << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "[ERROR] Photo with ID " << id << " not found.\n";
    }

    // Count Photos
    int countPhotos() const {
        if (!current) return 0;
        int count = 0;
        PhotoNode* temp = current;
        do {
            count++;
            temp = temp->next;
        } while (temp != current);
        return count;
    }
};

int main() {
    PhotoAlbum album;

    int initialCount;
    cout << "========================================\n";
    cout << "      CIRCULAR PHOTO ALBUM        \n";
    cout << "========================================\n";
    cout << "Enter initial number of photos to add: ";
    cin >> initialCount;

    for (int i = 0; i < initialCount; i++) {
        int id;
        string name, date, loc;
        cout << "\n--- Entering Photo " << (i + 1) << " Details ---\n";
        cout << "Photo ID: ";
        cin >> id;
        cin.ignore();
        cout << "Photo Name: ";
        getline(cin, name);
        cout << "Date Taken (DD/MM/YYYY): ";
        getline(cin, date);
        cout << "Location: ";
        getline(cin, loc);
        album.addPhoto(id, name, date, loc);
    }

    int choice;
    do {
        cout << "\n========================================\n";
        cout << "             ALBUM MENU                 \n";
        cout << "========================================\n";
        cout << "1. Add Photo (At End)\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo by ID\n";
        cout << "4. Remove Currently Selected Photo\n";
        cout << "5. Move Next Photo\n";
        cout << "6. Move Previous Photo\n";
        cout << "7. Display Album Forward\n";
        cout << "8. Display Album Backward\n";
        cout << "9. Search Photo by ID\n";
        cout << "10. Count Total Photos\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name, date, loc;
                cout << "Enter Photo ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Photo Name: ";
                getline(cin, name);
                cout << "Enter Date Taken: ";
                getline(cin, date);
                cout << "Enter Location: ";
                getline(cin, loc);
                album.addPhoto(id, name, date, loc);
                break;
            }
            case 2: {
                int id;
                string name, date, loc;
                cout << "Enter Photo ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Photo Name: ";
                getline(cin, name);
                cout << "Enter Date Taken: ";
                getline(cin, date);
                cout << "Enter Location: ";
                getline(cin, loc);
                album.insertPhotoAfterCurrent(id, name, date, loc);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Photo ID to remove: ";
                cin >> id;
                album.removePhoto(id);
                break;
            }
            case 4:
                album.removeCurrentPhoto();
                break;
            case 5:
                album.moveNext();
                break;
            case 6:
                album.movePrevious();
                break;
            case 7:
                album.displayAlbumForward();
                break;
            case 8:
                album.displayAlbumBackward();
                break;
            case 9: {
                int id;
                cout << "Enter Photo ID to search: ";
                cin >> id;
                album.searchPhoto(id);
                break;
            }
            case 10:
                cout << " Total Photos in Album: " << album.countPhotos() << "\n";
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "[ERROR] Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}