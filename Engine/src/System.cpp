#include "PCH.h"
#include "System.h"
#include "Components.h"
#include "Coordinator.h"

void MovementSystem::Update(const float& dt)
{
	for (auto const& entity : m_entities)
	{
		auto& transform = Coordinator::GetComponent<Transform>(entity);
		const auto& tag = Coordinator::GetComponent<Tag>(entity);

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
			transform.velo = { 0, 0 };
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
		const auto& transform = Coordinator::GetComponent<Transform>(entity);
		const auto& tag = Coordinator::GetComponent<Tag>(entity);
		const auto& color = Coordinator::GetComponent<Color>(entity);

		switch (tag.tag)
		{
		case Tags::PLAYER:
		{

			SFMLTon::GetView().setCenter({transform.pos.x + transform.scale.x, transform.pos.y + transform.scale.y});
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
	//for (Entity entity = 0; entity < m_entities.size(); entity++)
	//{
	//	const Tag& tag1 = Coordinator::GetComponent<Tag>(entity);
	//	Collider& coll1 = Coordinator::GetComponent<Collider>(entity);

	//	// Don't check this entity if it is GOOD or already collided.
	//	if (((tag1.tag == Tags::GOOD) | (coll1.hasCollided == 1)) == 1)
	//		continue;

	//	const Transform& transf1 = Coordinator::GetComponent<Transform>(entity);
	//	firstShape.setScale(transf1.scale);
	//	firstShape.setPosition(transf1.pos);

	//	for (Entity other = 0; other < m_entities.size(); other++)
	//	{
	//		// Self check
	//		if (entity == other)
	//			continue;

	//		Collider& coll2 = Coordinator::GetComponent<Collider>(other);
	//		// Already collided with something? Skip.
	//		if (coll2.hasCollided)
	//			continue;

	//		const Transform& transf2 = Coordinator::GetComponent<Transform>(other);

	//		secondShape.setScale(transf2.scale);
	//		secondShape.setPosition(transf2.pos);

	//		// Collision Check
	//		if (firstShape.getGlobalBounds().intersects(secondShape.getGlobalBounds()))
	//		{
	//			coll1.hasCollided = 1;
	//			coll2.hasCollided = 1;
	//			m_collisions.push_back({ entity, other });
	//		}
	//	}
	//}


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
	//while (m_collisions.size() > 0)
	//{
	//	const CollInfo& info = m_collisions[(int)m_collisions.size() - 1];

	//	const Tag& tag1 = Coordinator::GetComponent<Tag>(info.first);
	//	const Tag& tag2 = Coordinator::GetComponent<Tag>(info.second);

	//	Value& val1 = Coordinator::GetComponent<Value>(info.first);
	//	Value& val2 = Coordinator::GetComponent<Value>(info.second);

	//	// One of them is either Player or Bad
	//	if (tag1.tag > tag2.tag)
	//	{
	//		val1.worth += val2.worth;
	//		val2.worth = 1;

	//		Coordinator::GetComponent<Transform>(info.first).scale += {(float)val1.worth, (float)val1.worth};
	//		Coordinator::DestroyEntity(info.second);
	//	}
	//	// One of them is either Player or Good
	//	else if (tag1.tag < tag2.tag)
	//	{
	//		val2.worth += val1.worth;
	//		val1.worth = 1;

	//		Coordinator::GetComponent<Transform>(info.second).scale += { (float)val2.worth, (float)val2.worth };
	//		Coordinator::DestroyEntity(info.first);
	//	}

	//	Collider& coll1 = Coordinator::GetComponent<Collider>(info.first);
	//	Collider& coll2 = Coordinator::GetComponent<Collider>(info.first);
	//	coll1.hasCollided = 0;
	//	coll2.hasCollided = 0;

	//	m_collisions.pop_back();
	//}


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
