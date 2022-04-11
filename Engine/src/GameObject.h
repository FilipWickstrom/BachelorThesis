#pragma once

class GameObject
{
private:
	// Bounding sphere around the figure
	float m_collisionRad;

protected:
	ETagType m_tag;
	std::unique_ptr<sf::Shape> m_shape;

public:
	GameObject();
	GameObject(const ETagType& type);
	~GameObject() = default;

	// Setters:
	void SetPosition(const vec2& pos);

	// Getters:
	const vec2& GetPosition() const;
	const float& GetCollionRad() const;


	// Collision
	bool IsColliding(const GameObject& obj) const;


	virtual void Update(const float& dt) = 0;
	virtual void Render() = 0;
};