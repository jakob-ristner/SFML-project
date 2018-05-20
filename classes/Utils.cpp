#include "../headers/Utils.h"

// A pure function that returns a normalized version of the input vector
// Args:
// vec - vector to be normalized
sf::Vector2f normalizedVec(sf::Vector2f vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    return sf::Vector2f(vec.x / length, vec.y / length);
}

// A pure function that returns a new vector where the x and y values are within
// the upper and lower bounds specified. Used for example in limiting viewport
// scrolling to the edge of the map
// Args:
// vec - vector to be clamped
// lower - vector specifying the lower bounds of the x and y coords
// upper - vector specifying the upper bounds of the x and y coords
sf::Vector2f clampVec(sf::Vector2f vec, sf::Vector2f lower, sf::Vector2f upper) {
    sf::Vector2f output;
    output.x = std::min(std::max(vec.x, lower.x), upper.x);
    output.y = std::min(std::max(vec.y, lower.y), upper.y);
    return output;
}

float getAngle(sf::Vector2f pos1, sf::Vector2f pos2) {
    sf::Vector2f diffPos = pos1 - pos2;
    sf::Vector2f normal = normalizedVec(diffPos);
    return atan2(normal.x, normal.y) * (180 / M_PI);
}

sf::Vector2f rotateNormalVect(sf::Vector2f vector, float radians) {
    float originalAngle = atan2(vector.x, vector.y);
    return sf::Vector2f(sin((originalAngle + radians)), cos(originalAngle + radians));
}
