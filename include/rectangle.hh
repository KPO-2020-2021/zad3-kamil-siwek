#pragma once

#include "size.hh"
#include "vector.hh"
#include <iostream>

class Rectangle {

private:

    Vector size[SIZE];     //Tablica wektora

public:

    Rectangle();

    Rectangle(Vector [SIZE]);

    Rectangle operator + (const Vector &v);

    const Vector &operator [] (int index) const;

    Vector &operator [] (int index);

};

 Rectangle::Rectangle()
 {

 }

    Rectangle::Rectangle(Vector [SIZE])
    {}

    Rectangle Rectangle::operator + (const Vector &v)
    {
        Rectangle result;
    for (int i = 0; i < SIZE; ++i) 
    {
        result[i] = size[i] + v;
    }
    return result;
    }

    const Vector &Rectangle::operator [] (int index) const
    {
        return size[index];
    }

    Vector &Rectangle::operator [] (int index)
    {
         return size[index];
    }

std::ostream &operator << (std::ostream &out, Rectangle const &tmp) 
{
   for (int i = 0; i < SIZE; ++i) {
        out  << tmp[i] << std::endl; // jeśli użyjemy tego przeciązenia do zapisu do pliku zapisze się to [x] \n [y] gnuplot szczytje punkty jakow wartosci wiersza z kolumn x y czy to nie bedzie powodowalo bledu?
    }
    return out;
}