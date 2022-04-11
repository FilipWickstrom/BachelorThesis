#pragma once

// Standard
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <exception>
#include <set>
#include <bitset>
#include <time.h>
// Add more if needed


// Multithreading
#include <omp.h>


// SFML
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/GpuPreference.hpp>


// type defs
typedef unsigned int uint;
typedef sf::Vector2f vec2;

// Singletons if needed
#include "SFMLTon.h"
#define WINDOW SFMLTon::GetWindow()

// Other necessary stuff that is needed everywhere
#include "Structures.h"

// Constants
constexpr uint WIN_WIDTH		= 1920;
constexpr uint WIN_HEIGHT		= 1080;
constexpr uint NR_OF_ENEMIES	= 100;
constexpr uint NR_OF_FOOD		= 100;