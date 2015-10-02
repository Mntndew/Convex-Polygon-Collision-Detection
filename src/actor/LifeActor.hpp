#pragma once

#include <memory>

#include "actor/Actor.hpp"
#include "actor/PlayerActor.hpp"


class LifeActor : public Actor
{
public:
	LifeActor();
	~LifeActor();

	void control(const float deltaTime);
	bool isPlayer() const;

private:
	float m_counter;
};

