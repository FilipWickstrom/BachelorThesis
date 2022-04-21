#pragma once

#ifdef DOD

struct Transform
{
	vec2 position = {static_cast<float>(rand() % 10000 - 5000), static_cast<float>(rand() % 10000 - 5000) };
	vec2 velocity = { static_cast<float>(rand() % 32 - 16), static_cast<float>(rand() % 32 - 16) };

	Transform() = default;
	Transform(float velo)
	{
		this->velocity = { velo, velo };
	}

	Transform(float x, float y)
	{
		this->position.x = x;
		this->position.y = y;

	}
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

struct Collider
{
	uint8_t canCollide = 1;
	sf::FloatRect collider;

	Collider()
	{
		collider.height = 0;
		collider.left = 0;
		collider.top = 0;
		collider.width = 0;
	}

	Collider(float radius)
	{
		collider.height = radius;
		collider.left = 0;
		collider.top = 0;
		collider.width = radius;
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


#endif