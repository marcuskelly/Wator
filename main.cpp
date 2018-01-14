/**
 *Authors:  Mark Kelly, Ronan Timmons
 *Date:     27 December 2017
 *License:  GNU General Public License v3.0
 *Brief:    4th year Wator simulation Project
**/

#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

const int N_FISH = 6399;
const int N_SHARK = 1;
const int F_BREED = 5;
const int S_BREED = 5;
const int STARVE = 5;
const int OCEAN_WIDTH = 80;
const int OCEAN_HEIGHT = 80;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int OCEAN = 0;
const int FISH = 1;
const int SHARK = -1;
int fishPop = N_FISH;
int sharkPop = N_SHARK;
int x, y, xMove, yMove;
int chronon = 0;
Cell ocean[OCEAN_WIDTH][OCEAN_HEIGHT];
sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Wa-Tor Simulation");

/**
 *  Randomly adds the creature to the ocean.
 *  Set ocean cell to Green for fish,
 *  Ser ocean cell to Red for shark.
**/
void addCreature(int creature, int nCreatures) 
{
    for (int i = 0; i < nCreatures; ++i) 
    {
        x = rand() % OCEAN_WIDTH;
        y = rand() % OCEAN_HEIGHT;
        if (ocean[x][y].Cell::cellType == OCEAN)
        {
            ocean[x][y].Cell::age = rand() % F_BREED;
            ocean[x][y].Cell::cellType = creature;
            if (creature == FISH)
            {
                ocean[x][y].cell.setFillColor(sf::Color::Green);
            }
            else
            {
                ocean[x][y].cell.setFillColor(sf::Color::Red);
            }
        }
        else // Cell is occupied, so try again
        {
            --i;
        }
    }
} // end addFish

/**
 *  Draws the current state of the ocean to the screen.
**/
void drawOcean()
{
    for (x = 0; x < OCEAN_WIDTH; ++x)
    {  
        for (y = 0; y < OCEAN_HEIGHT; ++y)
        {
            ocean[x][y].Cell::hasMoved = false;
            window.draw(ocean[x][y].cell);
        }
    }
} // end drawOcean

void setMove(int *xPosition, int *yPosition) 
{
    int x, y, counter, xSearch, ySearch, top, right, bottom, left, move;
    counter = 0;
    xSearch = -1;
    ySearch= -1;
    x = *xPosition;
    y = *yPosition;
    xSearch = x;
    ySearch = y;

    std::vector<int> v;
    
    /*
    if (x-1 < 0)
    {
        xSearch = 79;
    }
    else if (x == OCEAN_WIDTH -1)
    {
        xSearch = 0;
    }
    if (y-1 < 0)
    {
        ySearch = 79;
    }
    else if (y == OCEAN_WIDTH -1)
    {
        ySearch = 0;
    }

    std::cout << counter << ": " << xSearch << ", " << ySearch << std::endl;
    
    if (ocean[xSearch][ySearch-1].Cell::isOcean == true)
    {
        v.push_back(1);
        ++counter;
    }
    if (ocean[xSearch+1][ySearch].Cell::isOcean == true)
    {
        v.push_back(2);
        ++counter;
    }
    if (ocean[xSearch][ySearch+1].Cell::isOcean == true)
    {
        v.push_back(3);
        ++counter;
    }
    if (ocean[xSearch-1][ySearch].Cell::isOcean == true)
    {
        v.push_back(4);
        ++counter;
    }
    
    move = rand() % counter+1; // random number between 1 and 4
    switch (v[move])
    {
        case 1: // move North
            x = xSearch;
            y = ySearch-1;
            break;
        case 2: // move x
            x = xSearch+1;
            y = ySearch;
            break;
        case 3: // move y
            x = xSearch;
            y = ySearch+1; 
            break;
        case 4: // move West
            x = xSearch-1;
            y = ySearch;
            break;
    }
    */
    (*xPosition) = x;
    (*yPosition) = y;
}

/**
 *  Moves the fish.
**/
void moveFish()
{   int move, moves, xPosition, yPosition;

    for (x = 0; x < OCEAN_WIDTH; ++x)
    {  
        for (y = 0; y < OCEAN_HEIGHT; ++y)
        {   
            if (ocean[x][y].Cell::cellType == FISH
                && ocean[x][y].Cell::hasMoved == false)
            {   
                xPosition = x;
                yPosition = y;
                //setMove(&yPosition, &xPosition);
                move = rand() % 4+1; // random number between 1 and 4
                switch (move)
                {
                    case 1: // move North
                        xMove = x;
                        yMove = y-1;
                        break;
                    case 2: // move x
                        xMove = x+1;
                        yMove = y;
                        break;
                    case 3: // move y
                        xMove = x;
                        yMove = y+1; 
                        break;
                    case 4: // move West
                        xMove = x-1;
                        yMove = y;
                        break;
                }
                
                if (xMove < 0)
                {
                    xMove = OCEAN_WIDTH-1;
                }
                if (xMove == OCEAN_WIDTH)
                {
                    xMove = 0;
                }
                if (yMove < 0)
                {
                    yMove = OCEAN_HEIGHT-1;
                }
                if (yMove == OCEAN_HEIGHT)
                {
                    yMove = 0;
                }
                
                if (ocean[xMove][yMove].Cell::cellType == OCEAN)
                {
                    ocean[xMove][yMove].cell.setFillColor(sf::Color::Green);
                    ocean[xMove][yMove].Cell::cellType = FISH;
                    ocean[xMove][yMove].Cell::hasMoved = true;
                    if (ocean[x][y].Cell::age < F_BREED)
                    {
                        ocean[x][y].cell.setFillColor(sf::Color::Blue);
                        ocean[x][y].Cell::cellType = OCEAN;
                        ocean[xMove][yMove].Cell::age = ocean[x][y].Cell::age + 1;
                    }
                    else
                    {
                        ocean[xMove][yMove].Cell::age = 0;
                        ocean[x][y].Cell::age = 0;
                        ++fishPop;
                    }
                }
                else
                {
                    ocean[x][y].Cell::age++;
                } 
            }
        }
    }
} // end moveFish

/**
 *  Moves shark, and Handles shark breeding and feeding.
**/
void moveShark()
{     
    for (x = 0; x < OCEAN_WIDTH; ++x)
    {  
        for (y = 0; y < OCEAN_HEIGHT; ++y)
        {
            if (ocean[x][y].Cell::cellType == SHARK
                && ocean[x][y].Cell::hasMoved == false)
            {   
                if (ocean[x][y].Cell::starveTime == STARVE)
                {
                    ocean[x][y].cell.setFillColor(sf::Color::Blue);
                    ocean[x][y].Cell::cellType = OCEAN;
                    --sharkPop;
                }
                else
                {
                    int move = rand() % 4+1; // random number between 1 and 4
                    switch (move)
                    {
                        case 1: // move North
                            xMove = x;
                            yMove = y-1;
                            break;
                        case 2: // move x
                            xMove = x+1;
                            yMove = y;
                            break;
                        case 3: // move y
                            xMove = x;
                            yMove = y+1; 
                            break;
                        case 4: // move West
                            xMove = x-1;
                            yMove = y;
                            break;
                    }

                    if (xMove < 0)
                    {
                        xMove = OCEAN_WIDTH-1;
                    }
                    if (xMove == OCEAN_WIDTH)
                    {
                        xMove = 0;
                    }
                    if (yMove < 0)
                    {
                        yMove = OCEAN_HEIGHT-1;
                    }
                    if (yMove == OCEAN_HEIGHT)
                    {
                        yMove = 0;
                    }

                    if (ocean[xMove][yMove].Cell::cellType == OCEAN)
                    {
                        ocean[xMove][yMove].cell.setFillColor(sf::Color::Red);
                        ocean[xMove][yMove].Cell::cellType = SHARK;
                        ocean[xMove][yMove].Cell::hasMoved = true;
                        ocean[xMove][yMove].Cell::starveTime = ocean[x][y].Cell::starveTime +1;
                        if (ocean[x][y].Cell::age < S_BREED)
                        {
                            ocean[x][y].cell.setFillColor(sf::Color::Blue);
                            ocean[x][y].Cell::cellType = OCEAN;
                            ocean[xMove][yMove].Cell::age = ocean[x][y].Cell::age + 1;
                        }
                        else
                        {
                            ocean[xMove][yMove].Cell::age = 0;
                            ocean[xMove][yMove].Cell::starveTime = 0;
                            ocean[x][y].Cell::age = 0;
                            ++sharkPop;
                        }
                    }
                    else if (ocean[xMove][yMove].Cell::cellType == FISH)
                    {
                        ocean[xMove][yMove].Cell::cellType = SHARK;
                        ocean[xMove][yMove].cell.setFillColor(sf::Color::Red);
                        ocean[xMove][yMove].Cell::starveTime = 0;
                        --fishPop;
                        if (ocean[x][y].Cell::age < S_BREED)
                        {
                            ocean[x][y].cell.setFillColor(sf::Color::Blue);
                            ocean[x][y].Cell::cellType = OCEAN;
                            ocean[xMove][yMove].Cell::age = ocean[x][y].Cell::age + 1;  
                        }
                        else
                        {
                            ocean[xMove][yMove].Cell::age = 0;
                            ocean[x][y].Cell::age = 0;
                            ocean[x][y].cell.setFillColor(sf::Color::Red);
                            ++sharkPop;
                        }
                    }
                } 
            }
        }
    }
} // end moveShark

/**
 *  This method is called once and sets up the simulation.
**/
void setUpSimulation()
{
    const int OFF_SET = 6;
    int xPos = 0;
    int yPos = 0;
	for (x = 0; x < OCEAN_WIDTH; ++x)
	{
		for (y = 0; y < OCEAN_HEIGHT; ++y)
		{
			ocean[x][y] = Cell();
			ocean[x][y].cell.setPosition(sf::Vector2f(float(xPos), float(yPos)));
            xPos += OFF_SET;
		}
        xPos = 0;
        yPos += OFF_SET;
	}
    addCreature(FISH, N_FISH);
    addCreature(SHARK, N_SHARK);
} // end setUpSimulation

int main()
{
    sf::Text mainDisplay, populationDisplay;
    sf::Font font;
    font.loadFromFile("OpenSans-Regular.ttf");
    mainDisplay.setFont(font);
    mainDisplay.setCharacterSize(24);
    mainDisplay.setPosition(500, 20);
    mainDisplay.setString("Starting Fish: "+ std::to_string(N_FISH) +"\n" 
                        + "Fish Breed Age: "+ std::to_string(F_BREED) +"\n"
                        + "Starting Shark: "+std::to_string(N_SHARK)+"\n"
                        + "Shark Breed Age: "+std::to_string(S_BREED)+"\n"
                        + "Shark Starve Time: "+std::to_string(STARVE));
    populationDisplay.setFont(font);
    populationDisplay.setCharacterSize(24);
    populationDisplay.setPosition(500, 360);
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
        moveShark();
        populationDisplay.setString("Fish Population: "+std::to_string(fishPop)+"\n"
                                  + "Shark Population: "+std::to_string(sharkPop)+"\n"
                                  + "Chronon: "+std::to_string(chronon));
        window.draw(mainDisplay);
        window.draw(populationDisplay);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds());
        ++chronon;
    } // end while
    return 0;
} // end main
