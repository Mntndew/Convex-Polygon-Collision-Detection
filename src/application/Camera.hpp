#pragma once

#include <memory>

#include "actor/Actor.hpp"


class Camera
{
public:
	Camera();
	~Camera();

	void update(const float deltaTime);
	void trackActor(const std::weak_ptr<Actor> actor);

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);

	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f& velocity);

private:
	sf::Vector2f m_position, m_velocity;
	std::weak_ptr<Actor> m_actor;
};

