#pragma once
#include <iostream>
using namespace std;
class Grass
{
public:
	void set_age() { age = 0; }
	bool check_life() { return age == 2; }
	void update_life() { age++; };
	void print();
private:
	int age;
};

