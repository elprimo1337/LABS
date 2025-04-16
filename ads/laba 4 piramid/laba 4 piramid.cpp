#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stack> // Для итеративной реализации


// Функция разделения
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Итеративная функция быстрой сортировки
void quickSort(std::vector<int>& arr) {
    std::stack<std::pair<int, int>> st;
    st.push({ 0, arr.size() - 1 });

    while (!st.empty()) {
        int low = st.top().first;
        int high = st.top().second;
        st.pop();
        if (low < high) {
            int pi = partition(arr, low, high);
            // Сначала кладем в стек больший подмассив
            if (pi - low > high - pi) {
                st.push({ low, pi - 1 });
                st.push({ pi + 1, high });
            }
            else {
                st.push({ pi + 1, high });
                st.push({ low, pi - 1 });
            }

        }
    }
}



// Функция проверки отсортированности массива
template <typename T>
bool isSorted(const std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// Функция для чтения массива из файла
std::vector<int> readArrayFromFile(const std::string& filename) {
    std::vector<int> arr;
    std::ifstream file(filename);
    if (file.is_open()) {
        int val;
        while (file >> val) { // Читаем числа, пока не достигнем конца файла
            arr.push_back(val);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    return arr;
}


int main() {
    setlocale(LC_ALL, "ru");
    std::string filename = "array_1000000_-100000_100000.txt";

    // Читаем массив из файла
    std::vector<int> originalArray = readArrayFromFile(filename);
    if (originalArray.empty()) {
        std::cerr << "Error: Could not read array from file: " << filename << std::endl;
        return 1;
    }

    // Создаем копию для сортировки
    std::vector<int> arrayToSort = originalArray;
    std::cout << "Размер массива: " << arrayToSort.size() << std::endl;


    // Измеряем время сортировки
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arrayToSort);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Проверяем, отсортирован ли массив
    bool sorted = isSorted(arrayToSort);


    // Выводим результаты
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << std::setw(30) << std::left << "Алгоритм:" << "Быстрая сортировка" << std::endl;
    std::cout << std::setw(30) << std::left << "Размер массива:" << originalArray.size() << std::endl;
    std::cout << std::setw(30) << std::left << "Отсортирован:" << (sorted ? "Да" : "Нет") << std::endl;
    std::cout << std::setw(30) << std::left << "Среднее время сортировки:" << duration.count() << " мс" << std::endl;
    if (originalArray.size() <= 20) {
        std::cout << "Отсортированный массив: ";
        for (const auto& elem : arrayToSort) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------------------" << std::endl << std::endl;

    return 0;
}