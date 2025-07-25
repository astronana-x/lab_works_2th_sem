#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int add(int **D, const char *str1, const char *str2, int n, int m, int x, int y) {
    if (x == 0 && y == 0) {
        D[x][y] = 0;
        return add(D, str1, str2, n, m, x + 1, y);
    }
    if (x > 0 && y == 0) {
        for (int i = x; i < n; i++) {
            D[i][y] = i;
        }
        return add(D, str1, str2, n, m, 0, y + 1);
    }
    if (x == 0 && y > 0) {
        for (int j = y; j < m; j++) {
            D[x][j] = j;
        }
        return add(D, str1, str2, n, m, 1, 1);
    }
    if (x > 0 && y > 0) {
        for (int i = x; i < n; i++) {
            for (int j = y; j < m; j++) {
                int a = D[i][j - 1] + 1; 
                int b = D[i - 1][j] + 1; 
                int c = (str1[i - 1] != str2[j - 1]) ? D[i - 1][j - 1] + 1 : D[i - 1][j - 1]; 
                D[i][j] = min({a, b, c});
            }
        }
        return D[n - 1][m - 1]; // Возвращаем результат из правого нижнего угла
    }
    return 0; // На случай, если что-то пошло не так
}
int main() {
    const char *str1 = "pesik";
    const char *str2 = "superpesik";
    int N = strlen(str1) + 1;
    int M = strlen(str2) + 1;

    int **dist = new int*[N];
    for (int i = 0; i < N; i++) {
        dist[i] = new int[M];
    }

    cout << add(dist, str1, str2, N, M, 0, 0) << endl;

    for (int i = 0; i < N; i++) {
        delete[] dist[i];
    }
    delete[] dist;

    return 0;
}
