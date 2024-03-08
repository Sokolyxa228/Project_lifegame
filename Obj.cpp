#include "Obj.h"

Obj::Obj(string new_type, int age, int gender)
{
	type = new_type;
	if (type == "sheep") {
		set_sheep_parametrs(age);
	}
}

Obj::Obj(string new_type, int view)
{
	type = new_type;
	if (type == "grass") {
		set_grass_parametrs(view);
	}
}

void Obj::print_info() const
{
	cout << type;
}
