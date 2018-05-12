#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cmath"
#include "Settings.h"

sf::Vector2f normalizedVec(sf::Vector2f vec);

sf::Vector2f clampVec(sf::Vector2f vec, sf::Vector2f lower, sf::Vector2f upper);