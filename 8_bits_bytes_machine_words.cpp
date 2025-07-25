#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

char* IntTo6BitBinary(int x) { //Преобразует целое число x в 6-битную бинарную строку (например, 5 → "000101")
    char* binary = (char*)malloc(7); // выдел память под 7 символов 6 бит + '\0'
    for (int i = 5; i >= 0; i--) { //Идёт от 5 до 0 (старший бит → младший)
        binary[i] = (x & 1) ? '1' : '0'; //получает младший бит числа, записывает или 1 или 0
        x >>= 1;//сдвигает биты вправо(от старшего к млад), откидывает меньший
    }
    binary[6] = '\0';
    return binary; //возвращает указатель на строку
}

void ProcessBitSequence(const int* bits, int size) {//Выводит исходную последовательность бит в обратном порядке (справа налево)
    for (int i = size-1; i >= 0; i--) {
        cout << bits[i];
    }
    cout << endl;

    if (size == 0) return;

    int current = bits[size-1];//текущий бит (начинается с последнего элемента массива
    int count = 1;//счётчик подряд идущих одинаковых битов (начальное значение 1)

    // Обрабатывает последовательность справа налево, группируя подряд идущие одинаковые биты
    for (int i = size-2; i >= 0; i--) {
        if (bits[i] == current) {
            count++;
        } else {
            char* code = IntTo6BitBinary(count);
            cout << code << " "; //Для каждой группы выводит её длину в 6-битном формате
            free(code);
            current = bits[i];
            count = 1;
        }
    }

    // Вывод последней серии и терминатора
    char* last_code = IntTo6BitBinary(count);
    cout << last_code << " ";
    free(last_code);
    cout << "000000" << endl; //вывод терминатора 0
}

int main() {
    int test_sequence[] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
    int size = sizeof(test_sequence)/sizeof(test_sequence[0]);

    ProcessBitSequence(test_sequence, size);

    return 0;
}
