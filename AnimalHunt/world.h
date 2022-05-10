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
	void SendItemToTake(string item, string subitem);
	void SendItemToDrop(string item);
	void SendPlaceToLook(string placeToLook);
	void SendTargetToAttack(string target);
	void ShowStats();

private:

	list<Entity*> entities;
	Player* player;
};

#endif //__World__