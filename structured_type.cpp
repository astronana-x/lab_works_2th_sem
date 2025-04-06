#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    string surname;  
    int number;
    int ratings[20];
    double average;
};

struct Table {
    Student line[100];
    int n = 0;
};

double getAverage(int* A, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum / n;
}

void loading(Table* group) {
    ifstream f("Group.txt");
    if (f.is_open()) {
        while (!f.eof()) {
            f >> group->line[group->n].surname;
            f >> group->line[group->n].number;
            for (int i = 0; i < group->line[group->n].number; i++) {
                f >> group->line[group->n].ratings[i];
            }
            group->line[group->n].average = getAverage(group->line[group->n].ratings, 
                                                     group->line[group->n].number);
            group->n++;
        }
        f.close();
    }
}

void input(Table* group) {
    cout << "\nEnter the surname, the kol-vo of ratings, ratings of all the time\n";
    cin >> group->line[group->n].surname;
    cin >> group->line[group->n].number;
    for (int i = 0; i < group->line[group->n].number; i++) {
        cin >> group->line[group->n].ratings[i];
    }
    group->line[group->n].average = getAverage(group->line[group->n].ratings, 
                                             group->line[group->n].number);
    group->n++;
}

void show(Table group) {
    for (int i = 0; i < group.n; i++) {
        cout << group.line[i].surname << "\t"
             << group.line[i].number << "\t";
        for (int k = 0; k < group.line[i].number; k++) {
            cout << group.line[i].ratings[k] << " ";
        }
        cout << "\t" << fixed << setprecision(2) << group.line[i].average << endl;
    }
}

void saving(Table group) {
    ofstream f("New_group.txt");
    if (f.is_open()) {
        for (int i = 0; i < group.n; i++) {
            f << group.line[i].surname << "\t"
              << group.line[i].number << "\t";
            for (int k = 0; k < group.line[i].number; k++) {
                f << group.line[i].ratings[k] << " ";
            }
            f << "\t" << fixed << setprecision(2) << group.line[i].average << endl;
        }
        f.close();
    }
}

Table sortAverage(Table group) {
    for (int i = 0; i < group.n - 1; i++) {
        for (int j = 0; j < group.n - i - 1; j++) {
            if (group.line[j].average > group.line[j+1].average) {
                swap(group.line[j], group.line[j+1]);
            }
        }
    }
    cout << "Table has been sorted\n";
    return group;
}

Table sortNumber(Table group) {
    for (int i = 0; i < group.n - 1; i++) {
        for (int j = 0; j < group.n - i - 1; j++) {
            if (group.line[j].number > group.line[j+1].number) {
                swap(group.line[j], group.line[j+1]);
            }
        }
    }
    cout << "Table has been sorted\n";
    return group;
}

Table sortSurname(Table group) {
    for (int i = 0; i < group.n - 1; i++) {
        for (int j = 0; j < group.n - i - 1; j++) {
            if (group.line[j].surname > group.line[j+1].surname) {
                swap(group.line[j], group.line[j+1]);
            }
        }
    }
    cout << "Table has been sorted\n";
    return group;
}

void search(Table group) {
    string s;
    cout << "Enter a surname\n";
    cin >> s;
    bool found = false;
    
    for (int i = 0; i < group.n; i++) {
        if (group.line[i].surname == s) { 
            cout << group.line[i].surname << "\t" 
                 << group.line[i].number << "\t";
            for (int j = 0; j < group.line[i].number; j++) {
                cout << group.line[i].ratings[j] << " ";
            }
            cout << "\t" << fixed << setprecision(2) << group.line[i].average << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "\nNothing found\n";
    }
}
Table del(Table group) {
    cout << "Enter a line number\n";
    int n;
    cin >> n;
    n--;
    
    for (int i = n; i < group.n - 1; i++) {
        group.line[i] = group.line[i+1];
    }
    group.n--;
    cout << "\nSuccessful\n";
    return group;
}

Table edit(Table group) {
    cout << "Enter a line number\n";
    int n;
    cin >> n;
    n--;
    
    cout << "\nEnter in turn the surname, the number of ratings, ratings one at a time\n";
    cin >> group.line[n].surname;
    cin >> group.line[n].number;
    for (int i = 0; i < group.line[n].number; i++) {
        cin >> group.line[n].ratings[i];
    }
    group.line[n].average = getAverage(group.line[n].ratings, group.line[n].number);
    cout << "\nSuccessful\n";
    return group;
}

void avg(Table group) {
    double sum = 0, k = 0;
    for (int i = 0; i < group.n; i++) {
        for (int j = 0; j < group.line[i].number; j++) {
            sum += group.line[i].ratings[j];
            k++;
        }
    }
    cout << fixed << setprecision(2) << sum / k << endl;
}

int interface() {
    int mode, choice;
    Table group;
    
    cout << "Press 1 to download the table:\t";
    cin >> mode;
    
    if (mode == 1) {
        loading(&group);
    }
    
    while (mode == 1) {
        cout << "\nChoose what to do:\n1 - save to file and exit\n"
             << "2 - add table row\n3 - show table in console\n"
             << "4 - sort the table by average\n5 - sort the table by the number of rating\n"
             << "6 - sort the table by surname\n7 - search by surname\n"
             << "8 - delete line\n9 - edit line\n0 - average rating of the group\n";
        
        cin >> choice;

        switch (choice) {
            case 1: saving(group); return 0;
            case 2: input(&group); break;
            case 3: show(group); break;
            case 4: group = sortAverage(group); break;
            case 5: group = sortNumber(group); break;
            case 6: group = sortSurname(group); break;
            case 7: search(group); break;
            case 8: group = del(group); break;
            case 9: group = edit(group); break;
            case 0: avg(group); break;
            default: return 1;
        }
    }
    return 0;
}

int main() {
    if (interface() == 0) {
        cout << "\nEverything is good\n";
    } else {
        cout << "\nSomething went wrong\n";
    }
    return 0;
}
