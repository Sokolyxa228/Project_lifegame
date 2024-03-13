#include "Wolfs.h"

void Wolfs::set_wolf_parametrs(int age,int gender)
{
    wolfs_age = age;
    this->gender = gender;
    satiety = 2;
}

void Wolfs::wolf_update_life()
{
    wolfs_age++;
    satiety--;
}
