#include <iostream>
#include <cstring>
#include <string>

using namespace std;

enum DataType { INT, STR };

struct Variant {
    DataType type;
    union {
        int intVal;
        char* strVal;
    } data;
};

void printVariant(const Variant& v) {
    if (v.type == INT) cout << v.data.intVal;
    else if (v.type == STR && v.data.strVal) cout << v.data.strVal;
}

void freeVariant(Variant& v) {
    if (v.type == STR && v.data.strVal) {
        delete[] v.data.strVal; // Освобождаем память через delete[]
    }
}

struct ListNode {
    Variant value;
    ListNode* next;
    ListNode* prev;
};

// Итератор для списка
struct ListIterator {
    ListNode* node;
    
    ListIterator(ListNode* n = nullptr) : node(n) {}
    
    Variant& operator*() { return node->value; }
    ListIterator& operator++() { node = node->next; return *this; }
    bool operator!=(const ListIterator& other) { return node != other.node; }
};

// Итератор для массива
struct ArrayIterator {
    Variant** ptr;
    
    ArrayIterator(Variant** p = nullptr) : ptr(p) {}
    
    Variant& operator*() { return **ptr; }
    ArrayIterator& operator++() { ++ptr; return *this; }
    bool operator!=(const ArrayIterator& other) { return ptr != other.ptr; }
};


typedef int (*CompareFunc)(const Variant&, const Variant&);

int compareVariants(const Variant& a, const Variant& b) {
    if (a.type == INT && b.type == INT) {
        return a.data.intVal - b.data.intVal;
    } else if (a.type == STR && b.type == STR) {
        return strcmp(a.data.strVal, b.data.strVal);
    } else if (a.type == INT) {
        return -1; // int < string
    } else {
        return 1;  // string > int
    }
}


template<typename Iterator>
void sortRange(Iterator begin, Iterator end, CompareFunc cmp) {
    for (Iterator i = begin; i != end; ++i) {
        for (Iterator j = begin; j != i; ++j) {
            if (cmp(*j, *i) > 0) {
                swap(*j, *i);
            }
        }
    }
}


char* copyString(const char* src) {
    if (!src) return nullptr;
    char* dst = new char[strlen(src) + 1];
    strcpy(dst, src);
    return dst;
}

ListNode* createList() {
    int size;
    cout << "Enter list size: ";
    cin >> size;
    cin.ignore();
    
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    
    cout << "Enter " << size << " elements (numbers or words):\n";
    for (int i = 0; i < size; i++) {
        string input;
        cout << "Element " << i+1 << ": ";
        getline(cin, input);
        
        ListNode* node = new ListNode();
        try {
            node->value.type = INT;
            node->value.data.intVal = stoi(input);
        } catch (...) {
            node->value.type = STR;
            node->value.data.strVal = copyString(input.c_str()); // Используем copyString
        }
        
        if (!head) {
            head = tail = node;
            node->prev = nullptr;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        node->next = nullptr;
    }
    return head;
}

void printList(ListNode* list) {
    cout << "Sorted list:\n";
    for (ListNode* p = list; p; p = p->next) {
        printVariant(p->value);
        cout << " ";
    }
    cout << endl;
}

void freeList(ListNode* list) {
    while (list) {
        ListNode* next = list->next;
        freeVariant(list->value);
        delete list;
        list = next;
    }
}

Variant** createArray(int& size) {
    cout << "Enter array size: ";
    cin >> size;
    cin.ignore();
    
    Variant** arr = new Variant*[size];
    
    cout << "Enter " << size << " elements (numbers or words):\n";
    for (int i = 0; i < size; i++) {
        string input;
        cout << "Element " << i+1 << ": ";
        getline(cin, input);
        
        arr[i] = new Variant();
        try {
            arr[i]->type = INT;
            arr[i]->data.intVal = stoi(input);
        } catch (...) {
            arr[i]->type = STR;
            arr[i]->data.strVal = copyString(input.c_str()); 
        }
    }
    return arr;
}

void printArray(Variant** arr, int size) {
    cout << "Sorted array:\n";
    for (int i = 0; i < size; i++) {
        printVariant(*arr[i]);
        cout << " ";
    }
    cout << endl;
}

void freeArray(Variant** arr, int size) {
    for (int i = 0; i < size; i++) {
        freeVariant(*arr[i]);
        delete arr[i];
    }
    delete[] arr;
}

int main() {
    while (true) {
        cout << "\nMenu:\n";
        cout << "[1] Sort array\n";
        cout << "[2] Sort list\n";
        cout << "[0] Exit\n";
        cout << "Enter choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int size;
                Variant** arr = createArray(size);
                sortRange(ArrayIterator(arr), ArrayIterator(arr + size), compareVariants);
                printArray(arr, size);
                freeArray(arr, size);
                break;
            }
            case 2: {
                ListNode* list = createList();
                sortRange(ListIterator(list), ListIterator(nullptr), compareVariants);
                printList(list);
                freeList(list);
                break;
            }
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}
