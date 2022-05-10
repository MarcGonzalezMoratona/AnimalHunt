#ifndef __World__
#define __World__

#include <list>
#include <vector>


using namespace std;

class Entity;
class Player;

class World {
public:

	World(string playerName);
	~World();

	void SendDirection(string command);
	void SendItemToEquip(string item);
	void SendItemToUnequip(string item);
	bool SendItemToTake(string item, string subitem);
	bool SendItemToDrop(string item, string subitem);
	void SendExaminationTarget(string targetName);
	void SendLootTarget(string targetName);
	void SendPlaceToLook(string placeToLook);
	void SendTargetToAttack(string target);
	void ShowStats();
	bool PlayerIsAlive();
	void ShowInventory();

private:

	list<Entity*> entities;
	Player* player;
};

#endif //__World__