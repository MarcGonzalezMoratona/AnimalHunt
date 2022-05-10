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
	Room* bank = new Room("Bank", "The bank of America.");
	Room* cave = new Room("Cave", "A cave.");
	Room* mountain = new Room("Mountain", "You are on highest mountain of this world.");
	Room* fountain = new Room("Fountain", "You are next to a magic fountain that has healing properties.");
	Room* church = new Room("Church", "A church where you can donate money and pray.");

	Exit* ex1 = new Exit("east", "west", "Little path", house, forest);
	Exit* ex2 = new Exit("north", "south", "Little path", house, bank);
	Exit* ex3 = new Exit("south", "north", "Little path", house, store);
	Exit* ex4 = new Exit("east", "west", "Little path", forest, cave);
	Exit* ex5 = new Exit("north", "south", "Little path", forest, mountain);
	Exit* ex6 = new Exit("south", "north", "Little path", forest, fountain);
	Exit* ex7 = new Exit("west", "east", "Little path", house, church);

	entities.push_back(forest);
	entities.push_back(house);
	entities.push_back(store);
	entities.push_back(bank);
	entities.push_back(cave);
	entities.push_back(mountain);
	entities.push_back(fountain);
	entities.push_back(church);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);

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

	// Items ----
	Item* knife = new Item("knife", "A knife.", house, WEAPON);
	knife->min_value = 2;
	knife->max_value = 6;

	Item* chest = new Item("chest", "This chest might contain an awesome treasure.", fountain);
	Item* sword = new Item("sword", "A simple, old and rusty sword.", chest, WEAPON);
	sword->min_value = 4;
	sword->max_value = 8;

	entities.push_back(knife);
	entities.push_back(chest);
	entities.push_back(sword);

	Item* bearFur = new Item("fur", "", bear);
	bear->AutoEquip();
	Item* snakeSkin = new Item("skin", "Skin from a long, venomous snake", snake);
	snake->AutoEquip();
	Item* eagleFeathers = new Item("feathers", "Feathers from an eagle of the highest mountain in this world.", eagle);
	eagle->AutoEquip();

	entities.push_back(bearFur);
	entities.push_back(snakeSkin);
	entities.push_back(eagleFeathers);

	player = new Player(playerName, "You are an amazing adventurer!", house);
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

void World::RecoverHP() {
	player->RecoverHP();
}

bool World::PayDebt() {
	return player->PayDebt();
}

bool World::SendItemToTake(string item, string subitem) {
	return player->Take(item, subitem);
}

void World::SendExaminationTarget(string targetName) {
	player->Examine(targetName);
}

void World::ShowInventory() {
	player->Inventory();
}

void World::SendLootTarget(string targetName) {
	player->Loot(targetName);
}

bool World::PlayerIsAlive() {
	return player->IsAlive();
}

void World::SendItemToEquip(string item) {
	player->Equip(item);
}

void World::SendItemToUnequip(string item) {
	player->Unequip(item);
}

bool World::SendItemToDrop(string item, string subitem) {
	return player->Drop(item, subitem);
}

void World::ShowStats() {
	player->Stats();
}

void World::SendPlaceToLook(string placeToLook) {
	player->Look(placeToLook);
}

void World::SendTargetToAttack(string target) {
	player->Attack(target);
}