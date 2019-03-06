#include "pch.h"
#include "DataBase.h"

DataBase::DataBase()
{
}


DataBase::~DataBase()
{
}

ArmorComponent * DataBase::getArmor(int ID)
{
	for (auto i = armors.begin(); i != armors.end(); ++i)
		if (ID == i->getid())
			return i->copySelf();
	throw "404: not found";
	return nullptr;
}

ArmorComponent * DataBase::getArmor(string Name)
{
	for (auto i = armors.begin(); i != armors.end(); ++i)
		if (Name == i->getname())
			return i->copySelf();
	throw "404: not found";
	return nullptr;
}


WeaponComponent * DataBase::getWeapon(int ID)
{
	for (auto i = weapons.begin(); i != weapons.end(); ++i) {
		if (ID == i->getid())
			return i->copySelf();
	}
	throw "404: not found";
	return nullptr;
}

WeaponComponent * DataBase::getWeapon(string Name)
{
	for (auto i = weapons.begin(); i != weapons.end(); ++i) {
		if (Name == i->Getname())
			return i->copySelf();
	}
	throw "404: not found";
	return nullptr;
}
