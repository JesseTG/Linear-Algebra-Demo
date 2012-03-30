#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>

#define DEBUG

class Logger
{
    public:
        Logger();
        virtual ~Logger();
        void log(const std::string& input);

    #ifdef DEBUG
    private:
        std::ofstream output;
    #endif DEBUG
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

void Logger::log(const std::string& input)
{
    #ifdef DEBUG
    std::cout << input << std::endl;
    output << input << std::endl;
    #endif
}

#endif // LOGGER_H
