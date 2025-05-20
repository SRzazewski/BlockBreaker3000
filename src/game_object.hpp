#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

class game_object
{
public:
    virtual ~game_object() = default;
    virtual void set_position(sf::Vector2f position) = 0;
    virtual sf::Vector2f get_position() const = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

class moving_object : public game_object
{
public:
    virtual ~moving_object() = default;
    virtual void set_velocity_vector(sf::Vector2f vector) = 0;
    virtual sf::Vector2f get_velocity_vector() const = 0;
};

class rectangle_object : public game_object
{
public:
    virtual ~rectangle_object() = default;
    virtual sf::Vector2f get_size() const = 0;
};

#endif