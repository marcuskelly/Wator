/**
 *Authors:  Mark Kelly, Ronan Timmons
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
const int NUMBER_OF_SHARK = 10;
const int FISH_BREED_AGE = 5;
const int SHARK_BREED_AGE = 5;
const int SHARK_STARVE_TIME = 10;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int FISH = 1;
const int SHARK = -1;
const int OCEAN = 0;
const int OCEAN_WIDTH = 80;
const int OCEAN_HEIGHT = 80;
int fishPopuation = NUMBER_OF_FISH;
int sharkPopulation = NUMBER_OF_SHARK;
int east, south, xPos, yPos, eMove, sMove;
int year = 0;
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
        ocean[yPos][xPos] = FISH;
        cells[OCEAN_WIDTH*xPos+yPos].cell.setFillColor(sf::Color::Green);
        cells[OCEAN_WIDTH*xPos+yPos].Cell::fishAge = rand() % FISH_BREED_AGE;
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
        ocean[yPos][xPos] = SHARK;
        cells[OCEAN_WIDTH*xPos+yPos].cell.setFillColor(sf::Color::Red);
        cells[OCEAN_WIDTH*xPos+yPos].Cell::sharkAge = rand() % SHARK_BREED_AGE;
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

/**
 *  Moves and breeds the fish.
**/
void moveFishAndShark()
{     
    for (east=0; east<OCEAN_WIDTH; ++east)
    {  
        for (south=0; south<OCEAN_HEIGHT; ++south)
        {  
            if (ocean[east][south]!=OCEAN)
            {  
                int move=rand() % 4+1; // random number between 1 and 4
                // std::cout << move << std::endl;
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

                if (eMove<0) eMove=0;
                if (eMove==OCEAN_WIDTH) eMove=OCEAN_WIDTH-1;
                if (sMove<0) sMove=0;
                if (sMove==OCEAN_HEIGHT) sMove=OCEAN_HEIGHT-1;

                // make the move if cell is empty
                if (ocean[eMove][sMove]==OCEAN)
                {   
                    if (ocean[east][south]==FISH)
                    {
                        ocean[eMove][sMove]=FISH;
                        cells[OCEAN_WIDTH*sMove+eMove].cell.setFillColor(sf::Color::Green);
                        if (cells[OCEAN_WIDTH*south+east].Cell::fishAge==FISH_BREED_AGE)
                        {
                            cells[OCEAN_WIDTH*south+east].Cell::fishAge=0;
                            cells[OCEAN_WIDTH*sMove+eMove].Cell::fishAge=0;
                            ++fishPopuation;
                        }
                        else
                        {
                            ocean[east][south]=OCEAN;
                            cells[OCEAN_WIDTH*south+east].cell.setFillColor(sf::Color::Blue);
                            cells[OCEAN_WIDTH*south+east].Cell::fishAge++;
                        }
                    }
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
                            ++sharkPopulation;
                        }
                        else
                        {
                            ocean[eMove][sMove]=SHARK;
                            cells[OCEAN_WIDTH*sMove+eMove].cell.setFillColor(sf::Color::Red);
                            ocean[east][south]=OCEAN;
                            cells[OCEAN_WIDTH*south+east].cell.setFillColor(sf::Color::Blue);
                            cells[OCEAN_WIDTH*south+east].Cell::sharkAge++;
                            cells[OCEAN_WIDTH*south+east].Cell::sharkStarveTime++;
                        }

                    }
                }
                else if (ocean[eMove][sMove]==FISH && ocean[east][south]==SHARK)
                {
                    ocean[eMove][sMove]=SHARK;
                    cells[OCEAN_WIDTH*sMove+eMove].cell.setFillColor(sf::Color::Red);
                    cells[OCEAN_WIDTH*sMove+eMove].Cell::sharkStarveTime=0;
                    ocean[east][south]=OCEAN;
                    cells[OCEAN_WIDTH*south+east].cell.setFillColor(sf::Color::Blue);
                    --fishPopuation;
                }
            }
        }
    }
} // end moveFish

/**
 *  This method is called once and sets up the simulation.
**/
void setUpSimulation()
{
    int counter = 0;
    const float X_OFFSET = 6;
	const float Y_OFFSET = 6;
    int numberOfCells = Y_OFFSET*OCEAN_WIDTH;
    for (int y=0; y<OCEAN_WIDTH; y++)
    {  
        for (int x=0; x<OCEAN_HEIGHT; x++)
        {  
            ocean[y][x]=OCEAN;
        }
    }
    // Create an array of Rectangle objects to display the ocean
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
    addShark();
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
    endMessage.setFont(font);
    endMessage.setCharacterSize(40);
    endMessage.setPosition(75, 200);
    endMessage.setString("A Lifeless World!");
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
                                  + "Year: " + std::to_string(year));
        window.draw(mainDisplay);
        window.draw(populationDisplay);
        if (sharkPopulation==0&&fishPopuation==0)
        {
            window.draw(endMessage);
        }
        

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        ++year;
    } // end while
    return 0;
} // end main
