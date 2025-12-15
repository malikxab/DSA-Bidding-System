#include <iostream>
#include <string>
#include <chrono>
#include <future>
#include <limits>
#include <cctype>
#include <algorithm>
#include <unordered_map>

using namespace std;

// =====================================================
//              HELPERS
// =====================================================

string trim_copy(string s) {
    auto notSpace = [](unsigned char ch) { return !isspace(ch); };
    s.erase(s.begin(), find_if(s.begin(), s.end(), notSpace));
    s.erase(find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
    return s;
}

string collapse_spaces(string s) {
    string out;
    bool space = false;
    for (char c : s) {
        if (isspace(c)) {
            if (!space) out += ' ';
            space = true;
        } else {
            out += c;
            space = false;
        }
    }
    return out;
}

string normalize_name(string s) {
    s = trim_copy(collapse_spaces(s));
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool try_parse_int(const string& s, int& out) {
    if (s.empty()) return false;
    for (char c : s) if (!isdigit(c)) return false;
    try {
        long long v = stoll(s);
        if (v > INT_MAX) return false;
        out = (int)v;
        return true;
    } catch (...) {
        return false;
    }
}

// =====================================================
//            LINKED LIST QUEUE (REPLACEMENT)
// =====================================================

struct QueueNode {
    string key;
    QueueNode* next;
    QueueNode(string k) : key(k), next(nullptr) {}
};

class LinkedQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int sz;

public:
    LinkedQueue() : front(nullptr), rear(nullptr), sz(0) {}

    bool isEmpty() const { return sz == 0; }
    int size() const { return sz; }

    bool exists(const string& key) const {
        QueueNode* temp = front;
        while (temp) {
            if (temp->key == key) return true;
            temp = temp->next;
        }
        return false;
    }

    void enqueue(const string& key) {
        QueueNode* n = new QueueNode(key);
        if (!rear) front = rear = n;
        else { rear->next = n; rear = n; }
        sz++;
    }

    void clear() {
        while (front) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        sz = 0;
    }

    void display(const unordered_map<string, string>& names) const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        QueueNode* temp = front;
        cout << "Queue: ";
        while (temp) {
            cout << names.at(temp->key) << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    QueueNode* getFront() const { return front; }
};

// =====================================================
//                  USER BST
// =====================================================

struct UserNode {
    string key;
    UserNode* left;
    UserNode* right;
    UserNode(string k) : key(k), left(nullptr), right(nullptr) {}
};

class UserBST {
private:
    UserNode* root = nullptr;

    UserNode* insert(UserNode* node, const string& key) {
        if (!node) return new UserNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        return node;
    }

    bool search(UserNode* node, const string& key) const {
        if (!node) return false;
        if (node->key == key) return true;
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }

    void inorder(UserNode* node, const unordered_map<string, string>& names) const {
        if (!node) return;
        inorder(node->left, names);
        cout << names.at(node->key) << "\n";
        inorder(node->right, names);
    }

    void destroy(UserNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    ~UserBST() { destroy(root); }

    bool exists(const string& key) const { return search(root, key); }

    void registerUser(const string& key) { root = insert(root, key); }

    void showUsers(const unordered_map<string, string>& names) const {
        if (!root) cout << "No registered users.\n";
        else inorder(root, names);
    }
};

// =====================================================
//             BID HISTORY (LINKED LIST)
// =====================================================

struct BidNode {
    string key;
    int bid;
    BidNode* next;
    BidNode(string k, int b) : key(k), bid(b), next(nullptr) {}
};

class BidHistory {
private:
    BidNode* head = nullptr;
    BidNode* tail = nullptr;

public:
    ~BidHistory() { clear(); }

    void add(const string& key, int bid) {
        BidNode* n = new BidNode(key, bid);
        if (!head) head = tail = n;
        else { tail->next = n; tail = n; }
    }

    void display(const unordered_map<string, string>& names) const {
        if (!head) {
            cout << "No bid history.\n";
            return;
        }
        BidNode* t = head;
        while (t) {
            cout << names.at(t->key) << " -> " << t->bid << "\n";
            t = t->next;
        }
    }

    void clear() {
        while (head) {
            BidNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};

// =====================================================
//                 TIMED INPUT
// =====================================================

bool timedInput(int sec, string& out) {
    cout << "Enter bid within " << sec << " seconds: " << flush;
    auto fut = async(launch::async, [] {
        string s;
        getline(cin, s);
        return s;
    });

    if (fut.wait_for(chrono::seconds(sec)) == future_status::ready) {
        out = fut.get();
        return true;
    }

    cout << "\nTime expired!\n";
    return false;
}

// =====================================================
//               AUCTION SYSTEM
// =====================================================

UserBST users;
LinkedQueue queue1;
BidHistory history;
unordered_map<string, string> displayName;

int highestBid = 0;
string highestBidder;

void startAuction() {

    if (queue1.size() < 2) {
        cout << "At least 2 users are required to start the auction.\n";
        return;
    }

    highestBid = 0;
    highestBidder.clear();
    history.clear();

    cout << "\n=== AUCTION STARTED ===\n";

    int skip = 0;
    int total = queue1.size();
    QueueNode* current = queue1.getFront();

    while (skip < total) {
        cout << displayName[current->key] << "'s turn\n";

        string input;
        if (timedInput(5, input)) {
            int bid;
            if (try_parse_int(input, bid) && bid > highestBid) {
                highestBid = bid;
                highestBidder = current->key;
                history.add(current->key, bid);
                cout << "Bid accepted!\n";
                skip = 0;
            } else {
                cout << "Invalid bid.\n";
                skip++;
            }
        } else skip++;

        current = current->next ? current->next : queue1.getFront();
    }

    cout << "\n=== AUCTION ENDED ===\n";
    if (highestBid > 0)
        cout << "Winner: " << displayName[highestBidder] << " with bid " << highestBid << "\n";
    else
        cout << "No valid bids.\n";

    queue1.clear();
}

// =====================================================
//                    MAIN
// =====================================================

int main() {
    while (true) {
        cout << "\n1. Register User\n2. Join Queue\n3. Start Auction\n"
             << "4. Highest Bid\n5. Bid History\n6. Display Queue\n"
             << "7. Exit\n8. Display Registered Users\nChoice: ";

        string line;
        getline(cin, line);
        int ch;
        if (!try_parse_int(line, ch)) continue;

        if (ch == 1) {
            cout << "Enter username: ";
            string raw;
            getline(cin, raw);
            string key = normalize_name(raw);
            string show = trim_copy(raw);

            if (users.exists(key)) cout << "User already exists.\n";
            else {
                users.registerUser(key);
                displayName[key] = show;
                cout << "User registered.\n";
            }
        }
        else if (ch == 2) {
            cout << "Enter username: ";
            string raw;
            getline(cin, raw);
            string key = normalize_name(raw);

            if (!users.exists(key)) cout << "User not registered.\n";
            else if (queue1.exists(key)) cout << "User already in queue.\n";
            else {
                queue1.enqueue(key);
                cout << "Joined queue.\n";
            }
        }
        else if (ch == 3) startAuction();
        else if (ch == 4) {
            if (highestBid == 0) cout << "No bids yet.\n";
            else cout << "Highest bid: " << highestBid << " by " << displayName[highestBidder] << "\n";
        }
        else if (ch == 5) history.display(displayName);
        else if (ch == 6) queue1.display(displayName);
        else if (ch == 8) users.showUsers(displayName);
        else if (ch == 7) break;
    }
    return 0;
}
