#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
    public:
        Logger() {}
        virtual ~Logger() {}
        void log(std::string input, ...);
    protected:
    private:
};

#endif // LOGGER_H
