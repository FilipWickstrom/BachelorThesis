#include "PCH.h"
#include "System.h"
#include "Components.h"
#include "Coordinator.h"

void MovementSystem::Update(const float& dt)
{
	for (auto const& entity : m_entities)
	{
		auto& transform = Coordinator::GetComponent<Transform>(entity);
		auto& tag = Coordinator::GetComponent<Tag>(entity);

		switch (tag.tag)
		{
		case Tags::PLAYER:
		{
			transform.velo = { 0.0f, 0.0f };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				transform.velo.x = 500.0f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				transform.velo.x = -500.0f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				transform.velo.y = -500.0f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				transform.velo.y = 500.0f;

			break;
		}
		case Tags::GOOD:
		{

			break;
		}
		default:
			break;
		}

		transform.pos.x += transform.velo.x * dt;
		transform.pos.y += transform.velo.y * dt;
	}
}

static sf::CircleShape circle(1.0f);
static sf::RectangleShape rectangle({1.0f, 1.0f});

void RenderSystem::Draw()
{
	for (auto const& entity : m_entities)
	{
		auto& transform = Coordinator::GetComponent<Transform>(entity);
		auto& tag = Coordinator::GetComponent<Tag>(entity);
		auto& color = Coordinator::GetComponent<Color>(entity);

		switch (tag.tag)
		{
		case Tags::PLAYER:
		{
			SFMLTon::GetView().setCenter(transform.pos);
			SFMLTon::GetWindow().setView(SFMLTon::GetView());
			break;
		}
		case Tags::BAD:
		{
			break;
		}
		case Tags::GOOD:
		{
			break;
		}
		default:
			break;
		}

		circle.setScale(transform.scale);
		circle.setPosition(transform.pos);
		circle.setFillColor(color.color);
		SFMLTon::GetWindow().draw(circle);

	}
}

static sf::FloatRect first;
static sf::FloatRect second;

void CollisionSystem::Detect()
{
	for (auto const& entity : m_entities)
	{

	}
}

void CollisionSystem::Act()
{
	for (auto const& entity : m_collisions)
	{

	}
}
