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

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int OCEAN_WIDTH = 80;
const int OCEAN_HEIGHT = 80;
const int MAZ_SIZE = 80;
int east, south;

int ocean[OCEAN_WIDTH][OCEAN_HEIGHT];

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Wa-Tor Simulation");
    //window.setPosition(sf::Vector2i(0, 0));

    sf::RectangleShape shark;
    shark.setSize(sf::Vector2f(10, 10));
    shark.setFillColor(sf::Color::Red);
    shark.setPosition(10, 20);

    sf::RectangleShape fish;
    fish.setSize(sf::Vector2f(10, 10));
    fish.setFillColor(sf::Color::Green);
    fish.setPosition(20, 40);

    int counter = 0;

    for (east=0; east<MAZ_SIZE; east++)
    {  
        for (south=0; south<MAZ_SIZE; south++)
        {  
            ocean[east][south]=0;
            counter++;
        }
    }
    Cell cells[counter];
    counter = 0;
    const float X_OFFSET = 5;
	const float Y_OFFSET = 5;
    int size = X_OFFSET*MAZ_SIZE;
	for (float y = 0; y < size; y += Y_OFFSET)
	{
		for (float x = 0; x < size; x += X_OFFSET)
		{
			cells[counter] = Cell();
			cells[counter].cell.setPosition(sf::Vector2f(x, y));
			counter++;
		}
	}
    


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        //window.draw(shark);
        //window.draw(fish);

        
        // draw the Cells
        for (int i = 0; i < counter; ++i)
        {
            window.draw(cells[i].cell);
            std::cout << i  << std::endl;
        }
            

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } // end while
    return 0;
} // end main
