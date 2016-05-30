//
//  <Quinones>_hw1.cpp
//  Project1 - Snakes and Ladders
//
//  Description: This program will have players, totalPlayers, play a game of snakes and ladders on a board sized , n*n, with a die of d sides.
//          Parameters for game will be read from the file input.txt in the same working directory.
//          game array stores positions after every turn. Each player takes a turn after totalPlayers turns have passed.
//
//  Created by Andres Quinones on 10/18/14.
//  Copyright (c) 2014 Andres Quinones. All rights reserved.

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
short n, totalPLayers, d, snakes[144], ladders[144], newSnakes[144],newLadders[144];        //variables where information from input.text file will be stored
                                                                                            //stored as global variables because we wont be making any changes to the data stored

void readInputFile()
{
    short offset,s=0,l=0;
    ifstream inGameFile;
    inGameFile.open("input.txt");                                       //open input.txt file
    inGameFile >> n >> totalPLayers >> d;                               //store the first 3 tokens in constant variables n, totalPlayers,d respectively
    while (! inGameFile.eof())                                          //while not the end of the file
    {
        char startofLine;
        inGameFile >> startofLine;                                      //store following token (should be either s or l) in startofLine
        if(startofLine =='S')
        {
            inGameFile >> snakes[s] >> offset;                            //store 2 tokens following S in snakes array (contains positions for snakes) and offset
            newSnakes[s] = snakes[s] - offset;                            //subtract offset from number stored in snakes and stores the new number in newSnakes array
            s++;                                                        //increment s to store more data later on from file
        }
        if(startofLine=='L')
        {
            inGameFile >> ladders[l] >>  offset;                          //same action as if('S') except info is stored in arrays ladders and newLadders
            newLadders[l] = ladders[l] + offset;                          //note temp is added instead of subtracted because ladders move players forward
            l++;
        }
    }
    inGameFile.close();
}

short rollDice(short d)                     //gets a random number on a die with 'number passed' sides
{
    short roll = rand() % d + 1;
    return roll;
}


short isLadderORsnake(short position)       //checks if position passed is in global
{                                           //variable snakes[] or ladders[]. If it is, the position
    for (int i=0;i<144;i++)                 //is changed to the position at the other end.
        if(position == ladders[i])          //If it isnt the position passed is returned
        {
            position = newLadders[i];
            cout << " Moved to " << position << " due to ladder.";
            return position;
        }
    for (int i=0;i<144;i++)
        if(position == snakes[i])
        {
            position = newLadders[i];
            cout << " Moved to "<< position << " due to snake.";
            return position;
        }
    return position;
}

short takeTurn(short position, short diceRoll)      //adds second number passed (typically a diceRoll)
{                                                   //to the first number and stores it in newPosition
    short newPosition = position + diceRoll;
    cout << " and moved to " << newPosition << ".";
    newPosition = isLadderORsnake(newPosition);     //uses function isLadderORsnake to see if further
    return newPosition;                             //action needs to be taken.
}

int main()
{
    readInputFile();
    srand(time(0));
    short move=0, game[721] = {0}, winner=0;
    
    for (short turn=1;turn <=721;turn++)                                                //keeps track of turn and performs actions every turn
    {
        short playersTurn = turn % totalPLayers;                                        //playersTurn represents whos players turn it is
        if (playersTurn==0)                                                             //if player turn is assigned to 0 it should be last player
            playersTurn=totalPLayers;
        move = rollDice(d);
        cout << "Turn " << turn << ": Player " << playersTurn << " rolled a " << move;
        if(turn<totalPLayers)                                                           //for the first turn for each player everyone starts @ 0
            game[turn] = takeTurn(game[0], move);
        else
            game[turn] = takeTurn(game[turn-totalPLayers], move);                       //otherwise player starts at last position. totalPlayer turns ago
        if (move == d)                                                                  //if roll of die is highest possible. Roll again
        {
            move = rollDice(d);
            cout << " Roll again! Rolled " << move;
            game[turn] = takeTurn(game[turn], move);                                    //change position to position after rolling again
        }
        if  (game[turn]>=(n*n))                                                         //check if game should end and stores the winner
        {
            winner=playersTurn;
            break;
        }
        cout << endl;
        if (winner!=0)                                                                  //if theres a winner stop counting turns
        break;
    }
    cout << endl << "Player " << winner << " won!" << endl;                             //print out winner and end program
    return 0;
}

