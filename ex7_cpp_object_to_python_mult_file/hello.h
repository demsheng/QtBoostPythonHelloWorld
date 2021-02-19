#ifndef __CSHELLO__
#define __CSHELLO__

#include <string>
#include <iostream>

using namespace std;

class World
{
private:
    string name;
public:
    World() { std::cout << "default constructor" << std::endl; }
    World(std::string name): name(name) { std::cout << "constructor of struct World" << std::endl; }
    void set(string name) {
        this->name = name;
    }
    void greet() {
        std::cout << "hello, I am " << name << std::endl;
    }
    string cs();
};

#endif
