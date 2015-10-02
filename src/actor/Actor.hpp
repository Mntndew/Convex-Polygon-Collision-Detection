#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "actor/ActorIdTracker.hpp"
#include "application/Math.hpp"


enum class ActorType
{
	Carrot,
	CarrotLife,
	Rabbit,
};

class Actor : public sf::Drawable
{
public:
	Actor();
	~Actor();

	virtual void control(const float deltaTime) = 0;
	virtual void update(const float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);

	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f& velocity);

	math::Polygon getPolygon() const;
	void setPolygon(const math::Polygon& polygon);

	math::Polygon getBottom() const;
	void setBottom(const math::Polygon& bottom);

	void move(const sf::Vector2f& offset);
	void move(const float x, const float y);

	void updateShape();

	bool isGrounded() const;
	void setGrounded(const bool grounded);

	bool isColliding() const;
	void setColliding(const bool colliding);

	ActorId getId() const;
	void setId(const ActorId& id);

	virtual bool isPlayer() const = 0;

	ActorType getType() const;
	void setType(const ActorType& type);

	std::vector<sf::Vector2f> getJumpPoints() const;
	void clearJumpPoints();
	void addJumpPoints(const std::vector<sf::Vector2f> jumpPoints);

protected:
	sf::Vector2f m_position, m_velocity;
	math::Polygon m_polygon, m_bottom;
	sf::ConvexShape	m_shape;

	bool m_grounded, m_colliding;
	ActorId m_id;

	ActorType m_type;

	std::vector<sf::Vector2f> m_jumpPoints;
};

