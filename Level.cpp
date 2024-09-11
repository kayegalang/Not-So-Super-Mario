#include "Level.h"

//default constructor
Level::Level() {
    l_gridSize = 0; //size of grid is NxN
    levelArray = nullptr; 
    isOnWarpPipe = false;
}

//overloaded constructor that takes in an input file and uses the lines from the file to create levels
Level::Level(Mario* mario, unsigned int gridSize, float coinPercentage, float emptyPercentage, float goombaPercentage,
float koopaPercentage, float mushroomPercentage, bool isLastLevel) {
    Generate(mario, gridSize, coinPercentage, emptyPercentage, goombaPercentage, koopaPercentage, mushroomPercentage, isLastLevel);
}

//deconstructor 
Level::~Level() {
    //Deallocate memory for 2D array
   for (int i = 0; i < l_gridSize; ++i) {
    delete[] levelArray[i]; // Delete each row
    }
    delete[] levelArray; // Delete the array of pointers
}

void Level::Generate(Mario* mario, unsigned int gridSize, float coinPercentage, float emptyPercentage, float goombaPercentage,
float koopaPercentage, float mushroomPercentage, bool isLastLevel) {
    l_mario = mario;
    l_gridSize = gridSize;
    l_coinPercentage = coinPercentage;
    l_emptyPercentage = emptyPercentage;
    l_goombaPercentage = goombaPercentage;
    l_koopaPercentage = koopaPercentage;
    l_mushroomPercentage = mushroomPercentage;
    totalGrids = 0;
    isOnWarpPipe = false;

    levelArray = new char*[l_gridSize]; //creating a 2D array
    //allocate memory for the 2D array
    for(int i = 0; i < l_gridSize; ++i) {
        levelArray[i] = new char[l_gridSize];
    }

    //creating 2D array and initializing it
    for(int i = 0; i <l_gridSize; ++i) {
        for(int j = 0; j < l_gridSize; ++j) {
            levelArray[i][j] = 'x'; // Initialize with default character 'x'
            totalGrids++;
        }
    }

    CreateLevel(isLastLevel); 
}

//method to print out the grid
void Level::PrintLevel() {
    //printing the grid
    for(int row = 0; row < l_gridSize; ++row) {
        for(int col = 0; col < l_gridSize; ++col) {
            cout << levelArray[row][col];
        }
        cout << endl;
    }

    cout << "==========" << endl;
}

//method that creates the level generating every item and spawning Mario
void Level::CreateLevel(bool isLastLevel) {
    GenerateCoins();
    GenerateGoombas();
    GenerateKoopas();
    GenerateMushrooms();
    GenerateBoss();
    if(!isLastLevel) {
        GenerateWarpPipe();
    }
}

//method that utilizes rand() to get a random row and column index until it finds an empty grid
void Level::GetRandomEmptyGrid() {
    // Loop until a valid random position with ' ' is found
    do {
        randomRow = rand() % l_gridSize;
        randomCol = rand() % l_gridSize;
    } while (levelArray[randomRow][randomCol] != 'x');
}

//method that utilizes rand() to get a random row and column index 
void Level::GetRandomGrid() {
    randomRow = rand() % l_gridSize;
    randomCol = rand() % l_gridSize;
}

//method to generate coins based on percentages from .txt file
void Level::GenerateCoins() {
    int totalCoins = l_coinPercentage * totalGrids;

    for(int i = 0; i < totalCoins; ++i) {
        GetRandomEmptyGrid();
        levelArray[randomRow][randomCol] = 'c';
    }
}

//method to generate goombas based on percentages from .txt file
void Level::GenerateGoombas() {
    int totalGoombas = l_goombaPercentage * totalGrids;

    for(int i = 0; i < totalGoombas; ++i) {
        GetRandomEmptyGrid();
        levelArray[randomRow][randomCol] = 'g';
    }
}

//method to generate koopas based on percentages from .txt file
void Level::GenerateKoopas() {
    int totalKoopas = l_koopaPercentage * totalGrids;

    for(int i = 0; i < totalKoopas; ++i) {
        GetRandomEmptyGrid();
        levelArray[randomRow][randomCol] = 'k';
    }
}

//method to generate mushrooms based on percentages from .txt file
void Level::GenerateMushrooms() {
    int totalMushrooms = l_mushroomPercentage * totalGrids;

    for(int i = 0; i < totalMushrooms; ++i) {
        GetRandomEmptyGrid();
        levelArray[randomRow][randomCol] = 'm';
    }
}

//method to generate a level boss
void Level::GenerateBoss() {
    GetRandomEmptyGrid();
    levelArray[randomRow][randomCol] = 'b';
}

//method to generate a warp pipe
void Level::GenerateWarpPipe() {
    GetRandomEmptyGrid();
    levelArray[randomRow][randomCol] = 'w';
}

//method to spawn Mario at a random empty location
char Level::SpawnMario() {
    GetRandomGrid();
    char item = levelArray[randomRow][randomCol];
    levelArray[randomRow][randomCol] = 'H';

    marioRow = randomRow; //keep track of Mario's row
    marioCol = randomCol; //keep track of Mario's col

    return item;
}

//method to randomly move Mario in one direction
char Level::MoveMario() {
    int randomMove = rand() % 4; //chooses random number between 0 and 3 and move in a direction based on the number
    char item;

    switch (randomMove) {
        case 0:
            item = MoveUp();
            break;
        case 1:
            item = MoveDown();
            break;
        case 2:
            item = MoveLeft();
            break;
        case 3:
            item = MoveRight();
            break;
    }
    return item;
}

//method to move Mario up
char Level::MoveUp() {
    cout << "Mario will move up. " << endl;
    int tempRow = marioRow; //variable to store Mario's previous row index

    if(marioRow == 0) { //if Mario is in the first row and tries to move up, he ends up in the last row
        marioRow = l_gridSize - 1;
    }
    else { //otherwise, he moves up a row
        marioRow--;
    }

    char item = levelArray[marioRow][marioCol]; //char variable to store the item Mario moved to

    levelArray[marioRow][marioCol] = 'H'; //Mario's new location is now H

    return item;
}

//method to move Mario down
char Level::MoveDown() {
    cout << "Mario will move down. " << endl;
    int tempRow = marioRow; //variable to store Mario's previous row index

    if(marioRow == l_gridSize - 1) { //if Mario is in the last row and tries to move down, he ends up in the first row
        marioRow = 0;
    }
    else { //otherwise, he moves down a row
        marioRow++;
    }

    char item = levelArray[marioRow][marioCol]; //char variable to store the item Mario moved to
   
    levelArray[marioRow][marioCol] = 'H'; //Mario's new location is now H

    return item;
}

//method to move Mario left
char Level::MoveLeft() {
    cout << "Mario will move left. " << endl;
    int tempCol = marioCol; //variable to store Mario's previous col index

    if(marioCol == 0) { //if Mario is in the first column and tries to move left, he ends up in the last columnb
        marioCol = l_gridSize - 1;
    }
    else { //otherwise, he moves left a column
        marioCol--;
    }

    char item = levelArray[marioRow][marioCol]; //char variable to store the item Mario moved to

    levelArray[marioRow][marioCol] = 'H'; //Mario's new location is now H

    return item;
}


//method to move Mario right
char Level::MoveRight() {
    cout << "Mario will move right. " << endl;
    int tempCol = marioCol; //variable to store Mario's previous col index

    if(marioCol == l_gridSize - 1) { //if Mario is in the last column and tries to move right, he ends up in the first column
        marioCol = 0;
    }
    else { //otherwise, he moves right a column
        marioCol++;
    }

    char item = levelArray[marioRow][marioCol]; //char variable to store the item Mario moved to

    levelArray[marioRow][marioCol] = 'H'; //Mario's new location is now H

    return item;
}

//method that handles Mario's interaction with an item he is on
void Level::HandleMarioInteraction(char item) {
    bool defeatedEnemy;
    switch (item) {
        case 'c':
            l_mario->CollectCoin();
            levelArray[marioRow][marioCol] = 'x';
            break;
        case 'g':
            defeatedEnemy = l_mario->FightEnemy(item);
            if(defeatedEnemy) { //if Mario defeats an enemy, he moves on and the previous position is empty
                levelArray[marioRow][marioCol] = 'x';
            }
            if(!defeatedEnemy && l_mario->lifeLost && l_mario->GetLives() > 0) { //if Mario loses to the enemy and loses a life, he fights it again
                HandleMarioInteraction('g');
                l_mario->lifeLost = false;
            }
            if(!defeatedEnemy && !l_mario->lifeLost) { //if Mario loses to the enemy and doesn't lose a life, he moves on and the enemy stays
                levelArray[marioRow][marioCol] = 'g';
            }
            break;
        case 'k':
            defeatedEnemy = l_mario->FightEnemy(item); 
            if(defeatedEnemy) { //if Mario defeats an enemy, he moves on and the previous position is empty
                levelArray[marioRow][marioCol] = 'x';
            }
            if(!defeatedEnemy && l_mario->lifeLost && l_mario->GetLives() > 0) { //if Mario loses to the enemy and loses a life, he fights it again
                HandleMarioInteraction('k');
                l_mario->lifeLost = false;
            }
            if(!defeatedEnemy && !l_mario->lifeLost) { //if Mario loses to the enemy and doesn't lose a life, he moves on and the enemy stays
                levelArray[marioRow][marioCol] = 'k';
            }
            break;
        case 'm':
            l_mario->PowerUp();
            levelArray[marioRow][marioCol] = 'x';
            break;
        case 'b':
            l_mario->FightBoss();
            if(!l_mario->GetBossDefeated() && l_mario->GetLives() > 0) {
                HandleMarioInteraction('b');
            }
            break;
        case 'w':
            cout << "Mario found a warp pipe. ";
            isOnWarpPipe = true;
            break;
        case 'x':
            cout << "The position is empty. ";
            levelArray[marioRow][marioCol] = 'x';
            break;
        default: 
            break;
    }
}

bool Level::GetIsOnWarpPipe() {
    return isOnWarpPipe;
}

void Level::SetIsOnWarpPipe(bool willWarp) {
    isOnWarpPipe = willWarp;
}