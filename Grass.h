#pragma once
#include <iostream>
using namespace std;
class Grass
{
public:
	void set_parametrs(int view);
	bool check_life() const { return age == 3; }
	int get_age() const { return age; }
    int get_kind() const {return type_grass;}
	void update_life() { age++; }
private:
	int age;
    int type_grass;
};

