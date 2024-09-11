#ifndef LEVEL_H
#define LEVEL_H

#include "Mario.h"

class Level {
    public:
        Level(); //default constructor
        Level(Mario* mario, unsigned int gridSize, float coinPercentage, float emptyPercentage, float goombaPercentage,
        float koopaPercentage, float mushroomPercentage, bool isLastLevel); //overloaded constructor that takes in a file as input and creates a level based on the text w/ 2D array
        ~Level(); //destructor to allocate 2D array

        void CreateLevel(bool isLastLevel); //method to create the level based on the percentage of the items

        void Generate(Mario* mario, unsigned int gridSize, float coinPercentage, float emptyPercentage, float goombaPercentage,
        float koopaPercentage, float mushroomPercentage, bool isLastLevel); //method to generate the levels based on given information

        char SpawnMario(); //method to spawn Mario in random location
        char MoveMario(); //method that moves Mario randomly in a direction of up, down, left, or right and return the item Mario moved to
        char MoveUp(); //method to move Mario up
        char MoveDown(); //method to move Mario down
        char MoveLeft(); //method to move Mario left
        char MoveRight(); //method to move Mario right
        void HandleMarioInteraction(char item); //method that handles Mario's interaction with an item he is on
        bool GetIsOnWarpPipe();
        void SetIsOnWarpPipe(bool willWarp);

        int marioRow; //member variable storing the row index of Mario
        int marioCol; //member variable storing the col index of Mario

        void PrintLevel(); //method to print out the level for testing purposes

    private:
        void ReadFile(string inputFileName); //method to read the file and store lines in member variables
        void GetRandomEmptyGrid(); //method to get a random grid number that is empty (x)
        void GetRandomGrid(); //method to get a random grid number

        void GenerateCoins(); //method to generate coins based on percentages (c)
        void GenerateGoombas(); //method to generate goombas based on percentages (g)
        void GenerateKoopas(); //method to generate koopas based on percentages (k)
        void GenerateMushrooms(); //method to generate koopas based on percentages (m)
        void GenerateBoss(); //method to geerate level boss (b)
        void GenerateWarpPipe(); //method to generate a warp pipe unless it's the last level (w)

        Mario* l_mario;
        unsigned int l_gridSize; //member variable to store the grid size given from World class
        float l_coinPercentage; //member variable storing coin percentage from .txt file
        float l_emptyPercentage; //member variable storing empty percentage from .txt file
        float l_goombaPercentage; //member variable storing goomba percentage from .txt file
        float l_koopaPercentage; //member variable storing koopa percentage from .txt file
        float l_mushroomPercentage; //member variable storing mushroom percentage from .txt file
        bool isOnWarpPipe; //variable storing whether or not Mario is on a warp pipe

        int totalGrids; //member variable to store the total grids
        int randomRow; //member variable to store a random row index 
        int randomCol; //member variable to store a random col index

        char **levelArray; //pointer to 2D array of the level
};

#endif