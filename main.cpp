/**
 *Authors:   Mark Kelly, Ronan Timmons
 *Date:     27 December 2017
 *License:  GNU General Public License v3.0
 *Brief:    4th Year Wator simulation Project
**/

#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

const int NUMBER_OF_FISH = 10;
const int NUMBER_OF_SHARK = 5;
const int FISH_BREED_TIME = 5;
const int SHARK_BREED_TIME = 5;
const int SHARK_STARVE_TIME = 5;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int FISH = 1;
const int SHARK = -1;
const int OCEAN = 0;
const int OCEAN_WIDTH = 80;
const int OCEAN_HEIGHT = 80;
int east, south, xPos, yPos, emove, smove;
int ocean[OCEAN_WIDTH][OCEAN_HEIGHT];
Cell cells[OCEAN_WIDTH*OCEAN_HEIGHT];
sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Wa-Tor Simulation");

/**
 *  Randomly adds the fish to the 2d ocean array.
 *  Changes the cell colour to Green to represent a fish.
**/
void addFish() {
    for (int i = 0; i < NUMBER_OF_FISH; ++i) {
        yPos = rand() % OCEAN_WIDTH;
        xPos = rand() % OCEAN_HEIGHT;
        ocean[xPos][yPos] = FISH;
        cells[OCEAN_WIDTH*xPos+yPos].cell.setFillColor(sf::Color::Green);
    }
} // end addFish

/**
 *  Randomly adds the shark to the 2d ocean array.
 *  Changes the cell colour to Red to represent a shark.
**/
void addShark() {
    for (int i = 0; i < NUMBER_OF_SHARK; ++i) {
        yPos = rand() % OCEAN_WIDTH;
        xPos = rand() % OCEAN_HEIGHT;
        ocean[xPos][yPos] = SHARK;
        cells[OCEAN_WIDTH*xPos+yPos].cell.setFillColor(sf::Color::Red);
    }
} // end addShark

/**
 *  Draws the current state of the ocean to the screen.
**/
void drawOcean()
{
    // draw the Cells
    for (int i = 0; i < OCEAN_WIDTH*OCEAN_HEIGHT; ++i)
    {
        window.draw(cells[i].cell);
    }
} // end drawOcean



void moveFish()
{     
    for (east=0; east<OCEAN_WIDTH; ++east)
    {  
        for (south=0; south<OCEAN_HEIGHT; ++south)
        {  
            if (ocean[east][south]==FISH)
            {  
                int move=rand() % 4+1;
                switch (move)
                {
                    case 1:     //move N
                        emove=east;
                        smove=south-1;
                        break;
                    case 2:     // move E
                        emove=east+1;
                        smove=south;
                        break;
                    case 3:     // move S
                        emove=east;
                        smove=south+1; 
                        break;
                     case 4:     // move W
                        emove=east-1;
                        smove=south;
                        break;
                }

                if (emove<0) emove=0;
                if (emove==OCEAN_WIDTH) emove=OCEAN_WIDTH-1;
                if (smove<0) smove=0;
                if (smove==OCEAN_HEIGHT) smove=OCEAN_HEIGHT-1;

                // make the move if cell is empty
                if (ocean[emove][smove]==OCEAN)
                {  
                    ocean[emove][smove]=FISH;
                    ocean[east][south]=OCEAN;
                    cells[OCEAN_WIDTH*smove+emove].cell.setFillColor(sf::Color::Green);
                    cells[OCEAN_WIDTH*south+east].cell.setFillColor(sf::Color::Blue);
                }




            }
        }
    }
}






/**
 *  This method is called once and sets up the simulation.
**/
void setUpSimulation()
{
    int counter = 0;
    const float X_OFFSET = 6;
	const float Y_OFFSET = 6;
    int numberOfCells = Y_OFFSET*OCEAN_WIDTH;
    // 2d array for the ocean to keep track of whats in each cell.
    for (int y=0; y<OCEAN_WIDTH; y++)
    {  
        for (int x=0; x<OCEAN_HEIGHT; x++)
        {  
            ocean[y][x]=OCEAN; // Every cell set to ocean.
        }
    }
    // Create an array of Rectangle objects to represent the ocean
	for (int y = 0; y < numberOfCells; y += Y_OFFSET)
	{
		for (int x = 0; x < numberOfCells; x += X_OFFSET)
		{
			cells[counter] = Cell();
			cells[counter].cell.setPosition(sf::Vector2f(float(x), float(y)));
			counter++;
		}
	}    
    addFish();
    //addShark();
} // end setUpSimulation

int main()
{
    srand(time(NULL));    
    setUpSimulation();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        } // end while

        window.clear();

        
        drawOcean();
        
        
        moveFish();


        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } // end while
    return 0;
} // end main
