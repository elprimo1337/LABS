#pragma once

#include <iostream>

class Fraction {
public:
    Fraction();
    Fraction(long long num, long long den);
    // Установка числителя
    void setNumerator(long long num);

    // Получение числителя
    long long getNumerator() const;

    // Установка знаменателя
    void setDenominator(long long den);

    // Получение знаменателя и операторы действий
    long long getDenominator() const;
    Fraction operator*(Fraction const& b) const;
    Fraction operator/(Fraction const& b) const;
    Fraction operator+(Fraction const& b) const;
    Fraction operator-(Fraction const& b) const;
    //операторты сравнения
    bool operator<(Fraction const& b) const;
    bool operator>(Fraction const& b) const;
    bool operator==(Fraction const& b) const;
    bool operator!=(Fraction const& b) const;
    //фрэнды
    friend std::istream& operator>>(std::istream& in, Fraction& f);
    friend std::ostream& operator<<(std::ostream& out, Fraction const& f);
    // Уникальный метод 1:  Нахождение обратной дроби
    Fraction inverse() const;
    // Уникальный метод 2:
    bool isProper() const;


private:
    long long num;
    long long den;
    void reduce();

};