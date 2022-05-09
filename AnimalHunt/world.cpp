#include <iostream>
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "world.h"

World::World() {
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
	//Creature* butler = new Creature("Butler", "It's James, the house Butler.", house);
	//butler->hit_points = 10;

	//entities.push_back(butler);

	// Items -----
	//Item* mailbox = new Item("Mailbox", "Looks like it might contain something.", house);
	//Item* sword = new Item("Sword", "A simple old and rusty sword.", forest, WEAPON);
	//sword->min_value = 2;
	//sword->max_value = 6;

	//Item* sword2(sword);
	//sword2->parent = butler;

	//Item* shield = new Item("Shield", "An old wooden shield.", butler, ARMOUR);
	//shield->min_value = 1;
	//shield->max_value = 3;
	//butler->AutoEquip();

	//entities.push_back(mailbox);
	//entities.push_back(sword);
	//entities.push_back(shield);

	player = new Player("Hero", "You are an awesome adventurer!", house);
	player->hit_points = 25;
	entities.push_back(player);

}

World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

void World::sendDirection(string direction) {
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

//bool World::Tick(vector<string>& args)
//{
//	bool ret = true;
//
//	if (args.size() > 0 && args[0].length() > 0)
//		ret = ParseCommand(args);
//
//	GameLoop();
//
//	return ret;
//}

//void World::GameLoop()
//{
//	clock_t now = clock();
//
//	if ((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
//	{
//		for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
//			(*it)->Tick();
//
//		tick_timer = now;
//	}
//}
//
//bool World::ParseCommand(vector<string>& args)
//{
//	bool ret = true;
//
//	switch (args.size())
//	{
//	case 1: // commands with no arguments ------------------------------
//	{
//		if (Same(args[0], "look") || Same(args[0], "l"))
//		{
//			player->Look(args);
//		}
//		else if (Same(args[0], "north") || Same(args[0], "n"))
//		{
//			(args.size() == 1) ? args.push_back("north") : args[1] = "north";
//			player->Go(args);
//		}
//		else if (Same(args[0], "south") || Same(args[0], "s"))
//		{
//			(args.size() == 1) ? args.push_back("south") : args[1] = "south";
//			player->Go(args);
//		}
//		else if (Same(args[0], "east") || Same(args[0], "e"))
//		{
//			(args.size() == 1) ? args.push_back("east") : args[1] = "east";
//			player->Go(args);
//		}
//		else if (Same(args[0], "west") || Same(args[0], "w"))
//		{
//			(args.size() == 1) ? args.push_back("west") : args[1] = "west";
//			player->Go(args);
//		}
//		else if (Same(args[0], "stats") || Same(args[0], "st"))
//		{
//			player->Stats();
//		}
//		else if (Same(args[0], "inventory") || Same(args[0], "i"))
//		{
//			player->Inventory();
//		}
//		else
//			ret = false;
//		break;
//	}
//	case 2: // commands with one argument ------------------------------
//	{
//		if (Same(args[0], "look") || Same(args[0], "l"))
//		{
//			player->Look(args);
//		}
//		else if (Same(args[0], "go"))
//		{
//			player->Go(args);
//		}
//		else if (Same(args[0], "take") || Same(args[0], "pick"))
//		{
//			player->Take(args);
//		}
//		else if (Same(args[0], "drop") || Same(args[0], "put"))
//		{
//			player->Drop(args);
//		}
//		else if (Same(args[0], "equip") || Same(args[0], "eq"))
//		{
//			player->Equip(args);
//		}
//		else if (Same(args[0], "unequip") || Same(args[0], "uneq"))
//		{
//			player->UnEquip(args);
//		}
//		else if (Same(args[0], "examine") || Same(args[0], "ex"))
//		{
//			player->Examine(args);
//		}
//		else if (Same(args[0], "attack") || Same(args[0], "at"))
//		{
//			player->Attack(args);
//		}
//		else if (Same(args[0], "loot") || Same(args[0], "lt"))
//		{
//			player->Loot(args);
//		}
//		else
//			ret = false;
//		break;
//	}
//	case 3: // commands with two arguments ------------------------------
//	{
//		break;
//	}
//	case 4: // commands with three arguments ------------------------------
//	{
//		if (Same(args[0], "take") || Same(args[0], "pick"))
//		{
//			player->Take(args);
//		}
//		else if (Same(args[0], "drop") || Same(args[0], "put"))
//		{
//			player->Drop(args);
//		}
//		else
//			ret = false;
//		break;
//	}
//	default:
//		ret = false;
//	}
//
//	return ret;
//}