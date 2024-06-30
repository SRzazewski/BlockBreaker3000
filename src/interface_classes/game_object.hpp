#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

class game_object
{
public:
    game_object(sf::RenderWindow *const app_window = nullptr):
        window(app_window){}
    virtual void set_position(sf::Vector2f position) = 0;
    virtual sf::Vector2f get_position() const = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

protected:
    sf::RenderWindow *const window;
};

class moving_object : public game_object
{
public:
    moving_object(sf::RenderWindow *const app_window = nullptr, sf::Clock *const app_clock = nullptr):
        window(app_window),
        clock(app_clock) {}
    virtual void set_velocity_vector(sf::Vector2f vector) = 0;
    virtual sf::Vector2f get_velocity_vector() const = 0;
    
protected:
    sf::RenderWindow *const window;
    sf::Clock *const clock;
    sf::Vector2f velocity_vector;
};

#endif