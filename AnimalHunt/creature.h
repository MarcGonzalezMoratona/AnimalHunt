#ifndef __Creature__
#define __Creature__

#include <string>
#include "entity.h"
#include <vector>

class Room;
class Item;

using namespace std;

class Creature : public Entity {
public:
	Creature(const string name, const char* description, Room* room);
	~Creature();

	virtual void Look(const vector<string>& args) const;
	virtual bool AutoEquip();
	virtual void Inventory() const;

	virtual bool Attack(const string targetName);
	virtual void Attack();
	virtual int MakeAttack();
	virtual int ReceiveAttack(int damage);
	virtual void Die();
	virtual void Stats() const;

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;

public:

	int hit_points;
	int min_damage;
	int max_damage;
	int min_protection;
	int max_protection;
	Creature* combat_target;
	Item* weapon;
	Item* armour;
};

#endif //__Creature__