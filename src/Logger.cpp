#include "../include/Logger.h"

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
