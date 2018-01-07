#include "Cell.h"

Cell::Cell()
{
	cell.setSize(sf::Vector2f(5, 5));
	cell.setFillColor(sf::Color::Blue);
    fishAge=0;
	// sharkAge=0;
}