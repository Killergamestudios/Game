#pragma once
#include "component.h"
#include <list>

using namespace std;

class DataBase
{
public:
	DataBase();
	~DataBase();
	ArmorComponent* getArmor(int ID);
	ArmorComponent* getArmor(string Name);

	WeaponComponent* getWeapon(int ID);
	WeaponComponent* getWeapon(string Name);


private:
	list<ArmorComponent> armors;
	list<WeaponComponent> weapons;
};

