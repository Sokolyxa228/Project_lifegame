#pragma once
#include <iostream>
using namespace std;
class Grass
{
public:
	void set_parametrs(int view);
	bool check_life() { return age == 3; }
	int get_age() { return age; }
    int get_kind(){return type_grass;}
	void update_life() { age++; }
private:
	int age;
    int type_grass;
};

