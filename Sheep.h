#pragma once
#include <iostream>
using namespace std;
class Sheep
{
public:
    bool check_sheep_life() const { return sheep_age == 20; }
    int get_sheep_age() const  { return sheep_age; }
    void set_sheep_parametrs(int age){sheep_age = age;};
    void set_sheep_flag(int step) { flag = step; }
    int get_sheep_flag() { return flag; }
    int get_satiety() const {return satiety;}
    int get_flag()const {return flag;}
    void sheep_update_satiety() { satiety++; }
    void sheep_update_life() { sheep_age++; }
private:
    int sheep_age;
    int satiety;
    int flag;
};