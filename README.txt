Name: Kaye Galang
ID: 2429149
Course: CPSC 350
Assignment: Mario Project
Files: "Level.cpp", "Level.h", "main.cpp", "Mario.cpp", "Mario.h", "World.cpp", "World.h", "input-spec.txt"
Sources:
- Keira Ryan who took the class last semester helped me put the output in a log.txt file 
- srand: https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
- Brendan Chen who took the class last semester helped me figure out a seg fault which was basically my Level default constructor was making a 0x0 2D array and
it did not like, so he told me to make it a nullptr
- Lindsey Lee who is taking the class right now reminded me how to get command line arguments
Description: This project involves creating a Super Mario Bros.-inspired simulation game. The objective is for Mario to navigate through a series of levels, collecting coins, interacting with power-ups, and battling enemies to defeat a boss and save the princess.

The world consists of multiple levels (L) represented by NxN grids, with Mario starting at power level 0 and a set number of lives (V). He can increase his power by collecting mushrooms and earn extra lives by collecting coins or defeating enemies. Mario must defeat regular enemies like Goombas and Koopas, as well as a level boss to advance. The final goal is to defeat the last boss and win the game.

The program reads a plain text file for world specifications (level count, grid size, and enemy/item distribution) and logs each of Mario’s moves and interactions, tracking his progress through the simulation. The game ends when Mario either wins by defeating the final boss or loses by running out of lives.
