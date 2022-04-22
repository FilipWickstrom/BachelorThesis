#pragma once

#ifdef DOD

struct Transform
{
	vec2 position = { static_cast<float>(rand() % 10000 - 5000), static_cast<float>(rand() % 10000 - 5000) };
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
	float radius = 0.f;
	vec2 position = { 0.f, 0.f };

	Collider() = default;
	Collider(const float& rad)
	{
		radius = std::abs(rad);
	}
};

struct Value
{
	uint worth = 0;
};

struct Renderable
{
	uint8_t shouldRender = 1;
	sf::CircleShape shape;
	Renderable()
	{
		shape.setRadius(10.f);
		shape.setFillColor(sf::Color::White);
	}
	Renderable(const sf::Color& color, const float& radius)
	{
		shape.setRadius(radius);
		shape.setFillColor(color);
	}
};


#endif