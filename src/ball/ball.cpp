#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

ball::ball()
{
    float radius = 16.0f;
    ball_shape = sf::CircleShape();
    ball_shape.setRadius(radius);
    ball_shape.setOrigin(radius, radius);
    ball_shape.setFillColor(sf::Color(255, 0, 0));
    velocity_vector.x = 250.0f;
    velocity_vector.y = 250.0f;
    ball_shape.setPosition(sf::Vector2f(385.0f, 500.0f));
}

ball::~ball() {}

void ball::set_position(sf::Vector2f new_position)
{
    ball_shape.setPosition(new_position);
}

sf::Vector2f ball::get_position() const
{
    return ball_shape.getPosition();
}

sf::CircleShape ball::get_ball() const
{
    return this->ball_shape;
}

void ball::set_velocity_vector(sf::Vector2f vector)
{
    velocity_vector = vector;
}

sf::Vector2f ball::get_velocity_vector() const
{
    return velocity_vector;
}

sf::Time ball::count_delta_time(sf::Clock &clock)
{
    sf::Time current_time = clock.getElapsedTime();
    sf::Time delta = current_time - previus_time;
    previus_time = current_time;
    return delta;
}

void ball::draw(sf::RenderWindow &window)
{
    window.draw(ball_shape);
}

void ball::reset()
{
    velocity_vector.x = 250.0f;
    velocity_vector.y = 250.0f;
    ball_shape.setPosition(sf::Vector2f(385.0f, 500.0f));;
    previus_time = sf::seconds(0.0f);
}
