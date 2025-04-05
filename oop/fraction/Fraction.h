#pragma once

#include <iostream>

class Fraction {
public:
    Fraction();
    Fraction(long long num, long long den);
    // ��������� ���������
    void setNumerator(long long num);

    // ��������� ���������
    long long getNumerator() const;

    // ��������� �����������
    void setDenominator(long long den);

    // ��������� ����������� � ��������� ��������
    long long getDenominator() const;
    Fraction operator*(Fraction const& b) const;
    Fraction operator/(Fraction const& b) const;
    Fraction operator+(Fraction const& b) const;
    Fraction operator-(Fraction const& b) const;
    //���������� ���������
    bool operator<(Fraction const& b) const;
    bool operator>(Fraction const& b) const;
    bool operator==(Fraction const& b) const;
    bool operator!=(Fraction const& b) const;
    //������
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