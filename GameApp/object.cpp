#include "pch.h"
#include "object.h"
#include <iostream>

/****************************************************************************************************************************************/
//                                                   The Object Class                                                                   //
/****************************************************************************************************************************************/
object::object(RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture, Map *map)
{
	m_window = &window;
	type = Type;
	category = Category;
	m_texture = &texture;
	m_position.x = Position.x; m_position.y = Position.y;
	vertarr.setPrimitiveType(Quads);
	vertarr.resize(4);
	m_map = map;
}


object::~object()
{
	category.clear();
	type.clear();
	m_window = NULL;
}

Map * object::getmap()
{
	return m_map;
}


/****************************************************************************************************************************************/
//                                                   The CharacterObject Class                                                          //
/****************************************************************************************************************************************/
CharacterObject::CharacterObject(String Name, RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture,Map *map) :
	object(window, Category, Type, Position, texture,map)
{
	name = Name;
	move = Move::standing;

	//setting all the pointers to NULL
	m_weapon = nullptr;
	m_Armor = nullptr;
	m_ability1 = m_ability2 = m_ability3 = nullptr;
	m_AI = nullptr;

}

CharacterObject::~CharacterObject()
{
	name.clear();
	if (m_weapon) delete m_weapon;
	/*for (unsigned int i = m_modifiers.size() - 1; i >= 0 ; i--) {
		m_modifiers.pop_back();
	}
	for (unsigned int i = m_items.size() - 1; i >= 0 ; i--) {
		m_items.pop_back();
	}*/
	if (m_ability1) delete m_ability1;
	if (m_ability2) delete m_ability2;
	if (m_ability3) delete m_ability3;
	if (m_AI) delete m_AI;
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

	m_statGain.MaxHealthGain += statgain.MaxHealthGain;
	m_statGain.AgilityGain += statgain.AgilityGain;
	m_statGain.PrecisionGain += statgain.PrecisionGain;
	m_statGain.MaxActionsGain += statgain.MaxActionsGain;
	m_statGain.MaxEnergyGain += statgain.MaxEnergyGain;
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
				m_map->swapPosition(category,Vector2i(m_position.x,m_position.y - 1),m_position);
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
				m_map->swapPosition(category, Vector2i(m_position.x, m_position.y + 1), m_position);

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
				m_map->swapPosition(category, Vector2i(m_position.x + 1, m_position.y), m_position);

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
				m_map->swapPosition(category, Vector2i(m_position.x - 1, m_position.y), m_position);

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

Map * CharacterObject::getmap()
{
	return m_map;
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



const Stats & CharacterObject::getM_stats()
{
	return m_stats;
}
/****************************************************************************************************************************************/
//                                                   The Setters                                                                        //
/****************************************************************************************************************************************/

void CharacterObject::UpdateStats(Stats & stats)
{
	m_stats.Agility = stats.Agility;
	m_stats.Mastery = stats.Mastery;
	m_stats.Precision = stats.Precision;
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
		elementdamage = target->isAttackedMagic(amplitude, dark, 0);
		break;
	case nature:
		amplitude = m_weapon->getAmplitude();
		elementdamage = target->isAttackedMagic(amplitude, nature, 0);
		break;
	}
	return target->isAttackedPhysical(place, damagetodeal) + elementdamage;
}

int CharacterObject::isAttackedPhysical(string place, int damage)
{
	int armor;
	if (m_Armor->getcoverage(place) == false) armor = 0;
	else armor = m_Armor->getPhysicalResistance();
	int damageDealt;
	damageDealt = damage - armor;
	loseHp(damageDealt);
	return damageDealt;
}

int CharacterObject::isAttackedMagic(float amplitude, ElementType element, int duration)
{
	int damage;
	int Duration;
	switch (element) {
	case fire:
		damage = int(amplitude - m_Armor->getResistance(fire));
		loseHp(damage);
		return damage;
		break;
	case ice:

		break;
	}
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

