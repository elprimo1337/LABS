#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <stack>

// Структура для хранения информации о подзадаче
struct Subtask {
    int l;
    int r;
    int k;
};

// Функция для проверки k - го бита числа
bool checkBit(const int& n, const int& k) {
    // Проверяем, является ли k-й бит установленным (равным 1)
    if ((n >> k) & 1) {
        return true; // Бит равен 1
    }
    else {
        return false; // Бит равен 0
    }
}

void bitsort(std::vector<int>& arr, const int& l, const int& r, const int& k) {
    if (arr.empty()) return;

    // 1. Инициализация стека
    std::stack<Subtask> taskStack;
    taskStack.push({ 0, static_cast<int>(arr.size() - 1), k });

    // 2. Итеративная обработка
    while (!taskStack.empty()) {
        // a. Извлечение задачи
        Subtask currentTask = taskStack.top();
        taskStack.pop();

        const int l = currentTask.l;
        const int r = currentTask.r;
        const int k = currentTask.k;

        // b. все рассмотрели
        if (l >= r || k < 0) {
            continue; // Ничего не делаем
        }

        // c. Разделение
        int i = l;
        int j = r;
        while (i <= j) {
            // i движется вправо, пока не найдет бит k равный 1
            while (i <= j && !checkBit(arr[i], k)) {
                i++;
            }

            // j движется влево, пока не найдет бит k равный 0
            while (i <= j && checkBit(arr[j], k)) {
                j--;
            }

            // Если i и j не пересеклись, меняем местами элементы
            if (i < j) {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }

        // d. Добавление подзадач (если они нужны)
        if (i <= r && k > 0) {
            taskStack.push({ i, r, k - 1 }); // И ТУТ
        }
        if (l <= j && k > 0) {
            taskStack.push({ l, j, k - 1 }); // И ТУТ
        }
    }
}

int main() {
        std::setlocale(LC_ALL, "Russian");

        std::string filename;
        std::cout << "Введите имя файла с числами: ";
        std::cin >> filename;

        std::ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            std::cerr << "Ошибка открытия файла: " << filename << std::endl;
            return 1;
        }

        std::vector<int> numbers;
        int number;
        while (inputFile >> number) {
            numbers.push_back(number);
        }

        inputFile.close();

        std::cout << "Считано " << numbers.size() << " чисел из файла." << std::endl;

        // Замер времени сортировки
        auto start = std::chrono::high_resolution_clock::now();
        bitsort(numbers, 0, numbers.size() - 1, 31); // Сортировка вектора
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        std::cout << "Время сортировки: " << duration.count() << " секунд" << std::endl;

        // Вывод отсортированного массива (опционально)
       /* std::cout << "Отсортированный массив: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
       */
        return 0;
}

