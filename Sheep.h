#pragma once
#include <iostream>
using namespace std;
class Sheep
{
public:
    bool check_sheep_life() const { return sheep_age == 20; }
    int get_sheep_age() const { return sheep_age; }
    int get_hunger() const {return hunger;}
    int get_flag()const {return flag;}
    void sheep_update_hunger() { hunger++; }
    void sheep_update_life() { sheep_age++; }
private:
    int sheep_age;
    int hunger;
    int flag;
};