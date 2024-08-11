# BabaIsYou

## Video
See the game before downloading.  
https://youtu.be/N-h9v40iITo

## Authors
Kamil Cisek & Konrad Karpiuk - students of Warsaw University of Technology. This is a clone of Arvi Teikari's game BabaIsYou.

## Game rules
Game consists of 8 different levels. Every level contains: 
* physical objects like wall, water, rock or flag,
* words that represents the objects (nouns) - WALL, ROCK,
* words that are properties that objects can obtain - HOT, STOP, SINK,
* words that connect nouns with their properties - IS, AND.
Player controlls only objects that have properties "YOU". To win the level player must make the object with property "YOU" to be in the same tile as object with property "WIN".
To achive this player has to change game rules by creating sentences from the words. Example: No object on the board has property "WIN". Player moves the words to create sentence "FLAG IS WIN".
Now if the player steps on the flag he will win the level. We encourge users to explore how other properties work. 

## How to run
### Installation
On debian-based linux distors: 
```
git clone https://github.com/Realagmag/BabaIsYou.git
sudo apt-get install libsfml-dev
```
### Compile and run
To compile the project go to its root directory and run:
```
cmake -S . -B build/
cd build/
make
```
After compilation is finished you can run the game:
```
./BabaIsYou
```
## Game controls
In Menu:
* **Arrows** - choose level to play
* **R** - reset progress
* **ESC** - exit the game

In level:
* **up arrow key** - objects with property "You" go up
* **down arrow key** - objects with property "You" go down
* **left arrow key** - objects with property "You" go left
* **right arrow key** - objects with property "You" go right
* **R** - reset level
* **Q** - undo last move
* **ESC** - go to Menu

## Project Structure
Important classes:
* **Game** class: other classes work inside Game object.
* **Window** class: displays menu and levels.
* **AudioManager** class: plays music and sound effects.
* **Board** class: tracks current game rules, position of objects and handles move action.
* **ObjectOnField** class: parent class of every object present in the level.

Types of objects in level:
* **ObjectOnField : SolidObject** class : represents objects like Baba, Tree or Door. Every object that is not a word.
* **ObjectOnField : Noun** class: represents words related to SolidObject type elements e.g. Noun BABA represents SolidObject Baba.
* **ObjectOnField : Property** class: represents properties that SolidObject can obtain. Examples are: PUSH, SINK, STOP.
* **ObjectOnField : Operator** class : words that connect nouns with their properties: IS, AND.

### Tests
To run tests while use this while in root directiory:
```
cmake -S . -B build/ # If not made already
cd build/
make test
./test
```
