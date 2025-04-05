#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Функция для ввода матрицы
vector<vector<int>> inputMatrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));

    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int calculateRouteCost(const vector<vector<int>>& matrix, const vector<int>& route) {
    int cost = 0;
    int n = route.size();
    for (int i = 0; i < n - 1; i++) {
        cost += matrix[route[i]][route[i + 1]];
    }
    cost += matrix[route[n - 1]][route[0]]; // Возвращение в начальный город
    return cost;
}

// Функция генерации следующей перестановки
void nextPermutation(vector<int>& permutation) {
    int n = permutation.size();

    // 1. Найти максимальное i такое, что P[i] < P[i+1]
    int i = n - 2;
    while (i >= 0 && permutation[i] >= permutation[i + 1]) {
        i--;
    }

    // 2. Если такого i не существует, процесс завершен
    if (i < 0) {
        return;
    }
    // 3. Найти максимальное j такое, что P[i] < P[j]
    int j = n - 1;
    while (permutation[i] >= permutation[j]) {
        j--;
    }

    // 4. Поменять P[i] и P[j] местами
    swap(permutation[i], permutation[j]);

    // 5. Инвертировать порядок элементов с i + 1 по n
    reverse(permutation.begin() + i + 1, permutation.end());
}
// Функция для создания квадратной матрицы размерности n, 
// заполненной случайными числами
vector<vector<int>> createRandomMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = distrib(gen);
        }
    }

    return matrix;
}
int Goida() {//то, что нам нада
    int rows;
    cout << "Введите размерность матрицы: ";
    cin >> rows;
    vector<vector<int>> matrix = createRandomMatrix(rows);
    printMatrix(matrix);
    int minway = 9999999;//то, что нужно найти
    vector<int> p(rows); // Вектор для хранения перестановки городов
    for (int i = 0; i < rows; i++) {
        p[i] = i;
    }
    // Переменная для отслеживания количества выведенных перестановок
    int count = 0;
    int factorial = 1;
    for (int i = 1; i <= rows; i++) {
        factorial *= i;
    }
    // Цикл для генерации и вывода всех перестановок
    while (count < factorial) {
        for (int i = 0; i < rows; i++) {
        }
        // Вычисляем стоимость текущего маршрута
        int currentCost = calculateRouteCost(matrix, p);

        // Обновляем минимальную стоимость, если нужно
        if (currentCost < minway) {
            minway = currentCost;
        }

        // Получаем следующую перестановку
        nextPermutation(p);

        count++;
    }

    cout << "Минимальная стоимость маршрута: " << endl;
    return minway;
}

int main() {
    setlocale(LC_ALL, "RU"); // RU локализация консоли
    cout << Goida();
    return 0;
}