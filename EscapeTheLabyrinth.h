// -----------------------------------------------------------------------

// Project 4 - Labyrinth Escape II, EscapeTheLabryrinth.h
//
// Author: Zaid Awaidah
// Date: 3 / 4 / 2022
// Class: CS 251, Spring 2022, UIC

// -----------------------------------------------------------------------

#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

// -----------------------------------------------------------------------

/* KYourName
 * decides which maze is used
 */
const string kYourName = "Zaid Awaidah.";

// constants to contain the paths out of my mazes.
const string kPathOutOfRegularMaze = "EESSSEWNNNESNWWWSSESW";
const string kPathOutOfTwistyMaze = "NNNSWSESSS";

// -----------------------------------------------------------------------

/* checkForMagicItems
 * checks the value of whatsHere
 * for the cell
*/
string checkForMagicItems(MazeCell* start) {
    if (start->whatsHere == "Potion")
        return start->whatsHere;
    else if (start->whatsHere == "Wand")
        return start->whatsHere;
    else if (start->whatsHere == "Spellbook")
        return start->whatsHere;
    else
        return "";
}

// -----------------------------------------------------------------------

/* makeMove
 * moves player according to direction 
*/
void makeMove(MazeCell* &start, const char move) {
    switch (move) {
    case 'S':
        start = start->south;
        break;
    case 'E':
        start = start->east;
        break;
    case 'W':
        start = start->west;
        break;
    case 'N':
        start = start->north;
        break;
    default:
        break;
    }
}

/* isPathToFreedom
 * determines whether the given path is
 * the right one to escape the maze
*/
bool isPathToFreedom(MazeCell *start, const string& moves) {
    // flags
    bool flagsFound = false;
    bool PotionFound = false;
    bool SpellBookFound = false;
    bool WandFound = false;

    // if items were found at starting pos
    string temp = checkForMagicItems(start);
    if (temp == "Potion")
        PotionFound = true;
    if (temp == "Spellbook")
        SpellBookFound = true;
    if (temp == "Wand")
        WandFound = true;

    for (int i = 0; i < moves.size(); ++i) {
        // error checking moves
        if (moves.at(i) != 'S' && moves.at(i) != 'N'
            && moves.at(i) != 'E' && moves.at(i) != 'W')
            return false;
        
        // moving pointer
        makeMove(start, moves.at(i));

        // check if pointer is null
        if (start == nullptr)
            return false;

        // setting item flags
        string temp = checkForMagicItems(start);
        if (temp == "Potion")
            PotionFound = true;
        if (temp == "Spellbook")
            SpellBookFound = true;
        if (temp == "Wand")
            WandFound = true;

        // return true if all flags were found
        if (SpellBookFound == true && WandFound == true
            && PotionFound == true && i == moves.size() - 1) {
            flagsFound = true;
            return true;
        }

        // return false if not all conditions were met
        if (i == moves.size() - 1
            && flagsFound == false)
                return false;
    }
}

// -----------------------------------------------------------------------
