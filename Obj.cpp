#include "Obj.h"

Obj::Obj(string new_type)
{
	type = new_type;
	if (type == "grass") {
		this->set_age();
	}
}

void Obj::print_info()
{
	cout << type;
}
