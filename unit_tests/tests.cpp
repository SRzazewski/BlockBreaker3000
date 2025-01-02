#include "src/game.hpp"
#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>
#include <numbers>

TEST(BlockBreaker3000_tests, BlockBreaker3000_tests_example)
{
    EXPECT_EQ(1, 1);
    EXPECT_NE(0, 1);
}

TEST(BlockBreaker3000_tests, BlockBreaker3000_tests_rotate_vector_45_degrees)
{
    sf::Vector2f vector = sf::Vector2f(5.0f, 0.0f);
    float angle = std::numbers::pi_v<float>/2;

    vector = game::rotate_vector(vector, angle);

    EXPECT_NEAR(vector.x, -5.0f, 0.01f);
    EXPECT_NEAR(vector.y, 0.0f, 0.01f);
}

TEST(BlockBreaker3000_tests, BlockBreaker3000_tests_rotate_vector_90_degrees)
{
    sf::Vector2f vector = sf::Vector2f(5.0f, 0.0f);
    float angle = std::numbers::pi_v<float>/4;

    vector = game::rotate_vector(vector, angle);

    EXPECT_NEAR(vector.x, 0.0f, 0.01f);
    EXPECT_NEAR(vector.y, 5.0f, 0.01f);
}

TEST(BlockBreaker3000_tests, BlockBreaker3000_tests_rotate_vector_180_degrees)
{
    sf::Vector2f vector = sf::Vector2f(5.0f, 0.0f);
    float angle = std::numbers::pi_v<float>;

    vector = game::rotate_vector(vector, angle);

    EXPECT_NEAR(vector.x, 5.0f, 0.01f);
    EXPECT_NEAR(vector.y, 0.0f, 0.01f);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}