#include <iostream>
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "world.h"

World::World(string playerName) {
	Room* forest = new Room("Forest", "You are surrounded by tall trees. It feels like a huge forest someone could get lost easily.");
	Room* house = new Room("House", "You are inside a beautiful but small white house.");
	Room* store = new Room("Store", "Store.");
	Room* bank = new Room("Bank", "The bank.");
	Room* cave = new Room("Cave", "A cave.");
	Room* mountain = new Room("Mountain", "Mountain.");
	Room* fountain = new Room("Fountain", "Fountain.");

	Exit* ex1 = new Exit("east", "west", "Little path", house, forest);
	Exit* ex2 = new Exit("north", "south", "Little path", house, bank);
	Exit* ex3 = new Exit("south", "north", "Little path", house, store);
	Exit* ex4 = new Exit("east", "west", "Little path", forest, cave);
	Exit* ex5 = new Exit("north", "south", "Little path", forest, mountain);
	Exit* ex6 = new Exit("south", "north", "Little path", forest, fountain);

	entities.push_back(forest);
	entities.push_back(house);
	entities.push_back(store);
	entities.push_back(bank);
	entities.push_back(cave);
	entities.push_back(mountain);
	entities.push_back(fountain);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);

	// Creatures ----
	Creature* bear = new Creature("bear", "A big angry bear.", forest);
	bear->hit_points = 10;
	entities.push_back(bear);

	Creature* snake = new Creature("snake", "A long, venomous snake.", cave);
	snake->hit_points = 15;
	entities.push_back(snake);

	Creature* eagle = new Creature("eagle", "A hungry eagle.", mountain);
	eagle->hit_points = 5;
	entities.push_back(eagle);

	// Items -----
	Item* knife = new Item("knife", "A knife.", house, WEAPON);
	knife->min_value = 2;
	knife->max_value = 6;
	//Item* sword = new Item("Sword", "A simple old and rusty sword.", forest, WEAPON);

	//Item* sword2(sword);
	//sword2->parent = butler;

	//Item* shield = new Item("Shield", "An old wooden shield.", butler, ARMOUR);
	//shield->min_value = 1;
	//shield->max_value = 3;
	//butler->AutoEquip();

	entities.push_back(knife);
	//entities.push_back(sword);
	//entities.push_back(shield);

	player = new Player(playerName, "You are an awesome adventurer!", house);
	player->hit_points = 25;
	entities.push_back(player);

}

World::~World() {
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) delete *it;
	entities.clear();
}

void World::SendDirection(string direction) {
	if (direction == "n") direction = "north";
	else if (direction == "s") direction = "south";
	else if (direction == "w") direction = "west";
	else if (direction == "e") direction = "east";
	else if (direction == "ne") direction = "north-east";
	else if (direction == "nw") direction = "north-west";
	else if (direction == "se") direction = "south-east";
	else if (direction == "sw") direction = "south-west";
	player->Go(direction);
}

void World::SendItemToTake(string item, string subitem) {
	player->Take(item, subitem);
}

void World::SendItemToDrop(string item) {
	//player->Drop(item);
}

void World::ShowStats() {
	player->Stats();
}

void World::SendPlaceToLook(string placeToLook) {
	player->Look(placeToLook);
}

void World::SendTargetToAttack(string target) {
	player->Attack(target);
	//for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) (*it)->Attack();
}