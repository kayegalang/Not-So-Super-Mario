#include "World.h"
// #include "Mario.h"
// #include "Level.h"

int main (int argc, char **argv) {
    string inputFileName = argv[1];
    string outputFileName = argv[2];
    World World(inputFileName, outputFileName);

    return 0;
}