#include <SFML/Graphics.hpp>

class Cell
{
public:
	sf::RectangleShape cell;
	Cell();
    int fishBreedTime;
    int sharkBreedTime;
    int sharkStarveTime;
};