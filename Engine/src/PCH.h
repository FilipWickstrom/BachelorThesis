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
#include <cassert>
#include <functional>
#include <cmath>
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


// Singleton
#include "SFMLTon.h"


// ############# Tweakable values: Start #############
//#define OOD
#define DOD
#define MULTITHREADING	0			//On or off
//#define NR_OF_THREADS	16			//Comment out for max threads
#define NR_OF_ENTITIES	5000
#define DRAW_GAME		0

// Benchmarking
#define BENCH_DT
#define CAPTURED_FRAMES_DT 100000
// ############# Tweakable values: End #############



// type defs
typedef unsigned int uint;
typedef sf::Vector2f vec2;

// ECS
using Entity = std::uint32_t;

const Entity MAX_ENTITIES = NR_OF_ENTITIES;

template<typename T>
using CompArray = std::array<T, MAX_ENTITIES>;

const uint MAX_OBJECTS = NR_OF_ENTITIES;

const uint WINDOW_WIDTH = 150;
const uint WINDOW_HEIGHT = 150;
