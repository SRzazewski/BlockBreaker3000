#include "ball.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>

ball::ball(game *game_inst, sf::Vector2f start_position)
{
    move_ptr = std::make_unique<Move_ball>();
    move_ptr->set_game_instance(game_inst);
    ball_shape.setOrigin({ball_radius, ball_radius});
    ball_shape.setFillColor(sf::Color(255, 0, 0));
    ball_shape.setPosition(start_position);
}

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

void ball::draw(sf::RenderWindow &window)
{
    window.draw(ball_shape);
}

void ball::move(sf::Time time_delta)
{
    move_ptr->move(time_delta, *this);
}
