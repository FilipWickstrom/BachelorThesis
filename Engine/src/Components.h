#pragma once
#include "PCH.h"

namespace comp
{
	struct Position
	{
		vec2 position	= {0.f, 0.f};
		
		Position() = default;
		Position(const vec2& pos)
			: position(pos) {}
	};

	struct Velocity
	{
		float speed		= { 0.f };
		vec2 direction	= {0.f, 0.f};

		Velocity(const float& speed, const vec2& dir = {0.f, 0.f})
			: speed(speed), direction(dir) {}
	};

	struct Score
	{
		int current	= 0;
		int max		= 100;

		Score() = default;
		Score(const int& cur, const int& max)
			: current(cur), max(max) {}
	};

	struct Tag
	{
		ETagType type = ETagType::none;
		
		Tag() = default;
		Tag(const ETagType& type)
			: type(type) {}
	};

	struct Worth
	{
		int points;

		Worth(const int& points)
			: points(points) {}
	};

	struct CircleShape
	{
		sf::CircleShape shape;

		CircleShape() = default;
		CircleShape(const float& radius, const sf::Color& color)
		{
			shape.setRadius(radius);
			shape.setFillColor(color);
			shape.setOrigin(shape.getLocalBounds().width / 2.f, shape.getLocalBounds().height / 2.f);
		}
	};
}
