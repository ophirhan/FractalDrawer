//
// Created by ophirhan on 06/01/2020.
//

#include "Fractal.h"
#include <cmath>
#include <iostream>

#define INVALID_INPUT "Invalid input"

Fractal::Fractal(int dim, int base_size) : _dim(dim), _size((int) pow(base_size, dim))
{
    if(dim < 1)
    {
        std::cerr << INVALID_INPUT << std::endl;
        exit(EXIT_FAILURE);
    }
    fill();
}

void Fractal::fill()
{
    std::string line;
    for(int i = 0; i < _size; i++)
    {
        line += " ";
    }
    for(int row = 0; row < _size; row++)
    {
        _shape.push_back(line);
    }
}

void Fractal::draw() const
{
    for(const std::string &line: _shape)
    {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

Fractal::~Fractal()
{
    _shape.clear();
    std::vector<std::string>().swap(_shape);
}

void Fractal::fillCorrect()
{
    for(int row=0;row<_size;row++)
    {
        for(int col = 0; col < _size; col++)
        {
            if(isFilled(col, row))
            {
                _shape[row][col] = '#';
            }
        }
    }
}

Carpet::Carpet(int dim):
Fractal(dim, 3)
{
    fillCorrect();
}

Triangle::Triangle(int dim) : Fractal(dim, 2)
{
    fillCorrect();
}

Vicsek::Vicsek(int dim) : Fractal(dim, 3)
{
    fillCorrect();
}

bool Carpet::isFilled(int x, int y) const
{
    if(x<=0 && y <= 0)
    {
        return true;
    }
    if(x%3 == 1 && y%3 == 1)
    {
        return false;
    }
    return isFilled(x/3, y/3);
}

bool Triangle::isFilled(int x, int y) const
{
    if(x<=0 && y <= 0)
    {
        return true;
    }
    if(x%2 == 1 && y%2 == 1)
    {
        return false;
    }
    return isFilled(x/2, y/2);
}

bool Vicsek::isFilled(int x, int y) const
{
    if(x<=0 && y <= 0)
    {
        return true;
    }
    if(x%3 == 1 ^ y%3 == 1)
    {
        return false;
    }
    return isFilled(x/3, y/3);
}


Fractal* FractalFactory::createFractal(int type, int dim)
{
    switch(type)
    {
        case 1:
            return new Carpet(dim);
        case 2:
            return new Triangle(dim);
        case 3:
            return new Vicsek(dim);
        default:
            return nullptr;
    }
}
