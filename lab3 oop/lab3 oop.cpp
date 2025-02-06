
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class BitVector {
private:
    std::vector<unsigned char> data;
    size_t bit_count;

    size_t get_byte_index(size_t bit_index) const {//позырить байт
        return bit_index / 8;
    }

    unsigned char get_bit_mask(size_t bit_index) const {//позырить бит
        return 1 << (bit_index % 8);
    }

public:
    class BoolRank { // Класс BoolRank
    private:
        BitVector* bv; // Указатель на BitVector
        size_t index;  // Индекс бита

    public:
        BoolRank(BitVector* bitVector, size_t bitIndex) : bv(bitVector), index(bitIndex) {}

        // Операторы присваивания
        BoolRank& operator=(bool value) {
            bv->set_bit(index, value);
            return *this;
        }

        BoolRank& operator=(int value) {
            bv->set_bit(index, value != 0);
            return *this;
        }

        BoolRank& operator=(const BoolRank& other) {
            bv->set_bit(index, other.bv->get_bit(other.index));
            return *this;
        }

        // Операторы преобразования типов
        explicit operator bool() const {
            return bv->get_bit(index);
        }

        explicit operator int() const {
            return bv->get_bit(index);
        }

        //Битовые операции
        BoolRank& operator&=(bool value) {
            bv->set_bit(index, bv->get_bit(index) & value);
            return *this;
        }

        BoolRank& operator|=(bool value) {
            bv->set_bit(index, bv->get_bit(index) | value);
            return *this;
        }

        BoolRank& operator^=(bool value) {
            bv->set_bit(index, bv->get_bit(index) ^ value);
            return *this;
        }


        BoolRank operator&(bool value) const {
            BoolRank result = *this;
            result &= value;
            return result;
        }

        BoolRank operator|(bool value) const {
            BoolRank result = *this;
            result |= value;
            return result;
        }

        BoolRank operator^(bool value) const {
            BoolRank result = *this;
            result ^= value;
            return result;
        }

    };
    // Конструкторы (желтый)
    BitVector() : bit_count(0) {} // Конструктор по умолчанию (желтый)

    BitVector(size_t size, bool initial_value = false) : bit_count(size) { // (желтый)
        size_t byte_count = (size + 7) / 8;
        data.resize(byte_count, initial_value ? 0xFF : 0x00);
        if (!initial_value) clear();
    }

    BitVector(const char* bit_string) { // (желтый)
        bit_count = 0;
        size_t len = 0;
        while (bit_string[len] != '\0') {
            if (bit_string[len] == '0' || bit_string[len] == '1') {
                bit_count++;
            }
            len++;
        }

        size_t byte_count = (bit_count + 7) / 8;
        data.resize(byte_count, 0x00);//ресайз который векторный

        size_t current_bit = 0;
        for (size_t i = 0; bit_string[i] != '\0'; ++i) {
            if (bit_string[i] == '0' || bit_string[i] == '1') {
                set_bit(current_bit, bit_string[i] == '1');
                current_bit++;
            }
        }
    }

    BitVector(const BitVector& other) : bit_count(other.bit_count), data(other.data) {} // (желтый)

    // Деструктор (желтый)
    ~BitVector() {} //(желтый)

    // Методы (желтый)
    size_t length() const { //(желтый)
        return bit_count;
    }

    void swap(BitVector& other) { //(желтый)
        std::swap(data, other.data);
        std::swap(bit_count, other.bit_count);
    }

    // Ввод/вывод в консоль (потоковый) (желтый)
    friend std::ostream& operator<<(std::ostream& os, const BitVector& bv) { //(желтый)
        for (size_t i = 0; i < bv.bit_count; ++i) {
            os << bv.get_bit(i);
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, BitVector& bv) { //(желтый)
        std::string input;
        is >> input;
        BitVector temp(input.c_str());
        bv.swap(temp);
        return is;
    }

    // Инверсия (зеленый)
    void invert() { //(зеленый)
        for (unsigned char& byte : data) {
            byte = ~byte;
        }
    }

    void invert_bit(size_t index) { //(зеленый)
        if (index >= bit_count) {
            throw std::out_of_range("Index out of range");
        }
        size_t byte_index = get_byte_index(index);
        unsigned char mask = get_bit_mask(index);
        data[byte_index] ^= mask;
    }

    // Установка бита (зеленый)
    void set_bit(size_t index, bool value) { //(зеленый)
        if (index >= bit_count) {
            throw std::out_of_range("Index out of range");
        }
        size_t byte_index = get_byte_index(index);
        unsigned char mask = get_bit_mask(index);

        if (value) {
            data[byte_index] |= mask;
        }
        else {
            data[byte_index] &= ~mask;
        }
    }

    bool get_bit(size_t index) const { //(зеленый)
        if (index >= bit_count) {
            throw std::out_of_range("Index out of range");
        }
        size_t byte_index = get_byte_index(index);
        unsigned char mask = get_bit_mask(index);
        return (data[byte_index] & mask) != 0;
    }

    void set_bits(size_t start_index, size_t count, bool value) { //(зеленый)
        if (start_index + count > bit_count) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = 0; i < count; ++i) {
            set_bit(start_index + i, value);
        }
    }

    void set_all(bool value) { //(зеленый)
        for (auto& byte : data) {
            byte = value ? 0xFF : 0x00;
        }
    }

    void clear() {
        set_all(false);
    }

    size_t weight() const { //(зеленый)
        size_t count = 0;
        for (size_t i = 0; i < bit_count; ++i) {
            if (get_bit(i)) {
                count++;
            }
        }
        return count;
    }

    // Перегрузки операторов (с BoolRank)
    BoolRank operator[](size_t index) { //()
        if (index >= bit_count) {
            throw std::out_of_range("Index out of range");
        }
        return BoolRank(this, index);
    }

    BitVector& operator=(const BitVector& other) { //()
        if (this != &other) {
            bit_count = other.bit_count;
            data = other.data;
        }
        return *this;
    }

    BitVector& operator&=(const BitVector& other) { //()
        if (bit_count != other.bit_count) {
            throw std::invalid_argument("BitVectors must have the same size for &=");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] &= other.data[i];
        }
        return *this;
    }

    BitVector operator&(const BitVector& other) const { //()
        BitVector result = *this;
        result &= other;
        return result;
    }

    // Побитовое сложение (|, |=) (нет цвета)
    BitVector& operator|=(const BitVector& other) { //()
        if (bit_count != other.bit_count) {
            throw std::invalid_argument("BitVectors must have the same size for |=");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] |= other.data[i];
        }
        return *this;
    }

    BitVector operator|(const BitVector& other) const { //()
        BitVector result = *this;
        result |= other;
        return result;
    }

    // Побитовое исключающее ИЛИ (^, ^=) ()
    BitVector& operator^=(const BitVector& other) { //()
        if (bit_count != other.bit_count) {
            throw std::invalid_argument("BitVectors must have the same size for ^=");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] ^= other.data[i];
        }
        return *this;
    }

    BitVector operator^(const BitVector& other) const { //()
        BitVector result = *this;
        result ^= other;
        return result;
    }

    // Побитовый сдвиг влево (<<, <<=) ()
    BitVector& operator<<=(size_t shift) {
        if (shift == 0) return *this;
        if (shift >= bit_count) {
            set_all(false); // Если сдвиг больше или равен размеру вектора, то заполняем все биты нулями
            return *this;
        }

        // Создаем новый вектор для хранения сдвинутых битов
        BitVector shifted(bit_count);

        // Копируем биты со сдвигом
        for (size_t i = 0; i < bit_count - shift; ++i) {
            shifted.set_bit(i + shift, get_bit(i));
        }

        // Присваиваем текущему объекту сдвинутый вектор
        *this = shifted;

        return *this;
    }

    BitVector operator<<(size_t shift) const {
        BitVector result = *this;
        result <<= shift;
        return result;
    }


    // Побитовый сдвиг вправо (>>, >>=) (нет цвета)
    BitVector& operator>>=(size_t shift) {
        if (shift == 0) return *this;
        if (shift >= bit_count) {
            set_all(false);  // Если сдвиг больше или равен размеру вектора, то заполняем все биты нулями
            return *this;
        }

        // Создаем новый вектор для хранения сдвинутых битов
        BitVector shifted(bit_count);

        // Копируем биты со сдвигом
        for (size_t i = shift; i < bit_count; ++i) {
            shifted.set_bit(i - shift, get_bit(i));
        }

        // Присваиваем текущему объекту сдвинутый вектор
        *this = shifted;

        return *this;
    }

    BitVector operator>>(size_t shift) const {
        BitVector result = *this;
        result >>= shift;
        return result;
    }

    // Побитовая инверсия (~) ()
    BitVector operator~() const {
        BitVector result = *this;
        result.invert();
        return result;
    }

};

int main() {
    // Создаем BitVector длиной 15, инициализированный нулями
    BitVector bv(15);
    std::cout << "Initial bv: " << bv << std::endl; // Вывод: 000000000000000

    // Устанавливаем несколько битов в 1
    bv[0] = true;
    bv[5] = 1;
    bv[10] = true;
    std::cout << "bv after setting bits 0, 5, 10 to 1: " << bv << std::endl; // Вывод: 100001000010000

    // Инвертируем бит 7
    bv.invert_bit(7);
    std::cout << "bv after inverting bit 7: " << bv << std::endl; // Вывод: 100001010010000

    // Проверяем значение бита 5
    std::cout << "Value of bit 5: " << (int)bv[5] << std::endl; // Вывод: 1

    // Устанавливаем диапазон битов (2-6) в 1
    bv.set_bits(2, 5, true);
    std::cout << "bv after setting bits 2-6 to 1: " << bv << std::endl; // Вывод: 10111111010010000

    // Считаем количество установленных битов
    std::cout << "Weight of bv: " << bv.weight() << std::endl; // Вывод: 9

    // Инвертируем весь вектор
    bv.invert();
    std::cout << "Inverted bv: " << bv << std::endl; // Вывод: 010000001011011

    // Побитовые операции
    BitVector bv2(15, true);
    std::cout << "bv2 (all 1s): " << bv2 << std::endl; // Вывод: 111111111111111

    BitVector bv3 = bv & bv2;
    std::cout << "bv3 = bv & bv2: " << bv3 << std::endl; // Вывод: Результат побитового И

    BitVector bv4 = bv | bv2;
    std::cout << "bv4 = bv | bv2: " << bv4 << std::endl; // Вывод: Результат побитового ИЛИ

    BitVector bv5 = bv ^ bv2;
    std::cout << "bv5 = bv ^ bv2: " << bv5 << std::endl; // Вывод: Результат побитового XOR

    //Сдвиги
    BitVector bv6 = bv << 2;
    std::cout << "bv6 = bv << 2: " << bv6 << std::endl; // Вывод:  сдвиг влево

    BitVector bv7 = bv >> 3;
    std::cout << "bv7 = bv >> 3: " << bv7 << std::endl; // Вывод: сдвиг вправо

    return 0;
}
