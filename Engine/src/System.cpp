#include "PCH.h"
#include "System.h"
#include "Components.h"
#include "Coordinator.h"

void MovementSystem::Update(const float& dt, Coordinator& coord)
{
	for (auto const& entity : m_entities)
	{
		
		auto& rigidbody = coord.GetComponent<RigidBody>(entity);
		const auto& tag = coord.GetComponent<Tag>(entity);

		switch (tag.tag)
		{
		case Tags::PLAYER:
		{
			rigidbody.velo = { 0.0f, 0.0f };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				rigidbody.velo.x = 500.0f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				rigidbody.velo.x = -500.0f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				rigidbody.velo.y = -500.0f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				rigidbody.velo.y = 500.0f;

			break;
		}
		default:
			break;
		}

		auto& transform = coord.GetComponent<Transform>(entity);
		transform.pos.x += rigidbody.velo.x * dt;
		transform.pos.y += rigidbody.velo.y * dt;
	}
}

sf::CircleShape circle(1.0f);
sf::RectangleShape rectangle({1.0f, 1.0f});

void RenderSystem::Draw(Coordinator& coord)
{
	for (auto const& entity : m_entities)
	{
		const auto& transform = coord.GetComponent<Transform>(entity);
		circle.setScale(transform.scale);
		circle.setPosition(transform.pos);

		const auto& tag = coord.GetComponent<Tag>(entity);
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

		const auto& color = coord.GetComponent<Color>(entity);
		circle.setFillColor(color.color);
		SFMLTon::GetWindow().draw(circle);

	}
}

sf::CircleShape firstShape(1.0f);
sf::CircleShape secondShape(1.0f);

CollisionSystem::CollisionSystem()
{
	m_collisions.resize(MAX_ENTITIES);
}

void CollisionSystem::Detect(Entity playerEntity, Coordinator& coord)
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


	const auto& playerTransf = coord.GetComponent<Transform>(playerEntity);
	firstShape.setScale(playerTransf.scale);
	firstShape.setPosition(playerTransf.pos);

	for (auto const& entity : m_entities)
	{
		const auto& otherTransf = coord.GetComponent<Transform>(entity);

		if (playerEntity != entity)
		{
			secondShape.setScale(otherTransf.scale);
			secondShape.setPosition(otherTransf.pos);

			if (firstShape.getGlobalBounds().intersects(secondShape.getGlobalBounds()))
				m_collisions.push_back({ playerEntity, entity });
		}
	}
}

void CollisionSystem::Act(Coordinator& coord)
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

		auto& playerTransf = coord.GetComponent<Transform>(info.first);
		Value& playerValue = coord.GetComponent<Value>(info.first);
		Tag& tagOther = coord.GetComponent<Tag>(info.second);

		switch (tagOther.tag)
		{
		case Tags::GOOD:
		{
			playerValue.worth++;
			coord.DestroyEntity(info.second);
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

		//SFMLTon::GetWindow().setTitle("Points: " + std::to_string(playerValue.worth));

		playerTransf.scale.x = playerValue.worth;
		playerTransf.scale.y = playerValue.worth;

		m_collisions.pop_back();
	}
}
