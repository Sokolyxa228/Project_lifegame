#pragma once
#include <iostream>
using namespace std;
class Grass
{
public:
	void set_age(int view) { age = 0; type = view; }
	bool check_life() { return age == 2; }
	int get_age() { return age; }
    int get_kind(){return type;};
	void update_life() { age++; };
	void print() const;
private:
	int age;
    int type;
};

