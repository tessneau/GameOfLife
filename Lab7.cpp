//File Name: health.cpp 
//Author: Tess Neau
//Email Address: neaut@kenyon.edu
//Assignment Number: 11
//Description: This program recreates John Conway's Game of Life through steps only and where the user can choose coordinates of "alive" cells.
//Last Changed: November 4th 2016

#include <stdlib.h>
#include <iostream>

using namespace std;

void getInitialWorld (char world[][82]);
// Precondition: world is a two dimensional array with a size of 24.
// Postcondition: the user enters the coordinates of each '*' .
void displayWorld (char world[][82]);
// Precondition: world is a two dimensional array with size of 24 and each index has values.
// Postcondition: the array world is displayed as a 23x81 grid.
void clearWorld (char world[][82]);
// Precondition: world is a two dimensional array with size of 24.
// Postcondition: for each index, the array value is initialized to ' '.
int alive (char cell);
// Precondition: cell is a value of the array world.
// Postcondition: is the array value is '*', the function returns 1 and otherwise returns 0.
void nextGenWorld(char current[][82]);
// Precondition: current is a two dimensional array with the same size as world.
// Postcondition: the current array now contains the values of the new generation world.
char nextGenCell(char world[][82], int x, int y);
// Precondition: world is a two dimensional array with size of 24, x and y are the respective coordinates for rows and columns.
// Postcondition: returns, for each index of the array world, either a ' ' if the indexed value "dies" in the next generation or '*' if it lives on.
void copyWorld(char from[][82],char to[][82]);
// Precondition: from and to are two dimensional arrays with the same size of 24.
// Postcondition: the array to takes on the values of the array from.

int main( )
 {
    char answer, LIFE[24][82];
    
    clearWorld(LIFE); // we set each indexed LIFE value to ' '.
    getInitialWorld(LIFE); // the user implements the coordinates of the '*'s.
    displayWorld(LIFE); // our initial world is displayed.

    do {
        cout << "Enter 'Y' to continue: ";
        cin  >> answer; 
        if (answer!='Y' && answer!='y')
            break;
        nextGenWorld(LIFE);
        // the array LIFE goes under an evolution for the next generation world.
        displayWorld(LIFE);
        // the array LIFE, now the next generation world, is displayed.
    }while (answer=='Y' || answer== 'y');
    
    cout << "Bye!";
    
    return 0;  
}

void getInitialWorld (char world[][82])
{
    int count(1),x_coordinate,y_coordinate;
    
    cout << "Welcome to LIFE. Enter x and y coordinates where 0 < x < 81 and 0 < y < 23. Enter x of -1 to end." << endl;       
    cout << "Enter coordinate " << count << ": ";
    cin  >> x_coordinate >> y_coordinate;
    
    while (x_coordinate > 0 && x_coordinate < 23 && y_coordinate > 0 && y_coordinate < 81)
    {
        world[x_coordinate][y_coordinate]='*';
        count++;
        cout << "Enter coordinate " << count << ": ";
        cin >> x_coordinate;
        if (x_coordinate == -1)  
            break;
        cin >> y_coordinate;
    }
}

void displayWorld (char world[][82])
{
    cout << endl;
    
    for (int i = 0; i < 24;i++)
    {
        for (int j = 0; j < 82; j++)
        {
            cout << world[i][j];
        }
        cout << endl;
    }
    
    cout << endl;
}

void clearWorld (char world[][82])
{
    for (int i=0 ; i < 24 ; i++)
    {
        for (int j=0 ; j < 82 ; j++)
        {
            world[i][j] = ' ';
        }
    }
}

int alive (char cell)
{
    if (cell=='*')
        return 1;
    else
        return 0;
}

void nextGenWorld(char current[][82])
{
    char newWorld[24][82];
    
    clearWorld(newWorld);
    
    for (int i = 1; i < 23;i++)
    {
        for (int j = 1; j < 81; j++) 
        {
            newWorld[i][j]= nextGenCell(current,i,j);
        }
    }
    clearWorld(current);
    // the current world is lated clean, ready for new implementations
    copyWorld(newWorld,current);
    // each indexed value of newWorld is implemented into the corresponding current array indexes
    
}

char nextGenCell(char world[][82], int x, int y)
{
    int neighbor(0);

    neighbor = alive(world[x-1][y-1]) + alive(world[x-1][y]) + alive(world[x-1][y+1]) + alive(world[x][y-1]) + alive(world[x][y+1]) + alive(world[x+1][y-1]) + alive(world[x+1][y]) + alive(world[x+1][y+1]);
    // here we calculate how many neighbors world[x][y] has through the 8 cells around it.
    
    if (world[x][y]==' ')
    {
        if (neighbor == 3)
            // then a cell which was originally a space now comes alive into a '*'
            return '*';
        else
            return ' ';
    }
    else// if world[x][y]=='*'
    {
        if (neighbor < 2 || neighbor > 3)  
            // then a cell which was originally alive now dies into a ' '
            return ' ';
        else
            return'*';
    }
    
}

void copyWorld(char from[][82],char to[][82])
{
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 82; j++)
        {
           to[i][j]=from[i][j]; 
        }
    }
}
