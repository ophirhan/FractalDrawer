//
// Created by ophirhan on 06/01/2020.
//

#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H

#include <vector>
#include <string>

/**
 * @brief Fractal object for fractal project.
 */
class Fractal
{
public:

    /**
     * @brief draws the fractal to screen.
     */
    void draw() const;

    /**
     * @brief Creates fractal object.
     * @param dim dimension of the fractal.
     * @param base_size size of dim 1 of the specific fractal.
     */
    Fractal(int dim, int base_size);

    /**
     * @brief frees memory of fractal..
     */
    virtual ~Fractal();

protected:

    /**
     * @brief Dimension of the fractal.
     */
    int _dim;

    /**
     * @brief size of the fractal (height and width).
     */
    int _size;

    /**
     * @brief vertical vector containing horizontal strings.
     * visual description of the fractal.
     */
    std::vector<std::string> _shape;

    /**
     * @brief fills the fractal according to its type.
     */
    void fillCorrect();

    /**
     * @brief fills the string vector to the correct size.
     */
    void fill();

    /**
     * @brief Checks if a given char in the vector string should be filled.
     * @param x number of char in the string.
     * @param y number of string in vector.
     * @return true if given location should be filled, false otherwise.
     */
    virtual bool isFilled(int x, int y) const = 0;
};

/**
 * @brief Sierpenski Carpet fractal object for fractal project.
 */
class Carpet : public Fractal
{
public:
    /**
     * @brief Creates new carpet fractal.
     * @param dim the dimension of new fractal.
     */
    Carpet(int dim);

    /**
     * @brief Checks if a given char in the vector string should be filled.
     * @param x number of char in the string.
     * @param y number of string in vector.
     * @return true if given location should be filled, false otherwise.
     */
    bool isFilled(int x, int y) const override;
};


/**
 * @brief Sierpenski triangle fractal object for fractal project.
 */
class Triangle : public Fractal
{
public:

    /**
     * @brief Creates new triangle fractal.
     * @param dim the dimension of new fractal.
     */
    Triangle(int dim);

    /**
     * @brief Checks if a given char in the vector string should be filled.
     * @param x number of char in the string.
     * @param y number of string in vector.
     * @return true if given location should be filled, false otherwise.
     */
    bool isFilled(int x, int y) const override;
};

/**
 * @brief Vicsek fractal object for fractal project.
 */
class Vicsek : public Fractal
{
public:

    /**
     * @brief Creates new vicsek fractal.
     * @param dim the dimension of new fractal.
     */
    Vicsek(int dim);

    /**
     * @brief Checks if a given char in the vector string should be filled.
     * @param x number of char in the string.
     * @param y number of string in vector.
     * @return true if given location should be filled, false otherwise.
     */
    bool isFilled(int x, int y) const override;
};

/**
 * Fractal factory object creates fractals.
 */
class FractalFactory
{
public:

    /**
     * @brief Creates a new fractal object.
     * @param type number specifying which fractal to create.
     * @param dim number specifying what is the dimension of the new fractal.
     * @return
     */
    static Fractal *createFractal(int type, int dim);
};

#endif //CPP_EX2_FRACTAL_H
