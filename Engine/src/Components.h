#pragma once

struct Transform
{
	vec2 position = {rand() % 10000 - 5000, rand() % 10000 - 5000 };
	vec2 velocity = {rand() % 32 - 16, rand() % 32 - 16 };

	Transform() = default;
};

struct Color
{
	sf::Color color = sf::Color::White;
	Color() = default;
	Color(const sf::Color& color)
	{
		this->color = color;
	}


};

struct Moveable
{

};

enum class Tags : uint8_t
{
	DEFAULT,
	GOOD,
	PLAYER,
	BAD
};
struct Tag
{
	Tags tag = Tags::DEFAULT;
	Tag() = default;
	Tag(Tags tag)
	{
		this->tag = tag;
	}
};

struct Value
{
	uint worth = 1;
};

struct Renderable
{
	sf::CircleShape shape;
	Renderable() = default;
	Renderable(const sf::Color& color)
	{
		shape.setRadius(12.5f);
		shape.setFillColor(color);
	}
};