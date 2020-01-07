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

void exitFailure(const std::string &msg)
{
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

int checkString(const std::string &basicString, int maxValue, std::ifstream &fileStream)
{
    switch(basicString.length())
    {
        case 2:
        {
            if(!isspace(basicString[1]))
            {
                goto error_label;
            }
        }
        case 1:
        {
            char c = basicString[0];
            int value = c - '0';
            if(isdigit(c) && value <= maxValue && value > 0)
            {
                return value;
            }
        }
        default:
        error_label:
        {
            fileStream.close();
            exitFailure(INVALID_INPUT);
        }
    }
}

int main(int argc, char** argv){
    if(argc!=2)
    {
        exitFailure("Usage: FractalDrawer <file path>");
    }
    std::ifstream fileStream(argv[1]);
    std::string ext = boost::filesystem::extension(argv[1]);
    if(!fileStream.is_open())
    {
        exitFailure(INVALID_INPUT);
    }
    if(ext != ".csv")
    {
        fileStream.close();
        exitFailure(INVALID_INPUT);
    }
    boost::char_separator<char> sep{","};
    std::string line;
    std::vector<Fractal*> results;
    while(std::getline(fileStream, line))
    {
        tokenizer tok{line, sep};
        int counter = 0, fractalType = 0, fractalDimension = 0;
        for(auto current = tok.begin(); current != tok.end();current++, counter++)
        {
            switch(counter)
            {
                case 0:
                {
                    fractalType = checkString(*current, 3, fileStream);
                    break;
                }
                case 1:
                {
                    fractalDimension = checkString(*current, 6, fileStream);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        if(counter != 2)
        {
            fileStream.close();
            results.clear();
            std::vector<Fractal*>().swap(results);
            exitFailure(INVALID_INPUT);
        }
        results.insert(results.begin(), FractalFactory::createFractal(fractalType, fractalDimension));
    }
    fileStream.close();
    for(const Fractal* fractal: results)
    {
        fractal->draw();
        delete(fractal);
    }
    results.clear();
    std::vector<Fractal*>().swap(results);
    exit(EXIT_SUCCESS);
}
