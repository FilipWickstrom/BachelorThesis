#pragma once

class GameObject
{
protected:
	ETagType		m_tag;
	sf::CircleShape	m_shape;
	float			m_collisionRadius;

public:
	GameObject();
	GameObject(const ETagType& type);
	~GameObject() = default;

	// Setters:
	void SetPosition(const vec2& pos);
	void SetTag(const ETagType& tag);
	void SetCollisionRadius(const float& rad);

	// Getters:
	const vec2& GetPosition() const;
	const ETagType& GetTag() const;
	const float& GetCollisionRadius() const;

	bool IsColliding(const GameObject& obj) const;
	virtual void Update(const float& dt) = 0;
	virtual void Render() = 0;
};