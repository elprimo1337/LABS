#pragma once

#include <iostream>

class Fraction {
public:
    Fraction();
    Fraction(long long num_, long long den_);
    // ��������� ���������
    void setNumerator(long long sex);

    // ��������� ���������
    long long getNumerator();

    // ��������� �����������
    void setDenominator(long long sex);

    // ��������� �����������
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
    // ���������� ����� 1:  ���������� �������� �����
    Fraction inverse() const;
    // ���������� ����� 2:
    bool isProper() const;


private:
    long long num;
    long long den;
    void reduce();

};