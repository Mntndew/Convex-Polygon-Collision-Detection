#include "actor/Actor.hpp"


Actor::Actor()
{
	m_id.id = -1;
}

Actor::~Actor()
{
}

void Actor::update(const float deltaTime)
{
	m_position += m_velocity*deltaTime;
	m_polygon.offset(m_velocity.x*deltaTime, m_velocity.y*deltaTime);
	m_bottom.offset(m_velocity.x*deltaTime, m_velocity.y*deltaTime);
	m_shape.move(m_velocity*deltaTime);
}

void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
}

sf::Vector2f Actor::getPosition() const
{
	return m_position;
}

void Actor::setPosition(const sf::Vector2f& position)
{
	m_position = position;
	m_polygon.offset(position.x - m_position.x, position.y - m_position.y);
	m_bottom.offset(position.x - m_position.x, position.y - m_position.y);
	m_shape.move(position.x - m_position.x, position.y - m_position.y);
}

sf::Vector2f Actor::getVelocity() const
{
	return m_velocity;
}

void Actor::setVelocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}

math::Polygon Actor::getPolygon() const
{
	return m_polygon;
}

void Actor::setPolygon(const math::Polygon& polygon)
{
	m_polygon = polygon;
}

math::Polygon Actor::getBottom() const
{
	return m_bottom;
}

void Actor::setBottom(const math::Polygon& bottom)
{
	m_bottom = bottom;
}

void Actor::move(const sf::Vector2f& offset)
{
	m_position += offset;
	m_polygon.offset(offset.x, offset.y);
	m_bottom.offset(offset.x, offset.y);
	m_shape.move(offset);
}

void Actor::move(const float x, const float y)
{
	m_position += {x, y};
	m_polygon.offset(x, y);
	m_bottom.offset(x, y);
	m_shape.move(x, y);
}

void Actor::updateShape()
{
	m_shape.setPointCount(m_polygon.getPointCount());
	
	for (int i = 0; i < m_polygon.getPointCount(); ++i)
		m_shape.setPoint(i, m_polygon.getPoint(i));

	switch (m_type)
	{
		case ActorType::Carrot:
			m_shape.setFillColor({0, 0, 255, 100});
		break;

		case ActorType::CarrotLife:
			m_shape.setFillColor({255, 0, 255, 100});
		break;

		case ActorType::Rabbit:
			m_shape.setFillColor({255, 0, 0, 100});
		break;
	}
}

bool Actor::isGrounded() const
{
	return m_grounded;
}

void Actor::setGrounded(const bool grounded)
{
	m_grounded = grounded;
}

bool Actor::isColliding() const
{
	return m_colliding;
}

void Actor::setColliding(const bool colliding)
{
	m_colliding = colliding;
}

ActorId Actor::getId() const
{
	return m_id;
}

void Actor::setId(const ActorId& id)
{
	m_id = id;
}

ActorType Actor::getType() const
{
	return m_type;
}

void Actor::setType(const ActorType& type)
{
	m_type = type;
}

