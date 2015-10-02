#pragma once

#include "actor/Actor.hpp"


class NPCActor : public Actor
{
public:
	NPCActor();
	~NPCActor();

	void control(const float deltaTime);
	bool isPlayer() const;
};

