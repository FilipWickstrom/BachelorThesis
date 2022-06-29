#pragma once

#ifdef OOD

enum class Tags : uint
{
	DEFAULT,
	GOOD,
	BAD,
	PLAYER
};


class GameObject
{
protected:

	vec2 m_position;
	vec2 m_scale;
	Tags m_tag;

public:

	GameObject();
	//virtual ~GameObject() = 0;

	void SetTag(const Tags& tag);
	const vec2& GetPosition() const;
	const vec2& GetScale() const;

	// Get the type of object this is.
	const Tags& GetTag() const;
};

class RenderObject : public sf::Drawable, public GameObject
{
private:

	sf::CircleShape m_shape;

public:

	RenderObject() = default;
	~RenderObject() = default;

	void SetShape(sf::CircleShape& shape);
	void SetPosition(const vec2& pos);

	// Move the object.
	virtual void Move(const float& dt) = 0;


	void SetScale(const vec2& scale);
	const sf::FloatRect GetBounds() const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Check for collision with other object.
	const bool IsColliding(RenderObject& other);
};

#endif