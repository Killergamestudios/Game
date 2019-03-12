#pragma once
#include "../../Header Files/Objects/component.h"
#include "../../Header Files/Core/Algorithms.h"
#include "../../Header Files/Core/Controller.h"


string CalculateBuffType(CharacterObject *obj) {
	if (obj->getCategory() == "enemy") return "buff";
	else return "debuff";

}

AbilityComponent *readAbility(string &s, CharacterObject *object) {
	AbilityComponent *ability = nullptr;
	if (s == "whirldwind")
		ability = new Whirlwind(object);
	else if (s == "rally")
		ability = new Rally(object);
	else if (s == "charge")
		ability = new Charge(object);
	return ability;
}



/****************************************************************************************************************************************/
//                                                   The Component Class                                                                 //
/****************************************************************************************************************************************/
component::component(object *Parent, String Category)
{
	parent = Parent;
	category = Category;
}



component::~component()
{
	if (parent) parent = nullptr;
}

String component::getCategory()
{
	return category;
}


/****************************************************************************************************************************************/
//                                                   The Weapon Class                                                                    //
/****************************************************************************************************************************************/




WeaponComponent::WeaponComponent(WeaponType Type, String Name, int ID, CharacterObject * Parent):component(nullptr,"Weapon")
{
	name = Name;
	parent = Parent;
	type = Type;
}

WeaponComponent::~WeaponComponent()
{
	if (parent) parent = nullptr;
}



bool WeaponComponent::canEquip(CharacterObject * Parent)
{
	string Characterclass = Parent->getType();
	int CharacterMastery = Parent->getMastery();
	if (Parent->getCategory() == "enemy") return true;
	if (Characterclass == ClassRequirment && CharacterMastery >= MasteryRequirment) return true;
	else return false;
}

void WeaponComponent::equip(CharacterObject * Parent)
{
	if (!canEquip(Parent)) throw "iligal equip";
	parent = Parent;
}

void WeaponComponent::update()
{
}

WeaponComponent * WeaponComponent::copySelf()
{
	WeaponComponent *copy = new WeaponComponent(type,name,id,parent);
	copy->spawn(element, elementAmplitude, elementDuration, Damage, range, MasteryRequirment, ClassRequirment, Description);
	return copy;
}

WeaponType WeaponComponent::Gettype()
{
	return type;
}

String WeaponComponent::Getname()
{
	return name;
}

ElementType WeaponComponent::getElement()
{
	return element;
}

float WeaponComponent::getAmplitude()
{
	return elementAmplitude;
}

int WeaponComponent::getDamage()
{
	return Damage;
}

int WeaponComponent::getRange()
{
	return range;
}

int WeaponComponent::getduration()
{
	return elementDuration;
}

string WeaponComponent::getDescription()
{
	return Description;
}

int WeaponComponent::getid()
{
	return id;
}



void WeaponComponent::spawn(ElementType Element, float amplitude, int duration, int damage, int Range, int mastery, string classrequirment, string description)
{
	element = Element;
	elementAmplitude = amplitude;
	elementDuration = duration;
	Damage = damage;
	range = Range;
	MasteryRequirment = mastery;
	ClassRequirment = classrequirment;
	Description = description;
}

/****************************************************************************************************************************************/
//                                                   The Armor Class                                                                    //
/****************************************************************************************************************************************/





ArmorComponent::ArmorComponent(String Name, int ID, CharacterObject *Parent) :component(nullptr, "Armor")
{	
	id = ID;
	name = Name;
	parent = nullptr;
}

ArmorComponent::~ArmorComponent()
{
	if (parent) parent = nullptr;
}

void ArmorComponent::spawn(pair<ElementType, float> Resistance[9], bool Isdropable, string description, pair<string, bool> Coverage[5], int mastery, string Class, int physicalresistance)
{
	for (int i = 0; i < 9; i++) {
		elementResistance[i].first = Resistance[i].first;
		elementResistance[i].second = Resistance[i].second;
	}
	physicalResistance = physicalresistance;
	isdropable = Isdropable;
	Description = description;
	MasteryRequirment = mastery;
	ClassRequirment = Class;
	for(int i = 0; i < 5; i++) {
		coverage[i].first = Coverage[i].first;
		coverage[i].second = Coverage[i].second;
	}
}

bool ArmorComponent::canEquip(CharacterObject * Parent)
{
	string Characterclass = Parent->getType();
	int CharacterMastery = Parent->getMastery();
	if (Parent->getCategory() == "enemy") return true;
	if (Characterclass == ClassRequirment && CharacterMastery >= MasteryRequirment) return true;
	else return false;
}

void ArmorComponent::equip(CharacterObject * Parent)
{
	if (!canEquip(Parent)) throw "iligal equip";
	parent = Parent;
	for (unsigned int i = 0; i < Modifiers.size(); i++)
		parent->addModifier(Modifiers[i]);
}

void ArmorComponent::unequip()
{
	for (unsigned int i = 0; i < Modifiers.size(); i++)
		Modifiers[i]->setisDead();
}

void ArmorComponent::update()
{
}

ArmorComponent * ArmorComponent::copySelf()
{
	ArmorComponent* copy = new ArmorComponent(name, id, parent);
	pair<ElementType, float> copyResistance[9];
	for (int i = 0; i < 9; i++) {
		copyResistance[i] = pair<ElementType, float>(elementResistance[i]);
	}
	pair<string, bool> copyCoverage[5];
	for (int i = 0; i < 5; i++)
		copyCoverage[i] = pair<string, bool>(coverage[i]);
	copy->spawn(copyResistance, isdropable, string(Description), copyCoverage, MasteryRequirment, string(ClassRequirment),physicalResistance);
	return copy;
}

string ArmorComponent::getname()
{
	return name;
}

float ArmorComponent::getResistance(ElementType element)
{
	for (int i = 0; i < 8; i++) {
		if (elementResistance[i].first == element)
			return elementResistance[i].second;
	}
	return 0;
}

bool ArmorComponent::isDropable()
{
	return isdropable;
}

string ArmorComponent::getDescription()
{
	return Description;
}

bool ArmorComponent::getcoverage(string place)
{
	for (int i = 0; i < 5; i++)
		if (coverage[i].first == place)
			return coverage[i].second;
	return false;
}

int ArmorComponent::getid()
{
	return id;
}

int ArmorComponent::getPhysicalResistance()
{
	return physicalResistance;
}



/****************************************************************************************************************************************/
//                                                   The Modifier Class                                                                  //
/****************************************************************************************************************************************/


ModifierComponent::ModifierComponent(CharacterObject *Prnt, int turns, std::string Type) :component(nullptr, "modifier"), turnsToDie(turns)
{
	Parent = Prnt;
	isdead = false;
	type = Type;
}


ModifierComponent::~ModifierComponent()
{
	if (Parent) Parent = nullptr;
}

bool ModifierComponent::getIsDead()
{
	return isdead;
}

int ModifierComponent::GetTurnsToDie()
{
	return turnsToDie;
}

string ModifierComponent::getType()
{
	return type;
}

void ModifierComponent::setisDead()
{
	isdead = true;
}

void ModifierComponent::setParent(CharacterObject * Prnt)
{
	Parent = Prnt;
}

void ModifierComponent::update()
{

	turnsToDie--;
	aply();
	if (turnsToDie == 0) {
		isdead = true;
		kill();
	}
}

/****************************************************************************************************************************************/
//                                                   The Buff Class                                                                      //
/****************************************************************************************************************************************/




BuffModifierComponent::BuffModifierComponent(CharacterObject * Prnt, int turns, string Atribute, int Amplitude,string bufftype) :ModifierComponent(Prnt, turns, bufftype)
{
	atribute = Atribute;
	amplitude = Amplitude;

}

BuffModifierComponent::~BuffModifierComponent()
{
	if (Parent) Parent = nullptr;
}

void BuffModifierComponent::update()
{
	turnsToDie--;
	if (turnsToDie == 0) isdead = true;
}

void BuffModifierComponent::kill()
{
	if (!isdead) return;
	if (atribute == "agility") {
		Parent->setAgility(Parent->getAgility() - previousValue);
		return;
	}
	else if (atribute == "precision") {
		Parent->setPrecision(Parent->getPrecision() - previousValue);
		return;
	}
}

void BuffModifierComponent::aply()
{
	if (atribute == "agility") {
		int agility = Parent->getAgility();
		previousValue = agility;
		if(type == "buf")
			agility += amplitude;
		else {
			agility -= amplitude;
			if (agility < 1) agility = 1;
		}
		previousValue = previousValue - agility;
		Parent->setAgility(agility);
		return;
	}
	else if (atribute == "precision") {
		int Precision = Parent->getPrecision();
		previousValue = Precision;
		if (type == "buf")
			Precision += amplitude;
		else {
			Precision -= amplitude;
			if (Precision < 1) Precision = 1;
		}
		Precision += amplitude;
		previousValue = previousValue - Precision;
		Parent->setPrecision(Precision);
		return;
	}
}




/****************************************************************************************************************************************/
//                                                   The Ability Class                                                                   //
/****************************************************************************************************************************************/

AbilityComponent::AbilityComponent(CharacterObject *Parent, String Name) :component(nullptr, "Ability")
{
	parent = Parent;
	name = Name;
}

AbilityComponent::~AbilityComponent()
{
	parent = nullptr;
}

void AbilityComponent::ChangeParent(CharacterObject * prnt)
{
	parent = prnt;
}

string AbilityComponent::getName()
{
	return name;
}

int AbilityComponent::getCost()
{
	return ActionCost;
}
/****************************************************************************************************************************************/
//                                                   The Wirlwind Class                                                                  //
/****************************************************************************************************************************************/

Whirlwind::Whirlwind(CharacterObject * Parent) :AbilityComponent(Parent, "Whirlwind")
{
	ActionCost = 3;
}

Whirlwind::~Whirlwind()
{
	parent = nullptr;
}

Whirlwind * Whirlwind::copyself()
{
	Whirlwind *copy = new Whirlwind(parent);
	return copy;
}

void Whirlwind::update()
{
}

void Whirlwind::use(Vector2i & position, CharacterObject * target)
{
	int mastery = parent->getMastery();
	Vector2i m_position = parent->getMyPosition();
	if (position.x != m_position.x || position.y != m_position.y) throw std::exception("invalid position");
	Map *map = Controller::getMap();
	std::vector<Vector2i> enemysToHit;
	CharacterObject *enemy;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) {
			if ((i != 0 && j != 0) && map->getEnemyinPosition(Vector2i(i + m_position.x, j + m_position.y)) != 0)
				enemysToHit.push_back(Vector2i(i + m_position.x, j + m_position.y));
		}

	for (unsigned int i = 0; i < enemysToHit.size(); i++) {
		enemy = &map->getenemy(enemysToHit[i]);
		switch (mastery) {
		case 1:
		case 2:
			parent->Attack(enemy, "body");
			break;
		case 3:
		case 4:
			parent->Attack(enemy, "body");
			parent->Attack(enemy, "body");
			break;
		case 5:
			parent->Attack(enemy, "body");
			parent->Attack(enemy, "body");
			parent->Attack(enemy, "body");
			break;
		}
	}
}

bool Whirlwind::canUse(Vector2i & position, CharacterObject * target)
{
	return (parent->getActionsRemaining() >= ActionCost);
}

/****************************************************************************************************************************************/
//                                                   The Rally  Modifier Class                                                           //
/****************************************************************************************************************************************/



RallyModifier::RallyModifier(CharacterObject * Prnt,int mastery):ModifierComponent(Prnt,3,CalculateBuffType(Prnt))
{
	Mastery = mastery;
}

void RallyModifier::kill()
{
	if (Parent->getType() == "enemy") {
		switch (Mastery) {
		case 1:
		case 2:
			Parent->UpdateStats(Parent->getAgility() + 1, Parent->getPrecision() + 1);
			break;
		case 3:
		case 4:
			Parent->UpdateStats(Parent->getAgility() + 2, Parent->getPrecision() + 2);
			break;
		case 5:
			Parent->UpdateStats(Parent->getAgility() + 3, Parent->getPrecision() + 3);
			break;
		}
	}
	else {
		switch (Mastery) {
		case 1:
		case 2:
			Parent->UpdateStats(Parent->getAgility() - 1, Parent->getPrecision() - 1);
			break;
		case 3:
		case 4:
			Parent->UpdateStats(Parent->getAgility() - 2, Parent->getPrecision() - 2);
			break;
		case 5:
			Parent->UpdateStats(Parent->getAgility() - 3, Parent->getPrecision() - 3);
			break;
		}
	}
}
void RallyModifier::aply()
{
	if (Parent->getType() == "friendly") {
		switch (Mastery) {
		case 1:
		case 2:
			Parent->UpdateStats(Parent->getAgility() + 1 , Parent->getPrecision() + 1);
			break;
		case 3:
		case 4:
			Parent->UpdateStats(Parent->getAgility() + 2, Parent->getPrecision() + 2);
			break;
		case 5:
			Parent->UpdateStats(Parent->getAgility() + 3 , Parent->getPrecision() + 3);
			break;
		}
	}
	else {
		switch (Mastery) {
		case 1:
		case 2:
			Parent->UpdateStats(Parent->getAgility() - 1, Parent->getPrecision() - 1);
			break;
		case 3:
		case 4:
			Parent->UpdateStats(Parent->getAgility() - 2, Parent->getPrecision() - 2);
			break;
		case 5:
			Parent->UpdateStats(Parent->getAgility() - 3, Parent->getPrecision() - 3);
			break;
		}
	}
}

/****************************************************************************************************************************************/
//                                                   The Rally Class                                                                     //
/****************************************************************************************************************************************/

Rally::Rally(CharacterObject * Parent) :AbilityComponent(Parent, "Rally")
{
	ActionCost = 6;
}

Rally * Rally::copyself()
{
	return new Rally(parent);
}

void Rally::update()
{
}

void Rally::use(Vector2i & position, CharacterObject * target)
{
	Map *map = Controller::getMap();
	vector<CharacterObject> party = map->getparty();
	vector<CharacterObject> enemys = map->getenemys();
	int Mastery = parent->getMastery();
	for (unsigned int i = 0; i < party.size(); i++) {
		RallyModifier *raly = new RallyModifier(&party[i], Mastery);
		party[i].addModifier(raly);
	}
	for (unsigned int i = 0; i < enemys.size(); i++) {
		RallyModifier *raly = new RallyModifier(&enemys[i], Mastery);
		enemys[i].addModifier(raly);
	}

}

bool Rally::canUse(Vector2i & position, CharacterObject * target)
{
	return (parent->getActionsRemaining() >= ActionCost);
}



/****************************************************************************************************************************************/
//                                                   The Charge Class                                                                    //
/****************************************************************************************************************************************/


Charge::Charge(CharacterObject * Parent) :AbilityComponent(Parent, "charge")
{
	ActionCost = 4;
	mastery = parent->getMastery();
}

Charge * Charge::copyself()
{
	return new Charge(parent);
}

void Charge::setmastery()
{
	mastery = parent->getMastery();
}

void Charge::setNumOfTiles(int n)
{
	numOfTiles = n;
}

void Charge::update()
{
}

void Charge::use(Vector2i & position, CharacterObject * target)
{
	vector<Vector2i> path;
	Vector2i m_position = parent->getMyPosition();
	int temp = 100;
	Map *map = Controller::getMap();
	int range = 2 + mastery;
	vector<Vector3i> strpath = getStraightPath(m_position.x, m_position.y, range , *map);

	int travelcoordinate;//0 = up,1 = right, 2 = down, 3=left
	if (m_position.x < position.x) travelcoordinate = 1;
	else if (m_position.x > position.x) travelcoordinate = 3;
	else if (m_position.y < position.y) travelcoordinate = 2;
	else travelcoordinate = 0;
	
	int distanceTravelled = 0;

	//attack the target
	switch (travelcoordinate) {
	case 0:
		distanceTravelled = abs(position.y - m_position.y);
		for (int i = m_position.y - 1; i >= position.y; i++) {
			path.push_back(Vector2i(m_position.x, i));
		}

		break;
	case 1:
		distanceTravelled = abs(position.x - m_position.x);
		for (int i = m_position.x + 1; i <= position.x; i++) {
			path.push_back(Vector2i(i, m_position.y));
		}
		break;
	case 2:
		distanceTravelled = abs(position.y - m_position.y);
		for (int i = m_position.y + 1; i <= position.y; i++) {
			path.push_back(Vector2i(m_position.x, i));
		}
		break;
	case 3:
		distanceTravelled = abs(position.x - m_position.x);
		for (int i = m_position.x - 1; i >= position.x; i++) {
			path.push_back(Vector2i(i, m_position.y));
		}
		break;
	}
	int Damage = mastery * distanceTravelled * parent->getWeaponDamage();
	target->loseHp(Damage);
	//move there
	parent->MoveToPosition(path);
}

bool Charge::canUse(Vector2i & position, CharacterObject * target)
{
	bool ret = false;
	//has not enough action points
	if (!(parent->getActionsRemaining() >= ActionCost))
		ret = false;
	//can only charge in a straight line
	Vector2i m_position = parent->getMyPosition();
	if (m_position.x != position.x)
		if (m_position.y != position.y)
			ret = false;
	// position must be tile before the target
	Vector2i targetPos = target->getMyPosition();
	if (m_position.x < position.x && position.x + 1 != targetPos.x)
		return false;
	else if (m_position.x > position.x && position.x - 1 != targetPos.x)
		return false;
	else if (m_position.y < position.y && position.y + 1 != targetPos.y)
		return false;
	else if (m_position.y > position.y && position.y - 1 != targetPos.y)
		return false;

	//invalid target
	vector<Vector3i> pathoptions = getStraightPath(m_position.x, m_position.y, 2 + mastery, *Controller::getMap());
	for (unsigned int i = 0; i < pathoptions.size(); i++) {
		if (position.x == pathoptions[i].x && position.y == pathoptions[i].y)
			return true;
	}
	return ret;
}
/****************************************************************************************************************************************/
//                                                   The Damage over time Class                                                          //
/****************************************************************************************************************************************/

DamageOverTimeModifier::DamageOverTimeModifier(CharacterObject * Prnt, int turns, string dmgtype, int Amplitude): ModifierComponent(Prnt,turns,"Damage Over Time")
{
	damagetype = dmgtype;
	amplitude = Amplitude;
}

DamageOverTimeModifier::~DamageOverTimeModifier() {}

void DamageOverTimeModifier::kill(){}

void DamageOverTimeModifier::aply()
{
	Parent->loseHp(amplitude);
}

