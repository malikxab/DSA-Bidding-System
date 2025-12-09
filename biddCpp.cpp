#include <iostream>
#include <chrono>
#include <conio.h>     // for kbhit()
#include <string>
#include <vector>
using namespace std;

// =====================================================
//                CIRCULAR QUEUE (Array)
// =====================================================

class CircularQueue {
public:  // Made public for simplicity (Option 2)
    int front, rear, size, capacity;
    vector<string> arr;

    CircularQueue(int cap) {
        capacity = cap;
        arr.resize(capacity);
        front = -1;
        rear = -1;
        size = 0;
    }

    bool isEmpty() { return size == 0; }
    bool isFull() { return size == capacity; }

    bool exists(string name) {
        if (isEmpty()) return false;
        int i = front;
        for (int c = 0; c < size; c++) {
            if (arr[i] == name) return true;
            i = (i + 1) % capacity;
        }
        return false;
    }

    void enqueue(string name) {
        if (isFull()) {
            cout << "Queue is full!\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        arr[rear] = name;
        size++;
        cout << name << " joined the queue.\n";
    }

    int getSize() { return size; }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue: ";
        int i = front;
        for (int c = 0; c < size; c++) {
            cout << arr[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << "\n";
    }
};

// =====================================================
//            USER BST (REGISTRATION)
// =====================================================

struct Node {
    string username;
    Node* left;
    Node* right;

    Node(string name) {
        username = name;
        left = right = NULL;
    }
};

class UserBST {
public:
    Node* root = NULL;

    Node* insert(Node* node, string name) {
        if (!node) return new Node(name);
        if (name < node->username) node->left = insert(node->left, name);
        else if (name > node->username) node->right = insert(node->right, name);
        return node;
    }

    void registerUser(string name) {
        root = insert(root, name);
        cout << "User '" << name << "' registered.\n";
    }

    bool exists(Node* node, string name) {
        if (!node) return false;
        if (node->username == name) return true;
        if (name < node->username) return exists(node->left, name);
        return exists(node->right, name);
    }

    bool exists(string name) {
        return exists(root, name);
    }

    void displayUsers(Node* node) {
        if (!node) return;
        displayUsers(node->left);
        cout << node->username << "\n";
        displayUsers(node->right);
    }

    void showAllUsers() {
        if (!root) {
            cout << "No registered users.\n";
            return;
        }
        cout << "Registered Users:\n";
        displayUsers(root);
    }
};

// =====================================================
//            GLOBAL AUCTION VARIABLES
// =====================================================

UserBST users;
CircularQueue queue1(20);
vector<pair<string,int>> history;

int highestBid = 0;
string highestBidder = "";

// =====================================================
//           INPUT WITH 5 SECOND TIMER
// =====================================================

int timedInput(int timeoutSec, bool &timedOut) {
    timedOut = false;
    string input = "";
    auto start = chrono::steady_clock::now();

    cout << "Enter bid within " << timeoutSec << " seconds: ";

    while (true) {
        if (_kbhit()) {
            char c = _getch();
            if (isdigit(c)) {
                cout << c;
                input += c;
            } else if (c == '\r') {
                cout << "\n";
                break;
            }
        }

        auto now = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(now - start).count() >= timeoutSec) {
            timedOut = true;
            cout << "\nTime up! Skipped.\n";
            return -1;
        }
    }

    if (input == "") return -1;
    return stoi(input);
}

// =====================================================
//                   AUCTION LOGIC (CIRCULAR)
// =====================================================

void startAuction() {
    if (queue1.isEmpty()) {
        cout << "Queue empty. Cannot start auction.\n";
        return;
    }

    highestBid = 0;
    highestBidder = "";
    history.clear();

    cout << "\n=== AUCTION STARTED ===\n";

    int totalUsers = queue1.getSize();
    vector<string> circularUsers;

    // Copy queue to circularUsers
    int i = queue1.front;
    for (int c = 0; c < queue1.getSize(); c++) {
        circularUsers.push_back(queue1.arr[i]);
        i = (i + 1) % queue1.capacity;
    }

    int index = 0;
    int consecutiveSkips = 0;

    while (consecutiveSkips < totalUsers) {
        string user = circularUsers[index];
        cout << "\n" << user << "'s turn.\n";

        bool timeout = false;
        int bid = timedInput(5, timeout);

        if (timeout || bid <= highestBid) {
            cout << "Turn skipped.\n";
            consecutiveSkips++;
        } else {
            highestBid = bid;
            highestBidder = user;
            history.push_back({user, bid});
            cout << "Bid accepted.\n";
            consecutiveSkips = 0; // reset because valid bid
        }

        index = (index + 1) % totalUsers; // circular
    }

    cout << "\n=== AUCTION ENDED ===\n";
    if (highestBid == 0)
        cout << "No valid bids.\n";
    else
        cout << "Winner: " << highestBidder << " with bid: " << highestBid << "\n";
}

// =====================================================
//                         MAIN
// =====================================================

int main() {
    while (true) {
        cout << "\n1. Register User\n";
        cout << "2. Join Queue\n";
        cout << "3. Start Auction\n";
        cout << "4. Display Highest Bid\n";
        cout << "5. Display Bid History\n";
        cout << "6. Display Queue\n";
        cout << "7. Exit\n";
        cout << "8. Display Registered Users\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;

        if (ch == 1) {
            string name;
            cout << "Enter username: ";
            cin >> name;

            if (users.exists(name)) cout << "User already exists.\n";
            else users.registerUser(name);
        }
        else if (ch == 2) {
            string name;
            cout << "Enter username: ";
            cin >> name;

            if (!users.exists(name)) {
                cout << "User not registered.\n";
            } else if (queue1.exists(name)) {
                cout << "User already in queue.\n";
            } else {
                queue1.enqueue(name);
            }
        }
        else if (ch == 3) startAuction();
        else if (ch == 4) {
            if (highestBid == 0) cout << "No bids yet.\n";
            else cout << "Highest bid: " << highestBid << " by " << highestBidder << "\n";
        }
        else if (ch == 5) {
            if (history.empty()) cout << "No bid history.\n";
            else {
                cout << "Bid History:\n";
                for (auto &h : history) cout << h.first << " -> " << h.second << "\n";
            }
        }
        else if (ch == 6) queue1.display();
        else if (ch == 8) users.showAllUsers();
        else if (ch == 7) break;
    }

    return 0;
}
