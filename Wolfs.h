#pragma once
#include <iostream>
using namespace std;
class Wolfs
{
public:
    bool check_wolf_life() const { return wolfs_age == 13; }
    int get_wolf_age() const  { return wolfs_age; }
    int get_wolf_gender() const { return gender; }
    void set_wolf_parametrs(int age,int gender);
    void set_wolf_flag(int step) { flag = step; }
    bool ready_for_babes_wolf(){return satiety>1;}
    int get_wolf_flag() { return flag; }
    int get_satiety_wolf() const {return satiety;}
    void wolf_update_satiety() { satiety+=2;}
    void wolf_update_life();
private:
    int wolfs_age;
    int satiety;
    int flag;
    int gender;

};
