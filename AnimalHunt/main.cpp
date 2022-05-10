#include <iostream>
#include <string>
#include "world.h"

using namespace std;

void commandNotValid() {
	cout << "Sorry, I don't understand your command" << endl;
}

int main() {
	cout << "Welcome to Animal Hunt!" << endl << endl;
	cout << "Commands of the game:" << endl << endl;
	cout << "\t help - Shows the commands that you can use to play Animal Hunt" << endl;
	cout << "\t go (direction) - Move the player to the given direction" << endl;
	cout << "\t take (item, container) - Take an item from the room, inventory or container" << endl;
	cout << "\t drop (item) - Drop an item from inventory" << endl;
	cout << "\t put (item, container) - Put an item inside a container" << endl;
	cout << "\t look (place) - Look into a place to know which items or creatures are there" << endl;
	cout << "\t attack (target) - Attack an animal in order to hunt it" << endl;
	cout << "\t stats - Shows the player stats (HP, attack and Protection)" << endl;
	cout << "\t equip - Lets you equip a weapon or another object from your inventory" << endl;
	cout << "\t unequip - Lets you unequip a weapon or another object" << endl;
	cout << "\t examine (target) - Shows stats and objects that belong to an animal" << endl;
	cout << "\t loot (target) - Takes all the objects that belong to an animal" << endl;
	cout << "\t inventory - Shows all the objects that belong to you" << endl;
	cout << "\t swim - If you are on the magic fountain, yo can recover HP" << endl;
	cout << "\t quit - Closes the game" << endl << endl;

	cout << "\t There are 8 possible directions:" << endl;
	cout << "\t north (n), south (s), east (e), west (w), north-east (ne), north-west (nw), south-east (se), south-west (sw)" << endl << endl;

	cout << "Enter your name:" << endl;
	string name;
	getline(cin, name);
	World world(name);

	cout << endl << "Dear " << name << "," << endl << endl;
	cout << "I am writing to remind you that you have an outstanding debt on your house." << endl << endl;
	cout << "In order to pay the debt, we strongly recommend you to use your hunting skills and bring to the bank a bear fur, a snake skin, and eagle feathers, "
		"otherwise Mr. Smith will personally take care of this matter and you will lose your house." << endl << endl;
	cout << "Best regards," << endl;
	cout << "John Williams. Bank of America." << endl << endl;

	cout << "Press Enter to continue" << endl;
	cin.ignore();
	system("CLS");
	world.SendPlaceToLook("here");
	
	string command = "";
	bool restart = false;

	while (command != "quit" && !restart) {
		cin >> command;
		cout << endl;

		if (command == "help") {
			cout << "Commands of the game:" << endl << endl;
			cout << "\t help - Shows the commands that you can use to play Animal Hunt" << endl;
			cout << "\t go (direction) - Move the player to the given direction" << endl;
			cout << "\t take (item, container) - Take an item from the room, inventory or container" << endl;
			cout << "\t drop (item) - Drop an item from inventory" << endl;
			cout << "\t put (item, container) - Put an item inside a container" << endl;
			cout << "\t look (place) - Look into a place to know which items or creatures are there" << endl;
			cout << "\t attack (target) - Attack an animal in order to hunt it" << endl;
			cout << "\t stats - Shows the player stats (HP, attack and Protection)" << endl;
			cout << "\t equip - Lets you equip a weapon or another object from your inventory" << endl;
			cout << "\t unequip - Lets you unequip a weapon or another object" << endl;
			cout << "\t examine (target) - Shows stats and objects that belong to an animal" << endl;
			cout << "\t loot (target) - Takes all the objects that belong to an animal" << endl;
			cout << "\t inventory - Shows all the objects that belong to you" << endl;
			cout << "\t swim - If you are on the magic fountain, yo can recover HP" << endl;
			cout << "\t quit - Closes the game" << endl << endl;

			cout << "\t There are 8 possible directions:" << endl;
			cout << "\t north (n), south (s), east (e), west (w), north-east (ne), north-west (nw), south-east (se), south-west (sw)" << endl << endl;
		}
		else if (command == "go") {
			string direction = "";
			cin >> direction;
			if(direction == "n" || direction == "north" || 
				direction == "s" || direction == "south" || 
				direction == "w" || direction == "west" || 
				direction == "e" || direction == "east" || 
				direction == "nw" || direction == "north-west" || 
				direction == "ne" || direction == "north-east" ||
				direction == "sw" || direction == "south-west" ||
				direction == "se" || direction == "south-east") world.SendDirection(direction);
			else commandNotValid();
		}
		else if (command == "take" || command == "pick") {
			string item;
			cin >> item;
			if(!world.SendItemToTake("", item)) {
				cout << endl << command << " " << item << " from ";
				string parent;
				cin >> parent;
				world.SendItemToTake(parent, item);
			}
		}
		else if (command == "stats") {
			world.ShowStats();
		}
		else if (command == "equip") {
			string item;
			cin >> item;
			world.SendItemToEquip(item);
		}
		else if (command == "unequip") {
			string item;
			cin >> item;
			world.SendItemToUnequip(item);
		}
		else if (command == "examine") {
			string target;
			cin >> target;
			world.SendExaminationTarget(target);
		}
		else if (command == "drop") {
			string item;
			cin >> item;
			world.SendItemToDrop("", item);
		}
		else if (command == "put") {
			string item;
			cin >> item;
			cout << endl << command << " " << item << " into ";
			string parent;
			cin >> parent;
			world.SendItemToDrop(parent, item);
		}
		else if (command == "swim") {
			world.RecoverHP();
		}
		else if (command == "inventory") {
			world.ShowInventory();
		}
		else if (command == "look") {
			string placeToLook;
			cin >> placeToLook;
			world.SendPlaceToLook(placeToLook);
		}
		else if (command == "loot") {
			string target;
			cin >> target;
			world.SendLootTarget(target);
		}
		else if (command == "attack") {
			string target;
			cin >> target;
			world.SendTargetToAttack(target);
		}
		else if (command != "quit") commandNotValid();
		if (command != "quit") cout << endl;

		restart = !world.PlayerIsAlive();
	}

	if (restart) cout << "You are dead." << endl;
	else system("CLS");
	cout << "Thanks for playing!" << endl;

	return 0;
}