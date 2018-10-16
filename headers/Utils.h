#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "cmath"
#include "Settings.h"

sf::Vector2f normalizedVec(sf::Vector2f vec);

sf::Vector2f clampVec(sf::Vector2f vec, sf::Vector2f lower, sf::Vector2f upper);

float getAngle(sf::Vector2f pos1, sf::Vector2f pos2);

sf::Vector2f rotateNormalVect(sf::Vector2f vector, float degrees);

void printVec(sf::Vector2f vec);

std::vector<std::string> strSplit(std::string, char c);

float getDistance(sf::Vector2f vec1, sf::Vector2f vec2);
