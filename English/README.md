# Werewolves

_________________
-- Description --
_________________

This is a tool for the narrator for the game "The werewolves of Miller's Hollow" in the format and roles of "Best Of".

The program is in charge of managing the things of the game so that the narrator does not have that much work. In the "Notes" file is the list of characters that are currently made in the program.

_______________
-- Compiling --
_______________

These steps only work on a Linux Operating System.

1. First of all go with the terminal to the folder where the files are located.

2. You can directly execute the already created .exe file in a terminal (./Werewolves.exe) to start a game.

If the code of the .cc file is modified, compile the progam writing in the terminal:

	#g++ -std=c++11 -o Werewolves.exe Werewolves.cc

And then execute the .exe file with: 

	#./Werewolves.exe
	
3. You can exit the program at any time with Ctrl + C.

__________________
-- Functioning --
__________________

1. The program will ask for a list of the names of the people playing. Enter a series of names separated by spaces and ending with a hyphen (-). Line breaks can be done without problems.

For instance:

	#Juanito Ana Alba Marcos Pepe Alvin Maria Pepa -
	
2. Then the program will ask you to enter the roles of the game in a specific format ([number] [role]) and ending with a zero. This is to determine how many roles will be in the match. Uppercase and lowercase letters can be inserted without problems.

For instance:

	#5 Villager 2 Hunter 2 Wolf 1 Little_Kid 1 Seer 0
	
In the example above, there will be 5 people with the role of Villager, 2 with Hunter, 2 with Wolf... etc.

	PLAYABLE CHARACTERS CURRENTLY:
	
	Seer
	Wolf
	White_Wolf
	Hunter
	Dog_Wolf
	Little_Kid
	Villager
	Piper
	Bear_Tamer

If the total number of roles is higher than the number of people in the game, there may be situations where there is an imbalance. This is good for making games that rely on chance. For instance, in this game:

	#A B C D E F -		//6 people
	#6 Villager 2 Wolf 0	//8 roles

There may be 0, 1 or 2 Wolves in the game. It might be unfair to the wolves, but the game is also more mysterious and fun.

3. Once the roles have been entered, a list will appear with the results and the game will start with the phases of each role.

If you write a person's name that is not on the list, in that phase nothing will be done. For instance, if the wolves must kill a person from this list:

	Joan
	Pablo
	Ana
	Rosa
	
And the user types "Maria" nothing will happen. In the same way, if a name is spelled incorrectly (Juan) or with different upper or lower case letters (joan or JOAN or JoAn) nothing will happen.

4. The game ends and works based on the rulebook of "Werewolves of Miller's Hollow" in the "Best of" format.
