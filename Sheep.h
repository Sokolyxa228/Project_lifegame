#pragma once
#include <iostream>
using namespace std;
class Sheep
{
public:
    bool check_sheep_life() const { return sheep_age == 20; } //провека на смерть овцы
    int get_sheep_age() const  { return sheep_age; } //возвращает сколько лет овце
    int get_sheep_gender() const { return gender; } //возвращает гендер
    void set_sheep_parametrs(int age,int gender); // установка параметров при создании
    void set_sheep_flag(int step) { flag = step; } //флаг для проверки хода на одной итерации
    bool ready_for_babes(){return satiety>2;} //готова ли овца к размножению
    int get_sheep_flag() { return flag; } //возврат флага для проверки хода 
    int get_satiety() const {return satiety;} // возврат сытости
    void sheep_update_satiety() { satiety+=2; }// обновление сытости
    void sheep_update_life(); //обновление параметров после одного движения
private:
    int sheep_age;
    int satiety;
    int flag;
    int gender;

};