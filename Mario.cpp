#include "Mario.h"

//default constructor initializing Mario's member variables to zero
Mario::Mario() {
    lives = 0;
    coins = 0;
    state = 0;
    enemiesDefeated = 0;
    bossDefeated = false;
    lifeLost = false;
}

//overloaded constructor initializing lives based on given numLives and everything else to zero
Mario::Mario(int numLives) {
    lives = numLives;
    coins = 0;
    state = 0;
    enemiesDefeated = 0;
    bossDefeated = false;
    lifeLost = false;
}


//deconstructor
Mario::~Mario() {
    cout << "Mario deconstructor" << endl; 
}

//method to collect a coin
void Mario::CollectCoin() {
    coins++;
    cout << "Mario found a coin. ";
    //if Mario gets 20 coins, he gains a life and coins resets to 0
    if(coins == 20) { 
        cout << "Mario got 20 coins. ";
        GainLife();
        coins = 0;
    }
}

//method to gain a life
void Mario::GainLife() {
    cout << "Mario gained a life. ";
    lives++;
}

//method to lose a life, if lives is zero, lose game
void Mario::LoseLife() {
    cout << "Mario lost a life. ";
    lives--;
    enemiesDefeated = 0;
    state = 0;
    lifeLost = true;
    if(lives > 0) {
        cout << "Mario respawned. ";
    }
}

//method to power up Mario
void Mario::PowerUp() {
    cout << "Mario found a mushroom. ";
    state++; 
    if(state > 2) { //if Mario is on the highest state and tries to go past it, he stays at last state
        state = 2;
    }
}

//method to power down Mario
void Mario::PowerDown() {
    state--;
}

//method to handle fighting an enemy
bool Mario::FightEnemy(char enemy) {
    bool defeatedEnemy;
    switch (enemy) {
        case 'g':
            defeatedEnemy = FightGoomba();
            break;
        case 'k':
            defeatedEnemy = FightKoopa();
            break;
        case 'b':
            FightBoss();
            break;
    }
    return defeatedEnemy;
}

//method to fight a goomba
bool Mario::FightGoomba() {
    int chance = rand() % 101;
    bool defeatedGoomba;

    if(chance <= 80) {
        cout << "Mario encountered a goomba and won. ";
        DefeatEnemy();
        defeatedGoomba = true;
    }
    else {
        PowerDown();
        cout << "Mario encountered a goomba and lost. ";
        if(state < 0) {
            LoseLife();
        }
        defeatedGoomba = false;
    }
    return defeatedGoomba;
}

//method to fight a koopa
bool Mario::FightKoopa() {
    int chance = rand() % 101;
    bool defeatedKoopa;

    if(chance <= 65) {
        cout << "Mario encountered a koopa and won. ";
        DefeatEnemy();
        defeatedKoopa = true;
    }
    else {
        PowerDown();
        cout << "Mario encountered a koopa and lost. ";
        if(state < 0) {
        LoseLife();
        }
        defeatedKoopa = false;
    }

    return defeatedKoopa;
}

//method to fight boss
void Mario::FightBoss() {
    int chance = rand() % 101;

    if(chance <= 50) {
        cout << "Mario encountered a boss and won. ";
        DefeatBoss();
    }
    else {
        PowerDown();
        PowerDown();
        cout << "Mario encountered a boss and lost. ";
        if(state < 0) {
        LoseLife();
        }
        bossDefeated = false;
    }
}

//method to defeat boss
void Mario::DefeatBoss() {
    bossDefeated = true;
    enemiesDefeated++;
    if(enemiesDefeated % 7 == 0) { //if Mario defeats 7 enemies on a single life, he gains a life
        cout << "Mario defeated 7 enemies. ";
        GainLife();
    }
}

//method to defeat enemy
void Mario::DefeatEnemy() {
    enemiesDefeated++; //enemies defeated goes up by one
    if(enemiesDefeated % 7 == 0) { //if Mario defeats 7 enemies on a single life, he gains a lifet
        cout << "Mario defeated 7 enemies. ";
        GainLife();
    }
}

int Mario::GetLives() {
    return lives;
}

int Mario::GetCoins() {
    return coins;
}

int Mario::GetState() {
    return state;
}

bool Mario::GetBossDefeated() {
    return bossDefeated;
}

void Mario::SetBossDefeated(bool didDefeatBoss) {
    bossDefeated = didDefeatBoss;
}

