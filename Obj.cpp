#include "Obj.h"

Obj::Obj(string new_type, int view)
{
	type = new_type;
	if (type == "grass") {
		set_parametrs(view);
	}
}

void Obj::print_info()
{
	cout << type;
}
