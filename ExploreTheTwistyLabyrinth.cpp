// -----------------------------------------------------------------------

// Project 4 - Labyrinth Escape II, ExploreTheTwistyLabyrinth.cpp
// 
// Escaping the twirly labyrinth
//
// Author: Zaid Awaidah
// Date: 2 / 23 / 2022
// Class: CS 251, Spring 2022, UIC

// -----------------------------------------------------------------------

#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"
using namespace std;

// -----------------------------------------------------------------------

int main() {	
	Maze m(4, 4);
	MazeCell* start = m.twistyMazeFor(kYourName);
	
    // Put your break point here!
    
    if (isPathToFreedom(start, kPathOutOfTwistyMaze)) {
    	cout << "You escaped!" << endl;
    } else {
    	cout << "You have not escaped!" << endl;
    }
    
    return 0;
}

// -----------------------------------------------------------------------
