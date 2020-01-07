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
     *
     */
    void fillCorrect();
    void fill();
    virtual bool isFilled(int x,int y) const = 0;
};

class Carpet: public Fractal
{
public:
    Carpet(int dim);

    bool isFilled(int x, int y) const override;
};

class Triangle: public Fractal
{
public:
    Triangle(int dim);

    bool isFilled(int x, int y) const override;
};

class Vicsek: public Fractal
{
public:
    Vicsek(int dim);

    bool isFilled(int x, int y) const override;
};

class FractalFactory
{
public:
    static Fractal* createFractal(int type, int dim);
};
#endif //CPP_EX2_FRACTAL_H
