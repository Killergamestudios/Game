#include "pch.h"
#include "object.h"



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
	m_ability1 = m_ability2 = m_ability3 = m_passiveAbility = nullptr;
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
	m_stats.Agility = stats.Agility;
	m_stats.MagicResistance = stats.MagicResistance;
	m_stats.Armor = stats.Armor;
	m_stats.Mastery = stats.Mastery;
	m_stats.Precision = stats.Precision;

	m_stats.Health = m_stats.MaxHealth;
	m_stats.Energy = m_stats.MaxEnergy;

	m_statGain.MaxHealthGain += statgain.MaxHealthGain;
	m_statGain.AgilityGain += statgain.AgilityGain;
	m_statGain.MagicResistanceGain += statgain.MagicResistanceGain;
	m_statGain.ArmorGain += statgain.ArmorGain;
	m_statGain.PrecisionGain += statgain.PrecisionGain;
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

const Stats & CharacterObject::getM_stats()
{
	return m_stats;
}

/****************************************************************************************************************************************/
//                                                   Leveling Up                                                                        //
/****************************************************************************************************************************************/

void CharacterObject::LevelUp()
{
	int EnergyGain = 1; int MasteryGain = 1; int ActionGain = 1;
	int LevelstoUpdate = 3;

	m_stats.level++;

	m_stats.MaxHealth += m_statGain.MaxHealthGain;
	m_stats.MaxEnergy += m_stats.level % LevelstoUpdate == 0 ? 0 : EnergyGain ;
	m_stats.Agility += m_statGain.AgilityGain;
	m_stats.MagicResistance += m_statGain.MagicResistanceGain;
	m_stats.Armor += m_statGain.ArmorGain;
	m_stats.Mastery += m_stats.level % LevelstoUpdate == 0 ? 0 : MasteryGain;
	m_stats.Precision += m_statGain.PrecisionGain;
	m_stats.actions += m_stats.level % LevelstoUpdate == 0 ? 0 : ActionGain;
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


/****************************************************************************************************************************************/
//                                                   The combat Related Functions                                                       //
/****************************************************************************************************************************************/


int CharacterObject::Attack(CharacterObject *target, String place) // NEEDS WORK
{
	if (!AttackRegisters(place, target)) return -1;
	int damage = (int) m_stats.Mastery*m_weapon->getDamage() * (100 - 25*RightHandTimesHit)/100;
	return target->isAttacked(place, damage, m_weapon->GetDamageType(), m_weapon->getPenetration());;
}

int CharacterObject::isAttacked(string place, int damage, string damageType, int Penetration)
{
	int damagedealt;
	float damageresisted;
	if (damageType == "physical") {
		damageresisted = (float)(m_stats.Armor*(100 - Penetration));
		damageresisted /= 100;
	}
	else if (damageType == "magic") {
		damageresisted = (float)m_stats.MagicResistance*(100 - Penetration);
		damageresisted /= 100;
	}
	else if (damageType == "hybrid") {
		float magicdamageresisted = (float)m_stats.MagicResistance*(100 - Penetration);
		magicdamageresisted /= 200;
		float physicaldamageresisted = (float)m_stats.Armor*(100 - Penetration);
		physicaldamageresisted /= 200;
		damageresisted = magicdamageresisted + physicaldamageresisted;

	}
	damagedealt = damage - (int)damageresisted;
	if (damagedealt < 0) damagedealt = 0;
	if (place == "head") {
		damagedealt *= 2;
	}
	else if (place == "righthand") {
		damagedealt = (int) ((float)damagedealt*0.75f);
		if (RightHandTimesHit < RightHandTimesHit) RightHandTimesHit++;
	}
	else if (place == "lefthand") {
		damagedealt = (int)((float)damagedealt*0.75f);
		if (LeftHandTimesHit < MaxLeftHandTimesHit) LeftHandTimesHit++;
	}
	else if (place == "legs") {
		damagedealt = (int)((float)damagedealt*0.75f);
		if (LegsTimeHit < MaxLegsTimesHit) LegsTimeHit++;
	}
	loseHp(damagedealt);
	return damagedealt;
}

void CharacterObject::loseHp(int HpLoss)
{
	m_stats.Health -= HpLoss;
	if (m_stats.Health < 0) {
		m_stats.Health = 0;
		isAlive = false;
	}
}

bool CharacterObject::AttackRegisters(string place, CharacterObject * target)
{
	// throw exception
	srand(int(time(0)));
	bool registers;
	
	float actualprecition = (float)(m_stats.Precision*(100 - LeftHandTimesHit * 25));
	int precisionModifier = 5;

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

void CharacterObject::UseAblity1(Vector2i & position, CharacterObject * target)
{
	if (!m_ability1->canUse()) return;
	m_ability1->use(position,target);
	usedAction(m_ability1->getCost());
}

