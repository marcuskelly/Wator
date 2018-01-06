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

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int OCEAN_WIDTH = 80;
const int OCEAN_HEIGHT = 80;
const int MAZ_SIZE = 80;
const int NUMBER_OF_FISH = 10;
const int NUMBER_OF_SHARK = 0;
int east, south, xPos, yPos;
bool started = true;

int ocean[OCEAN_WIDTH][OCEAN_HEIGHT];
Cell cells[OCEAN_WIDTH*OCEAN_HEIGHT];

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Wa-Tor Simulation");

void drawOcean()
{
    // draw the Cells
    for (int i = 0; i < OCEAN_WIDTH*OCEAN_HEIGHT; ++i)
    {
        window.draw(cells[i].cell);
    }
} // end drawOcean


void addFish() {
    srand(time(NULL));
    for (int i = 0; i < NUMBER_OF_FISH; ++i) {
        yPos = random() % OCEAN_WIDTH;
        xPos = random() % OCEAN_HEIGHT;
        std::cout << xPos;
        ocean[xPos][yPos] = 1;
        cells[OCEAN_WIDTH*xPos+yPos].cell.setFillColor(sf::Color::Green);
    }
} // end addFish


int main()
{
    sf::RectangleShape shark;
    shark.setSize(sf::Vector2f(10, 10));
    shark.setFillColor(sf::Color::Red);
    shark.setPosition(10, 20);

    sf::RectangleShape fish;
    fish.setSize(sf::Vector2f(10, 10));
    fish.setFillColor(sf::Color::Green);
    fish.setPosition(20, 40);


    for (east=0; east<OCEAN_WIDTH; east++)
    {  
        for (south=0; south<OCEAN_HEIGHT; south++)
        {  
            ocean[east][south]=0;
        }
    }
    
    int counter = 0;
    const float X_OFFSET = 6;
	const float Y_OFFSET = 6;
    int size = Y_OFFSET*OCEAN_WIDTH;
	for (int y = 0; y < size; y += Y_OFFSET)
	{
		for (int x = 0; x < size; x += X_OFFSET)
		{
			cells[counter] = Cell();
			cells[counter].cell.setPosition(sf::Vector2f(float(x), float(y)));
			counter++;
		}
	}
    
    //int v1 = rand() % 100;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        } // end while

        window.clear();


        //window.draw(shark);
        //window.draw(fish);

        drawOcean();
        if(started)
        {
            addFish();
            started = false;
        }
        


        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } // end while
    return 0;
} // end main
