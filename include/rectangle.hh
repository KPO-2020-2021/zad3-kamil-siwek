#pragma once

#include "size.hh"
#include "vector.hh"
#include <iostream>

class Rectangle
{

private:
    Vector size[SIZE_RECTANGLE]; //Tablica wektora

public:
    Rectangle();

    Rectangle(Vector Start, double h, double w);

    Rectangle operator+(const Vector &v);

    const Vector &operator[](int index) const;

    Vector &operator[](int index);
};

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(Vector Start, double h, double w)
{
    for (int i = 0; i < SIZE_RECTANGLE; i++)
        size[i] = Start;

    size[1][0] += w;
    size[2][0] += w;
    size[2][1] += h;
    size[3][1] += h;
}

Rectangle Rectangle::operator+(const Vector &v)
{
    Rectangle result;
    for (int i = 0; i < SIZE_RECTANGLE; ++i)
    {
        result[i] = size[i] + v;
    }
    return result;
}

const Vector &Rectangle::operator[](int index) const
{
    return size[index];
}

Vector &Rectangle::operator[](int index)
{
    return size[index];
}

std::ostream &operator<<(std::ostream &out, Rectangle const &tmp)
{
    for (int i = 0; i < SIZE_RECTANGLE; ++i)
    {
        out << tmp[i] << std::endl; // jeśli użyjemy tego przeciązenia do zapisu do pliku zapisze się to [x] \n [y] gnuplot szczytje punkty jakow wartosci wiersza z kolumn x y czy to nie bedzie powodowalo bledu?
    }
    out << tmp[0]<< std::endl;
    return out;
}