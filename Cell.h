/**
 *Authors:  Mark Kelly, Ronan Timmons
 *Date:     27 December 2017
 *License:  GNU General Public License v3.0
 *Brief:    4th Year Wator simulation Project
**/

#include <SFML/Graphics.hpp>

class Cell
{
public:
	sf::RectangleShape cell;
	Cell();
    int fishAge;
    int sharkAge;
    int sharkStarveTime;
    int cellType;
    bool hasMoved;
};