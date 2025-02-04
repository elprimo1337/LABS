#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h> // Include для WinAPI

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

// Функция быстрой сортировки
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Функция для проверки отсортированности массива
bool isSorted(const std::vector<int>& arr) {
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
        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);
        int val;
        while (iss >> val) {
            arr.push_back(val);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    return arr;
}

// Функция для вывода отчета
void printReport(int array_size, const std::vector<int>& original_array,
    std::vector<int> sorted_array, long long duration_ms, bool sorted) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << std::setw(30) << std::left << "Алгоритм:" << "Быстрая сортировка" << std::endl;
    std::cout << std::setw(30) << std::left << "Размер массива:" << array_size << std::endl;
    std::cout << std::setw(30) << std::left << "Отсортирован:" << (sorted ? "Да" : "Нет") << std::endl;
    std::cout << std::setw(30) << std::left << "Среднее время сортировки:" << duration_ms << " мс" << std::endl;
    if (array_size <= 20) {
        std::cout << "Отсортированный массив: ";
        for (const auto& elem : sorted_array) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------------------" << std::endl << std::endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    std::vector<int> sizes = { 10000, 100000, 1000000 };
    std::vector<std::pair<int, int>> ranges = {
        {-10, 10},
        {-1000, 1000},
        {-100000, 100000}
    };

    // Получаем путь к текущей директории
    char currentDir[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDir);
    std::cout << "Текущий путь: " << currentDir << std::endl;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    std::string searchPattern = std::string(currentDir) + "\\*.txt"; // Шаблон поиска файлов
    hFind = FindFirstFileA(searchPattern.c_str(), &findFileData);


    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "FindFirstFile failed" << std::endl;
        return 1;
    }

    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        std::string filename = findFileData.cFileName;

        for (int i = 0; i < sizes.size(); ++i) {
            int size = sizes[i];
            for (int j = 0; j < ranges.size(); ++j) {
                int min_val = ranges[j].first;
                int max_val = ranges[j].second;
                std::string target_filename = "array_" + std::to_string(size) + "_" + std::to_string(min_val) + "_" + std::to_string(max_val) + ".txt";

                if (filename == target_filename) {
                    std::vector<int> arr = readArrayFromFile(filename);
                    if (arr.empty()) {
                        std::cerr << "Error reading array from file: " << filename << std::endl;
                        continue;
                    }
                    std::cout << "Тестирование массива (размер " << size << ", диапазон " << min_val << "/" << max_val << "):" << std::endl;
                    std::vector<int> sorted_arr = arr;
                    auto start_time = std::chrono::high_resolution_clock::now();
                    quickSort(sorted_arr, 0, sorted_arr.size() - 1);
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                    bool is_sorted = isSorted(sorted_arr);
                    printReport(size, arr, sorted_arr, duration.count(), is_sorted);
                }
            }
        }


    } while (FindNextFileA(hFind, &findFileData) != 0);


    FindClose(hFind);


    return 0;
}