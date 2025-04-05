#pragma once

#include <iostream>

class Fraction {
public:
    Fraction();
    Fraction(long long num_, long long den_);
    // Установка числителя
    void setNumerator(long long sex);

    // Получение числителя
    long long getNumerator();

    // Установка знаменателя
    void setDenominator(long long sex);

    // Получение знаменателя
    long long getDenominator();
    Fraction operator*(Fraction b);
    Fraction operator/(Fraction b);
    Fraction operator+(Fraction const& b) const;
    Fraction operator-(Fraction const& b) const;
    //goida
    bool operator<(Fraction const& b) const;
    bool operator>(Fraction const& b) const;
    bool operator==(Fraction const& b) const;
    bool operator!=(Fraction const& b) const;
    //goida
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