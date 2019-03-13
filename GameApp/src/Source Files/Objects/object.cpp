#pragma once
#include "../../Header Files/Objects/object.h"
#include <iostream>
#include <algorithm>
#include "../../Header Files/Core/controller.h"

/****************************************************************************************************************************************/
//                                                   The Object Class                                                                   //
/****************************************************************************************************************************************/
object::object(RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture)
{
	m_window = &window;
	type = Type;
	category = Category;
	m_texture = &texture;
	m_position.x = Position.x; m_position.y = Position.y;
	vertarr.setPrimitiveType(Quads);
	vertarr.resize(4);
}


object::~object()
{
	category.clear();
	type.clear();
	m_window = nullptr;
}



/****************************************************************************************************************************************/
//                                                   The CharacterObject Class                                                          //
/****************************************************************************************************************************************/
CharacterObject::CharacterObject(String Name, RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture) :
	object(window, Category, Type, Position, texture)
{
	name = Name;
	move = Move::standing;

	//setting all the pointers to NULL
	m_weapon = nullptr;
	m_Armor = nullptr;
	m_ability1 = m_ability2 = m_ability3 = nullptr;

}

CharacterObject::~CharacterObject()
{
	name.clear();
	if (m_weapon) delete m_weapon;
	for (int i = m_modifiers.size() - 1; i >= 0 ; i--) {
		m_modifiers.pop_back();
	}
	/*for (unsigned int i = m_items.size() - 1; i >= 0 ; i--) {
		m_items.pop_back();
	}*/
	if (m_ability1) delete m_ability1;
	if (m_ability2) delete m_ability2;
	if (m_ability3) delete m_ability3;
}
CharacterObject * CharacterObject::copyself()
{
	CharacterObject *copy = new CharacterObject(name, *m_window, category, type, m_position, *m_texture);
	Stats stats;
	StatGain statGain;
	stats.level = m_stats.level;
	stats.exp = m_stats.exp;
	stats.MaxHealth = m_stats.MaxHealth;
	stats.MaxEnergy = m_stats.MaxEnergy;
	stats.MaxActions = m_stats.MaxActions;
	stats.Agility = m_stats.Agility;
	stats.Mastery = m_stats.Mastery;
	stats.Precision = m_stats.Precision;

	stats.Health = m_stats.MaxHealth;
	stats.Energy = m_stats.MaxEnergy;
	stats.actionsremaining = m_stats.MaxActions;

	statGain.MaxHealthGain = m_statGain.MaxHealthGain;
	statGain.AgilityGain = m_statGain.AgilityGain;
	statGain.PrecisionGain = m_statGain.PrecisionGain;
	statGain.MaxActionsGain = m_statGain.MaxActionsGain;
	statGain.MaxEnergyGain = m_statGain.MaxEnergyGain;

	stats.MaxAgility = m_stats.MaxAgility;
	stats.MaxActions = m_stats.MaxActions;

	copy->spawn(stats, statGain);
	
	WeaponComponent *weapon = m_weapon->copySelf();
	weapon->equip(copy);
	copy->equipWeapon(weapon);
	
	ArmorComponent *armor = m_Armor->copySelf();
	armor->equip(copy);
	copy->equipArmor(armor);

	string ability1 = m_ability1->getName();
	AbilityComponent *ab1 = readAbility(ability1, copy);
	copy->AddAbility1(ab1);

	string ability2 = m_ability2->getName();
	AbilityComponent *ab2 = readAbility(ability2, copy);
	copy->AddAbility2(ab2);

	string ability3 = m_ability3->getName();
	AbilityComponent *ab3 = readAbility(ability3, copy);
	copy->AddAbility3(ab3);

	return copy;

}
/****************************************************************************************************************************************/
//                                                   The Spawn Functions                                                                //
/****************************************************************************************************************************************/
void CharacterObject::spawn(Stats & stats, StatGain &statgain)
{
	m_stats.level = stats.level;
	m_stats.exp = stats.exp;
	m_stats.MaxHealth = stats.MaxHealth;
	m_stats.MaxEnergy = stats.MaxEnergy;
	m_stats.MaxActions = stats.MaxActions;
	m_stats.Agility = stats.Agility;
	m_stats.Mastery = stats.Mastery;
	m_stats.Precision = stats.Precision;

	m_stats.Health = m_stats.MaxHealth;
	m_stats.Energy = m_stats.MaxEnergy;
	m_stats.actionsremaining = m_stats.MaxActions;

	m_statGain.MaxHealthGain = statgain.MaxHealthGain;
	m_statGain.AgilityGain = statgain.AgilityGain;
	m_statGain.PrecisionGain = statgain.PrecisionGain;
	m_statGain.MaxActionsGain = statgain.MaxActionsGain;
	m_statGain.MaxEnergyGain = statgain.MaxEnergyGain;

	m_stats.MaxAgility = stats.MaxAgility;
	m_stats.MaxActions = stats.MaxActions;

}


void CharacterObject::equipWeapon(WeaponComponent * weapon)
{
	if (m_weapon) delete m_weapon;
	m_weapon = weapon;
}

void CharacterObject::equipArmor(ArmorComponent *armorcomponent)
{
	if (m_Armor) delete m_Armor;
	m_Armor = armorcomponent;
}

void CharacterObject::AddAbility1(AbilityComponent * ability)
{
	m_ability1 = ability;
}

void CharacterObject::AddAbility2(AbilityComponent * ability)
{
	m_ability2 = ability;
}

void CharacterObject::AddAbility3(AbilityComponent * ability)
{
	m_ability3 = ability;
}


/****************************************************************************************************************************************/
//                                                   The Move Functions                                                                 //
/****************************************************************************************************************************************/

void CharacterObject::MoveAdj(Vector2i newPos)
{
	if (m_position.x == newPos.x && m_position.y == newPos.y + 1) {
		move = Move::up;

		isMoving = true;
	}
	else if (m_position.x == newPos.x && m_position.y == newPos.y - 1) {
		move = Move::down;
		isMoving = true;
	}
	else if (m_position.x == newPos.x - 1 && m_position.y == newPos.y) {
		move = Move::right;
		isMoving = true;
	}
	else if (m_position.x == newPos.x + 1 && m_position.y == newPos.y) {
		move = Move::left;
		isMoving = true;
	}
}

void CharacterObject::MoveToPosition(vector<Vector2i> &path)
{
	m_path.resize(path.size());
	//copy the path and rotating it
	for (unsigned int i = 0; i <path.size(); i++) {
		m_path[i] = path[i];
	}
	std::reverse(m_path.begin(), m_path.end());
}
/****************************************************************************************************************************************/
//                                                   The update Functions                                                               //
/****************************************************************************************************************************************/
void CharacterObject::moveupdate(float dtAsSeconds) {
	const float timeatframe = 0.10f;
	Vector2f drowpos;
	drowpos.x = (float)(m_position.x * 64);
	drowpos.y = (float)(m_position.y * 64);
	if (!isMoving) {
		if (!m_path.empty()) {
			MoveAdj(m_path.back());
			m_path.pop_back();
		}
	}
	switch (move) {
	case Move::standing:
		vertarr[0].position = drowpos;
		vertarr[1].position = Vector2f(drowpos.x + 63, drowpos.y);
		vertarr[2].position = Vector2f(drowpos.x + 63, drowpos.y + 63);
		vertarr[3].position = Vector2f(drowpos.x, drowpos.y + 63);
		switch (facingdir)
		{
		case FacingDirection::front:
			vertarr[0].texCoords = Vector2f(63, 0);
			vertarr[1].texCoords = Vector2f(127, 0);
			vertarr[2].texCoords = Vector2f(127, 63);
			vertarr[3].texCoords = Vector2f(63, 63);
			break;
		case FacingDirection::back:
			vertarr[0].texCoords = Vector2f(63, 127);
			vertarr[1].texCoords = Vector2f(127, 127);
			vertarr[2].texCoords = Vector2f(127, 191);
			vertarr[3].texCoords = Vector2f(63, 191);
			break;
		case FacingDirection::fright:
			vertarr[0].texCoords = Vector2f(63, 191);
			vertarr[1].texCoords = Vector2f(127, 191);
			vertarr[2].texCoords = Vector2f(127, 255);
			vertarr[3].texCoords = Vector2f(63, 255);
			break;
		case FacingDirection::fleft:
			vertarr[0].texCoords = Vector2f(63, 63);
			vertarr[1].texCoords = Vector2f(127, 63);
			vertarr[2].texCoords = Vector2f(127, 127);
			vertarr[3].texCoords = Vector2f(63, 127);
			break;
		}


		break;
	case Move::down:
		vertarr[0].position = Vector2f(drowpos.x, drowpos.y + pixelscrossed);
		vertarr[1].position = Vector2f(drowpos.x + 63, drowpos.y + pixelscrossed);
		vertarr[2].position = Vector2f(drowpos.x + 63, drowpos.y + 63 + pixelscrossed);
		vertarr[3].position = Vector2f(drowpos.x, drowpos.y + 63 + pixelscrossed);
		if (lastupdated >= timeatframe) {
			lastupdated = 0.0f;

			pixelscrossed += 8;
			vertarr[0].texCoords = Vector2f((float)(0 + 64 * movingquad), 0);
			vertarr[1].texCoords = Vector2f((float)(64 + 64 * movingquad), 0);
			vertarr[2].texCoords = Vector2f((float)(64 + 64 * movingquad), 63);
			vertarr[3].texCoords = Vector2f((float)(0 + 64 * movingquad), 63);
			movingquad++;
			movingquad %= 4;
			if (pixelscrossed == 64) {
				pixelscrossed = 0;
				move = Move::standing;
				m_position.y++;
				facingdir = FacingDirection::front;
				isMoving = false;
				Controller::getMap()->swapPosition(category,Vector2i(m_position.x,m_position.y - 1),m_position);
			}
		}
		break;
	case Move::up:
		vertarr[0].position = Vector2f(drowpos.x, drowpos.y - pixelscrossed);
		vertarr[1].position = Vector2f(drowpos.x + 63, drowpos.y - pixelscrossed);
		vertarr[2].position = Vector2f(drowpos.x + 63, drowpos.y + 63 - pixelscrossed);
		vertarr[3].position = Vector2f(drowpos.x, drowpos.y + 63 - pixelscrossed);
		if (lastupdated >= timeatframe) {
			lastupdated = 0.0f;

			pixelscrossed += 8;
			vertarr[0].texCoords = Vector2f((float)(0 + 64 * movingquad), 127);
			vertarr[1].texCoords = Vector2f((float)(64 + 64 * movingquad), 127);
			vertarr[2].texCoords = Vector2f((float)(64 + 64 * movingquad), 191);
			vertarr[3].texCoords = Vector2f((float)(0 + 64 * movingquad), 191);
			movingquad++;
			movingquad %= 4;
			if (pixelscrossed == 64) {
				pixelscrossed = 0;
				move = Move::standing;
				m_position.y--;
				facingdir = FacingDirection::back;
				isMoving = false;
				Controller::getMap()->swapPosition(category, Vector2i(m_position.x, m_position.y + 1), m_position);

			}
		}
		break;
	case Move::left:
		vertarr[0].position = Vector2f(drowpos.x - pixelscrossed, drowpos.y);
		vertarr[1].position = Vector2f(drowpos.x + 63 - pixelscrossed, drowpos.y);
		vertarr[2].position = Vector2f(drowpos.x + 63 - pixelscrossed, drowpos.y + 63);
		vertarr[3].position = Vector2f(drowpos.x - pixelscrossed, drowpos.y + 63);
		if (lastupdated >= timeatframe) {
			lastupdated = 0.0f;

			pixelscrossed += 8;
			vertarr[0].texCoords = Vector2f((float)(0 + 64 * movingquad), 63);
			vertarr[1].texCoords = Vector2f((float)(64 + 64 * movingquad), 63);
			vertarr[2].texCoords = Vector2f((float)(64 + 64 * movingquad), 127);
			vertarr[3].texCoords = Vector2f((float)(0 + 64 * movingquad), 127);
			movingquad++;
			movingquad %= 4;
			if (pixelscrossed == 64) {
				pixelscrossed = 0;
				move = Move::standing;
				m_position.x--;
				facingdir = FacingDirection::fleft;
				isMoving = false;
				Controller::getMap()->swapPosition(category, Vector2i(m_position.x + 1, m_position.y), m_position);

			}
		}
		break;
	case Move::right:
		vertarr[0].position = Vector2f(drowpos.x + pixelscrossed, drowpos.y);
		vertarr[1].position = Vector2f(drowpos.x + 63 + pixelscrossed, drowpos.y);
		vertarr[2].position = Vector2f(drowpos.x + 63 + pixelscrossed, drowpos.y + 63);
		vertarr[3].position = Vector2f(drowpos.x + pixelscrossed, drowpos.y + 63);
		if (lastupdated >= timeatframe) {
			lastupdated = 0.0f;

			pixelscrossed += 8;
			vertarr[0].texCoords = Vector2f((float)(0 + 64 * movingquad), 191);
			vertarr[1].texCoords = Vector2f((float)(64 + 64 * movingquad), 191);
			vertarr[2].texCoords = Vector2f((float)(64 + 64 * movingquad), 63 + 191);
			vertarr[3].texCoords = Vector2f((float)(0 + 64 * movingquad), 63 + 191);
			movingquad++;
			movingquad %= 4;
			if (pixelscrossed == 64) {
				pixelscrossed = 0;
				move = Move::standing;
				m_position.x++;
				facingdir = FacingDirection::fright;
				isMoving = false;
				Controller::getMap()->swapPosition(category, Vector2i(m_position.x - 1, m_position.y), m_position);

			}
		}
		break;
	}
	
} 
void CharacterObject::update(float dtAsseconds)
{
	
	const int tileSize = 64, vertsinquad = 4;
	/*for (unsigned int i = 0; i < m_modifiers.size(); i++)
	{
		//	if (m_modifiers[i].getIsDead) {
		//		m_modifiers.erase(m_modifiers.begin() + i);
		//}
		m_modifiers[i]->update();
	}*/
	moveupdate(dtAsseconds); // here we handle the movement on a seperate function

	
	lastupdated += dtAsseconds;
}

/****************************************************************************************************************************************/
//                                                   The draw Function                                                                  //
/****************************************************************************************************************************************/

void CharacterObject::Draw()
{

	m_window->draw(vertarr, m_texture);
}





/****************************************************************************************************************************************/
//                                                   The Getters                                                                        //
/****************************************************************************************************************************************/

Vector2i CharacterObject::getMyPosition()
{
	return Vector2i(m_position.x, m_position.y);
}

int CharacterObject::getActionsRemaining()
{
	return m_stats.actionsremaining;
}

string CharacterObject::getCategory()
{
	return string(category);
}

int CharacterObject::getEnergy()
{
	return m_stats.Energy;
}

int CharacterObject::getAgility()
{
	return m_stats.Agility;
}

int CharacterObject::getLegsTimesHit()
{
	return LegsTimeHit;
}

String CharacterObject::getType()
{
	return type;
}

int CharacterObject::getMastery()
{
	return m_stats.Mastery;
}

int CharacterObject::getPrecision()
{
	return m_stats.Precision;
}

int CharacterObject::getMaxAgility()
{
	return m_stats.MaxAgility;
}

int CharacterObject::getWeaponDamage()
{
	return m_weapon->getDamage();
}



const Stats & CharacterObject::getM_stats()
{
	return m_stats;
}
/****************************************************************************************************************************************/
//                                                   The Setters                                                                        //
/****************************************************************************************************************************************/

void CharacterObject::UpdateStats(int Agi, int Prec)
{
	m_stats.Agility = Agi;
	m_stats.Precision = Prec;
}

void CharacterObject::addModifier(ModifierComponent * m)
{
	m_modifiers.push_back(m);
	m->setParent(this);
}

void CharacterObject::setAgility(int agi)
{
	m_stats.Agility = agi;
}

void CharacterObject::setPrecision(int prec)
{
	m_stats.Precision = prec;
}




/****************************************************************************************************************************************/
//                                                   Leveling Up                                                                        //
/****************************************************************************************************************************************/

void CharacterObject::LevelUp()
{
	int LevelstoUpdate = 3;

	m_stats.level++;

	m_stats.MaxHealth += m_statGain.MaxHealthGain;
	m_stats.MaxEnergy += m_statGain.MaxEnergyGain;
	m_stats.Agility += m_statGain.AgilityGain;
	m_stats.Precision += m_statGain.PrecisionGain;
	m_stats.MaxActions += m_stats.level % LevelstoUpdate == 0 ? 0 : m_statGain.MaxActionsGain;

}

bool CharacterObject::GiveExp(int exp)
{
	m_stats.exp += exp;
	bool hasLeveledUp = false;
	while (m_stats.exp >= 100) { //leveled up
		m_stats.exp -= 100;
		LevelUp();
		hasLeveledUp = true;
	}
	return hasLeveledUp; 
}

void CharacterObject::LevelMastery()
{
	m_stats.Mastery++;
}


/****************************************************************************************************************************************/
//                                                   The combat Related Functions                                                       //
/****************************************************************************************************************************************/


int CharacterObject::Attack(CharacterObject *target, String place) // NEEDS WORK
{
	if (!AttackRegisters(place, target)) return -1;
	int damagetodeal = m_stats.Mastery*m_weapon->getDamage()*(100 - 25 * RightHandTimesHit) / 100;
	ElementType element = m_weapon->getElement();
	
	int physicalDamageDealt = target->isAttackedPhysical(place, damagetodeal);
	float amplitude;
	int duration;
	int elementdamage;
	switch (element) {
	case fire:
		amplitude = m_stats.Mastery*m_weapon->getAmplitude();
		elementdamage = target->isAttackedMagic(amplitude, fire, 0);
		break;
	case ice:
		amplitude = m_weapon->getAmplitude();
		duration = m_weapon->getduration();
		elementdamage = target->isAttackedMagic(amplitude, ice, duration);
		break;
	case wind:
		amplitude = m_weapon->getAmplitude();
		duration = m_weapon->getduration();
		elementdamage = target->isAttackedMagic(amplitude, wind, duration);
		break;
	case poison:
		amplitude = m_weapon->getAmplitude();
		duration = m_weapon->getduration();
		elementdamage = target->isAttackedMagic(amplitude, poison, duration);
		break;
	case dark:
		amplitude = m_weapon->getAmplitude() ;
		elementdamage = target->isAttackedMagic(amplitude, dark, 0, physicalDamageDealt);
		gainHp(elementdamage);
		elementdamage = 0;
		break;
	case nature:
		amplitude = m_weapon->getAmplitude();
		elementdamage = target->isAttackedMagic(amplitude, nature, 0, physicalDamageDealt);
		gainActions(elementdamage);
		elementdamage = 0;
		break;
	case harmony:
	{
		amplitude = m_weapon->getAmplitude();
		elementdamage = target->isAttackedMagic(amplitude, dark, 0, physicalDamageDealt);
		gainHp(elementdamage);

		elementdamage = target->isAttackedMagic(amplitude, nature, 0, physicalDamageDealt);
		gainActions(elementdamage);

		duration = m_weapon->getduration();
		elementdamage = target->isAttackedMagic(amplitude, poison, duration);

		duration = m_weapon->getduration();
		elementdamage = target->isAttackedMagic(amplitude, wind, duration);

		duration = m_weapon->getduration();
		elementdamage = target->isAttackedMagic(amplitude, ice, duration);

		amplitude = m_stats.Mastery*m_weapon->getAmplitude();
		elementdamage = target->isAttackedMagic(amplitude, fire, 0);
	}
		break;
	}
	return physicalDamageDealt + elementdamage;
}

int CharacterObject::isAttackedPhysical(string place, int damage)
{
	int armor;
	if (m_Armor->getcoverage(place) == false) armor = 0;
	else armor = m_Armor->getPhysicalResistance();
	int damageDealt;
	damageDealt = damage - armor;
	if (place == "body") BodyTimesHit++;
	else if (place == "head") {
		HeadTimesHit++;
		damageDealt *= 2;
	}
	else if (place == "legs") {
		LegsTimeHit++;
		if (LegsTimeHit > MaxLegsTimesHit) LegsTimeHit = MaxLegsTimesHit;
	}
	else if (place == "rightHand") {
		RightHandTimesHit++;
		if (RightHandTimesHit > MaxRightHandTimesHit) RightHandTimesHit = MaxRightHandTimesHit;
	}
	else if (place == "leftHand") {
		LeftHandTimesHit++;
		if (LeftHandTimesHit > MaxLeftHandTimesHit) LeftHandTimesHit = MaxLegsTimesHit;
	}
	loseHp(damageDealt);
	return damageDealt;
}

int CharacterObject::isAttackedMagic(float amplitude, ElementType element, int duration, int PhysicalDamage)
{
	int damage;
	int Amplitude;
	switch (element) {
	case fire:
		damage = int(amplitude - m_Armor->getResistance(fire));
		loseHp(damage);
		return damage;
		break;
	case ice:
	{
		Amplitude = int(m_stats.Agility * 0.1f * std::max(amplitude - m_Armor->getResistance(ice), 0.0f));// agility * 10/100 * amplitude - resistance.negative not allowed
		if (Amplitude == 0) return 0; //dont create a debuff with 0 amplitude
		BuffModifierComponent* icedebuff = new BuffModifierComponent(this, duration, "agility", Amplitude, "debuff");
		addModifier(icedebuff);
		return 0;
	}
		break;
	case wind:
	{
		Amplitude = int(m_stats.Precision * 0.1f * std::max(amplitude - m_Armor->getResistance(wind), 0.0f));// Precision * 10/100 * amplitude - resistance.negative not allowed
		if (Amplitude == 0) return 0; //dont create a debuff with 0 amplitude
		BuffModifierComponent* winddebuff = new BuffModifierComponent(this, duration, "precision", Amplitude, "debuff");
		addModifier(winddebuff);
		return 0;
	}
		break;
	case poison:
	{
		Amplitude = int(std::max(amplitude - m_Armor->getResistance(poison), 0.0f));
		if (Amplitude == 0) return 0;
		DamageOverTimeModifier *poison = new DamageOverTimeModifier(this, duration, "poison", Amplitude);
		addModifier(poison);
		return 0;
	}
		break;
	case dark:
		Amplitude = int(0.1f * PhysicalDamage * std::max(0.0f, amplitude - m_Armor->getResistance(dark)));
		return Amplitude;
		break;
	case nature:
		Amplitude = int(0.1f * PhysicalDamage * std::max(0.0f, amplitude - m_Armor->getResistance(nature)));
		return Amplitude;
		break;
	}
	return 0;
}

void CharacterObject::loseHp(int HpLoss)
{
	m_stats.Health -= HpLoss;
	if (m_stats.Health < 0) {
		m_stats.Health = 0;
		isAlive = false;
	}
}

void CharacterObject::gainHp(int HpGain, CharacterObject * target)
{
	if (target == nullptr) {
		m_stats.Health += HpGain;
		if (m_stats.Health > m_stats.MaxHealth) m_stats.Health = m_stats.MaxHealth;
	}
	else {
		target->gainHp(HpGain, nullptr);
	}
}

void CharacterObject::gainActions(int ActionGain)
{
	m_stats.actionsremaining += ActionGain;
	if (m_stats.actionsremaining > m_stats.MaxActions) m_stats.actionsremaining = m_stats.MaxActions;
}

bool CharacterObject::AttackRegisters(string place, CharacterObject * target)
{
	// throw exception
	srand(int(time(0)));
	bool registers;
	
	float actualprecition = (float)(m_stats.Precision*(100 - LeftHandTimesHit * 25));
	const int precisionModifier = 5;

	float actualAgility = (float)(target->m_stats.Agility*(100 - target->LegsTimeHit * 25));
	float AgilityModifier;
	if (place == "body") AgilityModifier = 1.0f;
	else if (place == "head") AgilityModifier = 1.5f;
	else if (place == "righthand" || place == "lefthand" || place == "legs") AgilityModifier = 1.2f;


	float ishit = actualprecition * precisionModifier - actualAgility * AgilityModifier;

	float randint = (float)(rand() % 101);
	
	registers = randint <= ishit;

	return registers;
}

void CharacterObject::usedAction(int used)
{
	m_stats.actionsremaining -= used;
	if (m_stats.actionsremaining < 0) m_stats.actionsremaining = 0;
}


void CharacterObject::UseAbility1(Vector2i & position, CharacterObject * target)
{
	if (!m_ability1->canUse(position, target)) return;
	m_ability1->use(position,target);
	usedAction(m_ability1->getCost());
}

void CharacterObject::UseAbility2(Vector2i & position, CharacterObject * target)
{
	if (!m_ability2->canUse(position, target)) return;
	m_ability2->use(position, target);
	usedAction(m_ability2->getCost());
}

void CharacterObject::UseAbility3(Vector2i & position, CharacterObject * target)
{
	if (!m_ability3->canUse(position, target)) return;
	m_ability3->use(position, target);
	usedAction(m_ability3->getCost());
}

