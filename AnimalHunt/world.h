#ifndef __World__
#define __World__

#include <list>
#include <vector>


using namespace std;

class Entity;
class Player;

class World {
public:

	World();
	~World();

	void sendDirection(string command);
	void sendItemToTake(string item, string subitem);
	void sendItemToDrop(string item);
	void sendPlaceToLook(string placeToLook);
	void sendTargetToAttack(string target);

private:

	list<Entity*> entities;
	Player* player;
};

#endif //__World__