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

// ############# Tweakable values: Start #############
//#define OOD
#define DOD
//#define MULTITHREADING	1		//On or off
//#define NR_OF_THREADS	16			//Comment out for max threads
#define NR_OF_ENTITIES	100000
#define DRAW_GAME		0

// Benchmarking
#define BENCH_DT
#define CAPTURED_FRAMES_DT 100000
// ############# Tweakable values: End #############


/*
	Adjustable values
*/

// Constants
constexpr uint	WIN_WIDTH		= 1920;
constexpr uint	WIN_HEIGHT		= 1080;

// Game specific
constexpr uint	NR_OF_ENEMIES	= NR_OF_ENTITIES / 2;
constexpr uint	NR_OF_FOOD		= NR_OF_ENTITIES / 2;
constexpr float SPAWNDENSITY	= 10.f;	//1 = everything fits within the window, 
										//3 = 3 times the window size
constexpr uint  GOALPOINTS		= 50;
constexpr float PLAYERSPEED		= 250.f;
