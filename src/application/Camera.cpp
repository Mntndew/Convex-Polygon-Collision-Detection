#include "application/Camera.hpp"


Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::update(const float deltaTime)
{
	if (auto actor = m_actor.lock())
	{
		m_velocity = (actor->getPosition() - m_position)*(math::distance<float>(m_position, actor->getPosition())/200);
		m_velocity.y /= 2;
		/*if (math::magnitude<float>(m_velocity) > 5)
		{
			math::normalize(m_velocity);
			m_velocity = {m_velocity.x*5, m_velocity.y*5};
		}*/

		m_position += m_velocity;
	}
}

void Camera::trackActor(const std::weak_ptr<Actor> actor)
{
	m_actor = actor;
}

sf::Vector2f Camera::getPosition() const
{
	return m_position;
}

void Camera::setPosition(const sf::Vector2f& position)
{
	m_position = position;
}

sf::Vector2f Camera::getVelocity() const
{
	return m_velocity;
}

void Camera::setVelocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}

