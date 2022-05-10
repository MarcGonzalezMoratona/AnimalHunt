#ifndef __Player__
#define __Player__

#include "creature.h"

using namespace std;

class Player : public Creature
{
public:
	Player(const char* name, const char* description, Room* room);
	~Player();

	bool Go(const string direction);
	void Look(const string item) const;
	bool Take(const string item, const string subitem);
	bool Drop(const string item);
	//void Inventory() const;
	//bool Equip(const vector<string>& args);
	//bool UnEquip(const vector<string>& args);
	//bool Examine(const vector<string>& args) const;
	//bool Attack(const vector<string>& args);
	//bool Loot(const vector<string>& args);

public:

};

#endif //__Player__