#include <SFML/Graphics.hpp>

class Cell
{
public:
	sf::RectangleShape cell;
	Cell();
    int fishAge;
    int sharkAge;
    int sharkStarveTime;
};