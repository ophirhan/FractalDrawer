//
// Created by ophirhan on 06/01/2020.
//

#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Fractal.h"

#define INVALID_INPUT "Invalid input"

typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

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

int main(int argc, char **argv)
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
    boost::char_separator<char> sep{","};
    std::string line;
    std::vector<Fractal *> results;
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
                    fractalType = checkString(*current, 3);
                    break;
                }
                case 1:
                {
                    fractalDimension = checkString(*current, 6);
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
            fileStream.close();
            for (auto &fractal: results)
            {
                delete (fractal);
            }
            results.clear();
            std::vector<Fractal *>().swap(results);
            std::cerr << INVALID_INPUT << std::endl;
            exit(EXIT_FAILURE);
        }
        results.insert(results.begin(),
                       FractalFactory::createFractal(fractalType, fractalDimension));
    }
    fileStream.close();
    for (const Fractal *fractal: results)
    {
        fractal->draw();
    }
    for (auto &fractal: results)
    {
        delete (fractal);
    }
    results.clear();
    std::vector<Fractal *>().swap(results);
    exit(EXIT_SUCCESS);
}
