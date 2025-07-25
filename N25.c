/*25.	Функция получает массив размерности N и  возвращает массив указателей на линейные массивы. 
Первый элемент линейного массива содержит очередное значение массива V, второй – количество следующих за ним 
элементов. Следующие элементы содержат значения из того же массива, отличающиеся от V не более, чем на W по 
абсолютному значению (W – параметр функции)*/

#include <stdio.h>
#include <stdlib.h>

int my_abs(int x) {
    return x >= 0 ? x : -x; //создаем функцию для абсолютного значения
}

// сосздаем функцию которая создает массив указателей на линейные массивы
int** createArrays(int *V, int N, int W) {
    int **result = (int **)malloc(N * sizeof(int *));
    if (!result) {
        return NULL;//если память не выдилилась, то выходим с NULL
    }

    for (int i = 0; i < N; i++) {  // идём по каждому элементу массива V
        int count = 0;  // считаем сколько следующих элементов подходят
        for (int j = i + 1; j < N; j++) {  // смотрим только элементы после i
            if (my_abs(V[j] - V[i]) <= W) {  // если разница не больше W (абсолютная)
                count++;  // то увеличиваем счётчик подходящих
            }
        }

        
        result[i] = (int *)malloc((2 + count) * sizeof(int)); //выделяем память для линейного массива
        if (!result[i]) {  
            for (int k = 0; k < i; k++) free(result[k]);  // если не выделилась память освобождаем уже выделенное
            free(result);  // и сам массив указателей
            return NULL;  
        }

        result[i][0] = V[i];  // первый элемент это текущее значение из V
        result[i][1] = count;  // второй количество подходящих элементов

        int idx = 2;  // начинаем вставлять подходящие элементы с позиции 2
        for (int j = i + 1; j < N; j++) {  // снова проходим по элементам после i
            if (my_abs(V[j] - V[i]) <= W) { 
                result[i][idx++] = V[j];  // если элемент подходит записываем его в массив
            }
        }
    }

    return result;
}

// функция для вывода результата
void printRes(int **arr, int N) {
    for (int i = 0; i < N; i++) {  // пробегаем по каждому подмассиву
        int len = arr[i][1] + 2;  // считаем длину текущего подмассива: 1 элемент т.е значение + 1икол-во + все найденные значения
        printf("Array %d: ", i);  // печатаем номер массива (для удобства)
        for (int j = 0; j < len; j++) {  // идём по всем элементам текущего подмассива
            printf("%d ", arr[i][j]);  // выводим число
        }
        printf("\n");
    }
}

// функция для освобождения памяти чтобы избежать утечек
void freeMemory(int **arr, int N) {
    for (int i = 0; i < N; i++) {
        free(arr[i]);
    }
    free(arr);
}

//3 теста на статических данных
int main() {
    int V1[] = {8, 2, 7, 5};
    int N1 = sizeof(V1)/sizeof(V1[0]);
    int W1 = 2;

    int V2[] = {20, 18, 22, 19, 25};
    int N2 = sizeof(V2)/sizeof(V2[0]);
    int W2 = 3;

    int V3[] = {1, 4, 6, 9, 10};
    int N3 = sizeof(V3)/sizeof(V3[0]);
    int W3 = 1;

    printf("Test 1:\n");
    int **res1 = createArrays(V1, N1, W1);
    if (res1) {
        printRes(res1, N1);
        freeMemory(res1, N1);
    }
    printf("\n");

    printf("Test 2:\n");
    int **res2 = createArrays(V2, N2, W2);
    if (res2) {
        printRes(res2, N2);
        freeMemory(res2, N2);
    }
    printf("\n");

    printf("Test 3:\n");
    int **res3 = createArrays(V3, N3, W3);
    if (res3) {
        printRes(res3, N3);
        freeMemory(res3, N3);
    }

    return 0;
}
