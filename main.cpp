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

const int NUMBER_OF_FISH = 1;
const int NUMBER_OF_SHARK = 10;
const int FISH_BREED_AGE = 5;
const int SHARK_BREED_AGE = 5;
const int SHARK_STARVE_TIME = 5;
const int OCEAN_WIDTH = 80;
const int OCEAN_HEIGHT = 80;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
int fishPopuation = NUMBER_OF_FISH;
int sharkPopulation = NUMBER_OF_SHARK;
int east, south, eastMove, southMove;
int chronon = 0;
Cell cells[OCEAN_WIDTH][OCEAN_HEIGHT];
sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Wa-Tor Simulation");

/**
 *  Randomly adds the fish to the ocean.
 *  Set ocean cell to Green for fish.
**/
void addFish() 
{
    for (int i=0; i<NUMBER_OF_FISH; ++i) 
    {
        east = rand() % OCEAN_WIDTH;
        south = rand() % OCEAN_HEIGHT;
        cells[east][south].cell.setFillColor(sf::Color::Green);
        cells[east][south].Cell::isFish = true;
    }
} // end addFish

/**
 *  Randomly adds the shark to the ocean.
 *  Set ocean cell to Red for shark.
**/
void addShark() 
{
    for (int i=0; i<NUMBER_OF_SHARK; ++i) 
    {
        east = rand() % OCEAN_WIDTH;
        south = rand() % OCEAN_HEIGHT;
        cells[east][south].cell.setFillColor(sf::Color::Red);
        cells[east][south].Cell::isShark = true;
    }
} // end addShark

/**
 *  Draws the current state of the ocean to the screen.
**/
void drawOcean()
{
    for (east=0; east<OCEAN_WIDTH; ++east)
    {  
        for (south=0; south<OCEAN_HEIGHT; ++south)
        {
            cells[east][south].Cell::hasMoved=false;
            window.draw(cells[east][south].cell);
        }
    }
} // end drawOcean

/**
 *  Moves and breeds the fish.
**/
void moveFish()
{     
    for (east=0; east<OCEAN_WIDTH; ++east)
    {  
        for (south=0; south<OCEAN_HEIGHT; ++south)
        {  
            if (cells[east][south].Cell::isFish == true)
            {  
                int move = rand() % 4+1; // random number between 1 and 4
                switch (move)
                {
                    case 1: // move North
                        eastMove = east;
                        southMove = south-1;
                        break;
                    case 2: // move East
                        eastMove = east+1;
                        southMove = south;
                        break;
                    case 3: // move South
                        eastMove = east;
                        southMove = south+1; 
                        break;
                    case 4: // move West
                        eastMove = east-1;
                        southMove = south;
                        break;
                }

                if (eastMove < 0)
                {
                    eastMove = OCEAN_WIDTH-1;
                }
                if (eastMove == OCEAN_WIDTH)
                {
                    eastMove = 0;
                }
                if (southMove < 0)
                {
                    southMove = OCEAN_HEIGHT-1;
                }
                if (southMove == OCEAN_HEIGHT)
                {
                    southMove = 0;
                }

                
                if (cells[east][south].Cell::hasMoved == false
                    && cells[eastMove][southMove].Cell::isFish == false
                    && cells[eastMove][southMove].Cell::isShark == false)
                {
                    std::cout << cells[east][south].Cell::fishAge << std::endl;
                    cells[eastMove][southMove].cell.setFillColor(sf::Color::Green);
                    cells[eastMove][southMove].Cell::isFish = true;
                    cells[eastMove][southMove].Cell::hasMoved = true;
                    if (cells[east][south].Cell::fishAge < FISH_BREED_AGE)
                    {
                        cells[east][south].cell.setFillColor(sf::Color::Blue);
                        cells[east][south].Cell::isFish = false;
                        cells[east][south].Cell::fishAge++;
                        cells[eastMove][southMove].Cell::fishAge = 0;
                        cells[eastMove][southMove].Cell::fishAge += cells[east][south].Cell::fishAge;
                    }
                    else
                    {
                        cells[eastMove][southMove].Cell::fishAge = 0;
                        cells[east][south].Cell::fishAge = 0;
                        ++fishPopuation;
                    }
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
    for (east=0; east<OCEAN_WIDTH; ++east)
    {  
        for (south=0; south<OCEAN_HEIGHT; ++south)
        {  
            if (cells[east][south].Cell::isShark == true)
            {  
                int move = rand() % 4+1; // random number between 1 and 4
                switch (move)
                {
                    case 1: // move North
                        eastMove = east;
                        southMove = south-1;
                        break;
                    case 2: // move East
                        eastMove = east+1;
                        southMove = south;
                        break;
                    case 3: // move South
                        eastMove = east;
                        southMove = south+1; 
                        break;
                    case 4: // move West
                        eastMove = east-1;
                        southMove = south;
                        break;
                }

                if (eastMove < 0)
                {
                    eastMove = OCEAN_WIDTH-1;
                }
                if (eastMove == OCEAN_WIDTH)
                {
                    eastMove = 0;
                }
                if (southMove < 0)
                {
                    southMove = OCEAN_HEIGHT-1;
                }
                if (southMove == OCEAN_HEIGHT)
                {
                    southMove = 0;
                }

                                        /*
                        else // Its a shark
                        {
                            if (cells[OCEAN_WIDTH*south+east].Cell::sharkStarveTime==SHARK_STARVE_TIME)
                            {
                                ocean[east][south]=OCEAN;
                                cells[OCEAN_WIDTH*south+east].cell.setFillColor(sf::Color::Blue);
                                --sharkPopulation;
                            }
                            else if (cells[OCEAN_WIDTH*south+east].Cell::sharkAge==SHARK_BREED_AGE)
                            {
                                ocean[eMove][sMove]=SHARK;
                                cells[OCEAN_WIDTH*sMove+eMove].cell.setFillColor(sf::Color::Red);
                                cells[OCEAN_WIDTH*south+east].Cell::sharkAge=0;
                                cells[OCEAN_WIDTH*sMove+eMove].Cell::sharkAge=0;
                                cells[OCEAN_WIDTH*sMove+eMove].Cell::hasMoved=true;
                                ++sharkPopulation;
                            }
                            else
                            {
                                ocean[eMove][sMove]=SHARK;
                                cells[OCEAN_WIDTH*sMove+eMove].cell.setFillColor(sf::Color::Red);
                                ocean[east][south]=OCEAN;
                                cells[OCEAN_WIDTH*south+east].cell.setFillColor(sf::Color::Blue);
                                cells[OCEAN_WIDTH*sMove+eMove].Cell::hasMoved=true;
                                cells[OCEAN_WIDTH*south+east].Cell::sharkAge++;
                                cells[OCEAN_WIDTH*south+east].Cell::sharkStarveTime++;
                            }

                        }
                        */
                    /*
                    if (ocean[eMove][sMove]==FISH && ocean[east][south]==SHARK)
                    {
                        ocean[eMove][sMove]=SHARK;
                        cells[OCEAN_WIDTH*sMove+eMove].Cell::hasMoved=true;
                        cells[OCEAN_WIDTH*sMove+eMove].cell.setFillColor(sf::Color::Red);
                        cells[OCEAN_WIDTH*sMove+eMove].Cell::sharkStarveTime=0;
                        --fishPopuation;

                        if (cells[OCEAN_WIDTH*south+east].Cell::sharkAge==SHARK_BREED_AGE)
                        {
                            //ocean[eMove][sMove]=SHARK;
                            //cells[OCEAN_WIDTH*sMove+eMove].cell.setFillColor(sf::Color::Red);
                            cells[OCEAN_WIDTH*south+east].Cell::sharkAge=0;
                            cells[OCEAN_WIDTH*sMove+eMove].Cell::sharkAge=0;
                            //cells[OCEAN_WIDTH*sMove+eMove].Cell::hasMoved=true;
                            ++sharkPopulation;
                        }
                        else
                        {
                            //ocean[eMove][sMove]=SHARK;
                            //cells[OCEAN_WIDTH*sMove+eMove].cell.setFillColor(sf::Color::Red);
                            //cells[OCEAN_WIDTH*sMove+eMove].Cell::sharkStarveTime=0;
                            ocean[east][south]=OCEAN;
                            cells[OCEAN_WIDTH*south+east].cell.setFillColor(sf::Color::Blue);
                            //cells[OCEAN_WIDTH*sMove+eMove].Cell::hasMoved=true;
                        }
                    }*/ 
                 
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
    int eastPos, southPos = 0;

	for (east=0; east<80; ++east)
	{
		for (south=0; south<80; ++south)
		{
			cells[east][south] = Cell();
			cells[east][south].cell.setPosition(sf::Vector2f(float(eastPos), float(southPos)));
            eastPos += OFF_SET;
		}
        eastPos = 0;
        southPos += OFF_SET;
	}
    addFish();
    //addShark();
} // end setUpSimulation

int main()
{
    sf::Text mainDisplay, populationDisplay;
    sf::Font font;
    font.loadFromFile("OpenSans-Regular.ttf");
    mainDisplay.setFont(font);
    mainDisplay.setCharacterSize(24);
    mainDisplay.setPosition(500, 20);
    mainDisplay.setString("Starting Fish: "+ std::to_string(NUMBER_OF_FISH) +"\n" 
                        + "Fish Breed Age: "+ std::to_string(FISH_BREED_AGE) +"\n"
                        + "Starting Shark: "+std::to_string(NUMBER_OF_SHARK)+"\n"
                        + "Shark Breed Age: "+std::to_string(SHARK_BREED_AGE)+"\n"
                        + "Shark Starve Time: "+std::to_string(SHARK_STARVE_TIME));
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
        //moveShark();

        populationDisplay.setString("Fish Population: "+std::to_string(fishPopuation)+"\n"
                                  + "Shark Population: "+std::to_string(sharkPopulation)+"\n"
                                  + "Chronon: "+std::to_string(chronon));
        window.draw(mainDisplay);
        window.draw(populationDisplay);
        
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        ++chronon;
    } // end while
    return 0;
} // end main
