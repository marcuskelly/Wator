/**
 *Authors:  Mark Kelly, Ronan Timmons
 *Date:     27 December 2017
 *License:  GNU General Public License v3.0
 *Brief:    4th year Wator simulation Project
**/

#include "Cell.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include "main.h"
#include <fstream> // for output filebenchmarking

const int N_FISH = 820;
const int N_SHARK = 450;
const int F_BREED = 5;
const int S_BREED = 5;
const int STARVE = 5;
const int TIME = 0; // time in milliseconds for each chronon
const int OCEAN_WIDTH = 80;
const int OCEAN_HEIGHT = 80;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int OCEAN = 0;
const int FISH = 1;
const int SHARK = -1;
const int ITERATIONS = 5000; // Iteration Data for benchmarking 
int fishPop = N_FISH;
int sharkPop = N_SHARK;
int chronon = 0;
int x, y, xMove, yMove;
Cell ocean[OCEAN_WIDTH][OCEAN_HEIGHT]; // array of cell objects
std::vector<std::tuple<int, int>> moves; // vector of tuples to store x y positions
sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Wa-Tor Simulation");
sf::Text display;

/**
 *  Takes an integer value for the creature, 
 *  and the number of creatures to add to the ocean.
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
            else // We have a shark
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
            ocean[x][y].Cell::madeMove = false;
            window.draw(ocean[x][y].cell);
        }
    }
} // end drawOcean

/**
 *  Takes current x, y positions and type of cell to check for.
 *  Adds the found cells to a vector, and returns the number of cells found.
**/
int checkCellType(int x, int y, int cellType)
{
    int counter = 0;
    // Check North
    if (ocean[x][((y -1) < 0) ? OCEAN_HEIGHT-1 : y-1].Cell::cellType == cellType)
    {
        moves.push_back(std::make_tuple(x, ((y -1) < 0) ? OCEAN_HEIGHT-1 : y-1));
        ++counter;
    }
    // Check East
    if (ocean[((x +1) > OCEAN_WIDTH-1) ? 0 : x+1][y].Cell::cellType == cellType)
    {
        moves.push_back(std::make_tuple(((x +1) > OCEAN_WIDTH-1) ? 0 : x+1, y));
        ++counter;
    }
    // Check South
    if (ocean[x][((y +1) > OCEAN_HEIGHT-1) ? 0 : y+1].Cell::cellType == cellType)
    {
        moves.push_back(std::make_tuple(x, ((y +1) > OCEAN_HEIGHT-1) ? 0 : y+1));
        ++counter;
    }
    // Check West
    if (ocean[((x -1) < 0) ? OCEAN_WIDTH-1 : x-1][y].Cell::cellType == cellType)
    {
        moves.push_back(std::make_tuple(((x -1) < 0) ? OCEAN_WIDTH-1 : x-1, y));
        ++counter;
    }
    return counter;
} // end checkCellType

/**
 *  Takes pointers to current x and y positions and the creature type.
**/
void findMove(int *xPosition, int *yPosition, int creature) 
{
    int counter = 0;
    int x = *xPosition;
    int y = *yPosition;
    if (creature == FISH)
    {
        counter = checkCellType(x, y , OCEAN);
        if (!moves.empty())
        {
            int move = rand() % int(counter);
            (*xPosition) = std::get<0>(moves[move]);
            (*yPosition) = std::get<1>(moves[move]);
        }
    }
    else // We have a shark
    {
        counter = checkCellType(x, y , FISH);
        if (!moves.empty())
        {
            int move = rand() % int(counter);
            (*xPosition) = std::get<0>(moves[move]);
            (*yPosition) = std::get<1>(moves[move]);
        }
        else // No food found, so check for ocean
        {
            counter = checkCellType(x, y , OCEAN);
            if (!moves.empty())
            {
                int move = rand() % int(counter);
                (*xPosition) = std::get<0>(moves[move]);
                (*yPosition) = std::get<1>(moves[move]);
            }
        }
    }
    moves.clear();
} // end findMove

/**
 *  Moves the fish.
**/
void moveFish()
{
    for (x = 0; x < OCEAN_WIDTH; ++x)
    {  
        for (y = 0; y < OCEAN_HEIGHT; ++y)
        {  
            if (ocean[x][y].Cell::cellType == FISH
                && ocean[x][y].Cell::madeMove == false)
            {   
                xMove = x;
                yMove = y;
                findMove(&xMove, &yMove, FISH);
                if (xMove == x && yMove == y)
                {
                    ocean[x][y].Cell::age++;
                }
                else // we have a position to move to
                {
                    ocean[xMove][yMove].cell.setFillColor(sf::Color::Green);
                    ocean[xMove][yMove].Cell::cellType = FISH;
                    ocean[xMove][yMove].Cell::madeMove = true;
                    if (ocean[x][y].Cell::age < F_BREED)
                    {
                        ocean[x][y].cell.setFillColor(sf::Color::Blue);
                        ocean[x][y].Cell::cellType = OCEAN;
                        ocean[xMove][yMove].Cell::age = ocean[x][y].Cell::age + 1;
                    }
                    else // fish got jiggy with it
                    {
                        ocean[xMove][yMove].Cell::age = 0;
                        ocean[x][y].Cell::age = 0;
                        ++fishPop;
                    }
                } 
            }
        }
    }
} // end moveFish

/**
 *  Moves shark.
**/
void moveShark()
{     
    for (x = 0; x < OCEAN_WIDTH; ++x)
    {  
        for (y = 0; y < OCEAN_HEIGHT; ++y)
        {
            if (ocean[x][y].Cell::cellType == SHARK
                && ocean[x][y].Cell::madeMove == false)
            {   
                if (ocean[x][y].Cell::starveAge == STARVE)
                {
                    ocean[x][y].cell.setFillColor(sf::Color::Blue);
                    ocean[x][y].Cell::cellType = OCEAN;
                    --sharkPop;
                }
                else // shark is alive and hungry
                {
                    if (xMove == x && yMove == y)
                    {
                        ocean[x][y].Cell::age++;
                        ocean[x][y].Cell::starveAge++;
                    }
                    else // we have a position to move to
                    {
                        xMove = x;
                        yMove = y;
                        findMove(&xMove, &yMove, SHARK);
                        if (ocean[xMove][yMove].Cell::cellType == OCEAN)
                        {
                            ocean[xMove][yMove].cell.setFillColor(sf::Color::Red);
                            ocean[xMove][yMove].Cell::cellType = SHARK;
                            ocean[xMove][yMove].Cell::madeMove = true;
                            ocean[xMove][yMove].Cell::starveAge = ocean[x][y].Cell::starveAge +1;
                            if (ocean[x][y].Cell::age < S_BREED)
                            {
                                ocean[x][y].cell.setFillColor(sf::Color::Blue);
                                ocean[x][y].Cell::cellType = OCEAN;
                                ocean[xMove][yMove].Cell::age = ocean[x][y].Cell::age + 1;
                            }
                            else // shark got jiggy with it
                            {
                                ocean[xMove][yMove].Cell::age = 0;
                                ocean[xMove][yMove].Cell::starveAge = 0;
                                ocean[x][y].Cell::age = 0;
                                ++sharkPop;
                            }
                        }
                        else if (ocean[xMove][yMove].Cell::cellType == FISH)
                        {
                            ocean[xMove][yMove].Cell::cellType = SHARK;
                            ocean[xMove][yMove].cell.setFillColor(sf::Color::Red);
                            ocean[xMove][yMove].Cell::madeMove = true;
                            ocean[xMove][yMove].Cell::starveAge = 0;
                            --fishPop;
                            if (ocean[x][y].Cell::age < S_BREED)
                            {
                                ocean[x][y].cell.setFillColor(sf::Color::Blue);
                                ocean[x][y].Cell::cellType = OCEAN;
                                ocean[xMove][yMove].Cell::age = ocean[x][y].Cell::age + 1;  
                            }
                            else // shark got jiggy with it
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
    }
} // end moveShark

/**
 *  This method is called once and sets up the simulation.
**/
void setUpSimulation()
{
    const int OFF_SET = 6; // offset = width of cell + 1
    int xPos = 0;
    int yPos = 0;
	for (x = 0; x < OCEAN_WIDTH; ++x)
	{
		for (y = 0; y < OCEAN_HEIGHT; ++y)
		{
			ocean[x][y] = Cell();
			ocean[x][y].cell.setPosition(sf::Vector2f(float(yPos), float(xPos)));
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
    sf::Text display;
    sf::Font font;
	std::ofstream benchFileWrite;
	benchFileWrite.open("benchTimeTaken320.csv");
	std::clock_t benchStartTime;
	double benchTimeTaken = 0.0;
	font.loadFromFile("OpenSans-Regular.ttf");
    display.setFont(font);
    display.setCharacterSize(24);
    display.setPosition(500, 20); 
    srand(time(NULL));  
    setUpSimulation();
	while (window.isOpen() && chronon < ITERATIONS) //stop collecting data after 5000 for benchmarking
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        } // end while
		benchStartTime = std::clock(); 
        window.clear();
        drawOcean();
        moveFish();
        moveShark();
        display.setString("Starting Fish: "+std::to_string(N_FISH)+"\n" 
                         +"Fish Breed Age: "+std::to_string(F_BREED)+"\n"
                         +"Starting Shark: "+std::to_string(N_SHARK)+"\n"
                         +"Shark Breed Age: "+std::to_string(S_BREED)+"\n"
                         +"Shark Starve: "+std::to_string(STARVE)+"\n\n"
                         +"Fish Population: "+std::to_string(fishPop)+"\n"
                         +"Shark Population: "+std::to_string(sharkPop)+"\n"
                         +"Chronons: "+std::to_string(chronon));
        window.draw(display);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
        ++chronon;
		benchTimeTaken = ((std::clock() - benchTimeTaken) / (double)CLOCKS_PER_SEC); // dividing start by CLOCKS_PER_SEC --> gives the number of seconds
		benchFileWrite << benchTimeTaken << ",\n"; // after each chronon
    } // end while
	benchFileWrite.close(); 
    return 0;
} // end main
