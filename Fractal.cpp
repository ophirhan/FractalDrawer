//
// Created by ophirhan on 06/01/2020.
//

#include "Fractal.h"
#include <cmath>
#include <iostream>

#define INVALID_INPUT "Invalid input"

/**
 * @brief Creates fractal object.
 * @param dim dimension of the fractal.
 * @param base_size size of dim 1 of the specific fractal.
 */
Fractal::Fractal(int dim, int base_size) : _dim(dim), _size((int) pow(base_size, dim))
{
    if (dim < 1)
    {
        std::cerr << INVALID_INPUT << std::endl;
        exit(EXIT_FAILURE);
    }
    fill();
}

/**
 * @brief fills the string vector to the correct size.
 */
void Fractal::fill()
{
    std::string line;
    for (int i = 0; i < _size; i++)
    {
        line += " ";
    }
    for (int row = 0; row < _size; row++)
    {
        _shape.push_back(line);
    }
}

/**
 * @brief draws the fractal to screen.
 */
void Fractal::draw() const
{
    for (const std::string &line: _shape)
    {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief frees memory of fractal..
 */
Fractal::~Fractal()
{
    _shape.clear();
    std::vector<std::string>().swap(_shape);
}

/**
 * @brief fills the fractal according to its type.
 */
void Fractal::fillCorrect()
{
    for (int row = 0; row < _size; row++)
    {
        for (int col = 0; col < _size; col++)
        {
            if (isFilled(col, row))
            {
                _shape[row][col] = '#';
            }
        }
    }
}

/**
 * Creates new carpet fractal.
 * @param dim the dimension of new fractal.
 */
Carpet::Carpet(int dim) :
        Fractal(dim, 3)
{
    fillCorrect();
}

/**
 * Creates new triangle fractal.
 * @param dim the dimension of new fractal.
 */
Triangle::Triangle(int dim) : Fractal(dim, 2)
{
    fillCorrect();
}

/**
 * Creates new vicsek fractal.
 * @param dim the dimension of new fractal.
 */
Vicsek::Vicsek(int dim) : Fractal(dim, 3)
{
    fillCorrect();
}

/**
 * @brief Checks if a given char in the vector string should be filled.
 * @param x number of char in the string.
 * @param y number of string in vector.
 * @return true if given location should be filled, false otherwise.
 */
bool Carpet::isFilled(int x, int y) const
{
    if (x <= 0 && y <= 0)
    {
        return true;
    }
    if (x % 3 == 1 && y % 3 == 1)
    {
        return false;
    }
    return isFilled(x / 3, y / 3);
}

/**
 * @brief Checks if a given char in the vector string should be filled.
 * @param x number of char in the string.
 * @param y number of string in vector.
 * @return true if given location should be filled, false otherwise.
 */
bool Triangle::isFilled(int x, int y) const
{
    if (x <= 0 && y <= 0)
    {
        return true;
    }
    if (x % 2 == 1 && y % 2 == 1)
    {
        return false;
    }
    return isFilled(x / 2, y / 2);
}

/**
 * @brief Checks if a given char in the vector string should be filled.
 * @param x number of char in the string.
 * @param y number of string in vector.
 * @return true if given location should be filled, false otherwise.
 */
bool Vicsek::isFilled(int x, int y) const
{
    if (x <= 0 && y <= 0)
    {
        return true;
    }
    if (x % 3 == 1 ^ y % 3 == 1)
    {
        return false;
    }
    return isFilled(x / 3, y / 3);
}

/**
 * Creates a new fractal object.
 * @param type number specifying which fractal to create.
 * @param dim number specifying what is the dimension of the new fractal.
 * @return
 */
Fractal *FractalFactory::createFractal(int type, int dim)
{
    switch (type)
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
