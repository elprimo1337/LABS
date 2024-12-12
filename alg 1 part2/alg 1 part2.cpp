#include <iostream>
#include <vector>
#include <random>
using std::cin;
using std::cout;
using std::vector;
using std::endl;
//Структура для хранения результата
struct RouteResult {
    int minCost;
    std::vector<int> route;
};

std::vector<std::vector<int>> createRandomMatrix(int n) {
    // Проверка на корректность ввода
    if (n <= 0) {
        throw std::invalid_argument("Размерность матрицы должна быть положительным числом.");
    }

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n)); // Создание матрицы n x n

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd()); // Стандартный генератор на основе Mersenne Twister
    std::uniform_int_distribution<> distrib(1, 100); // Равномерное распределение от 1 до 100 (включительно)

    // Заполнение матрицы случайными числами
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = distrib(gen);
        }
    }

    return matrix;
}
bool search(vector<int> q, int index) {
    int n = q.size();
    bool z = 0;
    for (int i = 0; i < n; i++) {
        if (q[i] == index) {
            z = 1;
        }
    }
    return z;
}
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
RouteResult findGreedyRoute(vector<vector<int>> matrix,int k, int rows ) {
    int minway = 2147483647;//то, что нужно найти
    vector<int> p;
    p.push_back(k);
    //реализация гадости
    int minsum = 0;
    while (p.size() < rows) {
        int currentmin = 2147483647;//минимум в гузлике
        int index = 0; //индекс минимального гузли

        for (int i = 0; i < rows; i++) {
            if (matrix[p[p.size() - 1]][i] <= currentmin and search(p, i) == 0) {
                currentmin = matrix[p[p.size() - 1]][i];
                index = i;
            }
        }
        if (minsum < 0) {
            cout << "переполнение";
            RouteResult result;
            result.minCost = -1;
            result.route = { 0 };
            return result;
        }
        minsum = minsum + currentmin;
        p.push_back(index);
    }
    minsum += matrix[p[p.size() - 1]][k];
    RouteResult result;
    result.minCost = minsum;
    result.route = p;
    return result;
}


int main() {
    setlocale(LC_ALL, "RU"); // RU локализация консоли
    int rows, k;
    cout << "Введите размерность матрицы:";
    cin >> rows;
    cout << "Введите начальный город:";
    cin >> k;

    vector<vector<int>> matrix = createRandomMatrix(rows);

    cout << "Введенная матрица:" << endl;
    printMatrix(matrix);
    RouteResult ans = findGreedyRoute(matrix, k, rows);
    for (int i = 0; i < ans.route.size(); i++) {
        cout << ans.route[i] << ' ';
    }
    cout << ans.route[0] << ' ';
    cout << ans.minCost;

    return 0;
}