#ifndef NO_HPP
#define NO_HPP

#include <iostream>
using namespace std;

template <typename T>
struct No {
    T info;
    No<T>* eloA;
    No<T> *eloP;
};

#endif