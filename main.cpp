/**
 *Authors:  Mark Kelly, Ronan Timmons
 *Date:     27 December 2017
 *License:  GNU General Public License v3.0
 *Brief:    4th chronon Wator simulation Project
**/

#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

const int NUMBER_OF_FISH = 10;
const int NUMBER_OF_SHARK = 10;
const int FISH_BREED_AGE = 5;
const int SHARK_BREED_AGE = 5;
const int SHARK_STARVE_TIME = 5;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int FISH = 1;
const int SHARK = 2;
const int OCEAN = 3;
const int OCEAN_WIDTH = 80;
const int OCEAN_HEIGHT = 80;
int fishPopuation = NUMBER_OF_FISH;
int sharkPopulation = NUMBER_OF_SHARK;
int east, south, xPos, yPos, eMove, sMove;
int chronon = 0;
int ocean[OCEAN_WIDTH][OCEAN_HEIGHT];
Cell cells[OCEAN_WIDTH][OCEAN_HEIGHT];
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
        cells[xPos][yPos].cell.setFillColor(sf::Color::Green);
        //cells[xPos][yPos].Cell::fishAge = rand() % FISH_BREED_AGE;
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
        cells[xPos][yPos].cell.setFillColor(sf::Color::Red);
        cells[xPos][yPos].Cell::sharkAge = rand() % SHARK_BREED_AGE;
    }
} // end addShark

/**
 *  Draws the current state of the ocean to the screen.
**/
void drawOcean()
{
    // draw the Cells
    for (east=0; east<OCEAN_WIDTH; ++east)
    {  
        for (south=0; south<OCEAN_HEIGHT; ++south)
        {  
            window.draw(cells[east][south].cell);
        }
    }
} // end drawOcean

/**
 *  Moves and breeds the fish and shark, and Handles shark feeding.
**/
void moveFishAndShark()
{     
    for (east=0; east<OCEAN_WIDTH; ++east)
    {  
        for (south=0; south<OCEAN_HEIGHT; ++south)
        {  
            if (ocean[east][south]==FISH)
            {  
                int move=rand() % 4+1; // random number between 1 and 4
                switch (move)
                {
                    case 1: // move North
                        eMove=east;
                        sMove=south-1;
                        break;
                    case 2: // move East
                        eMove=east+1;
                        sMove=south;
                        break;
                    case 3: // move South
                        eMove=east;
                        sMove=south+1; 
                        break;
                    case 4: // move West
                        eMove=east-1;
                        sMove=south;
                        break;
                }

                if (eMove<0)
                {
                    eMove=OCEAN_WIDTH-1;
                }
                if (eMove==OCEAN_WIDTH)
                {
                    eMove=0;
                }
                if (sMove<0)
                {
                    sMove=OCEAN_HEIGHT-1;
                }
                if (sMove==OCEAN_HEIGHT)
                {
                    sMove=0;
                }

                
                
                if (ocean[eMove][sMove]==OCEAN && cells[east][south].Cell::hasMoved==false)
                {
                    std::cout << cells[east][south].Cell::fishAge << std::endl;
                    ocean[eMove][sMove]=FISH;
                    cells[eMove][sMove].cell.setFillColor(sf::Color::Green);
                    cells[eMove][sMove].Cell::hasMoved=true;

                    if (cells[east][south].Cell::fishAge < FISH_BREED_AGE)
                    {
                        ocean[east][south]=OCEAN;
                        cells[east][south].cell.setFillColor(sf::Color::Blue);
                        cells[east][south].Cell::fishAge++;
                        cells[eMove][sMove].Cell::fishAge += cells[east][south].Cell::fishAge;
                        
                    }
                    else
                    {
                        cells[eMove][sMove].Cell::fishAge=0;
                        cells[east][south].Cell::fishAge=0;
                        ++fishPopuation;
                        std::cout << "*** same age ***" << std::endl;
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
    }
    for (east=0; east<OCEAN_WIDTH; ++east)
    {  
        for (south=0; south<OCEAN_HEIGHT; ++south)
        { 
            cells[east][south].Cell::hasMoved=false;
        }
    }
} // end moveFish

/**
 *  This method is called once and sets up the simulation.
**/
void setUpSimulation()
{
    int epos=0;
    int spos=0;
    for (east=0; east<OCEAN_WIDTH; east++)
    {  
        for (south=0; south<OCEAN_HEIGHT; south++)
        {  
            ocean[east][south]=OCEAN;
        }
    }
    // Create an array of Rectangle objects to display the ocean
	for (east=0; east<80; ++east)
	{
		for (south=0; south<80; ++south)
		{
			cells[east][south] = Cell();
			cells[east][south].cell.setPosition(sf::Vector2f(float(epos), float(spos)));
            epos+=6;
		}
        epos=0;
        spos+=6;
	}

    addFish();
    //addShark();
} // end setUpSimulation

int main()
{
    sf::Text mainDisplay, populationDisplay, endMessage;
    sf::Font font;
    font.loadFromFile("OpenSans-Regular.ttf");
    mainDisplay.setFont(font);
    mainDisplay.setCharacterSize(24);
    mainDisplay.setPosition(500, 20);
    mainDisplay.setString("Starting Fish: " + std::to_string(NUMBER_OF_FISH) + "\n" 
                        + "Fish Breed Age: " + std::to_string(FISH_BREED_AGE) + "\n"
                        + "Starting Shark: " + std::to_string(NUMBER_OF_SHARK) + "\n"
                        + "Shark Breed Age: " + std::to_string(SHARK_BREED_AGE) + "\n"
                        + "Shark Starve Time: " + std::to_string(SHARK_STARVE_TIME));
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
        moveFishAndShark();

        populationDisplay.setString("Fish Population: " + std::to_string(fishPopuation) + "\n"
                                  + "Shark Population: " + std::to_string(sharkPopulation) + "\n"
                                  + "Chronon: " + std::to_string(chronon));
        window.draw(mainDisplay);
        window.draw(populationDisplay);
        

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        ++chronon;
    } // end while
    return 0;
} // end main
