#include "actor/NPCActor.hpp"

#include <iostream>


NPCActor::NPCActor()
{
	setType(ActorType::Rabbit);
}

NPCActor::~NPCActor()
{
}

void NPCActor::control(const float deltaTime)
{
	m_velocity.y += 9.82*3;

	if (isColliding())
	{
		if (m_velocity.x > -250)
		{
			m_velocity.x -= 50;

			if (m_velocity.x < -250)
				m_velocity.x = -250;
		}
	}

	if (math::magnitude<float>(m_velocity) > 900)
	{
		math::normalize(m_velocity);
		m_velocity = {m_velocity.x*900, m_velocity.y*900};
	}
}

bool NPCActor::isPlayer() const
{
	return false;
}

