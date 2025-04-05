#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

// Функция сортировки Шелла с разными вариантами шага
template <typename T>
void shellSort(std::vector<T>& arr, int gapType) {
    int n = arr.size();
    int gap;

    if (gapType == 1) {
        gap = n / 2;
        while (gap > 0) {
            for (int i = gap; i < n; ++i) {
                T temp = arr[i];
                int j = i;
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
            gap /= 2;
        }
    }
    else if (gapType == 2) {
        gap = n;
        while (gap > 1) {
            gap = gap / 2.2;
            if (gap < 1) {
                gap = 1;
            }
            for (int i = gap; i < n; ++i) {
                T temp = arr[i];
                int j = i;
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    }
    else if (gapType == 3) {
        for (int k = 1; (gap = n / std::pow(2, k)) > 0; ++k) {
            for (int i = gap; i < n; ++i) {
                T temp = arr[i];
                int j = i;
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    }
}

// Функция проверки отсортированности массива
template <typename T>
bool isSorted(const std::vector<T>& arr) {
    return std::is_sorted(arr.begin(), arr.end());
}

// Функция для генерации массива случайных чисел
std::vector<int> generateRandomArray(int size, int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = distrib(gen);
    }
    return arr;
}

// Функция для преобразования массива в строку
template <typename T>
std::string arrayToString(const std::vector<T>& arr) {
    std::stringstream ss;
    for (size_t i = 0; i < arr.size(); ++i) {
        ss << arr[i];
        if (i < arr.size() - 1) {
            ss << ", ";
        }
    }
    return ss.str();
}

int main() {
    setlocale(LC_ALL, "RU");// Размеры массивов
    std::vector<int> sizes = { 10000, 100000, 1000000 };

    // Диапазоны значений
    std::vector<std::pair<int, int>> ranges = {
        {-10, 10},
        {-1000, 1000},
        {-100000, 100000}
    };

    // Варианты шага для сортировки Шелла
    std::vector<int> gapTypes = { 1, 2, 3 };

    // Открываем файл для записи неотсортированных массивов
    std::ofstream outputFile("unsorted_arrays.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи неотсортированных массивов!" << std::endl;
        return 1;
    }

    // Генерация и сортировка массивов
    for (int size : sizes) {
        for (const auto& range : ranges) {
            for (int gapType : gapTypes) {
                std::cout << "Генерация массива размера " << size << " в диапазоне [" << range.first << ", " << range.second << "]..."
                    << " Вариант шага " << gapType << std::endl;

                std::vector<int> arr = generateRandomArray(size, range.first, range.second);
                std::vector<int> unsortedArr = arr; // Копия неотсортированного массива

                // Засекаем время перед сортировкой
                auto start = std::chrono::high_resolution_clock::now();

                // Сортируем массив
                shellSort(arr, gapType);

                // Засекаем время после сортировки
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;

                // Проверяем отсортированность массива
                bool sorted = isSorted(arr);

                // Записываем неотсортированный массив в файл
                std::string unsortedArrayString = arrayToString(unsortedArr);
                outputFile << unsortedArrayString << std::endl;

                std::cout << "Массив отсортирован: " << (sorted ? "Да" : "Нет") << std::endl;
                std::cout << "Время сортировки: " << duration.count() << " секунд" << std::endl;
                std::cout << "----------------------" << std::endl;
            }
        }
    }

    outputFile.close();
    std::cout << "Неотсортированные массивы сохранены в файл 'unsorted_arrays.txt'" << std::endl;
    return 0;
}