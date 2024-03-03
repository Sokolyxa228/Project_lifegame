#pragma once
#include "Grass.h"
class Obj: public Grass
{
public:
	Obj() :type("0") {};
	Obj(string new_type):type(new_type) {};
	string get_type() { return type; }
	void print_info();
private:
	string type;
};

