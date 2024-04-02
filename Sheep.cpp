#include "Sheep.h"

void Sheep::set_sheep_parametrs(int age,int gender)
{
	sheep_age = age;
	this->gender = gender;
	satiety = 2;
}

void Sheep::sheep_update_life()
{
	sheep_age++;
	satiety--;
}

void Sheep::sheep_update_satiety(int parametr)
{
	if (parametr) {
		satiety += 5;
	}
    else satiety++;
}


