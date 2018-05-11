#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Settings {
public:
    Settings();
    ~Settings();
    const static int WINDOW_WIDTH = 1200;
    const static int WINDOW_HEIGHT = 800;
    const static int TIMESCALE = 10;
};