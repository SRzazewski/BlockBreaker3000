#ifndef STATES
#define STATES

enum class states_name
{
    game_init = 0,
    game_init_level,
    game_playing,
    game_won,
    game_lost
};

class states
{
public:

private:
    states_name game_state = states_name::game_init;
    states_name game_state_requested = states_name::game_init_level;

};

#endif