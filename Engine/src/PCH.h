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


// EnTT
#ifdef __unix__  
#include "../../ThirdParty/EnTT/include/entt.hpp"
#elif _WIN32
#include <entt.hpp>
#endif

// type defs
typedef unsigned int uint;
typedef sf::Vector2f vec2;

// Singletons
#include "SFMLTon.h"
#define WINDOW SFMLTon::GetWindow()

// Other necessary stuff that is needed everywhere
#include "Structures.h"

// Constants
constexpr uint	WIN_WIDTH		= 1920;
constexpr uint	WIN_HEIGHT		= 1080;

// Game specific
constexpr uint	NR_OF_ENEMIES	= 1000;
constexpr uint	NR_OF_FOOD		= 1000;
constexpr float SPAWNDENSITY	= 4.f;	//1 = everything fits within the window, 
										//3 = 3 times the window size
constexpr uint  GOALPOINTS		= 50;
constexpr float PLAYERSPEED		= 250.f;