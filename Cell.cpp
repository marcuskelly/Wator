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
	age = 0;
	starveAge = 0;
	cellType = 0; // zero represents an ocean cell
	madeMove = false;
}