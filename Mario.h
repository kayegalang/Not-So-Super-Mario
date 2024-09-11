#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <fstream>
using namespace std;

class Mario {
    public:
        Mario(); //default constructor
        Mario(int numLives); //overloaded constructor
        ~Mario(); //deconstructor

        void CollectCoin(); //method for Mario to collect a coin
        void PowerUp(); //method for Mario to power up 
        bool FightEnemy(char enemy); //method for Mario to fight enemy
        void FightBoss(); //method to fight a boss with a 50% chance to win
        void PowerDown(); //method for Mario to power down if he loses to an enemy

        int GetLives(); //getter method to get lives
        int GetCoins(); //getter method to get coins
        int GetState(); //getter method to get state
        bool GetBossDefeated(); //getter method to get if boss is defeated
        void SetBossDefeated(bool didDefeatBoss); //setter method to set boss defeated

        bool lifeLost; //bool that stores whether a life had been lost

    private:
        void GainLife(); //method to gain a life
        void LoseLife(); //method to lose a life
        bool FightGoomba(); //method to fight a goomba with an 80% chance to win
        bool FightKoopa(); //method to fight a koopa with a 65% chance to win
        void DefeatEnemy(); //method that adds to enemies defeated if Mario defeats one
        void DefeatBoss(); //method that adds to enemies defeated and bosses defeated if Mario beats one

        int lives; //member variable storing Mario's lives
        int coins; //member variable storing coins
        int state; //member variable storing Mario's state based on mushrooms consumed, 0 - small, 1 - medium, 2 - large
        int enemiesDefeated; //member variable storing how many enemies Mario defeats in one life
        bool bossDefeated; //member variable storing whether or not Mario beat a boss
};

#endif