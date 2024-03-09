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


