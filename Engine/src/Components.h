#pragma once
#include "PCH.h"

namespace comp
{
	struct Transform
	{
		vec2 position	= {0.f, 0.f};
		vec2 velocity   = {0.f, 0.f};
		
		Transform() = default;
		Transform(const vec2& pos, const vec2& velo = {0.f, 0.f})
			: position(pos), velocity(velo) {}
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
		CircleShape(const float& radius, const sf::Color& color, const vec2& pos)
		{
			shape.setRadius(radius);
			shape.setFillColor(color);
			shape.setOrigin(shape.getLocalBounds().width / 2.f, shape.getLocalBounds().height / 2.f);
			shape.setPosition(pos);
		}
	};
}
