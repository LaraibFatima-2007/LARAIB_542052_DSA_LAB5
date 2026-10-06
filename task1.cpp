/*
 * Course: CS-250 Data Structures and Algorithms
 * Task: Task 1 - Browser Tab Manager 
 * Author: Laraib Fatima
 * CMS ID: 542052
 * Class: BSDS 3A
 * Date: 06-10-2026
 */

#include <iostream>
#include <string>

using namespace std;

// Node struct
struct TabNode {
    int tabID;
    string title;
    string url;
    TabNode* next;
    TabNode* prev;

    TabNode(int id, const string& t, const string& u)
        : tabID(id), title(t), url(u), next(nullptr), prev(nullptr) {}
};

// Circular Doubly Linked List Class 
class BrowserTabManager {
private:
    TabNode* current;

public:
    BrowserTabManager() : current(nullptr) {}

    ~BrowserTabManager() {
        if (!current) return;
        TabNode* head = current;
        TabNode* temp = head;
        do {
            TabNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
        current = nullptr;
    }

    // Insert a new tab 
    void openNewTab(int id, const string& title, const string& url) {
        TabNode* newNode = new TabNode(id, title, url);
        if (!current) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        } else {
            TabNode* nextTab = current->next;
            newNode->next = nextTab;
            newNode->prev = current;
            current->next = newNode;
            nextTab->prev = newNode;
            current = newNode; 
        }
        cout << "Opened tab '" << title << "' (ID: " << id << ")\n";
    }

    //  Remove the current tab
    void closeCurrentTab() {
        if (!current) {
            cout << "[ERROR] No tabs to close.\n";
            return;
        }

        TabNode* toDelete = current;

        // Single node case
        if (current->next == current) {
            current = nullptr;
        } else {
            TabNode* prevTab = current->prev;
            TabNode* nextTab = current->next;
            prevTab->next = nextTab;
            nextTab->prev = prevTab;
            current = nextTab;
        }

        cout << "Tab '" << toDelete->title << "' (ID: " << toDelete->tabID << ") closed.\n";
        delete toDelete;
    }

    void moveNext() {
        if (!current) {
            cout << "[ERROR] No tabs available.\n";
            return;
        }
        current = current->next;
        cout << " Switched to next tab: " << current->title << "\n";
    }

    void movePrevious() {
        if (!current) {
            cout << "[ERROR] No tabs available.\n";
            return;
        }
        current = current->prev;
        cout << " Switched to previous tab: " << current->title << "\n";
    }

    // Display
    void displayCurrentTab() const {
        if (!current) {
            cout << " No active tabs.\n";
            return;
        }
        cout << "\n--- CURRENT ACTIVE TAB ---\n";
        cout << "Tab ID: " << current->tabID << "\n";
        cout << "Title : " << current->title << "\n";
        cout << "URL   : " << current->url << "\n";
    }

    void displayAllTabsForward() const {
        if (!current) {
            cout << " No open tabs.\n";
            return;
        }
        cout << "\n--- ALL OPEN TABS (FORWARD) ---\n";
        TabNode* temp = current;
        do {
            cout << "ID: " << temp->tabID << " | Title: " << temp->title 
                 << " | URL: " << temp->url;
            if (temp == current) cout << "  <-- [ACTIVE]";
            cout << "\n";
            temp = temp->next;
        } while (temp != current);
    }

    void displayAllTabsBackward() const {
        if (!current) {
            cout << " No open tabs.\n";
            return;
        }
        cout << "\n--- ALL OPEN TABS (BACKWARD) ---\n";
        TabNode* temp = current;
        do {
            cout << "ID: " << temp->tabID << " | Title: " << temp->title 
                 << " | URL: " << temp->url;
            if (temp == current) cout << "  <-- [ACTIVE]";
            cout << "\n";
            temp = temp->prev;
        } while (temp != current);
    }

    // Search Tab by ID
    void searchTab(int id) const {
        if (!current) {
            cout << " No tabs to search.\n";
            return;
        }
        TabNode* temp = current;
        do {
            if (temp->tabID == id) {
                cout << "\n Tab Details:\n";
                cout << "ID   : " << temp->tabID << "\n";
                cout << "Title: " << temp->title << "\n";
                cout << "URL  : " << temp->url << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "[ERROR] Tab with ID " << id << " not found.\n";
    }
};

int main() {
    BrowserTabManager browser;
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "       BROWSER TAB MANAGER       \n";
        cout << "========================================\n";
        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next Tab\n";
        cout << "4. Move Previous Tab\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string title, url;
                cout << "Enter Tab ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Website Title: ";
                getline(cin, title);
                cout << "Enter URL: ";
                getline(cin, url);
                browser.openNewTab(id, title, url);
                break;
            }
            case 2:
                browser.closeCurrentTab();
                break;
            case 3:
                browser.moveNext();
                break;
            case 4:
                browser.movePrevious();
                break;
            case 5:
                browser.displayCurrentTab();
                break;
            case 6:
                browser.displayAllTabsForward();
                break;
            case 7:
                browser.displayAllTabsBackward();
                break;
            case 8: {
                int id;
                cout << "Enter Tab ID to search: ";
                cin >> id;
                browser.searchTab(id);
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "[ERROR] Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}