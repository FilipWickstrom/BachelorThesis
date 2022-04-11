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

static sf::CircleShape firstShape(1.0f);
static sf::CircleShape secondShape(1.0f);

CollisionSystem::CollisionSystem()
{
	m_collisions.resize(MAX_ENTITIES);
}

void CollisionSystem::Detect(const Entity& playerEntity)
{
	auto& playerTransf = Coordinator::GetComponent<Transform>(playerEntity);
	firstShape.setScale(playerTransf.scale);
	firstShape.setPosition(playerTransf.pos);

	for (auto const& entity : m_entities)
	{
		auto& otherTransf = Coordinator::GetComponent<Transform>(entity);

		if (playerEntity != entity)
		{
			secondShape.setScale(otherTransf.scale);
			secondShape.setPosition(otherTransf.pos);

			if (firstShape.getGlobalBounds().intersects(secondShape.getGlobalBounds()))
				m_collisions.push_back({ playerEntity, entity });
		}
	}
}

void CollisionSystem::Act()
{
	while (m_collisions.size() > 0)
	{
		const CollInfo& info = m_collisions[(int)m_collisions.size() - 1];

		auto& playerTransf = Coordinator::GetComponent<Transform>(info.first);
		Value& playerValue = Coordinator::GetComponent<Value>(info.first);
		Tag& tagOther = Coordinator::GetComponent<Tag>(info.second);

		switch (tagOther.tag)
		{
		case Tags::GOOD:
		{
			playerValue.worth++;
			Coordinator::DestroyEntity(info.second);
			break;
		}
		case Tags::BAD:
		{
			playerValue.worth = 1;
			break;
		}
		default:
			break;
		}

		playerTransf.scale.x = playerValue.worth;
		playerTransf.scale.y = playerValue.worth;

		m_collisions.pop_back();
	}
}
