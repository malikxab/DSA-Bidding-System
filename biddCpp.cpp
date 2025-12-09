#include <iostream>
#include <chrono>
#include <conio.h>
#include <string>
using namespace std;

// =====================================================
//                CIRCULAR QUEUE (Array)
// =====================================================

class CircularQueue {
public:
    int front, rear, size, capacity;
    string* arr;

    CircularQueue(int cap) {
        capacity = cap;
        arr = new string[cap];
        front = rear = -1;
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
        if (isFull()) { cout << "Queue is full!\n"; return; }
        if (isEmpty()) front = rear = 0;
        else rear = (rear + 1) % capacity;
        arr[rear] = name;
        size++;
        cout << name << " joined the queue.\n";
    }

    int getSize() { return size; }

    void display() {
        if (isEmpty()) { cout << "Queue is empty.\n"; return; }
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
        if (!root) { cout << "No registered users.\n"; return; }
        cout << "Registered Users:\n";
        displayUsers(root);
    }
};

// =====================================================
//                 LINKED LIST (Bid History)
// =====================================================

struct BidNode {
    string username;
    int bid;
    BidNode* next;
    BidNode(string u, int b) { username = u; bid = b; next = nullptr; }
};

class BidHistory {
public:
    BidNode* head = nullptr;

    void addBid(string user, int bid) {
        BidNode* newNode = new BidNode(user, bid);
        if (!head) head = newNode;
        else {
            BidNode* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void display() {
        if (!head) { cout << "No bid history.\n"; return; }
        cout << "Bid History:\n";
        BidNode* temp = head;
        while (temp) {
            cout << temp->username << " -> " << temp->bid << "\n";
            temp = temp->next;
        }
    }

    void clear() {
        BidNode* temp = head;
        while (temp) {
            BidNode* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        head = nullptr;
    }
};

// =====================================================
//       LINKED LIST (Circular Users for Auction)
// =====================================================

struct UserNode {
    string username;
    UserNode* next;
    UserNode(string name) { username = name; next = nullptr; }
};

class UserList {
public:
    UserNode* head = nullptr;
    UserNode* tail = nullptr;

    void addUser(string name) {
        UserNode* newNode = new UserNode(name);
        if (!head) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
        tail->next = head; // circular link
    }

    void clear() {
        if (!head) return;
        UserNode* curr = head;
        do {
            UserNode* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        } while (curr != head);
        head = tail = nullptr;
    }
};

// =====================================================
//            GLOBAL AUCTION VARIABLES
// =====================================================

UserBST users;
CircularQueue queue1(20);
BidHistory history;

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
    if (queue1.isEmpty()) { cout << "Queue empty. Cannot start auction.\n"; return; }

    highestBid = 0;
    highestBidder = "";
    history.clear();

    cout << "\n=== AUCTION STARTED ===\n";

    // Create circular linked list of users
    UserList circularUsers;
    int totalUsers = queue1.getSize();
    int i = queue1.front;
    for (int c = 0; c < totalUsers; c++) {
        circularUsers.addUser(queue1.arr[i]);
        i = (i + 1) % queue1.capacity;
    }

    UserNode* curr = circularUsers.head;
    int consecutiveSkips = 0;

    while (consecutiveSkips < totalUsers) {
        string user = curr->username;
        cout << "\n" << user << "'s turn.\n";

        bool timeout = false;
        int bid = timedInput(5, timeout);

        if (timeout || bid <= highestBid) {
            cout << "Turn skipped.\n";
            consecutiveSkips++;
        } else {
            highestBid = bid;
            highestBidder = user;
            history.addBid(user, bid);
            cout << "Bid accepted.\n";
            consecutiveSkips = 0;
        }

        curr = curr->next; // circular traversal
    }

    circularUsers.clear();

    cout << "\n=== AUCTION ENDED ===\n";
    if (highestBid == 0) cout << "No valid bids.\n";
    else cout << "Winner: " << highestBidder << " with bid: " << highestBid << "\n";
}

// =====================================================
//                         MAIN
// =====================================================

int main() {
    while (true) {
        cout << "\n1. Register User\n2. Join Queue\n3. Start Auction\n4. Display Highest Bid\n5. Display Bid History\n6. Display Queue\n7. Exit\n8. Display Registered Users\nEnter choice: ";
        int ch;
        cin >> ch;

        if (ch == 1) {
            string name; cout << "Enter username: "; cin >> name;
            if (users.exists(name)) cout << "User already exists.\n";
            else users.registerUser(name);
        }
        else if (ch == 2) {
            string name; cout << "Enter username: "; cin >> name;
            if (!users.exists(name)) cout << "User not registered.\n";
            else if (queue1.exists(name)) cout << "User already in queue.\n";
            else queue1.enqueue(name);
        }
        else if (ch == 3) startAuction();
        else if (ch == 4) cout << (highestBid == 0 ? "No bids yet.\n" : "Highest bid: " + to_string(highestBid) + " by " + highestBidder + "\n");
        else if (ch == 5) history.display();
        else if (ch == 6) queue1.display();
        else if (ch == 8) users.showAllUsers();
        else if (ch == 7) break;
    }

    return 0;
}