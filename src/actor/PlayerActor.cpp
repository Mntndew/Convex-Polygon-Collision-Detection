#include "actor/PlayerActor.hpp"


PlayerActor::PlayerActor() :
	Actor()
{
	setType(ActorType::Carrot);
}

PlayerActor::~PlayerActor()
{
}

void PlayerActor::control(const float deltaTime)
{
	m_velocity.y += 9.82*3;

	if (isColliding())
	{
		if (isGrounded() && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			m_velocity.y -= 400;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (m_velocity.x > -400)
				m_velocity.x -= 40;
			else
				m_velocity.x = -400;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (m_velocity.x < 400)
				m_velocity.x += 40;
			else
				m_velocity.x = 400;
		}
		else
		{
			if (m_velocity.x > 0)
			{
				m_velocity.x -= 50;

				if (m_velocity.x < 0)
					m_velocity.x = 0;
			}
			else if (m_velocity.x < 0)
			{
				m_velocity.x += 50;

				if (m_velocity.x > 0)
					m_velocity.x = 0;
			}
		}
	}

	if (math::magnitude<float>(m_velocity) > 900)
	{
		math::normalize(m_velocity);
		m_velocity = {m_velocity.x*900, m_velocity.y*900};
	}
}

bool PlayerActor::isPlayer() const
{
	return true;
}

