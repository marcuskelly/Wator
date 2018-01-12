/**
 *Authors:  Mark Kelly, Ronan Timmons
 *Date:     27 December 2017
 *License:  GNU General Public License v3.0
 *Brief:    4th Year Wator simulation Project
**/

#include "Cell.h"

Cell::Cell()
{
	cell.setSize(sf::Vector2f(5, 5));
	cell.setFillColor(sf::Color::Blue);
    fishAge = 0;
	sharkAge = 0;
	sharkStarveTime = 0;
	cellType = 0;
	hasMoved = false;
}