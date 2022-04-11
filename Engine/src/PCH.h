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


// Singletons if needed
#include "SFMLTon.h"


// type defs
typedef unsigned int uint;
typedef sf::Vector2f vec2;


// ECS
using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 5;
using Signature = std::bitset<MAX_COMPONENTS>;
const Entity MAX_ENTITIES = 1000;

const uint WINDOW_WIDTH = 1920;
const uint WINDOW_HEIGHT = 1080;


