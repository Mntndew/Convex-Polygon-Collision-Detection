#pragma once

#include "actor/Actor.hpp"


class PlayerActor : public Actor
{
public:
	PlayerActor();
	~PlayerActor();

	void control(const float deltaTime);
	bool isPlayer() const;
};

