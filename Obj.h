#pragma once
#include "Grass.h"
#include "Sheep.h"
#include "Wolfs.h"
class Obj: public Grass, public Sheep
{
public:
	Obj():type("0"){};
	Obj(string new_type,int age,int gender);
	Obj(string new_type, int view);
	string get_type() { return type; }
	void print_info() const;
private:
	string type;
};

