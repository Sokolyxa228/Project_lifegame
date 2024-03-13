#include "Obj.h"
#include "Grass.h"
#include "Sheep.h"
Obj::Obj(string new_type, int age, int gender)
{
	type = new_type;
	if (type == "sheep") {
		set_sheep_parametrs(age,gender);
	}
    else if (type == "wolf") {
        set_sheep_parametrs(age,gender);
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
