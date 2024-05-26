#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{ { 800u, 600u }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    sf::Text text;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        window.close();
    }

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("Hello world in BlockBreaker3000");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        

        window.clear();
        // inside the main loop, between window.clear() and window.display()
        window.draw(text);
        window.display();
    }
}