#ifndef WORLD_H
#define WORLD_H

#include <fstream>
#include "Mario.h"
#include "Level.h"

class World {
    public: 
        World(); //default constructor
        World(string inputFileName, string outputFileName); //overloaded constructor
        ~World(); //destructor

        void ReadFile(string inputFileName); //method to read the file and store each line in the member variables

        void PrintLevels(); //method to print out all the levels, for testing purposes
        void StartGame(string outputFileName); // method to begin the game!

        static void Warp(); // method to warp Mario to next level
    private:
        Level *worldArray; // pointer to an array of levels
        Mario *myMario; //pointer to a Mario object

        unsigned int maxLevels; //member variable to store the max levels given from .txt file
        unsigned int gridSize; //member variable to store the grid size given from .txt file
        unsigned int lives;  //member variable of Mario's lives from .txt file
        float coinPercentage; //member variable storing coin percentage from .txt file
        float emptyPercentage; //member variable storing empty percentage from .txt file
        float goombaPercentage; //member variable storing goomba percentage from .txt file
        float koopaPercentage; //member variable storing koopa percentage from .txt file
        float mushroomPercentage; //member variable storing mushroom percentage from .txt file
        bool isLastLevel; //member variable storing whether or not a level is the last

        unsigned int currentLevel; //member variable to store the current level Mario is in

        bool WonGame(); //method that returns whether or not the entire game has been won
        bool MarioIsDead(); //method that returns whether Mario is dead or not
        bool IsOnWarpPipe(); //method to return whether Mario is on a warp pipe or not
        bool BeatLevel(); //method to return whether Mario defeated a level boss that isn't the final boss or not
};

#endif 