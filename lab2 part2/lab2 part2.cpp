
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stdexcept> // Для std::out_of_range
#include <limits> // Для numeric_limits

template <typename T>
class myarray {
private:
    size_t capacity;
    size_t count;
    T* items;

    void resize(size_t cap) {
        assert(cap >= capacity);
        T* items_ = new T[cap];
        // Инициализируем новую память конструктором по умолчанию
        for (size_t i = 0; i < cap; ++i) {
            items_[i] = T();
        }
        if (items) {
            std::copy(items, items + count, items_);
            delete[] items;
        }
        items = items_;
        capacity = cap;
    }

    void expand(size_t by) {
        assert(count + by >= 0);
        if (count + by > capacity) {
            resize(((count + by) * 2));
        }
    }

public:
    // Итератор
    class iterator {
    private:
        T* ptr;
    public:
        iterator(T* p = nullptr) : ptr(p) {}

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        iterator& operator++() {
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
        // Added decrement operators to be consistent with other iterators.
        iterator& operator--() {
            --ptr;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --ptr;
            return temp;
        }

        friend class myarray<T>; // Чтобы myarray имел доступ к private членам iterator
    };

    // Константный итератор
    class const_iterator {
    private:
        const T* ptr;
    public:
        const_iterator(const T* p = nullptr) : ptr(p) {}

        const T& operator*() const {
            return *ptr;
        }

        const T* operator->() const {
            return ptr;
        }

        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++ptr;
            return temp;
        }

        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }
        // Added decrement operators to be consistent with other iterators.
        const_iterator& operator--() {
            --ptr;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator temp = *this;
            --ptr;
            return temp;
        }

        friend class myarray<T>; // Чтобы myarray имел доступ к private членам const_iterator
    };
    myarray() : capacity(0), count(0), items(nullptr) {}

    myarray(const T arr[], size_t size) : capacity(size), count(size) {
        items = new T[capacity];
        if (items == nullptr) {
            throw std::bad_alloc();
        }
        std::memcpy(items, arr, size * sizeof(T));
    }

    myarray(const myarray& other) : capacity(other.capacity), count(other.count) {
        items = new T[capacity];
        if (items == nullptr) {
            throw std::bad_alloc();
        }
        std::memcpy(items, other.items, count * sizeof(T));
    }

    ~myarray() {
        delete[] items;
    }

    size_t size() const { return count; }

    void swap(myarray& other) {
        std::swap(capacity, other.capacity);
        std::swap(count, other.count);
        std::swap(items, other.items);
    }

    size_t find(T el) const {
        for (size_t i = 0; i < count; ++i) if (items[i] == el) return i;
        return -1;
    }

    // Перегрузка оператора ==
    bool operator==(const myarray& other) const {
        if (count != other.count) {
            return false; // Массивы разного размера не могут быть равны
        }
        for (size_t i = 0; i < count; ++i) {
            if (items[i] != other.items[i]) {
                return false; // Если хотя бы один элемент отличается, массивы не равны
            }
        }
        return true; // Если все элементы равны, массивы равны
    }

    // Перегрузка оператора !=
    bool operator!=(const myarray& other) const {
        return !(*this == other); // Используем уже реализованный оператор ==
    }
    // Методы получения итераторов
    iterator begin() { return iterator(items); }
    iterator end() { return iterator(items + count); }

    const_iterator begin() const { return const_iterator(items); }
    const_iterator end() const { return const_iterator(items + count); }

    const_iterator cbegin() const { return const_iterator(items); }
    const_iterator cend() const { return const_iterator(items + count); }

    // Вставка элемента по индексу. Если индекс некорректный, вернуть false;
    bool insert(size_t index, const T& value) {
        if (index > count) {
            return false; // Некорректный индекс
        }

        expand(1); // Увеличиваем размер массива

        // Сдвигаем элементы вправо, начиная с конца массива
        for (size_t i = count; i > index; --i) {
            items[i] = items[i - 1];
        }

        // Вставляем элемент
        items[index] = value;
        ++count;

        return true;
    }

    // Удаление элемента по индексу. Если индекс некорректный, вернуть false;
    bool erase(size_t index) {
        if (index >= count) {
            return false; // Некорректный индекс
        }

        // Сдвигаем элементы влево, начиная со следующего после удаляемого
        for (size_t i = index; i < count - 1; ++i) {
            items[i] = items[i + 1];
        }

        --count; // Уменьшаем количество элементов
        return true;
    }
    // Вставка элемента перед итератором
    iterator insert(iterator pos, T value) {
        if (pos.ptr < items || pos.ptr > items + count) {
            throw std::out_of_range("Iterator out of range");
        }
        // Вычисляем смещение итератора от начала массива
        size_t offset = pos.ptr - items;
        expand(1); // Увеличиваем размер массива



        // Получаем новый указатель на место вставки
        T* new_pos_ptr = items + offset;

        // Проверяем, не указывает ли итератор за конец массива
        if (new_pos_ptr == items + count) {
            // Вставка в конец массива
            items[count] = value;
            ++count;
            return iterator(items + count - 1);
        }
        else if (new_pos_ptr < items || new_pos_ptr > items + count) {
            // Итератор стал невалидным после resize
            throw std::out_of_range("Iterator out of range after resize");
        }

        // Вычисляем индекс для вставки
        size_t index = new_pos_ptr - items;

        // Сдвигаем элементы вправо, начиная с конца массива
        for (size_t i = count; i > index; --i) {
            items[i] = items[i - 1];
        }

        // Вставляем элемент
        items[index] = value;
        ++count;

        return iterator(items + index);
    }
    // Удаление элемента по итератору
    iterator erase(iterator pos) {
        if (pos.ptr < items || pos.ptr >= items + count) {
            throw std::out_of_range("Iterator out of range");
        }

        size_t index = pos.ptr - items; // Индекс удаляемого элемента

        // Сдвигаем элементы влево, начиная со следующего после удаляемого
        for (size_t i = index; i < count - 1; ++i) {
            items[i] = items[i + 1];
        }

        --count; // Уменьшаем количество элементов

        return iterator(items + index); // Возвращаем итератор на следующий элемент
    }

    // Удаление диапазона элементов по итераторам
    iterator erase(iterator first, iterator last) {
        if (first.ptr < items || first.ptr > items + count || last.ptr < items || last.ptr > items + count || first.ptr > last.ptr) {
            throw std::out_of_range("Iterator out of range");
        }

        size_t first_index = first.ptr - items;
        size_t last_index = last.ptr - items;
        size_t range_size = last_index - first_index;

        // Сдвигаем элементы влево, начиная с конца диапазона
        for (size_t i = last_index; i < count; ++i) {
            items[first_index + (i - last_index)] = items[i];
        }

        count -= range_size; // Уменьшаем количество элементов

        return iterator(items + first_index); // Возвращаем итератор на первый элемент после удаленного диапазона
    }
    // Добавление элемента в конец массива (оператор +)
    myarray operator+(T value) const {
        myarray new_array(*this); // Создаем копию текущего массива
        new_array.expand(1); // Расширяем место для нового элемента
        new_array.items[new_array.count++] = value; // Добавляем элемент
        return new_array;
    }

    // Добавление элемента в конец массива (оператор +=)
    myarray& operator+=(T value) {
        expand(1); // Расширяем массив
        items[count++] = value; // Добавляем элемент
        return *this; // Возвращаем ссылку на текущий массив
    }

    T& operator[](size_t index) {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return items[index];
    }

    // [] operator to access elements (const version)
    const T& operator[](size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return items[index];
    }

    // Удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false;
    bool erase_first(const T& value) {
        size_t index = find(value);
        if (index == static_cast<size_t>(-1)) { // Элемент не найден
            return false;
        }
        return erase(index); // Используем erase по индексу
    }

    // Удаление всех элементов с заданным значением;
    void erase_all(const T& value) {
        for (size_t i = 0; i < count; ) {
            if (items[i] == value) {
                erase(i); // erase сдвигает элементы, поэтому индекс не увеличиваем сразу
            }
            else {
                ++i;
            }
        }
    }
    // Вывод в консоль (потоковый)
    friend std::ostream& operator<<(std::ostream& os, const myarray& arr) {
        os << "[";
        for (size_t i = 0; i < arr.count; ++i) {
            os << arr.items[i];
            if (i < arr.count - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    // Ввод из консоли (потоковый)
    friend std::istream& operator>>(std::istream& is, myarray& arr) {
        size_t size;
        std::cout << "Enter the number of elements: ";
        is >> size;

        arr.resize(size);
        arr.count = size;

        std::cout << "Enter the elements: ";
        for (size_t i = 0; i < size; ++i) {
            is >> arr.items[i];
        }

        return is;
    }
    // Присваивание
    myarray& operator=(const myarray& other) {
        if (this != &other) { // Проверка на самоприсваивание
            myarray temp(other); // Используем конструктор копирования
            swap(temp); // Обмениваем содержимое с временным объектом
        }
        return *this;
    }

    // Сложение (конкатенация) с другим массивом (+ и +=)
    myarray operator+(const myarray& other) const {
        myarray result(*this); // Копируем текущий массив
        result += other; // Добавляем элементы из другого массива
        return result;
    }

    myarray& operator+=(const myarray& other) {
        for (size_t i = 0; i < other.count; ++i) {
            *this += other.items[i]; // Используем operator+= для добавления одного элемента
        }
        return *this;
    }
    // Сортировка элементов (любым алгоритмом)
    void sort() {
        std::sort(items, items + count);
    }

    // Поиск максимального/минимального элемента;
    T find_max() const {
        if (count == 0) {
            throw std::runtime_error("Array is empty");
        }
        T max_element = items[0];
        for (size_t i = 1; i < count; ++i) {
            if (items[i] > max_element) {
                max_element = items[i];
            }
        }
        return max_element;
    }

    T find_min() const {
        if (count == 0) {
            throw std::runtime_error("Array is empty");
        }
        T min_element = items[0];
        for (size_t i = 1; i < count; ++i) {
            if (items[i] < min_element) {
                min_element = items[i];
            }
        }
        return min_element;
    }
};
