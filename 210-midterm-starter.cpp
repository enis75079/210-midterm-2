#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };



public:
    Node* head;
    Node* tail;
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {    
    srand(time(0));
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    vector<string> names;
    ifstream file("names.txt");
    string name;
    while (getline(file, name)) {
        names.push_back(name);
    }

    // delete later. tests name reading
    int count = 0;
    for (const auto& x : names) {
        count += 1;
    }
    
    DoublyLinkedList list;

    cout << "Store opens: " << endl;
    for (int i = 0; i < 5; i++) {
        int randName = rand() % count;
        cout << "   " << names[randName] << " joins the line" << endl;
        list.push_back(names[randName]);
    }
    
    cout << "   " << "Resulting line:" << endl;
    cout << "   ";
    list.print();

    for (int i = 0; i < 20; i++) {
        cout << "Time step #" << i + 1 << endl;

        int prob = rand() % 100 + 1;
        if (prob <= 40) {
            cout << list.head->data << " is served" << endl;
            list.pop_front();
        }

        int prob2 = rand() % 100 + 1;
        if (prob2 <= 60) {
            int randName = rand() % names.size();
            cout << names[randName] << " joins the line" << endl;
            list.push_back(names[randName]);
        }

        int prob3 = rand() % 100 + 1;
        if (prob3 <= 20) {
            cout << list.tail->data << " (at the rear) left the line" << endl;
            list.pop_back();
        }

        int prob4 = rand() % 100 + 1;
        if (prob4 <= 10) {
            int randName = rand() % names.size();
            cout << names[randName] << " (VIP) joins the front of the line" << endl;
            list.push_front(names[randName]);
        }

        list.print();
    }
    return 0;
}