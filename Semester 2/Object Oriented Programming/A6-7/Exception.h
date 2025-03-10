#pragma once
#include <string>
#include <utility>

using namespace std;

class Exception {
private:
    string msg;
public:
    Exception() {};
    ~Exception() {};
    explicit Exception(string m) : msg{ move(move(m)) } {
    }

    string getMessage() 
    {
        return msg;
    }
};

