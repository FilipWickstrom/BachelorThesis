#pragma once

struct Transform
{
	vec2 position = {rand() % 10000 - 5000, rand() % 10000 - 5000 };
	vec2 velocity = {rand() % 32 - 16, rand() % 32 - 16 };
	vec2 scale = { 1.0f, 1.0f };

	Transform() = default;
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
	uint8_t shouldRender = 1;
	sf::CircleShape shape;
	Renderable()
	{
		shape.setRadius(12.5f);
		shape.setFillColor(sf::Color::White);
	}
	Renderable(const sf::Color& color)
	{
		shape.setRadius(12.5f);
		shape.setFillColor(color);
	}
};