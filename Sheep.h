#pragma once
#include <iostream>
using namespace std;
class Sheep
{
public:
    bool check_sheep_life() const { return sheep_age == 20; } //������� �� ������ ����
    int get_sheep_age() const  { return sheep_age; } //���������� ������� ��� ����
    int get_sheep_gender() const { return gender; } //���������� ������
    void set_sheep_parametrs(int age,int gender); // ��������� ���������� ��� ��������
    void set_sheep_flag(int step) { flag = step; } //���� ��� �������� ���� �� ����� ��������
    bool ready_for_babes(){return satiety>2;} //������ �� ���� � �����������
    int get_sheep_flag() { return flag; } //������� ����� ��� �������� ���� 
    int get_satiety() const {return satiety;} // ������� �������
    void sheep_update_satiety() { satiety+=2; }// ���������� �������
    void sheep_update_life(); //���������� ���������� ����� ������ ��������
private:
    int sheep_age;
    int satiety;
    int flag;
    int gender;

};