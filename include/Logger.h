#ifndef LOGGER_H
#define LOGGER_H

#include <string>


#ifdef DEBUG
#include <iostream>
#include <fstream>
#endif

class Logger
{
    public:
        Logger();
        ~Logger();
        std::string log(const std::string& input);

    #ifdef DEBUG
    private:
        std::ofstream output;
    #endif
};

Logger::Logger()
{
    #ifdef DEBUG
    if (!output.is_open()) output.open("lad_log.txt");
    #endif
}

Logger::~Logger()
{
    #ifdef DEBUG
    if (output.is_open()) output.close();
    #endif
}

std::string Logger::log(const std::string& input)
{
    #ifdef DEBUG
    std::cout << input << std::endl;
    output << input << std::endl;
    #endif
    return input;
}

#endif // LOGGER_H
