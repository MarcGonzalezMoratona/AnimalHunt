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
	bool SendItemToTake(string item, string subitem);
	bool SendItemToDrop(string item, string subitem);
	void SendPlaceToLook(string placeToLook);
	void SendTargetToAttack(string target);
	void ShowStats();
	bool PlayerIsAlive();

private:

	list<Entity*> entities;
	Player* player;
};

#endif //__World__