#pragma once

class GameObject
{
protected:
	ETagType					m_tag;
	std::unique_ptr<sf::Shape>	m_shape;

public:
	GameObject();
	GameObject(const ETagType& type);
	~GameObject() = default;

	// Setters:
	void SetPosition(const vec2& pos);
	void SetTag(const ETagType& tag);

	// Getters:
	const vec2& GetPosition() const;
	const ETagType& GetTag() const;


	bool IsColliding(const GameObject& obj) const;
	virtual void Update(const float& dt) = 0;
	virtual void Render() = 0;
};