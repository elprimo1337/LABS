// against hoar sort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <fstream>
#include <chrono>
#include <iostream>
#include <vector>
struct elem
{
    int L, R;
};

void nonRecH(std::vector<int>& arr, int l, int r) {
    elem* S = new elem[arr.size()+10]; // Выделяем память под стек
    int k = 0; S[0].L = 0; S[0].R = arr.size()-1;
    while (k >= 0) { // пока стек не пуст
        l = S[k].L; r = S[k].R; k--;
        if (l < r) {
            int i = l; int j = r; int x = arr[(l + r) / 2];
            while (i <= j) {
                while (arr[i] < x) {
                    i++;
                }
                while (arr[j] > x) {
                    j--;
                }
                if (i <= j) {
                    std::swap(arr[i], arr[j]); i++; j--;
                }
            }
            //кладем в стек правый фрагмент
            k++; S[k].L = i; S[k].R = r;
            //кладем в стек левый фрагмент
            k++; S[k].L = l; S[k].R = j;
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
    nonRecH(numbers, 0, numbers.size() - 1); // Сортировка вектора
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