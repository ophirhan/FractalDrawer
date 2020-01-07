//
// Created by ophirhan on 06/01/2020.
//

#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Fractal.h"

#define MAX_TYPE 3
#define MAX_DIMENSION 6
#define INVALID_INPUT "Invalid input"

typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

/**
 * @brief Checks if a given string is in correct format, and returns its value.
 * @param basicString the string to check.
 * @param maxValue maximum value to return
 * @return value of first digit, if string is in correct format,
 * the first char is a digit and its value is between one and maxValue, -1 otherwise.
 */
int checkString(const std::string &basicString, int maxValue)
{
    switch (basicString.length())
    {
        case 2:
        {
            if (!isspace(basicString[1]))
            {
                return -1;
            }
        }
        case 1:
        {
            char c = basicString[0];
            int value = c - '0';
            if (isdigit(c) && value <= maxValue && value > 0)
            {
                return value;
            }
        }
        default:
        {
            return -1;
        }
    }
}

/**
 * @brief Reads given file, creates fractals and inserts them into the the start of the vector.
 * @param fileStream the stream to read.
 * @param results vector of fractals to fill.
 * @return true if no errors occurred, false otherwise.
 */
bool readFile(std::ifstream &fileStream, std::vector<Fractal *> &results)
{
    boost::char_separator<char> sep{","};
    std::string line;
    while (std::getline(fileStream, line))
    {
        tokenizer tok{line, sep};
        int counter = 0, fractalType = 0, fractalDimension = 0;
        for (auto current = tok.begin(); current != tok.end(); current++, counter++)
        {
            switch (counter)
            {
                case 0:
                {
                    fractalType = checkString(*current, MAX_TYPE);
                    break;
                }
                case 1:
                {
                    fractalDimension = checkString(*current, MAX_DIMENSION);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        if (counter != 2 || fractalType == -1 || fractalDimension == -1)
        {
            return false;
        }
        results.insert(results.begin(),
                       FractalFactory::createFractal(fractalType, fractalDimension));
    }
    return true;
}

/**
 * @brief frees memory allocated to fractals and the vector storing them.
 * @param results the vector storing the fractals.
 */
void freeResults(std::vector<Fractal *> &results)
{
    for (auto &fractal: results)
    {
        delete (fractal);
    }
    results.clear();
    std::vector<Fractal *>().swap(results);
}

/**
 * @brief main funtion of the programs; reads a file detailing desired
 * fractals and prints them in reverse order.
 * @param argc
 * @param argv
 * @return
 */
int main(const int argc, const char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: FractalDrawer <file path>" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::ifstream fileStream(argv[1]);
    std::string ext = boost::filesystem::extension(argv[1]);
    if (!fileStream.is_open())
    {
        std::cerr << INVALID_INPUT << std::endl;
        exit(EXIT_FAILURE);
    }
    if (ext != ".csv")
    {
        fileStream.close();
        std::cerr << INVALID_INPUT << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<Fractal *> results;
    if (!readFile(fileStream, results))
    {
        fileStream.close();
        freeResults(results);
        std::cerr << INVALID_INPUT << std::endl;
        exit(EXIT_FAILURE);
    }
    for (const Fractal *fractal: results)
    {
        fractal->draw();
    }
    fileStream.close();
    freeResults(results);
    exit(EXIT_SUCCESS);
}
