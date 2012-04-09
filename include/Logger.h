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

#endif // LOGGER_H
