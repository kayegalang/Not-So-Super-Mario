#include "World.h"

//default constructor
World::World() {
    srand (time(NULL)); //random seed is based on time so that it changes each time
    myMario = new Mario();
    maxLevels = 0;
    gridSize = 0;
    coinPercentage = 0;
    emptyPercentage = 0;
    goombaPercentage = 0;
    koopaPercentage = 0;
    mushroomPercentage = 0;
    isLastLevel = false;

    currentLevel = 0;

    //initialize array of levels
    worldArray = new Level[maxLevels];
    for(int i = 0; i < maxLevels; ++i) {
        worldArray[i] = Level();
    }
}

//overloaded constructor that takes in a file name as input
World::World(string inputFileName, string outputFileName) {
    srand (time(NULL)); //random seed is based on time so that it changes each time
    ReadFile(inputFileName); //reads the given file
    myMario = new Mario(lives); //initialize a Mario object with lives
    isLastLevel = false;    
    currentLevel = 0;

    //initialize array of levels
    worldArray = new Level[maxLevels];
    for(int i = 0; i < maxLevels; ++i) {
        if(i == maxLevels - 1) {
            isLastLevel = true;
        }
        worldArray[i].Generate(myMario, gridSize, coinPercentage, emptyPercentage, goombaPercentage, koopaPercentage, mushroomPercentage, isLastLevel);
    }

    StartGame(outputFileName);
}

//destructor
World::~World() {
    delete[] worldArray;
    delete myMario;
}

//method to read the file
void World::ReadFile(string inputFile) {
    ifstream infile(inputFile);
    if (!infile.is_open()) {
        throw runtime_error("Failed to open file: " + inputFile);
    }

    //read file contents
    string line1, line2, line3, line4, line5, line6, line7, line8;
    getline(infile, line1);
    getline(infile, line2);
    getline(infile, line3);
    getline(infile, line4);
    getline(infile, line5);
    getline(infile, line6);
    getline(infile, line7);
    getline(infile, line8);

    maxLevels = stoi(line1);
    gridSize = stoi(line2);
    lives = stoi(line3);
    coinPercentage = stof(line4) / 100.0f;
    emptyPercentage = stof(line5) / 100.0f;
    goombaPercentage = stof(line6) / 100.0f;
    koopaPercentage = stof(line7) / 100.0f;
    mushroomPercentage = stof(line8) / 100.0f;

    infile.close();
}


//method to print out each level
void World::PrintLevels() {
    for(int i = 0; i < maxLevels; ++i) {
        worldArray[i].PrintLevel();
    }
}

//method that begins game and plays until Mario either wins or loses
void World::StartGame(string outputFileName) {
    ofstream logFile(outputFileName); //used to store output into a file

    streambuf* coutToLog = cout.rdbuf();
    cout.rdbuf(logFile.rdbuf());

    PrintLevels(); //print the levels in order
    char item = worldArray[currentLevel].SpawnMario(); //spawns Mario into the first level

    cout << "Mario is starting in position: (" << worldArray[currentLevel].marioRow << ", " << worldArray[currentLevel].marioCol << ")" << endl;

    while(myMario->GetLives() > 0) {
        cout << "==========" << endl;
        worldArray[currentLevel].PrintLevel();
        
        //print Mario's states and his actions
        cout << "Level: " << currentLevel << ". Mario is at position: (" << worldArray[currentLevel].marioRow << ", " << worldArray[currentLevel].marioCol << "). ";
        cout << "Mario is at power level " << myMario->GetState() << ". ";
        worldArray[currentLevel].HandleMarioInteraction(item); 
        //if statements to make sure grammar is correct when printing out lives and coins
        if(myMario->GetLives() != 1) {
            cout << "Mario has " << myMario->GetLives() << " lives left. ";
        }
        else {
            cout << "Mario has " << myMario->GetLives() << " life left. ";
        }
        if(myMario->GetCoins() != 1) {
            cout << "Mario has " << myMario->GetCoins() << " coins. ";
        }
        else {
            cout << "Mario has " << myMario->GetCoins() << " coin. ";
        }
        
        //if Mario beats a level, he will move on to the next level
        if(BeatLevel()) {
            ++currentLevel;
            cout << "Mario moves on to the next level. " << endl;
            myMario->SetBossDefeated(false);
            item = worldArray[currentLevel].SpawnMario();
            continue;
        }
        //if Mario won the game, we exit without any problems
        if (WonGame())
        {
            cout << "Mario will stay put. " << endl;
            cout << "WE BEAT THE GAME! :)" << endl;
            exit(0);
        }

        //if Mario is on a warp pipe, he will move on to the next level
        if (IsOnWarpPipe())
        {
            cout << "Mario will WARP. " << endl;
            worldArray[currentLevel].SetIsOnWarpPipe(false);
            ++currentLevel;
            item = worldArray[currentLevel].SpawnMario();
        }
        else if (!IsOnWarpPipe() && myMario->GetLives() > 0) {//otherwise, he moves in the level
            item = worldArray[currentLevel].MoveMario();
        }

    }

    //if Mario runs out of lives, he loses the game
    if (MarioIsDead())
    {
        cout << "Mario lost all his lives. " << endl;
        cout << "WE LOST THE GAME! :(" << endl;
    }

    cout.rdbuf(coutToLog);

    logFile.close();
}

bool World::MarioIsDead()
{
    return myMario->GetLives() <= 0;
}

bool World::IsOnWarpPipe()
{
    return worldArray[currentLevel].GetIsOnWarpPipe();
}

bool World::BeatLevel()
{
    return myMario->GetBossDefeated() && currentLevel < maxLevels - 1;
}

bool World::WonGame()
{
    return myMario->GetBossDefeated() && currentLevel == maxLevels - 1;
}
