#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

class myarray {
private:
	size_t capacity;
	size_t count;
	int* items;
	void resize(size_t cap) {
		assert(cap >= capacity);
		int* items_ = new int[cap];
		if (items) {
			std::copy(items, items + count, items_);  // Используем std::copy
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
		int* ptr;
	public:
		iterator(int* p = nullptr) : ptr(p) {}

		int& operator*() const {
			return *ptr;
		}

		int* operator->() const {
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

		friend class myarray; // Чтобы myarray имел доступ к private членам iterator
	};

	// Константный итератор
	class const_iterator {
	private:
		const int* ptr;
	public:
		const_iterator(const int* p = nullptr) : ptr(p) {}

		const int& operator*() const {
			return *ptr;
		}

		const int* operator->() const {
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

		friend class myarray; // Чтобы myarray имел доступ к private членам const_iterator
	};
	myarray() :capacity(0), count(0), items(nullptr) {}
	myarray(const int arr[], size_t size) : capacity(size), count(size) {
		items = new int[capacity];
		if (items == nullptr) {
			throw std::bad_alloc();
		}
		std::memcpy(items, arr, size * sizeof(int));
	}
	myarray(const myarray& other) : capacity(other.capacity), count(other.count) {
		items = new int[capacity];
		if (items == nullptr) {
			throw std::bad_alloc();
		}
		std::memcpy(items, other.items, count * sizeof(int));
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
	size_t find(int el) const {
		for (size_t i = 0; i < count; ++i) if (items[i] == el) return i;
		return -1;
	}
	//до сюда с пивом пойдет
	friend std::ostream& operator<<(std::ostream& out, myarray& arr) {
		for (size_t i = 0; i < arr.count; i++) {
			out << arr.items[i] << ' ';
		}
		return out;
	}
	friend std::istream& operator>>(std::istream& is, myarray& arr) {
		int value;
		while (is >> value) {
			arr.expand(1);
			arr.items[arr.count] = value;
			arr.count++;
		}
		return is;
	}

	//фрэнды пойдут
	void sort() {
		std::sort(items, items + count);
	}
	bool insert(size_t index, int value) {
		if (index > count) return false; // Индекс за пределами

		expand(1); // 
		for (size_t i = count; i > index; --i) {
			items[i] = items[i - 1];
		}
		items[index] = value;
		++count;
		return true;
	}
	bool removebyindex(size_t index) {
		if (index >= count) return false; // Индекс за пределами массива

		// Сдвигаем элементы влево
		for (size_t i = index; i < count - 1; ++i) {
			items[i] = items[i + 1];
		}
		--count;
		return true; // Возвращаем true, если удаление прошло успешно
	}

	bool remove(int el) {
		size_t index = find(el);
		if (index == -1) return false; // Элемент не найден
		return removebyindex(index);
	}

	const int& operator[](size_t index) const { // Перегрузка для const-объектов
		assert(index < count); // Проверка выхода за границы массива
		return items[index];
	}
	void removeallbyvalue(int value) {
		size_t newCount = 0;
		for (size_t i = 0; i < count; ++i) {
			if (items[i] != value) {
				items[newCount++] = items[i];
			}
		}
		count = newCount;
	}

	int max() {
		assert(count);
		int m = items[0];
		for (int i = 0; i < count; i++) {
			if (items[i] >= m) {
				m = items[i];
			}
		}
		return m;
	}
	int min() {
		assert(count);
		int m = items[0];
		for (int i = 0; i < count; i++) {
			if (items[i] <= m) {
				m = items[i];
			}
		}
		return m;
	}
	myarray& operator=(const myarray& other) { // Оператор присваивания
		if (this != &other) { // Проверка самоприсваивания
			delete[] items;
			capacity = other.capacity;
			count = other.count;
			items = new int[capacity];
			std::copy(other.items, other.items + count, items);
		}
		return *this;
	}
	myarray operator+(const myarray& other) const {
		myarray result;
		result.resize(count + other.count);
		std::copy(items, items + count, result.items);
		std::copy(other.items, other.items + other.count, result.items + count);
		result.count = count + other.count;
		return result;
	}
	myarray& operator+=(const myarray& other) {
		resize(count + other.count);
		std::copy(other.items + other.count, other.items, items + count);
		count += other.count;
		return *this;
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
	//закончилось синее
	
	 // Добавление элемента в конец массива (оператор +)
	myarray operator+(int value) const {
		myarray new_array(*this); // Создаем копию текущего массива
		new_array.expand(1); // Расширяем место для нового элемента
		new_array.items[new_array.count++] = value; // Добавляем элемент
		return new_array;
	}

	// Добавление элемента в конец массива (оператор +=)
	myarray& operator+=(int value) {
		expand(1); // Расширяем массив
		items[count++] = value; // Добавляем элемент
		return *this; // Возвращаем ссылку на текущий массив
	}
	// Методы получения итераторов
	iterator begin() { return iterator(items); }
	iterator end() { return iterator(items + count); }

	const_iterator begin() const { return const_iterator(items); }
	const_iterator end() const { return const_iterator(items + count); }

	const_iterator cbegin() const { return const_iterator(items); }
	const_iterator cend() const { return const_iterator(items + count); }

	// Вставка элемента перед итератором
	iterator insert(iterator pos, int value) {
		if (pos.ptr < items || pos.ptr > items + count) {
			throw std::out_of_range("Iterator out of range");
		}
		size_t index = pos.ptr - items; // Вычисляем индекс позиции вставки
		expand(1);// Увеличиваем размер массива
		// Сдвигаем элементы вправо, начиная с конца массива
		for (size_t i = count; i > index; --i) {
			items[i] = items[i - 1];
		}
		items[index] = value; // Вставляем новое значение
		++count; // Увеличиваем счетчик элементов

		return iterator(items + index); // Возвращаем итератор на вставленный элемент
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


};
int main() {
	int initial_array[] = { 1, 2 };
	myarray arr(initial_array, 2);

	// Вывод элементов массива с использованием итераторов
	std::cout << "Original array: ";
	for (myarray::iterator it = arr.begin(); it != arr.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// Вставка элемента перед итератором
	myarray::iterator it = arr.begin();
	++it; // Перемещаемся на второй элемент
	++it;
	arr.insert(it, 10);
	std::cout << "After inserting 10: ";
	for (myarray::iterator it = arr.begin(); it != arr.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// Удаление элемента с помощью итератора
	it = arr.begin();
	++it; // Перемещаемся на второй элемент
	it = arr.erase(it);
	std::cout << "After erasing: ";
	for (myarray::iterator it = arr.begin(); it != arr.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	return 0;
}
