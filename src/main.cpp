#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080),
    "Bouncing Logosle!");
    sf::Texture texture;
    texture.loadFromFile("../src/textures/Logosle.png");
    sf::Sprite Logosle(texture);
    sf::Vector2u size = texture.getSize();
    Logosle.setOrigin(size.x / 2, size.y / 2);
    sf::Vector2f increment(0.4f, 0.4f);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
            // Close window button clicked.
            window.close();
            }
        }
        if((Logosle.getPosition().x + (size.x / 2) >
        window.getSize().x && increment.x > 0) ||
        (Logosle.getPosition().x - (size.x / 2) < 0 &&
        increment.x < 0))
        {
        // Reverse the direction on X axis.
        increment.x = -increment.x;
        }
        if((Logosle.getPosition().y + (size.y / 2) >
        window.getSize().y && increment.y > 0) ||
        (Logosle.getPosition().y - (size.y / 2) < 0 &&
        increment.y < 0))
        {
        // Reverse the direction on Y axis.
        increment.y = -increment.y;
        }
        Logosle.setPosition(Logosle.getPosition() + increment);
        window.clear(sf::Color(16,16,16,255)); // Dark gray.
        window.draw(Logosle); // Drawing our sprite.
        window.display();
    }
}