# AnimalHunt

## Getting started

Animal Hunt is a conversational game inspired in ZORK.

In this game, your main goal will be to hunt animals and get furs, skins and feathers to pay a debt that you have with the bank.
To win, you have to attack the animals (using a weapon is reccomended), kill them, loot them and give the items to the bank.
If you die during a combat, the game is over.
There is also a magic fountain where you can swim and recover your hit-points.

There are some commands that you will need to know in order to play the game:

- help - Shows the commands that you can use to play Animal Hunt
- go (direction) - Move the player to the given direction
- take (item) - Take an item from the room or inventory
- drop (item) - Drop an item from inventory
- put (item, container) - Put an item inside a container
- look (place) - Look into a place to know which items or creatures are there
- attack (target) - Attack an animal in order to hunt it
- stats - Shows the player stats (HP, attack and protection)
- equip - Lets you equip a weapon or another object from your inventory
- unequip - Lets you unequip a weapon or another object
- examine (target) - Shows stats and objects that belong to an animal
- loot (target) - Takes all the objects that belong to an animal
- inventory - Shows all the objects that belong to you
- swim - If you are on the magic fountain, you can recover HP
- pay - If you are on the bank, you can pay the debt
- quit - Closes the game

## Ideas not finished
- Having a store where you can buy weapons and armours and sell items to earn money.
- Use money to pay the debt to the bank.
- Having a wallet that you can open to know how much money you have.
- Having a church where you can pray and donate money to be more lucky (reduced prices in the store, more attack points and better weapons on the map).

## Guide to win
The easiest way to win is going to the fountain, taking the sword inside the chest and equiping it.
Then, kill and loot the bear, the eagle and the snake.
Finally, go to the bank and pay the debt.

## Comments
The most difficult part of the development has been my time availability. I have had a couple of days to develop it because the rest of the week I had to work and develop other projects for my bachelor's degree. I wanted to deliver a bigger project but I did not have time enough to achieve it.

I felt comfortable with the language because I have previous experience, although I needed some time to understand how the example code works. I had to remember how iterators work, because the last time I used them was a long time ago. The relationships between the classes in this project seem coherent to me, and having an UML schema helps a lot. I have decided NOT to use the tick function to update the game using a clock because I think that the game does not need it. I also got rid of the global functions.

I think that the most difficult part to understand were the different Find methods. Dropping and picking elements that are inside other elements has been challenging to develop. 

## Author
Marc González Moratona

## Links
- https://github.com/marcelinus99/AnimalHunt

## MIT License

Copyright (c) [2022] [Marc González Moratona]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
