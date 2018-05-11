#include "../headers/Utils.h"

sf::Vector2f normalizedVec(sf::Vector2f vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    return sf::Vector2f(vec.x / length, vec.y / length);
}