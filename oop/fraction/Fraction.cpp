#include <cmath>
#include <stdexcept>

#include "Fraction.h"

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
Fraction::Fraction () { num = 0; den = 1; }
Fraction::Fraction(long long num_, long long den_) {
    num = num_;
    den = den_;
    if (den == 0) {
        throw std::runtime_error("Деление на ноль");
    }
    reduce();
}
void Fraction::reduce()
{
    long long common = gcd(std::abs(num), std::abs(den));
    num /= common;
    den /= common;
    // Обработка случая деления на ноль
    if (den == 0) {
        throw std::runtime_error("Деление на ноль");
    }
    if (den < 0) {
        num *= -1;
        den *= -1;
    }
}
void Fraction:: setNumerator(long long sex) { num = sex; reduce(); }
long long Fraction:: getNumerator()const { return num; }
void Fraction:: setDenominator(long long sex) {
    if (sex == 0) {
        throw std::runtime_error("Деление на ноль");
    }
    den = sex;
    reduce();
}
long long Fraction:: getDenominator() const { return den; }
Fraction Fraction:: operator*(Fraction const&b)const {
    return Fraction(num * b.num, den * b.den);
}
Fraction Fraction:: operator/(Fraction const&b)const {
    return Fraction(num * b.den, den * b.num);
}
Fraction Fraction:: operator+(Fraction const& b) const {
    long long num_ = num * b.den + den * b.num;
    long long den_ = den * b.den;
    return Fraction(num_, den_);
}
Fraction Fraction:: operator-(Fraction const& b) const {
    return *this + Fraction(-1, 1) * b;//хайп свэг ниггерс
}
bool Fraction:: operator<(Fraction const& b) const {
    return num * b.den < b.num * den;
}
bool Fraction:: operator>(Fraction const& b) const {
    return !(*this < b);
}
bool Fraction:: operator==(Fraction const& b) const {
    return num * b.den == b.num * den;
}
bool Fraction:: operator!=(Fraction const& b) const {
    return !(*this == b);
}
std::istream&  operator>>(std::istream& in, Fraction& f) {
    in >> f.num >> f.den; f.reduce();
    return in;
}
std::ostream& operator<<(std::ostream& out, Fraction const& f) {
    out << f.num << "/" << f.den;
    return out;
}
Fraction Fraction:: inverse() const {
    if (num == 0) {
        throw std::runtime_error("Обратная дробь от 0/1 не существует");
    }
    return Fraction(den, num);
}
bool Fraction:: isProper() const {
    return std::abs(num) < std::abs(den);
}