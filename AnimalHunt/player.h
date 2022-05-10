#ifndef __Player__
#define __Player__

#include "creature.h"

using namespace std;

class Player : public Creature
{
public:
	Player(const string name, const char* description, Room* room);
	~Player();

	bool Go(const string direction);
	void Look(const string item) const;
	bool Take(const string item, const string subitem);
	bool Drop(const string item, const string subitem);
	void Inventory() const;
	bool Equip(const string itemName);
	bool Unequip(const string itemName);
	bool Examine(const string targetName) const;
	bool Attack(const string targetName);
	bool Loot(const string targetName);
	void RecoverHP();


public:

};

#endif //__Player__