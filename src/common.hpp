#ifndef COMMON_HHP_
#define COMMON_HHP_

#include <SFML/System/Vector2.hpp>

struct game_area
{
    unsigned int x_start;
    unsigned int x_stop;
    unsigned int y_start;
    unsigned int y_stop;
};

const game_area block_breaker_area = {0, 800, 60, 600};

const sf::Vector2f paddle_size = sf::Vector2f(120.0f, 20.0f);
const float position_paddle_x_min = block_breaker_area.x_start
                                        + paddle_size.x/2.0f;
const float position_paddle_x_max = block_breaker_area.x_stop
                                        - paddle_size.x/2.0f;

#endif /* COMMON_HHP_ */