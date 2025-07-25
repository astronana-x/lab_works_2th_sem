#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define N 2 // Начальное количество потомков

struct Tree {
    string value;
    vector<Tree*> children;

    Tree(const string& val, int size) : value(val), children(size, nullptr) {}
};

// Поиск вершины для вставки (передаем ссылку на указатель)
void ScanTree(Tree* node, Tree*& found_node) {
    if (node == nullptr) return;

    // Проверяем наличие свободного места у текущей вершины
    for (size_t i = 0; i < node->children.size(); ++i) {
        if (node->children[i] == nullptr) {
            if (found_node == nullptr || node->children.size() < found_node->children.size()) {
                found_node = node;
            }
        }
    } //Поиск свободного места среди детей

    // Рекурсивно обходим всех потомков
    for (size_t i = 0; i < node->children.size(); ++i) {
        if (node->children[i] != nullptr) {
            ScanTree(node->children[i], found_node);
        }
    }
}

// Вставка нового узла слева направо
Tree* InsertNode(Tree* root, const string& value) { //указатель на корень, значение нового узла
    if (root == nullptr) {
        return new Tree(value, N);//если дерево пустое, создается новый узел и явл корнем
    }

    Tree* found_node = nullptr;
    ScanTree(root, found_node); //ищет узел для вставки

    if (found_node != nullptr) {
        Tree* new_node = new Tree(value, found_node->children.size() * 2);
        for (size_t i = 0; i < found_node->children.size(); ++i) { //проходимся по детям и вставляем
            if (found_node->children[i] == nullptr) {
                found_node->children[i] = new_node;
                break;
            }
        }
        return new_node; //новый узел
    }

    return nullptr;
}

// Вывод дерева на экран
void PrintTree(const Tree* node, int level = 0) {
    if (node == nullptr) return;

    for (int i = 0; i < level; ++i) {
        cout << "   ";
    }
    cout << node->value << endl; //выводим значение узла и переводим в строку

    for (const auto& child : node->children) {
        PrintTree(child, level + 1);//для каждого ребёнка текущего узла вызываем эту же функцию, увеличивая уровень вложенности
    }
}

// Удаление дерева
void DeleteTree(Tree* node) {
    if (node == nullptr) return;

    for (auto& child : node->children) {
        DeleteTree(child);
    }

    delete node;
}

// Менюша
void Menu(Tree*& root) {
    while (true) {
        cout << "\nEnter a value to add (or 'q' to quit): ";
        string s;
        cin >> s;

        if (s == "q" || s == "Q") {
            cout << "Exiting program.\n";
            break;
        }

        InsertNode(root, s);

        cout << "\nCurrent tree:\n";
        PrintTree(root);
    }
}

int main() {
    Tree* root = nullptr;

    cout << "Enter 7 initial values:\n";
    string values[7];

    for (int i = 0; i < 7; ++i) {
        cin >> values[i];
    }

    root = InsertNode(root, values[0]);
    for (int i = 1; i < 7; ++i) {
        InsertNode(root, values[i]);
    }

    cout << "\nInitial tree:\n";
    PrintTree(root);

    Menu(root);

    DeleteTree(root);

    return 0;
}
