#ifndef __INTERFACE__
#define __INTERFACE__
#include "App.hpp"
#include <sstream>
#include <unordered_map>


class Interface{

    public:
    Interface();
    void read();
    static std::size_t hashing(std::string password);
    
    private:
    App* app;
    std::string process(std::string command);
    std::vector<std::string> parse(std::string command);
    std::string extractComment(std::string command);
    
};

#endif