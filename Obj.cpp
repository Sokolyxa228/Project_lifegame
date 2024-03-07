#include "Obj.h"

Obj::Obj(string new_type, int view)
{
	type = new_type;
	if (type == "grass") {
		set_parametrs(view);
	}
}
Obj::Obj(string new_type)
{
    type = new_type;
}


void Obj::print_info()
{
	cout << type;
}
