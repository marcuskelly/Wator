/**
 *Authors:   Mark Kelly, Ronan Timmons
 *Date:     27 December 2017
 *License:  GNU General Public License v3.0
 *Brief:    4th Year Wator simulation Project
**/

#include <SFML/Graphics.hpp>
#include <string>

int main()
{
    std::vector<sf::VideoMode> i = sf::VideoMode::getFullscreenModes();
    sf::RenderWindow window(i.front(), "Wator simulator", sf::Style::Fullscreen);

    sf::RectangleShape shark;
    shark.setSize(sf::Vector2f(10, 10));
    shark.setFillColor(sf::Color::Red);
    shark.setPosition(10, 20);

    sf::RectangleShape fish;
    fish.setSize(sf::Vector2f(10, 10));
    fish.setFillColor(sf::Color::Green);
    fish.setPosition(20, 40);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shark);
        window.draw(fish);
        window.display();
    }

    return 0;
}
